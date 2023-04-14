// defer_stack.cpp
#include "defer_stack.h"
using namespace yaksha;
defer_stack::defer_stack(ast_type stack_type) : stack_type_(stack_type) {}
defer_stack::~defer_stack() = default;
void defer_stack::write(stmt_visitor *visitor) {
  auto size = del_stack_.size();
  if (size == 0) { return; }
  for (auto i = 0; i < size; i++) {
    auto index = size - 1 - i;
    auto expression_to_write = del_stack_[index];
    if (expression_to_write->expression_ != nullptr) {
      auto st = expression_stmt{expression_to_write->expression_};
      visitor->visit_expression_stmt(&st);
    } else {
      expression_to_write->del_statement_->accept(visitor);
    }
  }
}
void defer_stack::push(defer_stmt *df) { del_stack_.push_back(df); }
