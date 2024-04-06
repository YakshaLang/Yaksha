// ==============================================================================================
// ╦  ┬┌─┐┌─┐┌┐┌┌─┐┌─┐    Yaksha Programming Language
// ║  ││  ├┤ │││└─┐├┤     is Licensed with GPLv3 + extra terms. Please see below.
// ╩═╝┴└─┘└─┘┘└┘└─┘└─┘
// Note: libs - MIT license, runtime/3rd - various
// ==============================================================================================
// GPLv3:
//
// Yaksha - Programming Language.
// Copyright (C) 2020 - 2024 Bhathiya Perera
//
// This program is free software: you can redistribute it and/or modify it under the terms
// of the GNU General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with this program.
// If not, see https://www.gnu.org/licenses/.
//
// ==============================================================================================
// Additional Terms:
//
// Please note that any commercial use of the programming language's compiler source code
// (everything except compiler/runtime, compiler/libs and compiler/3rd) require a written agreement
// with author of the language (Bhathiya Perera).
//
// If you are using it for an open source project, please give credits.
// Your own project must use GPLv3 license with these additional terms.
//
// You may use programs written in Yaksha/YakshaLisp for any legal purpose
// (commercial, open-source, closed-source, etc) as long as it agrees
// to the licenses of linked runtime libraries (see compiler/runtime/README.md).
//
// ==============================================================================================
#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
// parser.cpp
#include "ast/parser.h"
#include "compiler/literal_utils.h"
#include "tokenizer/block_analyzer.h"
#include "utilities/cpp_util.h"
#include "yaksha_lisp/macro_processor.h"
#include <algorithm>
#include <cassert>
#include <utility>
using namespace yaksha;
#ifdef YAKSHA_DEBUG
#define PRINT_PREPROCESSOR_OUTPUT
#endif
parser::parser(std::string filepath, std::vector<token *> &tokens,
               ykdt_pool *pool)
    : pool_{}, original_tokens_{tokens}, current_{0}, control_flow_{0},
      magic_return_token_(new token{}), sugar_else_(new token{}),
      dt_pool_(pool), import_stmts_(), filepath_(std::move(filepath)),
      pre_parse_import_stmts_() {
  // Create a fake return token to be injected at end of void functions.
  // WHY?: This ensures that defer + string freeing work
  // --
  magic_return_token_->token_ = "return";
  magic_return_token_->file_ = "desugar";
  magic_return_token_->original_ = "return";
  magic_return_token_->line_ = 0;
  magic_return_token_->pos_ = 0;
  magic_return_token_->type_ = token_type::KEYWORD_RETURN;
  // --
  sugar_else_->token_ = "else";
  sugar_else_->file_ = "desugar";
  sugar_else_->original_ = "return";
  sugar_else_->line_ = 0;
  sugar_else_->pos_ = 0;
  sugar_else_->type_ = token_type::KEYWORD_ELSE;
  // Tokens are stored in a vector of pointers to tokens.
  // This allows us to mutate this later when required.
  for (auto &t : original_tokens_) { tokens_.push_back(t); }
}
parser::~parser() {
  delete (magic_return_token_);
  delete (sugar_else_);
  datatypes_from_modules_.clear();
}
token *parser::advance() {
  if (!is_at_end()) { current_++; }
  return previous();
}
token *parser::recede() {
  if (current_ != 0) { current_--; }
  return peek();
}
bool parser::is_at_end() { return peek()->type_ == token_type::END_OF_FILE; }
bool parser::is_at_end_of_stream() {
  return current_ + 1 >= tokens_.size() ||
         peek()->type_ == token_type::END_OF_FILE;
}
token *parser::peek() { return tokens_[current_]; }
token *parser::previous() {
  assert(current_ > 0);
  return tokens_[current_ - 1];
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
  expr *ex = bit_or();
  while (match({token_type::GREAT, token_type::GREAT_EQ, token_type::LESS,
                token_type::LESS_EQ})) {
    auto opr = previous();
    expr *right = bit_or();
    ex = pool_.c_binary_expr(ex, opr, right);
  }
  return ex;
}
expr *parser::bit_or() {
  expr *ex = bit_xor();
  while (match({token_type::OR})) {
    auto opr = previous();
    expr *right = bit_xor();
    ex = pool_.c_binary_expr(ex, opr, right);
  }
  return ex;
}
expr *parser::bit_xor() {
  expr *ex = bit_and();
  while (match({token_type::XOR})) {
    auto opr = previous();
    expr *right = bit_and();
    ex = pool_.c_binary_expr(ex, opr, right);
  }
  return ex;
}
expr *parser::bit_and() {
  expr *ex = bit_shifts();
  while (match({token_type::AND})) {
    auto opr = previous();
    expr *right = bit_shifts();
    ex = pool_.c_binary_expr(ex, opr, right);
  }
  return ex;
}
expr *parser::bit_shifts() {
  expr *ex = term();
  while (match({token_type::SHL, token_type::SHR})) {
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
  while (match({token_type::DIV, token_type::MUL, token_type::MOD})) {
    auto opr = previous();
    expr *right = unary();
    ex = pool_.c_binary_expr(ex, opr, right);
  }
  return ex;
}
expr *parser::unary() {
  if (match({token_type::SUB, token_type::KEYWORD_NOT, token_type::TILDE})) {
    auto opr = previous();
    expr *right = unary();
    // optimize - then num -> -num
    if (opr->type_ == token_type::SUB &&
        right->get_type() == ast_type::EXPR_LITERAL) {
      auto lit = dynamic_cast<literal_expr *>(right);
      if (lit->literal_token_->type_ == token_type::FLOAT_NUMBER ||
          lit->literal_token_->type_ == token_type::DOUBLE_NUMBER ||
          lit->literal_token_->type_ == token_type::INTEGER_DECIMAL_8 ||
          lit->literal_token_->type_ == token_type::INTEGER_HEX_8 ||
          lit->literal_token_->type_ == token_type::INTEGER_OCT_8 ||
          lit->literal_token_->type_ == token_type::INTEGER_BIN_8 ||
          lit->literal_token_->type_ == token_type::INTEGER_DECIMAL_16 ||
          lit->literal_token_->type_ == token_type::INTEGER_HEX_16 ||
          lit->literal_token_->type_ == token_type::INTEGER_OCT_16 ||
          lit->literal_token_->type_ == token_type::INTEGER_BIN_16 ||
          lit->literal_token_->type_ == token_type::INTEGER_DECIMAL ||
          lit->literal_token_->type_ == token_type::INTEGER_HEX ||
          lit->literal_token_->type_ == token_type::INTEGER_OCT ||
          lit->literal_token_->type_ == token_type::INTEGER_BIN ||
          lit->literal_token_->type_ == token_type::INTEGER_DECIMAL_64 ||
          lit->literal_token_->type_ == token_type::INTEGER_HEX_64 ||
          lit->literal_token_->type_ == token_type::INTEGER_OCT_64 ||
          lit->literal_token_->type_ == token_type::INTEGER_BIN_64) {
        auto lit_tok = lit->literal_token_;
        auto converted = convert_literal(lit_tok->type_, lit_tok);
        if (!converted.error_.empty()) {
          throw error(lit_tok, converted.error_);
        }
        auto bits = get_bits(lit_tok->type_);
        auto new_token_string = converted.decimal_string_;
        // if it is a negative number, make it positive
        if (new_token_string[0] == '-') {
          lit_tok->token_ = new_token_string.substr(1);
        } else {// make it negative
          lit_tok->token_ = "-" + new_token_string;
        }
        if (bits == 32) {
          lit_tok->type_ = token_type::INTEGER_DECIMAL;
        } else if (bits == 64) {
          lit_tok->type_ = token_type::INTEGER_DECIMAL_64;
        } else if (bits == 16) {
          lit_tok->type_ = token_type::INTEGER_DECIMAL_16;
        } else if (bits == 8) {
          lit_tok->type_ = token_type::INTEGER_DECIMAL_8;
        }
        // else it is a float / double, keep as is
        return right;
      }
    }
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
    } else if (match({token_type::CURLY_BRACKET_OPEN})) {
      expr = match_rest_of_curly_call(expr);
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
  auto index_expr = expression();
  auto paren_close =
      consume(token_type::SQUARE_BRACKET_CLOSE, "Must end with a ']'");
  return pool_.c_square_bracket_access_expr(name, paren_close, index_expr);
}
expr *parser::match_rest_of_curly_call(expr *data_type_expr) {
  auto curly_open = previous();
  std::vector<name_val> values{};
  if (!check(token_type::CURLY_BRACKET_CLOSE)) {
    do {
      auto member_name =
          consume(token_type::NAME, "Member name must be present");
      consume(token_type::COLON,
              "Colon must be present between member name and expression");
      auto exp = expression();
      values.emplace_back(name_val{member_name, exp});
    } while (match({token_type::COMMA}));
  }
  auto curly_close = consume(token_type::CURLY_BRACKET_CLOSE,
                             "struct literal must end with '}'");
  return pool_.c_curly_call_expr(data_type_expr, curly_open, values,
                                 curly_close);
}
expr *parser::primary() {
  if (match({
          token_type::KEYWORD_FALSE,       token_type::KEYWORD_TRUE,
          token_type::KEYWORD_NONE,        token_type::DOUBLE_NUMBER,
          token_type::FLOAT_NUMBER,        token_type::STRING,
          token_type::THREE_QUOTE_STRING,  token_type::INTEGER_BIN,
          token_type::INTEGER_BIN_16,      token_type::INTEGER_BIN_64,
          token_type::INTEGER_BIN_8,       token_type::INTEGER_DECIMAL,
          token_type::INTEGER_DECIMAL_16,  token_type::INTEGER_DECIMAL_64,
          token_type::INTEGER_DECIMAL_8,   token_type::INTEGER_HEX,
          token_type::INTEGER_HEX_16,      token_type::INTEGER_HEX_64,
          token_type::INTEGER_HEX_8,       token_type::INTEGER_OCT,
          token_type::INTEGER_OCT_16,      token_type::INTEGER_OCT_64,
          token_type::INTEGER_OCT_8,       token_type::UINTEGER_BIN,
          token_type::UINTEGER_BIN_16,     token_type::UINTEGER_BIN_64,
          token_type::UINTEGER_BIN_8,      token_type::UINTEGER_DECIMAL,
          token_type::UINTEGER_DECIMAL_16, token_type::UINTEGER_DECIMAL_64,
          token_type::UINTEGER_DECIMAL_8,  token_type::UINTEGER_HEX,
          token_type::UINTEGER_HEX_16,     token_type::UINTEGER_HEX_64,
          token_type::UINTEGER_HEX_8,      token_type::UINTEGER_OCT,
          token_type::UINTEGER_OCT_16,     token_type::UINTEGER_OCT_64,
          token_type::UINTEGER_OCT_8,
      })) {
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
token *parser::consume_any_of(std::initializer_list<token_type> types,
                              const std::string &message) {
  if (is_at_end()) { throw error(peek(), message); }
  for (auto t : types) {
    if (check(t)) return advance();
  }
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
  // Mark global constants
  for (stmt *st : stmts_) {
    if (st->get_type() == ast_type::STMT_CONST) {
      auto casted = dynamic_cast<const_stmt *>(st);
      casted->is_global_ = true;
    }
    if (st->get_type() == ast_type::STMT_NATIVECONST) {
      auto casted = dynamic_cast<nativeconst_stmt *>(st);
      casted->is_global_ = true;
    }
  }
  return stmts_;
}
void parser::synchronize_parser() {
  advance();
  while (!is_at_end()) {
    if (previous()->type_ == token_type::NEW_LINE) { return; }
    switch (peek()->type_) {
      case token_type::KEYWORD_CLASS:
      case token_type::KEYWORD_STRUCT:
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
  if (match({token_type::KEYWORD_FOR})) { return for_statement(); }
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
  // elif*  KEYWORD_ELIF, EXPRESSION block_stmt
  //             (KEYWORD_ELSE block_stmt)?
  auto if_keyword = previous();
  auto exp = expression();
  stmt *if_branch = block_statement();
  token *in_code_else_keyword = nullptr;
  stmt *in_code_else_branch = nullptr;
  std::vector<elif_stmt *> elif_statements{};
  while (match({token_type::KEYWORD_ELIF})) {
    token *elif_keyword = previous();
    auto elif_expr = expression();
    stmt *elif_branch = block_statement();
    elif_statements.push_back(dynamic_cast<elif_stmt *>(
        pool_.c_elif_stmt(elif_keyword, elif_expr, elif_branch)));
  }
  if (match({token_type::KEYWORD_ELSE})) {
    in_code_else_keyword = previous();
    in_code_else_branch = block_statement();
  }
  // No elif statements nothing to do
  if (elif_statements.empty()) {
    return pool_.c_if_stmt(if_keyword, exp, if_branch, in_code_else_keyword,
                           in_code_else_branch);
  }
  // found elif statements -> compile elif syntax sugar to if/else
  std::vector<if_stmt *> ifs{};
  for (auto it = elif_statements.rbegin(); it != elif_statements.rend(); ++it) {
    elif_stmt *st = *it;
    if (ifs.empty()) {
      // last elif, add else to this
      ifs.push_back(dynamic_cast<if_stmt *>(
          pool_.c_if_stmt(st->elif_keyword_, st->expression_, st->elif_branch_,
                          in_code_else_keyword, in_code_else_branch)));
    } else {
      if_stmt *prev = ifs.back();
      ifs.pop_back();
      std::vector<stmt *> sugar_else_block{};
      sugar_else_block.push_back(prev);
      ifs.push_back(dynamic_cast<if_stmt *>(
          pool_.c_if_stmt(st->elif_keyword_, st->expression_, st->elif_branch_,
                          sugar_else_, pool_.c_block_stmt(sugar_else_block))));
    }
  }
  if_stmt *nested_if = ifs.back();
  ifs.clear();
  std::vector<stmt *> sugar_else_block{};
  sugar_else_block.push_back(nested_if);
  return pool_.c_if_stmt(if_keyword, exp, if_branch, sugar_else_,
                         pool_.c_block_stmt(sugar_else_block));
}
void parser::verify_statements(token *token, std::vector<stmt *> &statements) {
  for (stmt *st : statements) {
    if (st->get_type() == ast_type::STMT_IMPORT ||
        st->get_type() == ast_type::STMT_DEF ||
        st->get_type() == ast_type::STMT_CLASS ||
        st->get_type() == ast_type::STMT_RUNTIMEFEATURE) {
      throw error(token,
                  "Blocks with nested import/def/class is not supported");
    }
  }
}
void parser::verify_only_single_line_statements(
    token *token, std::vector<stmt *> &statements) {
  for (stmt *st : statements) {
    if (!(st->get_type() == ast_type::STMT_DEFER ||
          st->get_type() == ast_type::STMT_DEL ||
          st->get_type() == ast_type::STMT_PASS ||
          st->get_type() == ast_type::STMT_RETURN ||
          st->get_type() == ast_type::STMT_EXPRESSION ||
          st->get_type() == ast_type::STMT_CCODE)) {
      throw error(token,
                  "Blocks with nested import/def/class is not supported");
    }
  }
}
stmt *parser::block_statement() {
  // block_stmt -> COLON NEW_LINE BA_INDENT statement+ BA_DEDENT
  // block_stmt -> COLON SIMPLE_STMT
  consume(token_type::COLON, "Expected ':' at start of block");
  auto colon = previous();
  std::vector<stmt *> statements{};
  if (peek()->type_ != token_type::NEW_LINE) {
    statements.reserve(1);
    auto decl = declaration_statement();
    if (decl == nullptr) {
      throw error(colon, "Block cannot be empty. Use 'pass'"
                         " statement for an empty block.");
    }
    statements.emplace_back(decl);
    verify_only_single_line_statements(colon, statements);
    return pool_.c_block_stmt(statements);
  } else {
    consume(token_type::NEW_LINE, "Expected new line");
    consume(token_type::BA_INDENT, "Expected indented block");
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
    // Discard python style documentation comments
    if (statements.front()->get_type() == ast_type::EXPR_LITERAL) {
      auto first_item = dynamic_cast<literal_expr *>(statements.front());
      if (first_item->literal_token_->type_ == token_type::STRING ||
          first_item->literal_token_->type_ == token_type::THREE_QUOTE_STRING) {
        statements.erase(statements.begin());
      }
    }
    if (statements.empty()) {
      throw error(colon, "Block cannot be empty. Use 'pass'"
                         " statement for an empty block.");
    }
    consume(token_type::BA_DEDENT, "Expected dedent");
    verify_statements(colon, statements);
    return pool_.c_block_stmt(statements);
  }
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
  try {
    if (match({token_type::KEYWORD_IMPORT})) { return import_statement(); }
    if (match({token_type::KEYWORD_DIRECTIVE})) {
      return directive_statement();
    }
    if (match({token_type::KEYWORD_RUNTIMEFEATURE})) {
      return runtimefeature_statement();
    }
    if (match({token_type::KEYWORD_DEF})) { return def_statement({}); }
    if (match({token_type::KEYWORD_CLASS, token_type::KEYWORD_STRUCT})) {
      return class_statement({});
    }
    if (match({token_type::AT})) { return attempt_parse_def_or_class(); }
    if (!match({token_type::NAME})) { return statement(); }
    return parse_named_let_statement();
  } catch (parsing_error &ignored) {
    intentionally_ignored(ignored);
    synchronize_parser();
    return nullptr;
  }
}
stmt *parser::parse_named_let_statement() {
  token *var_name = nullptr;
  expr *exp = nullptr;
  var_name = previous();
  // Colon should come after name for a variable declaration
  if (!match({token_type::COLON})) {
    recede();
    return statement();
  }
  auto dt = parse_datatype();
  // `= expression` bit is optional
  if (match({token_type::EQ})) {
    if (check(token_type::KEYWORD_CCODE)) {
      auto ccode_token = advance();
      auto cc = peek();
      if (!(token_type::STRING == cc->type_ ||
            token_type::THREE_QUOTE_STRING == cc->type_)) {
        throw error(ccode_token,
                    "Expected ccode statement to have a string literal.");
      }
      if (!dt->is_const()) {
        throw error(ccode_token, "Variable on LHS needs to be a const");
      }
      advance();
      // We are in native constant
      consume_or_eof(
          token_type::NEW_LINE,
          "Expect new line after code text for native const declaration.");
      return pool_.c_nativeconst_stmt(var_name, dt, ccode_token, cc, false);
    } else {
      exp = expression();
    }
  }
  consume_or_eof(token_type::NEW_LINE,
                 "Expect new line after value for variable declaration.");
  if (dt->is_const()) { return pool_.c_const_stmt(var_name, dt, exp, false); }
  return pool_.c_let_stmt(var_name, dt, exp);
}
expr *parser::assignment() {
  auto exp = or_op();
  if (match({token_type::EQ, token_type::AND_EQ, token_type::XOR_EQ,
             token_type::OR_EQ, token_type::SHL_EQ, token_type::SHR_EQ,
             token_type::DIV_EQ, token_type::MOD_EQ, token_type::MUL_EQ,
             token_type::PLUS_EQ, token_type::SUB_EQ})) {
    auto assignment_operator = previous();
    auto val = assignment();
    if (exp->get_type() == ast_type::EXPR_VARIABLE) {
      auto name = (dynamic_cast<variable_expr *>(exp))->name_;
      return pool_.c_assign_expr(name, assignment_operator, val, false,
                                 nullptr);
    } else if (exp->get_type() == ast_type::EXPR_GET) {
      auto get = (dynamic_cast<get_expr *>(exp));
      auto set_expr = pool_.c_set_expr(get->lhs_, get->dot_, get->item_);
      return pool_.c_assign_member_expr(set_expr, assignment_operator, val);
    } else if (exp->get_type() == ast_type::EXPR_SQUARE_BRACKET_ACCESS) {
      auto get = (dynamic_cast<square_bracket_access_expr *>(exp));
      auto set_expr = pool_.c_square_bracket_set_expr(
          get->name_, get->sqb_token_, get->index_expr_);
      return pool_.c_assign_arr_expr(set_expr, assignment_operator, val);
    }
    throw error(assignment_operator, "Invalid assignment target!");
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
stmt *parser::for_statement() {
  control_flow_++;
  auto for_keyword = previous();
  if (check(token_type::COLON)) {// forendless_stmt -> FOR: block_stmt
    stmt *for_body = block_statement();
    control_flow_--;
    return pool_.c_forendless_stmt(for_keyword, for_body);
  } else if (check(token_type::NAME)) {
    // foreach_stmt -> FOR name: datatype in array: block_stmt
    auto name = consume(token_type::NAME, "Name must be present");
    ykdatatype *dt = nullptr;
    if (check(token_type::COLON)) {
      consume(token_type::COLON, "Colon must be present");
      dt = parse_datatype();
    }
    auto in_k =
        consume(token_type::KEYWORD_IN,
                "in must follow the data type declaration in for each loop.");
    auto for_source = expression();
    auto for_body = block_statement();
    control_flow_--;
    return pool_.c_foreach_stmt(for_keyword, name, dt, in_k, for_source,
                                for_body, nullptr);
  } else if (check(token_type::PAREN_OPEN)) {
    // c-for
    // for (x = 0; x < 5; x += 1) BLOCK
    auto paren_open = consume(token_type::PAREN_OPEN, "'(' must be present");
    expr *init_expr = nullptr;
    expr *comparision_expr = nullptr;
    expr *post_expr = nullptr;
    token *semi1 = nullptr;
    token *semi2 = nullptr;
    if (!check(token_type::SEMICOLON)) { init_expr = expression(); }
    semi1 = consume(token_type::SEMICOLON, "Semicolon must be present");
    if (!check(token_type::SEMICOLON)) { comparision_expr = expression(); }
    semi2 = consume(token_type::SEMICOLON, "Semicolon must be present");
    if (!check(token_type::PAREN_CLOSE)) { post_expr = expression(); }
    auto paren_close = consume(token_type::PAREN_CLOSE, "')' must be present");
    auto for_body = block_statement();
    control_flow_--;
    return pool_.c_cfor_stmt(for_keyword, paren_open, init_expr, semi1,
                             comparision_expr, semi2, post_expr, paren_close,
                             for_body);
  }
  control_flow_--;
  throw error(for_keyword, "invalid for loop");
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
  return pool_.c_return_stmt(tok, exp, nullptr);
}
stmt *parser::def_statement(annotations ants) {
  // def_statement -> KEYWORD_DEF NAME PAREN_OPEN
  //    [[NAME COLON DATA_TYPE]*] PAREN_CLOSE ARROW DATA_TYPE BLOCK
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
  if (!ants.native_macro_ && !ants.native_ && !ants.native_define_ &&
      return_dt->is_builtin_or_primitive() && return_dt->is_none()) {
    if (body->statements_.back()->get_type() != ast_type::STMT_RETURN) {
      body->statements_.emplace_back(
          pool_.c_return_stmt(magic_return_token_, nullptr, nullptr));
    }
  }
  return pool_.c_def_stmt(name, params, body, return_dt, std::move(ants));
}
ykdatatype *parser::parse_datatype() {
  if (!match({token_type::NAME, token_type::KEYWORD_NONE,
              token_type::INTEGER_DECIMAL})) {
    throw error(peek(), "Must have a data type.");
  }
  ykdatatype *dt;
  auto tk = previous();
  if (match({token_type::DOT})) {
    // None.XXX or 4.XXX are invalid it needs to be mod.Name
    if (tk->type_ != token_type::NAME) {
      throw error(tk, "Must have a name before dot");
    }
    auto after_dot = consume(token_type::NAME, "Must have a name after dot");
    auto module_import_alias = tk->token_;
    if (import_stmts_alias_.find(module_import_alias) ==
        import_stmts_alias_.end()) {
      throw error(tk, "Needs to be a module");
    }
    dt = dt_pool_->create(after_dot->token_, module_import_alias);
    datatypes_from_modules_.emplace_back(dt);
  } else if (tk->type_ == token_type::INTEGER_DECIMAL) {
    try {
      dt = dt_pool_->create_dimension(tk, filepath_);
    } catch (std::out_of_range &e) {
      intentionally_ignored(e);
      throw error(tk, "Integer value is out of range");
    }
  } else {
    dt = dt_pool_->create(tk->token_, filepath_);
  }
  auto error_throwing_token = previous();
  if (match({token_type::SQUARE_BRACKET_OPEN})) {
    if (dt->is_primitive() || dt->is_any_ptr() || dt->is_any_ptr_to_const() ||
        dt->is_dimension()) {
      throw error(
          error_throwing_token,
          "Primitive data types / AnyPtr cannot have internal data types.");
    }
    do {
      auto arg = parse_datatype();
      if (arg->is_none()) {
        throw error(error_throwing_token,
                    "None cannot be used as an argument for a data type.");
      }
      // WHY?: Dimension can only be used as an argument for a fixed size array.
      if (arg->is_dimension() && !dt->is_fixed_size_array()) {
        throw error(error_throwing_token,
                    "Dimension can only be used as an argument for a fixed "
                    "size array.");
      }
      // WHY?: Function In/Out can only be used as an argument for a function.
      if (!dt->is_function() &&
          (arg->is_function_input() || arg->is_function_output())) {
        throw error(
            error_throwing_token,
            "Function In/Out can only be used as an argument for a function.");
      }
      dt->args_.push_back(arg);
    } while (match({token_type::COMMA}));
    consume(token_type::SQUARE_BRACKET_CLOSE, "Must have a closing ']'");
  }
  if (dt->is_array() || dt->is_ptr() || dt->is_const() || dt->is_sm_entry()) {
    if (dt->args_.size() != 1) {
      throw error(
          error_throwing_token,
          "Array/Ptr/Const/SMEntry/Out must only have a single data type arg");
    }
  }
  if (dt->is_fixed_size_array() &&
      (dt->args_.size() != 2 || !dt->args_[1]->is_dimension() ||
       dt->args_[0]->is_dimension())) {
    throw error(error_throwing_token,
                "FixedArr must have a data type argument and a dimension arg."
                " Example: FixedArr[i8, 10]");
  }
  if (dt->is_fixed_size_array() && dt->args_.size() > 1 &&
      (dt->args_[0]->const_unwrap()->is_sm_entry() ||
       dt->args_[0]->const_unwrap()->is_m_entry())) {
    throw error(
        error_throwing_token,
        "FixedArr cannot have a SMEntry/MEntry as the data type argument.");
  }
  if (dt->is_m_entry()) {
    if (dt->args_.size() != 2) {
      throw error(error_throwing_token,
                  "MEntry must only have a two data types args");
    }
  }
  if (dt->is_function() &&
      (dt->args_.size() != 2 || !dt->args_[0]->is_function_input() ||
       !dt->args_[1]->is_function_output())) {
    throw error(error_throwing_token,
                "Function must have both In and Out in order");
  }
  if (dt->is_function_output() && dt->args_.size() > 1) {
    throw error(error_throwing_token,
                "Function's Out datatype must have 0 or 1 arguments");
  }
  if (dt->is_function_output() && dt->args_.size() == 1 &&
      dt->args_[0]->const_unwrap()->is_fixed_size_array()) {
    throw error(error_throwing_token, "A function cannot return a fixed size "
                                      "array. Use Array or wrap in a Tuple.");
  }
  if (dt->is_tuple() && dt->args_.empty()) {
    throw error(error_throwing_token, "Tuple must have at least one argument");
  }
  if (dt->is_const() && dt->args_[0]->is_const()) {
    throw error(error_throwing_token, "Const[Const[?]] is invalid data type");
  }
  return dt;
}
stmt *parser::class_statement(annotations ants) {
  auto class_token = previous();
  if (class_token->type_ == token_type::KEYWORD_STRUCT) {
    if (ants.on_stack_) {
      throw error(class_token, "struct is already @onstack");
    }
    ants.on_stack_ = true;
  }
  auto name = consume(token_type::NAME, "Class name must be present");
  consume(token_type::COLON, "Colon must be present after class name");
  consume(token_type::NEW_LINE, "Class block must start with a new line");
  consume(token_type::BA_INDENT,
          "Class block must start with an indentation increase");
  if (peek()->type_ == token_type::KEYWORD_PASS) {
    consume(token_type::KEYWORD_PASS, "Expected 'pass'");
    consume(token_type::NEW_LINE, "New line should follow 'pass'");
    consume(token_type::BA_DEDENT, "Expected dedent");
    return pool_.c_class_stmt(name, std::vector<parameter>{}, std::move(ants));
  }
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
    } else if (match({token_type::KEYWORD_CLASS, token_type::KEYWORD_STRUCT})) {
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
  if (import_stmts_alias_.find(name_token->token_) !=
      import_stmts_alias_.end()) {
    throw error(name_token, "Duplicate import alias");
  }
  // We can see if we encountered this in pre_parsing
  // If we did, then we can use the pre-parsed data
  // during preparsing, this section will do nothing if there are no pre_parse stuff
  if (pre_parse_import_stmts_alias_.find(name_token->token_) !=
      pre_parse_import_stmts_alias_.end()) {
    auto pre_parse_import = pre_parse_import_stmts_alias_[name_token->token_];
    import_stmts_.emplace_back(pre_parse_import);
    import_stmts_alias_.insert({name_token->token_, pre_parse_import});
    return pre_parse_import;
  }
  auto st = pool_.c_import_stmt(import_token, imp_names, name_token, nullptr);
  auto import_ = dynamic_cast<import_stmt *>(st);
  import_stmts_.emplace_back(import_);
  import_stmts_alias_.insert({name_token->token_, import_});
  return st;
}
void parser::rescan_datatypes() {
  for (auto &dt : datatypes_from_modules_) {
    if (dt->const_unwrap()->is_builtin_or_primitive()) continue;
    auto import_alias = dt->module_;
    auto module_data = import_stmts_alias_[import_alias];
    dt->module_ = module_data->data_->filepath_.string();
  }
}
stmt *parser::runtimefeature_statement() {
  auto runtime_feature_kw = previous();
  auto cc = peek();
  if (cc->type_ != token_type::STRING &&
      cc->type_ != token_type::THREE_QUOTE_STRING) {
    throw error(runtime_feature_kw,
                "Expected runtimefeature statement to have a string literal.");
  }
  advance();
  consume_or_eof(token_type::NEW_LINE,
                 "Expect new line after value for runtimefeature statement.");
  return pool_.c_runtimefeature_stmt(runtime_feature_kw, cc);
}
stmt *parser::directive_statement() {
  // directive name="str" name2="str" ... (name|ccode) ("STR")? (NEW_LINE|EOF)
  auto directive_keyword = previous();
  std::initializer_list<token_type> name_or_ccode = {token_type::NAME,
                                                     token_type::KEYWORD_CCODE};
  token *name = nullptr;
  token *param_value = nullptr;
  std::vector<parameter> params{};
  while (match(name_or_ccode)) {
    name = previous();
    auto cc = peek();
    if (cc->type_ == token_type::EQ) {
      // this is a parameter
      consume(token_type::EQ, "Expected '=' after directive parameter name");
      // now consume a string
      param_value = consume_any_of(
          {token_type::STRING, token_type::THREE_QUOTE_STRING},
          "Expected string literal for directive parameter value");
      auto param = parameter{name, nullptr, param_value};
      params.emplace_back(param);
    } else {
      break;
    }
  }
  if (peek()->type_ == token_type::STRING ||
      peek()->type_ == token_type::THREE_QUOTE_STRING) {
    param_value = advance();
  } else {
    param_value = nullptr;
  }
  consume_or_eof(token_type::NEW_LINE,
                 "Expect new line after value for directive statement.");
  return pool_.c_directive_stmt(directive_keyword, params, name, param_value);
}
void parser::preprocess(macro_processor *mp, gc_pool<token> *token_pool) {
  step_1_parse_token_soup();
  /* step_2_initialize_env */ mp->init_env(filepath_, import_stmts_alias_);
  step_3_execute_macros(mp);
  step_4_expand_macros(mp, token_pool);
}
void parser::step_4_expand_macros(macro_processor *mp,
                                  gc_pool<token> *token_pool) {
  try {
    std::vector<token *> tokens_buffer{};
    for (auto stmt : soup_statements_) {
      if (stmt->get_type() == ast_type::STMT_MACROS) { continue; }
      if (stmt->get_type() == ast_type::STMT_DSL_MACRO) {
        auto dsl_stmt = dynamic_cast<dsl_macro_stmt *>(stmt);
        auto result = macro_expand(mp, dsl_stmt, token_pool);
        tokens_buffer.insert(tokens_buffer.end(), result.begin(), result.end());
      } else if (stmt->get_type() == ast_type::STMT_TOKEN_SOUP) {
        auto tokens = dynamic_cast<token_soup_stmt *>(stmt);
        tokens_buffer.insert(tokens_buffer.end(), tokens->soup_.begin(),
                             tokens->soup_.end());
      } else {
        // Cannot happen
        throw std::runtime_error("Unknown statement type");
      }
    }
    block_analyzer analyzer{tokens_buffer, token_pool};
    analyzer.analyze();
    if (!analyzer.errors_.empty()) {
      throw error(&analyzer.errors_.front().tok_,
                  analyzer.errors_.front().message_);
    }
    // Update tokens_ for the parse() & inject EOF
    tokens_ = analyzer.tokens_;
    if (tokens_.empty() || tokens_.back()->type_ != token_type::END_OF_FILE) {
      tokens_.emplace_back(
          analyzer.c_token(filepath_, 0, 0, "", token_type::END_OF_FILE));
    }
#ifdef PRINT_PREPROCESSOR_OUTPUT
    std::cout << "----------- Preprocessor output for " << filepath_
              << "-------------------" << std::endl;
    token *prev = nullptr;
    for (auto tk : tokens_) {
      if (prev != nullptr && prev->type_ != token_type::NAME) {
        std::cout << " ";
      }
      if (tk->type_ == token_type::NEW_LINE) {
        std::cout << "[NL]" << std::endl;
      } else if (tk->type_ == token_type::BA_INDENT) {
        std::cout << "`{";
      } else if (tk->type_ == token_type::BA_DEDENT) {
        std::cout << "}`";
      } else if (tk->type_ == token_type::END_OF_FILE) {
        std::cout << "[EOF]" << std::endl;
      } else if (tk->type_ == token_type::STRING) {
        std::cout << "\"" << tk->token_ << "\"";
      } else {
        std::cout << tk->token_;
      }
      prev = tk;
    }
    std::cout << "---------------- end ------------------ " << std::endl;
#endif
    current_ = 0;
    // Clear imports so parser can parse them again, and verify validity
    pre_parse_import_stmts_ = import_stmts_;
    pre_parse_import_stmts_alias_ = import_stmts_alias_;
    import_stmts_alias_.clear();
    import_stmts_.clear();
    // Validate tokens
    for (auto tk : tokens_) {
      if (!is_valid(tk->token_, tk->type_)) {
        throw error(tk, "Invalid token");
      }
    }
    // macro expanded
  } catch (parsing_error &err) {
    errors_.emplace_back(err.message_, err.tok_.file_, err.tok_.line_,
                         err.tok_.pos_);
  }
}
void parser::step_3_execute_macros(macro_processor *mp) {
  try {
    std::vector<macros_stmt *> macros_stmts{};
    for (auto macro_stmt : soup_statements_) {
      if (macro_stmt->get_type() == ast_type::STMT_MACROS) {
        macros_stmts.emplace_back(dynamic_cast<macros_stmt *>(macro_stmt));
      }
    }
    for (auto macros_statement : macros_stmts) {
      mp->execute(filepath_, macros_statement->lisp_code_, import_stmts_alias_);
    }
  } catch (parsing_error &err) {
    errors_.emplace_back(err.message_, err.tok_.file_, err.tok_.line_,
                         err.tok_.pos_);
  }
}
void parser::step_1_parse_token_soup() {
  try {
    std::vector<token *> tokens_buffer{};
    parse_token_soup(soup_statements_, tokens_buffer);
  } catch (parsing_error &err) {
    errors_.emplace_back(err.message_, err.tok_.file_, err.tok_.line_,
                         err.tok_.pos_);
  }
}
std::vector<token *> parser::macro_expand(macro_processor *mp,
                                          dsl_macro_stmt *dsl_macro,
                                          gc_pool<token> *token_pool) {
  std::vector<token *> tokens_buffer{};
  std::vector<stmt *> stmts{};
  std::vector<token *> result{};
  current_ = 0;
  tokens_ = dsl_macro->internal_soup_;
  if (tokens_.empty() || tokens_.back()->type_ != token_type::END_OF_FILE) {
    auto token = token_pool->allocate();
    token->type_ = token_type::END_OF_FILE;
    token->token_ = "";
    token->line_ = 0;
    token->pos_ = 0;
    token->file_ = filepath_;
    token->original_ = token->token_;
    tokens_.emplace_back(token);
  }
  while (!is_at_end_of_stream()) { parse_dsl_soup(stmts, tokens_buffer); }
  if (!tokens_buffer.empty()) {
    stmts.emplace_back(pool_.c_token_soup_stmt(tokens_buffer));
    tokens_buffer.clear();
  }
  for (auto st : stmts) {
    if (st->get_type() == ast_type::STMT_TOKEN_SOUP) {
      auto tokens = dynamic_cast<token_soup_stmt *>(st);
      result.insert(result.end(), tokens->soup_.begin(), tokens->soup_.end());
    } else if (st->get_type() == ast_type::STMT_DSL_MACRO) {
      auto dsl_stmt = dynamic_cast<dsl_macro_stmt *>(st);
      auto inner_result = macro_expand(mp, dsl_stmt, token_pool);
      result.insert(result.end(), inner_result.begin(), inner_result.end());
    } else {
      throw std::runtime_error("Unknown statement type");
    }
  }
  try {
    if (dsl_macro->name2_ == nullptr) {
      return mp->expand_dsl(filepath_, import_stmts_alias_,
                            dsl_macro->name_->token_, result, "",
                            dsl_macro->name_);
    } else {
      return mp->expand_dsl(filepath_, import_stmts_alias_,
                            dsl_macro->name2_->token_, result,
                            dsl_macro->name_->token_, dsl_macro->name2_);
    }
  } catch (parsing_error &err) {
    if (err.tok_.line_ != 0 || err.tok_.pos_ != 0) { throw; }
    throw parsing_error{err.message_,
                        ((dsl_macro->name2_ == nullptr) ? dsl_macro->name_
                                                        : dsl_macro->name2_)};
  }
}
void parser::parse_token_soup(std::vector<stmt *> &stmts,
                              std::vector<token *> &tokens_buffer) {
  // Token soup parsing
  // ==================
  // 4 different criteria here are
  // 1) macros!{} - execute once before macro expansion, as this is the definition of macros, returned tokens are ignored.
  // 2) name!{}   - DSL macros, execute during macro expansion (this is an expression, wrap it up)
  // 2.1) path.name!{} - imported DSL macro
  // 3) arbitrary tokens  - preserve as is
  // 4) import statements - extracted, and executed as needed during macros defining and macro expansion
  while (!is_at_end_of_stream()) {
    if (match({token_type::KEYWORD_MACROS})) {
      if (!tokens_buffer.empty()) {
        stmts.emplace_back(pool_.c_token_soup_stmt(tokens_buffer));
        tokens_buffer.clear();
      }
      auto macros_kw = previous();
      auto not_symbol =
          consume(token_type::NOT_SYMBOL, "Expect '!' after macros keyword.");
      auto curly_open = consume(token_type::CURLY_BRACKET_OPEN,
                                "Expect '{' after 'macros!'.");
      size_t level = 1;
      while (level > 0) {
        if (is_at_end_of_stream()) {
          throw error(peek(), "Expect '}' to close macros!{} block.");
        }
        auto tk = advance();
        if (tk->type_ == token_type::CURLY_BRACKET_OPEN) {
          level++;
        } else if (tk->type_ == token_type::CURLY_BRACKET_CLOSE) {
          level--;
        }
        if (level > 0) { tokens_buffer.emplace_back(tk); }
      }
      auto curly_close = previous();
      stmts.emplace_back(pool_.c_macros_stmt(macros_kw, not_symbol, curly_open,
                                             tokens_buffer, curly_close));
      tokens_buffer.clear();
    } else if (match({token_type::KEYWORD_IMPORT})) {
      size_t pos = current_;
      tokens_buffer.emplace_back(previous());
      this->import_statement();
      // Preserve import statements as is, so it can be parsed again!
      for (size_t i = pos; i < current_; i++) {
        tokens_buffer.emplace_back(tokens_[i]);
      }
    } else {
      parse_dsl_soup(stmts, tokens_buffer);
    }
  }
  if (!tokens_buffer.empty()) {
    stmts.emplace_back(pool_.c_token_soup_stmt(tokens_buffer));
    tokens_buffer.clear();
  }
}
void parser::parse_dsl_soup(std::vector<stmt *> &stmts,
                            std::vector<token *> &tokens_buffer) {
  if (match({token_type::NAME})) {
    // DSL macro has 2 forms
    // 1) name!{...}
    // 2) path.name!{...}
    auto name = previous();
    token *name2 = nullptr;
    token *dot = nullptr;
    token *not_symbol = nullptr;
    if (check(token_type::DOT) || check(token_type::NOT_SYMBOL)) {
      if (check(token_type::NOT_SYMBOL)) {
        not_symbol = advance();
      } else {
        dot = advance();
        if (check(token_type::NAME)) {
          name2 = advance();
          if (check(token_type::NOT_SYMBOL)) {
            not_symbol = advance();
          } else {
            tokens_buffer.emplace_back(name);
            tokens_buffer.emplace_back(dot);
            tokens_buffer.emplace_back(name2);
            return;
          }
        } else {
          tokens_buffer.emplace_back(name);
          if (dot) tokens_buffer.emplace_back(dot);
          return;
        }
      }
      if (check(token_type::CURLY_BRACKET_OPEN)) {
        if (!tokens_buffer.empty()) {
          stmts.emplace_back(pool_.c_token_soup_stmt(tokens_buffer));
          tokens_buffer.clear();
        }
        auto curly_open = advance();
        size_t level = 1;
        while (level > 0) {
          if (is_at_end_of_stream()) {
            throw error(peek(), "Expect '}' to close dsl!{} block.");
          }
          auto tk = advance();
          if (tk->type_ == token_type::CURLY_BRACKET_OPEN) {
            level++;
          } else if (tk->type_ == token_type::CURLY_BRACKET_CLOSE) {
            level--;
          }
          if (level > 0) { tokens_buffer.emplace_back(tk); }
        }
        auto curly_close = previous();
        stmts.emplace_back(pool_.c_dsl_macro_stmt(
            name, name2, not_symbol, curly_open, tokens_buffer, curly_close));
        tokens_buffer.clear();
      } else {
        tokens_buffer.emplace_back(name);
        if (dot) tokens_buffer.emplace_back(dot);
        if (name2) tokens_buffer.emplace_back(name2);
        if (not_symbol) tokens_buffer.emplace_back(not_symbol);
      }
    } else {
      tokens_buffer.emplace_back(name);
    }
  } else {
    tokens_buffer.emplace_back(advance());
  }
}
#pragma clang diagnostic pop
