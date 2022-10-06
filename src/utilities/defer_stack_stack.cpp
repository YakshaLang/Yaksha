// defer_stack_stack.cpp
#include "defer_stack_stack.h"
using namespace yaksha;
defer_stack_stack::defer_stack_stack() : defer_stack(ast_type::STMT_PASS) {
  defer_levels_.emplace_back(defer_stack{ast_type::STMT_PASS});
}
defer_stack_stack::~defer_stack_stack() = default;
void defer_stack_stack::push_defer_stack(ast_type stack_type) {
  defer_levels_.emplace_back(defer_stack{stack_type});
}
void defer_stack_stack::pop_defer_stack() {
  if (defer_levels_.size() > 1) { defer_levels_.pop_back(); }
}
void defer_stack_stack::push(defer_stmt *df) { defer_levels_.back().push(df); }
void defer_stack_stack::write(stmt_visitor *statement_visitor) {
  auto size = defer_levels_.size();
  if (size == 0) { return; }
  for (auto i = 0; i < size; i++) {
    auto index = size - 1 - i;
    auto stack = defer_levels_[index];
    stack.write(statement_visitor);
  }
}
void defer_stack_stack::write_one(stmt_visitor *statement_visitor) {
  if (defer_levels_.empty()) { return; }
  defer_levels_.back().write(statement_visitor);
}
void defer_stack_stack::write_upto_loop(stmt_visitor *statement_visitor) {
  auto size = defer_levels_.size();
  if (size == 0) { return; }
  for (auto i = 0; i < size; i++) {
    auto index = size - 1 - i;
    auto stack = defer_levels_[index];
    stack.write(statement_visitor);
    if (stack.stack_type_ == ast_type::STMT_WHILE) { break; }
  }
}
