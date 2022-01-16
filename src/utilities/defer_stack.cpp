// defer_stack.cpp
#include "defer_stack.h"
using namespace yaksha;
defer_stack::defer_stack() = default;
defer_stack::~defer_stack() = default;
void defer_stack::write(stmt_visitor* visitor) {
  auto size = del_stack_.size();
  if (size == 0) { return; }
  for (auto i = 0; i < size; i++) {
    auto index = size - 1 - i;
    auto expression_to_write = del_stack_[index];
    auto st = expression_stmt{expression_to_write};
    visitor->visit_expression_stmt(&st);
  }
}
void defer_stack::push(expr *expression) {
  del_stack_.push_back(expression);
}
