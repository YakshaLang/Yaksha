// parser.cpp
#include "ast/parser.h"
#include <algorithm>
#include <cassert>
#include <utility>
using namespace yaksha;
parser::parser(std::string filepath, std::vector<token> &tokens,
               ykdt_pool *pool)
    : pool_{}, tokens_{tokens}, current_{0}, control_flow_{0}, dt_pool_(pool),
      import_stmts_(), filepath_(std::move(filepath)) {
  // Create a fake return token to be injected at end of void functions.
  // WHY?: This ensures that defer + string freeing work
  magic_return_token_ = new token{};
  magic_return_token_->token_ = "return";
  magic_return_token_->file_ = "syntax-sugar";
  magic_return_token_->original_ = "return";
  magic_return_token_->line_ = 0;
  magic_return_token_->pos_ = 0;
  magic_return_token_->type_ = token_type::KEYWORD_RETURN;
}
parser::~parser() { delete (magic_return_token_); }
token *parser::advance() {
  if (!is_at_end()) { current_++; }
  return previous();
}
token *parser::recede() {
  if (current_ != 0) { current_--; }
  return peek();
}
bool parser::is_at_end() { return peek()->type_ == token_type::END_OF_FILE; }
token *parser::peek() { return &tokens_[current_]; }
token *parser::previous() {
  assert(current_ > 0);
  return &tokens_[current_ - 1];
}
bool parser::match(std::initializer_list<token_type> types) {
  return std::any_of(types.begin(), types.end(), [this](token_type t) {
    if (this->check(t)) {
      this->advance();
      return true;
    }
    return false;
  });
}
bool parser::check(token_type t) {
  if (is_at_end()) { return false; }
  return peek()->type_ == t;
}
expr *parser::equality() {
  expr *ex = comparison();
  while (match({token_type::NOT_EQ, token_type::EQ_EQ})) {
    auto opr = previous();
    expr *right = comparison();
    ex = pool_.c_binary_expr(ex, opr, right);
  }
  return ex;
}
expr *parser::comparison() {
  expr *ex = term();
  while (match({token_type::GREAT, token_type::GREAT_EQ, token_type::LESS,
                token_type::LESS_EQ})) {
    auto opr = previous();
    expr *right = term();
    ex = pool_.c_binary_expr(ex, opr, right);
  }
  return ex;
}
expr *parser::term() {
  expr *ex = factor();
  while (match({token_type::SUB, token_type::PLUS})) {
    auto opr = previous();
    expr *right = factor();
    ex = pool_.c_binary_expr(ex, opr, right);
  }
  return ex;
}
expr *parser::factor() {
  expr *ex = unary();
  while (match({token_type::DIV, token_type::MUL, token_type::INT_DIV})) {
    auto opr = previous();
    expr *right = unary();
    ex = pool_.c_binary_expr(ex, opr, right);
  }
  return ex;
}
expr *parser::unary() {
  if (match({token_type::SUB, token_type::KEYWORD_NOT})) {
    auto opr = previous();
    expr *right = unary();
    return pool_.c_unary_expr(opr, right);
  }
  return fncall();
}
expr *parser::fncall() {
  auto expr = primary();
  while (true) {
    if (match({token_type::PAREN_OPEN})) {
      expr = match_rest_of_fncall(expr);
    } else if (match({token_type::DOT})) {
      auto dot_oper = previous();
      auto rhs = consume(token_type::NAME, "An identifier is expected");
      expr = pool_.c_get_expr(expr, dot_oper, rhs);
    } else if (match({token_type::SQUARE_BRACKET_OPEN})) {
      expr = match_array_access(expr);
    } else {
      break;
    }
  }
  return expr;
}
expr *parser::match_rest_of_fncall(expr *name) {
  std::vector<expr *> args{};
  if (!check(token_type::PAREN_CLOSE)) {
    do { args.emplace_back(expression()); } while (match({token_type::COMMA}));
  }
  auto paren_close =
      consume(token_type::PAREN_CLOSE, "Function call must end with ')'");
  return pool_.c_fncall_expr(name, paren_close, args);
}
expr *parser::match_array_access(expr *name) {
  auto arr_member = expression();
  auto paren_close =
      consume(token_type::SQUARE_BRACKET_CLOSE, "Must end with a ']'");
  return pool_.c_square_bracket_access_expr(name, paren_close, arr_member);
}
expr *parser::primary() {
  if (match({token_type::KEYWORD_FALSE, token_type::KEYWORD_TRUE,
             token_type::KEYWORD_NONE, token_type::FLOAT_NUMBER,
             token_type::INTEGER_DECIMAL, token_type::INTEGER_BIN,
             token_type::INTEGER_OCT, token_type::INTEGER_HEX,
             token_type::STRING, token_type::THREE_QUOTE_STRING})) {
    return pool_.c_literal_expr(previous());
  }
  if (match({token_type::NAME})) { return pool_.c_variable_expr(previous()); }
  if (match({token_type::PAREN_OPEN})) {
    expr *ex = expression();
    consume(token_type::PAREN_CLOSE, "Expect ')' after expression");
    return pool_.c_grouping_expr(ex);
  }
  throw error(peek(), "Expected expression!");
}
token *parser::consume(token_type t, const std::string &message) {
  if (check(t)) return advance();
  throw error(peek(), message);
}
parsing_error parser::error(token *tok, const std::string &message) {
  auto err = parsing_error{message, tok};
  handle_error(err);
  return err;
}
void parser::handle_error(const parsing_error &err) { errors_.push_back(err); }
expr *parser::expression() { return assignment(); }
std::vector<stmt *> parser::parse() {
  while (!is_at_end()) {
    auto decl = declaration_statement();
    if (decl == nullptr) { return stmts_; }
    stmts_.emplace_back(decl);
  }
  return stmts_;
}
void parser::synchronize_parser() {
  advance();
  while (!is_at_end()) {
    if (previous()->type_ == token_type::NEW_LINE) { return; }
    switch (peek()->type_) {
      case token_type::KEYWORD_CLASS:
      case token_type::KEYWORD_FOR:
      case token_type::KEYWORD_DEF:
      case token_type::KEYWORD_IF:
      case token_type::KEYWORD_WHILE:
      case token_type::KEYWORD_RETURN:
        return;
      default:
        break; /* do nothing for others */
    }
    advance();
  }
}
stmt *parser::statement() {
  // statement ->  print
  //             | if
  //             | pass
  //             | while
  //             | expression_statement
  if (match({token_type::KEYWORD_IF})) { return if_statement(); }
  if (match({token_type::KEYWORD_PASS})) { return pass_statement(); }
  if (match({token_type::KEYWORD_WHILE})) { return while_statement(); }
  if (match({token_type::KEYWORD_CONTINUE})) { return continue_statement(); }
  if (match({token_type::KEYWORD_BREAK})) { return break_statement(); }
  if (match({token_type::KEYWORD_RETURN})) { return return_statement(); }
  if (match({token_type::KEYWORD_DEFER})) { return defer_statement(); }
  if (match({token_type::KEYWORD_DEL})) { return del_statement(); }
  if (match({token_type::KEYWORD_CCODE})) { return ccode_statement(); }
  return expression_statement();
}
stmt *parser::pass_statement() {
  auto pass_tok = previous();
  consume_or_eof(token_type::NEW_LINE,
                 "Expect new line after 'pass' statement.");
  return pool_.c_pass_stmt(pass_tok);
}
stmt *parser::if_statement() {
  // if_stmt   -> KEYWORD_IF EXPRESSION block_stmt
  //             (KEYWORD_ELSE block_stmt)?
  auto if_keyword = previous();
  auto exp = expression();
  stmt *if_branch = block_statement();
  token *else_keyword = nullptr;
  stmt *else_branch = nullptr;
  if (match({token_type::KEYWORD_ELSE})) {
    else_keyword = previous();
    else_branch = block_statement();
  }
  return pool_.c_if_stmt(if_keyword, exp, if_branch, else_keyword, else_branch);
}
stmt *parser::block_statement() {
  // block_stmt -> COLON NEW_LINE BA_INDENT statement+ BA_DEDENT
  consume(token_type::COLON, "Expected ':' at start of block");
  auto colon = previous();
  consume(token_type::NEW_LINE, "Expected new line");
  consume(token_type::BA_INDENT, "Expected indented block");
  std::vector<stmt *> statements{};
  statements.reserve(3);
  while (!is_at_end()) {
    auto decl = declaration_statement();
    if (decl == nullptr) { break; }
    statements.emplace_back(decl);
    if (peek()->type_ == token_type::BA_DEDENT) { break; }
  }
  if (statements.empty()) {
    throw error(colon, "Block cannot be empty. Use 'pass'"
                       " statement for an empty block.");
  }
  consume(token_type::BA_DEDENT, "Expected dedent");
  return pool_.c_block_stmt(statements);
}
stmt *parser::defer_statement() {
  auto defer_keyword = previous();
  expr *exp = nullptr;
  stmt *st = nullptr;
  if (match({token_type::KEYWORD_DEL})) {
    st = del_statement_base();
  } else {
    exp = expression();
  }
  consume_or_eof(token_type::NEW_LINE,
                 "Expect new line after value for defer statement.");
  return pool_.c_defer_stmt(defer_keyword, exp, st);
}
stmt *parser::expression_statement() {
  expr *exp = expression();
  consume_or_eof(token_type::NEW_LINE,
                 "Expect new line after value for expression.");
  return pool_.c_expression_stmt(exp);
}
token *parser::consume_or_eof(token_type t, const std::string &message) {
  if (check(t)) return advance();
  if (is_at_end()) return peek();
  throw error(peek(), message);
}
stmt *parser::declaration_statement() {
  token *var_name = nullptr;
  expr *exp = nullptr;
  token *data_type = nullptr;
  try {
    if (match({token_type::KEYWORD_IMPORT})) { return import_statement(); }
    if (match({token_type::KEYWORD_DEF})) { return def_statement({}); }
    if (match({token_type::KEYWORD_CLASS})) { return class_statement({}); }
    if (match({token_type::AT})) { return attempt_parse_def_or_class(); }
    if (!match({token_type::NAME})) { return statement(); }
    var_name = previous();
    // Colon should come after name for a variable declaration
    if (!match({token_type::COLON})) {
      recede();
      return statement();
    }
    auto dt = parse_datatype();
    // `= expression` bit is optional
    if (match({token_type::EQ})) { exp = expression(); }
    consume_or_eof(token_type::NEW_LINE,
                   "Expect new line after value for variable declaration.");
    return pool_.c_let_stmt(var_name, dt, exp);
  } catch (parsing_error &err) {
    synchronize_parser();
    return nullptr;
  }
}
expr *parser::assignment() {
  auto exp = or_op();
  // a = b = 1
  if (match({token_type::EQ})) {
    auto equals = previous();
    auto val = assignment();
    if (exp->get_type() == ast_type::EXPR_VARIABLE) {
      auto name = (dynamic_cast<variable_expr *>(exp))->name_;
      return pool_.c_assign_expr(name, equals, val);
    } else if (exp->get_type() == ast_type::EXPR_GET) {
      auto get = (dynamic_cast<get_expr *>(exp));
      auto set_expr = pool_.c_set_expr(get->lhs_, get->dot_, get->item_);
      return pool_.c_assign_member_expr(set_expr, equals, val);
    } else if (exp->get_type() == ast_type::EXPR_SQUARE_BRACKET_ACCESS) {
      auto get = (dynamic_cast<square_bracket_access_expr *>(exp));
      auto set_expr = pool_.c_square_bracket_set_expr(
          get->name_, get->sqb_token_, get->index_expr_);
      return pool_.c_assign_arr_expr(set_expr, equals, val);
    }
    throw error(equals, "Invalid assignment target!");
  }
  return exp;
}
expr *parser::or_op() {
  auto exp = and_op();
  while (match({token_type::KEYWORD_OR})) {
    auto opr = previous();
    auto right = and_op();
    exp = pool_.c_logical_expr(exp, opr, right);
  }
  return exp;
}
expr *parser::and_op() {
  auto exp = equality();
  while (match({token_type::KEYWORD_AND})) {
    auto opr = previous();
    auto right = equality();
    exp = pool_.c_logical_expr(exp, opr, right);
  }
  return exp;
}
stmt *parser::while_statement() {
  // while_stmt   -> KEYWORD_WHILE EXPRESSION block_stmt
  control_flow_++;
  auto while_keyword = previous();
  auto exp = expression();
  stmt *while_body = block_statement();
  control_flow_--;
  return pool_.c_while_stmt(while_keyword, exp, while_body);
}
stmt *parser::continue_statement() {
  auto tok = previous();
  if (control_flow_ <= 0) { throw error(tok, "Invalid assignment target!"); }
  consume_or_eof(token_type::NEW_LINE,
                 "Expect new line after 'continue' statement.");
  return pool_.c_continue_stmt(tok);
}
stmt *parser::break_statement() {
  auto tok = previous();
  if (control_flow_ <= 0) { throw error(tok, "Invalid assignment target!"); }
  consume_or_eof(token_type::NEW_LINE,
                 "Expect new line after 'break' statement.");
  return pool_.c_break_stmt(tok);
}
stmt *parser::return_statement() {
  auto tok = previous();
  expr *exp;
  if (check(token_type::NEW_LINE) || is_at_end()) {
    // Return without an expression
    exp = nullptr;
  } else {
    exp = expression();
  }
  consume_or_eof(token_type::NEW_LINE,
                 "Expect new line after 'return' statement.");
  return pool_.c_return_stmt(tok, exp);
}
stmt *parser::def_statement(annotations ants) {
  // def_statement -> KEYWORD_DEF NAME PAREN_OPEN [[NAME COLON DATA_TYPE]*] PAREN_CLOSE ARROW DATA_TYPE BLOCK
  auto name = consume(token_type::NAME, "Function name must be present");
  consume(token_type::PAREN_OPEN, "Opening '(' must be present");
  std::vector<parameter> params{};
  if (!check(token_type::PAREN_CLOSE)) {
    do {
      auto param_name =
          consume(token_type::NAME, "Parameter name must be present");
      consume(token_type::COLON,
              "Colon must be present between parameter name and data type");
      auto dt = parse_datatype();
      params.emplace_back(parameter{param_name, dt});
    } while (match({token_type::COMMA}));
  }
  consume(token_type::PAREN_CLOSE, "Function call must end with ')'");
  consume(token_type::ARROW, "'->' operator must be present");
  auto return_dt = parse_datatype();
  auto body = dynamic_cast<block_stmt *>(block_statement());
  // Void function must have a return at the end to ensure strings are freed.
  if (!ants.native_macro_ && !ants.native_ &&
      return_dt->is_builtin_or_primitive() && return_dt->is_none()) {
    if (body->statements_.back()->get_type() != ast_type::STMT_RETURN) {
      body->statements_.emplace_back(
          pool_.c_return_stmt(magic_return_token_, nullptr));
    }
  }
  return pool_.c_def_stmt(name, params, body, return_dt, std::move(ants));
}
ykdatatype *parser::parse_datatype() {
  if (!match({token_type::NAME, token_type::KEYWORD_NONE})) {
    throw error(peek(), "Must have a data type.");
  }
  ykdatatype *dt;
  auto tk = previous();
  if (match({token_type::DOT})) {
    auto after_dot = consume(token_type::NAME, "Must have a name after dot");
    auto module_import_alias = tk->token_;
    if (import_stmts_alias_.find(module_import_alias) ==
        import_stmts_alias_.end()) {
      throw error(tk, "Needs to be a module");
    }
    dt = dt_pool_->create(after_dot->token_, module_import_alias);
    datatypes_from_modules_.emplace_back(dt);
  } else {
    dt = dt_pool_->create(tk->token_, filepath_);
  }
  if (match({token_type::SQUARE_BRACKET_OPEN})) {
    if (dt->is_primitive()) {
      throw error(dt->token_,
                  "Primitive data types cannot have internal data types.");
    }
    do {
      auto arg = parse_datatype();
      if (arg->is_none()) {
        throw error(dt->token_,
                    "None cannot be used as an argument for a data type.");
      }
      dt->args_.push_back(arg);
    } while (match({token_type::COMMA}));
    consume(token_type::SQUARE_BRACKET_CLOSE, "Must have a closing ']'");
  }
  return dt;
}
stmt *parser::class_statement(annotations ants) {
  auto name = consume(token_type::NAME, "Class name must be present");
  consume(token_type::COLON, "Colon must be present after class name");
  consume(token_type::NEW_LINE, "Class block must start with a new line");
  consume(token_type::BA_INDENT,
          "Class block must start with an indentation increase");
  std::vector<parameter> members = parse_class_members(name);
  return pool_.c_class_stmt(name, members, std::move(ants));
}
std::vector<parameter> parser::parse_class_members(token *name) {
  std::vector<parameter> members{};
  while (!is_at_end()) {
    auto param_name = consume(token_type::NAME, "Member name must be present");
    consume(token_type::COLON,
            "Colon must be present between member name and data type");
    auto dt = parse_datatype();
    members.emplace_back(parameter{param_name, dt});
    consume(token_type::NEW_LINE, "New line should separate members");
    if (peek()->type_ == token_type::BA_DEDENT) { break; }
  }
  if (members.empty()) {
    throw error(name, "Class statement cannot have an empty block");
  }
  consume(token_type::BA_DEDENT, "Expected dedent");
  return members;
}
stmt *parser::del_statement() {
  stmt *st = del_statement_base();
  consume_or_eof(token_type::NEW_LINE,
                 "Expect new line after value for del statement.");
  return st;
}
stmt *parser::del_statement_base() {
  auto del_keyword = previous();
  expr *exp = expression();
  return pool_.c_del_stmt(del_keyword, exp);
}
stmt *parser::attempt_parse_def_or_class() {
  auto at_sign = previous();
  annotations ants;
  ants.add(parse_annotation());
  if (!ants.error_.empty()) { throw error(at_sign, ants.error_); }
  while (!is_at_end()) {
    if (match({token_type::AT})) {
      ants.add(parse_annotation());
      if (!ants.error_.empty()) { throw error(at_sign, ants.error_); }
    } else if (match({token_type::KEYWORD_DEF})) {
      return def_statement(ants);
    } else if (match({token_type::KEYWORD_CLASS})) {
      return class_statement(ants);
    } else {
      break;
    }
  }
  throw error(at_sign, "End of file reached when parsing annotations. def or "
                       "class statement must come after annotations.");
}
annotation parser::parse_annotation() {
  auto name = consume(token_type::NAME, "Annotation must have a valid name");
  std::string argument{};
  if (match({token_type::PAREN_OPEN})) {
    auto nt = this->peek();
    if (nt->type_ == token_type::STRING ||
        nt->type_ == token_type::THREE_QUOTE_STRING) {
      advance();
      argument = nt->token_;
    } else {
      throw error(nt, "Invalid token as annotation argument. Only a single "
                      "string must be present.");
    }
    consume(token_type::PAREN_CLOSE, "Expected ')'");
  }
  consume(token_type::NEW_LINE, "Annotation must end with a new line.");
  annotation a{};
  a.name_ = name->token_;
  a.arg_ = argument;
  return a;
}
stmt *parser::ccode_statement() {
  auto ccode_keyword = previous();
  auto cc = peek();
  if (cc->type_ != token_type::STRING &&
      cc->type_ != token_type::THREE_QUOTE_STRING) {
    throw error(ccode_keyword,
                "Expected ccode statement have a string literal.");
  }
  advance();
  consume_or_eof(token_type::NEW_LINE,
                 "Expect new line after value for ccode statement.");
  return pool_.c_ccode_stmt(ccode_keyword, cc);
}
stmt *parser::import_statement() {
  auto import_token = previous();
  token *name_token;
  std::vector<token *> imp_names{};
  auto tk = consume(token_type::NAME,
                    "At least one name for imported module must be present");
  imp_names.emplace_back(tk);
  while (peek()->type_ == token_type::DOT) {
    consume(token_type::DOT, "Dot must be present");
    tk = consume(token_type::NAME,
                 "A name for imported module must be present after a dot");
    imp_names.emplace_back(tk);
  }
  if (match({token_type::KEYWORD_AS})) {
    name_token =
        consume(token_type::NAME, "Name must be present after 'as' keyword.");
  } else {
    name_token = imp_names.back();
  }
  consume(token_type::NEW_LINE, "Import must end with new line.");
  auto st = pool_.c_import_stmt(import_token, imp_names, name_token, nullptr);
  if (import_stmts_alias_.find(name_token->token_) !=
      import_stmts_alias_.end()) {
    throw error(name_token, "Duplicate import alias");
  }
  auto import = dynamic_cast<import_stmt *>(st);
  import_stmts_.emplace_back(import);
  import_stmts_alias_.insert({name_token->token_, import});
  return st;
}
void parser::rescan_datatypes() {
  for (auto &dt : datatypes_from_modules_) {
    if (dt->is_builtin_or_primitive()) continue;
    auto import_alias = dt->module_;
    auto module_data = import_stmts_alias_[import_alias];
    dt->module_ = module_data->data_->filepath_;
  }
  // Clean up temporary vector
  datatypes_from_modules_.clear();
}
