// defer_stack.h
#ifndef DEFER_STACK_H
#define DEFER_STACK_H
#include <algorithm>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "ast/ast.h"
namespace yaksha {
  struct defer_stack {
    defer_stack();
    virtual ~defer_stack();
    virtual void push(expr* expression);
    virtual void write(stmt_visitor* statement_visitor);

private:
    std::vector<expr*> del_stack_{};
  };
}// namespace yaksha
#endif
