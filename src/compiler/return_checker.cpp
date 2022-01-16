// return_checker.cpp
#include "return_checker.h"
using namespace yaksha;
return_checker::~return_checker() = default;
void return_checker::visit_assign_expr(assign_expr *obj) {}
void return_checker::visit_binary_expr(binary_expr *obj) {}
void return_checker::visit_fncall_expr(fncall_expr *obj) {}
void return_checker::visit_grouping_expr(grouping_expr *obj) {}
void return_checker::visit_literal_expr(literal_expr *obj) {}
void return_checker::visit_logical_expr(logical_expr *obj) {}
void return_checker::visit_unary_expr(unary_expr *obj) {}
void return_checker::visit_variable_expr(variable_expr *obj) {}
void return_checker::visit_block_stmt(block_stmt *obj) {
  if (obj->statements_.back()->get_type() == ast_type::STMT_RETURN) {
    push_return_found();
    return;
  }
  for (auto st: obj->statements_) {
    st->accept(this);
  }
}
void return_checker::visit_break_stmt(break_stmt *obj) {}
void return_checker::visit_continue_stmt(continue_stmt *obj) {}
void return_checker::visit_def_stmt(def_stmt *obj) {
  obj->function_body_->accept(this);
}
void return_checker::visit_defer_stmt(defer_stmt *obj) {}
void return_checker::visit_expression_stmt(expression_stmt *obj) {}
void return_checker::visit_if_stmt(if_stmt *obj) {
  obj->if_branch_->accept(this);
  if (peek_return_found()) {
    pop_return_found();
  } else {
    return;
  }
  if (obj->else_branch_ != nullptr) {
    obj->else_branch_->accept(this);
  }
}
void return_checker::visit_let_stmt(let_stmt *obj) {}
void return_checker::visit_pass_stmt(pass_stmt *obj) {}
void return_checker::visit_print_stmt(print_stmt *obj) {}
void return_checker::visit_return_stmt(return_stmt *obj) {
  push_return_found();
}
void return_checker::visit_while_stmt(while_stmt *obj) {
  obj->while_body_->accept(this);
}
void return_checker::check(def_visitor& functions) {
  for (const auto &function_name : functions.function_names_) {
    // TODO handle void/None returning functions
    auto function_def = functions.get(function_name);
    this->visit_def_stmt(function_def);
    if (!peek_return_found()) {
      error(function_def->name_, "This function does not return.");
    }
    return_found_.clear();
  }
}
void return_checker::error(token *tok, const std::string &message) {
  auto err = parsing_error{message, tok};
  errors_.emplace_back(err);
}
void return_checker::error(const std::string &message) {
  auto err = parsing_error{message, "", 0, 0};
  err.token_set_ = false;
  errors_.emplace_back(err);
}
void return_checker::push_return_found() { return_found_.push_back(true); }
bool return_checker::peek_return_found() {
  if (return_found_.empty()) { return false; }
  return return_found_.back();
}
void return_checker::pop_return_found() { return_found_.pop_back(); }
return_checker::return_checker() = default;
