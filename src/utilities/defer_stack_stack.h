// defer_stack_stack.h
#ifndef DEFER_STACK_STACK_H
#define DEFER_STACK_STACK_H
#include "defer_stack.h"
namespace yaksha {
  struct defer_stack_stack : defer_stack {
    defer_stack_stack();
    void push_defer_stack();
    void pop_defer_stack();
    ~defer_stack_stack() override;
    void push(defer_stmt *df) override;
    void write(stmt_visitor *statement_visitor) override;
    void write_one(stmt_visitor *statement_visitor);

private:
    std::vector<defer_stack> defer_levels_{};
  };
}// namespace yaksha
#endif
