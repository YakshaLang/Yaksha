// desugaring_compiler.cpp
#include "desugaring_compiler.h"
#include "compiler/compiler.h"
using namespace yaksha;
desugaring_compiler::desugaring_compiler(ast_pool *ast_pool_obj,
                                         ykdt_pool *dt_pool_obj)
    : statement_stack_(), global_statements_(), pre_continue_stack_(),
      ast_pool_(ast_pool_obj), dt_pool_(dt_pool_obj), true_token_(new token{}),
      while_token_(new token{}), break_token_(new token{}),
      if_token_(new token{}), not_token_(new token{}),
      paren_token_(new token{}), ccode_token_(new token{}),
      less_token_(new token{}), plus_eq_token_(new token{}),
      compiler_obj_(nullptr) {
  // -- True --
  true_token_->token_ = "True";
  true_token_->file_ = "syntax-sugar";
  true_token_->original_ = "True";
  true_token_->line_ = 0;
  true_token_->pos_ = 0;
  true_token_->type_ = token_type::KEYWORD_TRUE;
  internal_token_pool_.push_back(true_token_);
  // -- while --
  while_token_->token_ = "while";
  while_token_->file_ = "syntax-sugar";
  while_token_->original_ = "while";
  while_token_->line_ = 0;
  while_token_->pos_ = 0;
  while_token_->type_ = token_type::KEYWORD_WHILE;
  internal_token_pool_.push_back(while_token_);
  // -- break --
  break_token_->token_ = "break";
  break_token_->file_ = "desugar";
  break_token_->original_ = "break";
  break_token_->line_ = 0;
  break_token_->pos_ = 0;
  break_token_->type_ = token_type::KEYWORD_BREAK;
  internal_token_pool_.push_back(break_token_);
  // -- if --
  if_token_->token_ = "if";
  if_token_->file_ = "desugar";
  if_token_->original_ = "if";
  if_token_->line_ = 0;
  if_token_->pos_ = 0;
  if_token_->type_ = token_type::KEYWORD_IF;
  internal_token_pool_.push_back(if_token_);
  // -- not --
  not_token_->token_ = "not";
  not_token_->file_ = "desugar";
  not_token_->original_ = "not";
  not_token_->line_ = 0;
  not_token_->pos_ = 0;
  not_token_->type_ = token_type::KEYWORD_NOT;
  internal_token_pool_.push_back(not_token_);
  // -- paren open --
  paren_token_->token_ = "(";
  paren_token_->file_ = "desugar";
  paren_token_->original_ = "(";
  paren_token_->line_ = 0;
  paren_token_->pos_ = 0;
  paren_token_->type_ = token_type::PAREN_OPEN;
  internal_token_pool_.push_back(paren_token_);
  // -- ccode open --
  ccode_token_->token_ = "ccode";
  ccode_token_->file_ = "desugar";
  ccode_token_->original_ = "ccode";
  ccode_token_->line_ = 0;
  ccode_token_->pos_ = 0;
  ccode_token_->type_ = token_type::KEYWORD_CCODE;
  internal_token_pool_.push_back(ccode_token_);
  // -- paren less --
  less_token_->token_ = "<";
  less_token_->file_ = "desugar";
  less_token_->original_ = "<";
  less_token_->line_ = 0;
  less_token_->pos_ = 0;
  less_token_->type_ = token_type::LESS;
  internal_token_pool_.push_back(less_token_);
  // -- paren plus_eq --
  plus_eq_token_->token_ = "+=";
  plus_eq_token_->file_ = "desugar";
  plus_eq_token_->original_ = "+=";
  plus_eq_token_->line_ = 0;
  plus_eq_token_->pos_ = 0;
  plus_eq_token_->type_ = token_type::PLUS_EQ;
  internal_token_pool_.push_back(plus_eq_token_);
  // ---
  statement_stack_.emplace_back(&global_statements_);
}
desugaring_compiler::~desugaring_compiler() {
  for (token *t : internal_token_pool_) { delete t; }
}
void desugaring_compiler::visit_block_stmt(block_stmt *obj) {
  std::vector<stmt *> block_statements{};
  statement_stack_.emplace_back(&block_statements);
  for (stmt *st : obj->statements_) { st->accept(this); }
  statement_stack_.pop_back();
  statement_stack_.back()->emplace_back(
      ast_pool_->c_block_stmt(block_statements));
}
void desugaring_compiler::visit_break_stmt(break_stmt *obj) {
  statement_stack_.back()->emplace_back(obj);
}
void desugaring_compiler::visit_ccode_stmt(ccode_stmt *obj) {
  statement_stack_.back()->emplace_back(obj);
}
void desugaring_compiler::visit_class_stmt(class_stmt *obj) {
  statement_stack_.back()->emplace_back(obj);
}
void desugaring_compiler::visit_compins_stmt(compins_stmt *obj) {
  // Only used in compiler
  // Preserve if present
  statement_stack_.back()->emplace_back(obj);
}
void desugaring_compiler::visit_const_stmt(const_stmt *obj) {
  statement_stack_.back()->emplace_back(obj);
}
void desugaring_compiler::visit_continue_stmt(continue_stmt *obj) {
  if (pre_continue_stack_.back() != nullptr) {
    statement_stack_.back()->emplace_back(pre_continue_stack_.back());
  }
  statement_stack_.back()->emplace_back(obj);
}
void desugaring_compiler::visit_def_stmt(def_stmt *obj) {
  auto def = ast_pool_->c_def_stmt(
                          obj->name_, obj->params_, desugar(obj->function_body_), obj->return_type_,
                          obj->annotations_);
  def->hits_ = obj->hits_; // preserve hit count
  statement_stack_.back()->emplace_back(def);
}
void desugaring_compiler::visit_defer_stmt(defer_stmt *obj) {
  statement_stack_.back()->emplace_back(obj);
}
void desugaring_compiler::visit_del_stmt(del_stmt *obj) {
  statement_stack_.back()->emplace_back(obj);
}
void desugaring_compiler::visit_expression_stmt(expression_stmt *obj) {
  statement_stack_.back()->emplace_back(obj);
}
void desugaring_compiler::visit_if_stmt(if_stmt *obj) {
  // nest
  statement_stack_.back()->emplace_back(ast_pool_->c_if_stmt(
      obj->if_keyword_, obj->expression_, desugar(obj->if_branch_),
      obj->else_keyword_, desugar(obj->else_branch_)));
}
void desugaring_compiler::visit_import_stmt(import_stmt *obj) {
  statement_stack_.back()->emplace_back(obj);
}
void desugaring_compiler::visit_let_stmt(let_stmt *obj) {
  statement_stack_.back()->emplace_back(obj);
}
void desugaring_compiler::visit_nativeconst_stmt(nativeconst_stmt *obj) {
  statement_stack_.back()->emplace_back(obj);
}
void desugaring_compiler::visit_pass_stmt(pass_stmt *obj) {
  statement_stack_.back()->emplace_back(obj);
}
void desugaring_compiler::visit_return_stmt(return_stmt *obj) {
  statement_stack_.back()->emplace_back(obj);
}
void desugaring_compiler::visit_runtimefeature_stmt(runtimefeature_stmt *obj) {
  statement_stack_.back()->emplace_back(obj);
}
void desugaring_compiler::visit_while_stmt(while_stmt *obj) {
  // desugar
  // if expression is literal
  //    True / False -> just desugar body
  //    (False can be removed, but we don't want to handle that optimization here)
  if (obj->expression_->get_type() == ast_type::EXPR_LITERAL) {
    pre_continue_stack_.emplace_back(nullptr);
    statement_stack_.back()->emplace_back(ast_pool_->c_while_stmt(
        obj->while_keyword_, obj->expression_, desugar(obj->while_body_)));
    pre_continue_stack_.pop_back();
    return;
  }
  // if the expression is not a literal
  //    while True:
  //       if (not (expr)):
  //          break
  //       rest of the statements
  std::vector<stmt *> break_block{};
  break_block.emplace_back(ast_pool_->c_break_stmt(break_token_));
  // Reverse of current expression is needed to add an if block at the top of while
  auto reverse_expr = ast_pool_->c_unary_expr(
      not_token_, ast_pool_->c_grouping_expr(obj->expression_));
  // Simple if statement with reverse expr and (only) break statement
  auto if_st = ast_pool_->c_if_stmt(if_token_, reverse_expr,
                                    ast_pool_->c_block_stmt(break_block),
                                    nullptr, nullptr);
  // Combine old while body with if block -> new_while_body
  std::vector<stmt *> new_while_body{};
  new_while_body.emplace_back(if_st);
  auto *old_body = dynamic_cast<block_stmt *>(obj->while_body_);
  for (stmt *st : old_body->statements_) { new_while_body.emplace_back(st); }
  // Add in desugared while statement after desugaring the body
  pre_continue_stack_.emplace_back(nullptr);
  auto simplified_while = ast_pool_->c_while_stmt(
      obj->while_keyword_, ast_pool_->c_literal_expr(true_token_),
      desugar(ast_pool_->c_block_stmt(new_while_body)));
  pre_continue_stack_.pop_back();
  statement_stack_.back()->emplace_back(simplified_while);
}
void desugaring_compiler::visit_foreach_stmt(foreach_stmt *obj) {
  // desugar
  auto array_holder = compiler_obj_->temp("yy__") + "t";
  auto array_holder_tok = create_name(array_holder);
  auto counter = compiler_obj_->temp("yy__") + "t";
  auto counter_tok = create_name(counter);
  auto length_holder = compiler_obj_->temp("yy__") + "t";
  auto length_holder_tok = create_name(length_holder);
  auto prefixed_name = compiler_obj_->prefix_token(obj->name_);
  // -----------------------------------------
  // New statement -> array_holder: Array[T] = expression
  ykdatatype *arr = dt_pool_->create("Array");
  arr->args_.push_back(obj->data_type_);
  statement_stack_.back()->emplace_back(
      ast_pool_->c_let_stmt(array_holder_tok, arr, obj->expression_));
  // New statement -> counter: int = 0
  statement_stack_.back()->emplace_back(ast_pool_->c_let_stmt(
      counter_tok, dt_pool_->create("int"),
      ast_pool_->c_literal_expr(create_int_literal("0"))));
  // New statement -> length: int = len(array_holder)
  auto arr_holder_arg = std::vector<expr *>{};
  arr_holder_arg.push_back(ast_pool_->c_variable_expr(array_holder_tok));
  statement_stack_.back()->emplace_back(ast_pool_->c_let_stmt(
      length_holder_tok, dt_pool_->create("int"),
      ast_pool_->c_fncall_expr(ast_pool_->c_variable_expr(create_name("len")),
                               paren_token_, arr_holder_arg)));
  // While body
  std::vector<stmt *> new_while_body{};
  // While body    ->     #yaksha-define yy__item h__array[h__counter]
  // While body    ->     expose yy__item ==> obj->name + obj->data_type
  const std::string desugar_rewrite = "(" + array_holder + "[" + counter + "])";
  new_while_body.emplace_back(ast_pool_->c_compins_stmt(
      obj->name_, obj->data_type_, create_str_literal(desugar_rewrite), nullptr,
      nullptr));
  // Create counter += 1 statement
  auto counter_incr = ast_pool_->c_expression_stmt(ast_pool_->c_assign_expr(
      counter_tok, plus_eq_token_,
      ast_pool_->c_literal_expr(create_int_literal("1")), false));
  //                      desugar body (add counter += 1 before continue)
  pre_continue_stack_.emplace_back(counter_incr);
  auto desugared = desugar(obj->for_body_);
  pre_continue_stack_.pop_back();
  auto *desugard_for_body = dynamic_cast<block_stmt *>(desugared);
  for (stmt *st : desugard_for_body->statements_) {
    new_while_body.emplace_back(st);
  }
  // While body    ->     counter += 1
  new_while_body.emplace_back(counter_incr);
  // New statement -> while counter < length: + While body
  auto counter_less_length = ast_pool_->c_binary_expr(
      ast_pool_->c_variable_expr(counter_tok), less_token_,
      ast_pool_->c_variable_expr(length_holder_tok));
  auto desugared_while =
      ast_pool_->c_while_stmt(while_token_, counter_less_length,
                              ast_pool_->c_block_stmt(new_while_body));
  // Desugar again using while desugar!
  desugared_while->accept(this);
}
void desugaring_compiler::visit_forendless_stmt(forendless_stmt *obj) {
  // convert to a while True:
  pre_continue_stack_.emplace_back(nullptr);
  auto while_stmt = ast_pool_->c_while_stmt(
      obj->for_keyword_, ast_pool_->c_literal_expr(true_token_),
      desugar(obj->for_body_));
  pre_continue_stack_.pop_back();
  statement_stack_.back()->emplace_back(desugar(while_stmt));
}
stmt *desugaring_compiler::desugar(stmt *obj) {
  if (obj == nullptr) return nullptr;
  obj->accept(this);
  auto st = statement_stack_.back()->back();
  statement_stack_.back()->pop_back();
  return st;
}
std::vector<stmt *>
desugaring_compiler::desugar(const std::vector<stmt *> &statements,
                             compiler *compiler_obj) {
  this->compiler_obj_ = compiler_obj;
  for (stmt *st : statements) { st->accept(this); }
  return global_statements_;
}
// ----------
token *desugaring_compiler::create_name(const std::string &name) {
  auto *temp_token = new token{};
  temp_token->token_ = name;
  temp_token->file_ = "syntax-sugar";
  temp_token->original_ = name;
  temp_token->line_ = 0;
  temp_token->pos_ = 0;
  temp_token->type_ = token_type::NAME;
  internal_token_pool_.push_back(temp_token);
  return temp_token;
}
token *desugaring_compiler::create_int_literal(const std::string &lit) {
  auto *temp_token = new token{};
  temp_token->token_ = lit;
  temp_token->file_ = "desugar";
  temp_token->original_ = lit;
  temp_token->line_ = 0;
  temp_token->pos_ = 0;
  temp_token->type_ = token_type::INTEGER_DECIMAL;
  internal_token_pool_.push_back(temp_token);
  return temp_token;
}
token *desugaring_compiler::create_str_literal(
    const std::string &string_literal_content) {
  auto *temp_token = new token{};
  temp_token->token_ = string_literal_content;
  temp_token->file_ = "desugar";
  temp_token->original_ = string_literal_content;
  temp_token->line_ = 0;
  temp_token->pos_ = 0;
  temp_token->type_ = token_type::STRING;
  internal_token_pool_.push_back(temp_token);
  return temp_token;
}
