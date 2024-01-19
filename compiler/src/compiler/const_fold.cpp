// const_fold.cpp
#include "const_fold.h"
using namespace yaksha;
const_fold::const_fold(ast_pool *ast_pool, ykdt_pool *dt_pool)
    : statement_stack_(), global_statements_(), ast_pool_(ast_pool),
      dt_pool_(dt_pool), context_pool_(), internal_token_pool_() {
  // ---
  statement_stack_.emplace_back(&global_statements_);
};
const_fold::~const_fold() {
  for (auto &it : context_pool_) { delete it; }
  context_pool_.clear();
  for (auto &it : internal_token_pool_) { delete it; }
  internal_token_pool_.clear();
}
void const_fold::visit_assign_expr(assign_expr *obj) {
  obj->right_->accept(this);
  //  auto val = pop_last();
}
// ----------------------------------------------------
//  _______       ___    ___  ________   ________
// |\  ___ \     |\  \  /  /||\   __  \ |\   __  \-
// \ \   __/|    \ \  \/  / /\ \  \|\  \\ \  \|\  \-
//  \ \  \_|/__   \ \    / /  \ \   ____\\ \   _  _\-
//   \ \  \_|\ \   /     \/    \ \  \___| \ \  \\  \|-
//    \ \_______\ /  /\   \     \ \__\     \ \__\\ _\-
//     \|_______|/__/ /\ __\     \|__|      \|__|\|__|-
//               |__|/ \|__|
// ----------------------------------------------------
void const_fold::visit_assign_arr_expr(assign_arr_expr *obj) {}
void const_fold::visit_assign_member_expr(assign_member_expr *obj) {}
void const_fold::visit_binary_expr(binary_expr *obj) {}
void const_fold::visit_curly_call_expr(curly_call_expr *obj) {}
void const_fold::visit_fncall_expr(fncall_expr *obj) {}
void const_fold::visit_get_expr(get_expr *obj) {}
void const_fold::visit_grouping_expr(grouping_expr *obj) {}
void const_fold::visit_literal_expr(literal_expr *obj) {}
void const_fold::visit_logical_expr(logical_expr *obj) {}
void const_fold::visit_macro_call_expr(macro_call_expr *obj) {}
void const_fold::visit_set_expr(set_expr *obj) {}
void const_fold::visit_square_bracket_access_expr(
    square_bracket_access_expr *obj) {}
