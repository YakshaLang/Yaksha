// def_visitor.cpp
#include "def_visitor.h"
#include "compiler_utils.h"
using namespace yaksha;
def_visitor::def_visitor() = default;
def_visitor::~def_visitor() = default;
void def_visitor::visit_assign_expr(assign_expr *obj) {}
void def_visitor::visit_binary_expr(binary_expr *obj) {}
void def_visitor::visit_fncall_expr(fncall_expr *obj) {}
void def_visitor::visit_grouping_expr(grouping_expr *obj) {}
void def_visitor::visit_literal_expr(literal_expr *obj) {}
void def_visitor::visit_logical_expr(logical_expr *obj) {}
void def_visitor::visit_unary_expr(unary_expr *obj) {}
void def_visitor::visit_variable_expr(variable_expr *obj) {}
void def_visitor::visit_block_stmt(block_stmt *obj) {}
void def_visitor::visit_break_stmt(break_stmt *obj) {}
void def_visitor::visit_continue_stmt(continue_stmt *obj) {}
void def_visitor::visit_def_stmt(def_stmt *obj) {
  auto name = prefix(obj->name_->token_);
  if (has(name)) {
    error(obj->name_, "Critical!! Redefinition of function");
    return;
  }
  function_names_.push_back(name);
  functions_.insert({name, obj});
}
void def_visitor::visit_expression_stmt(expression_stmt *obj) {}
void def_visitor::visit_if_stmt(if_stmt *obj) {}
void def_visitor::visit_let_stmt(let_stmt *obj) {}
void def_visitor::visit_pass_stmt(pass_stmt *obj) {}
void def_visitor::visit_print_stmt(print_stmt *obj) {}
void def_visitor::visit_return_stmt(return_stmt *obj) {}
void def_visitor::visit_while_stmt(while_stmt *obj) {}
void def_visitor::extract(const std::vector<stmt *> &statements) {
  for (auto st : statements) { st->accept(this); }
}
def_stmt *def_visitor::get(const std::string &prefixed_name) {
  if (has(prefixed_name)) { return functions_[prefixed_name]; }
  return nullptr;
}
bool def_visitor::has(const std::string &prefixed_name) {
  return functions_.find(prefixed_name) != functions_.end();
}
void def_visitor::error(token *tok, const std::string &message) {
  auto err = parsing_error{message, tok};
  errors_.emplace_back(err);
}
void def_visitor::visit_defer_stmt(defer_stmt *obj) {}
