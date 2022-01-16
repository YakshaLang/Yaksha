// delete_stack_stack.cpp
#include "delete_stack_stack.h"
using namespace yaksha;
delete_stack_stack::delete_stack_stack() {
  delete_levels_.emplace_back(delete_stack{});
}
delete_stack_stack::~delete_stack_stack() = default;
void delete_stack_stack::push(const std::string &name,
                              const std::string &free_code) {
  delete_levels_.back().push(name, free_code);
}
void delete_stack_stack::remove(const std::string &name) {
  auto size = delete_levels_.size();
  if (size == 0) { return; }
  for (auto i = 0; i < size; i++) {
    auto index = size - 1 - i;
    auto stack = delete_levels_[index];
    stack.remove(name);
  }
}
void delete_stack_stack::write(std::stringstream &target, int indent_level) {
  this->write(target, indent_level, "");
}
void delete_stack_stack::write(std::stringstream &target, int indent_level,
                               const std::string &return_name) {
  auto size = delete_levels_.size();
  if (size == 0) { return; }
  for (auto i = 0; i < size; i++) {
    auto index = size - 1 - i;
    auto stack = delete_levels_[index];
    stack.write(target, indent_level, return_name);
  }
}
void delete_stack_stack::push_delete_stack() {
  delete_levels_.emplace_back(delete_stack{});
}
void delete_stack_stack::pop_delete_stack() {
  if (delete_levels_.size() > 1) { delete_levels_.pop_back(); }
}
void delete_stack_stack::write_one(std::stringstream &target,
                                   int indent_level) {
  this->write_one(target, indent_level, "");
}
void delete_stack_stack::write_one(std::stringstream &target, int indent_level,
                                   const std::string &return_name) {
  if (delete_levels_.empty()) { return; }
  delete_levels_.back().write(target, indent_level, return_name);
}