void const_fold::visit_square_bracket_set_expr(square_bracket_set_expr *obj) {}
void const_fold::visit_unary_expr(unary_expr *obj) {}
void const_fold::visit_variable_expr(variable_expr *obj) {}
// ----------------------------------------------------
//  ________   _________   _____ ______    _________
// |\   ____\ |\___   ___\|\   _ \  _   \ |\___   ___\-
// \ \  \___|_\|___ \  \_|\ \  \\\__\ \  \\|___ \  \_|
//  \ \_____  \    \ \  \  \ \  \\|__| \  \    \ \  \-
//   \|____|\  \    \ \  \  \ \  \    \ \  \    \ \  \-
//     ____\_\  \    \ \__\  \ \__\    \ \__\    \ \__\-
//    |\_________\    \|__|   \|__|     \|__|     \|__|-
//    \|_________|
// ----------------------------------------------------
void const_fold::visit_block_stmt(block_stmt *obj) {
  // If we visit a block statement that means we need to ensure tha the all sub statements are captured
  std::vector<const_fold_context *> block_statements{};
  statement_stack_.emplace_back(&block_statements);
  for (stmt *st : obj->statements_) { st->accept(this); }
  statement_stack_.pop_back();
  statement_stack_.back()->emplace_back(
      wrap(ast_pool_->c_block_stmt(unwrap_vector_stmt(block_statements))));
}
void const_fold::visit_break_stmt(break_stmt *obj) {
  statement_stack_.back()->emplace_back(wrap(obj));
}
void const_fold::visit_ccode_stmt(ccode_stmt *obj) {
  statement_stack_.back()->emplace_back(wrap(obj));
}
void const_fold::visit_cfor_stmt(cfor_stmt *obj) {
  statement_stack_.back()->emplace_back(wrap(obj));
}
void const_fold::visit_class_stmt(class_stmt *obj) {
  statement_stack_.back()->emplace_back(wrap(obj));
}
void const_fold::visit_compins_stmt(compins_stmt *obj) {
  statement_stack_.back()->emplace_back(wrap(obj));
}
void const_fold::visit_const_stmt(const_stmt *obj) {
  statement_stack_.back()->emplace_back(wrap(obj));
}
void const_fold::visit_continue_stmt(continue_stmt *obj) {
  statement_stack_.back()->emplace_back(wrap(obj));
}
void const_fold::visit_def_stmt(def_stmt *obj) {
  statement_stack_.back()->emplace_back(wrap(obj));
}
void const_fold::visit_defer_stmt(defer_stmt *obj) {
  statement_stack_.back()->emplace_back(wrap(obj));
}
void const_fold::visit_del_stmt(del_stmt *obj) {
  statement_stack_.back()->emplace_back(wrap(obj));
}
void const_fold::visit_enum_stmt(enum_stmt *obj) {
  statement_stack_.back()->emplace_back(wrap(obj));
}
void const_fold::visit_expression_stmt(expression_stmt *obj) {
  statement_stack_.back()->emplace_back(wrap(obj));
}
void const_fold::visit_foreach_stmt(foreach_stmt *obj) {
  statement_stack_.back()->emplace_back(wrap(obj));
}
void const_fold::visit_forendless_stmt(forendless_stmt *obj) {
  statement_stack_.back()->emplace_back(wrap(obj));
}
void const_fold::visit_if_stmt(if_stmt *obj) {
  statement_stack_.back()->emplace_back(wrap(obj));
}
void const_fold::visit_import_stmt(import_stmt *obj) {
  statement_stack_.back()->emplace_back(wrap(obj));
}
void const_fold::visit_let_stmt(let_stmt *obj) {
  statement_stack_.back()->emplace_back(wrap(obj));
}
void const_fold::visit_nativeconst_stmt(nativeconst_stmt *obj) {
  statement_stack_.back()->emplace_back(wrap(obj));
}
void const_fold::visit_pass_stmt(pass_stmt *obj) {
  statement_stack_.back()->emplace_back(wrap(obj));
}
void const_fold::visit_return_stmt(return_stmt *obj) {
  statement_stack_.back()->emplace_back(wrap(obj));
}
void const_fold::visit_runtimefeature_stmt(runtimefeature_stmt *obj) {
  statement_stack_.back()->emplace_back(wrap(obj));
}
void const_fold::visit_union_stmt(union_stmt *obj) { // this feature is not implemented yet
  statement_stack_.back()->emplace_back(wrap(obj));
}
void const_fold::visit_while_stmt(while_stmt *obj) {
  statement_stack_.back()->emplace_back(wrap(obj));
}
const_fold_context *const_fold::wrap(stmt *statement) {
  auto con = new_context();
  con->context_type_ = const_fold_context_type::CFT_STMT;
  con->expr_or_stmt_.stmt_val_ = statement;
  return con;
}
const_fold_context *const_fold::wrap(expr *expression) {
  auto con = new_context();
  con->context_type_ = const_fold_context_type::CFT_EXPR;
  con->expr_or_stmt_.expr_val_ = expression;
  return con;
}
const_fold_context *const_fold::new_context() {
  auto con = new const_fold_context();
  con->fold_type_ = const_fold_type::CFT_UNKNOWN;
  context_pool_.emplace_back(con);
  return con;
}
std::vector<stmt *> const_fold::unwrap_vector_stmt(
    const std::vector<const_fold_context *> &to_unwrap) {
  std::vector<stmt *> unwrapped{};
  for (auto &it : to_unwrap) {
    if (it->context_type_ == const_fold_context_type::CFT_STMT) {
      unwrapped.emplace_back(it->expr_or_stmt_.stmt_val_);
    }
  }
  return unwrapped;
}
