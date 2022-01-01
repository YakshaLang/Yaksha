// environment_stack.cpp
#include "environment_stack.h"
#include <utility>
using namespace yaksha;
environment_stack::environment_stack() {
  // Create global environment
  scope_stack_.emplace_back(environment());
};
environment_stack::~environment_stack() = default;
bool environment_stack::is_defined(const std::string &name) {
  if (scope_stack_.front().is_defined(name)) { return true; }
  if (!has_inner_scope()) { return false; }
  return peek().is_defined(name);
}
void environment_stack::define(const std::string &name, ykobject data) {
  peek().define(name, data);
}
void environment_stack::define_global(const std::string &name, ykobject data) {
  scope_stack_.front().define(name, std::move(data));
}
void environment_stack::assign(const std::string &name, ykobject data) {
  peek().assign(name, data);
}
ykobject &environment_stack::get(const std::string &name) {
  if (scope_stack_.front().is_defined(name)) {
    return scope_stack_.front().get(name);
  }
  return peek().get(name);
}
void environment_stack::push() { scope_stack_.emplace_back(environment()); }
void environment_stack::pop() {
  if (has_inner_scope()) { scope_stack_.pop_back(); }
}
bool environment_stack::has_inner_scope() { return scope_stack_.size() > 1; }
environment &environment_stack::peek() { return scope_stack_.back(); }
