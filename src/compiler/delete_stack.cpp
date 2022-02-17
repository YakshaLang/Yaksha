// delete_stack.cpp
#include "delete_stack.h"
using namespace yaksha;
delete_stack::delete_stack() = default;
delete_stack::~delete_stack() = default;
void delete_stack::push(const std::string &name, const std::string &free_code) {
  del_stack_.push_back(name);
  del_map_.insert({name, free_code});
}
void delete_stack::remove(const std::string &name) {
  auto found = del_map_.find(name);
  if (found == del_map_.end()) { return; }
  del_map_.erase(name);
  del_stack_.erase(std::remove(del_stack_.begin(), del_stack_.end(), name),
                   del_stack_.end());
}
void delete_stack::write(std::stringstream &target, int indent_level) {
  this->write(target, indent_level, "");
}
void delete_stack::write(std::stringstream &target, int indent_level,
                         const std::string &return_name) {
  auto size = del_stack_.size();
  if (size == 0) { return; }
  for (auto i = 0; i < size; i++) {
    auto index = size - 1 - i;
    auto name = del_stack_[index];
    if (!return_name.empty() && name == return_name) { continue; }
    write_indent(target, indent_level);
    target << del_map_[name];
    write_end_statement(target);
  }
}
void delete_stack::write_indent(std::stringstream &target, int indent_level) {
  for (int i = 0; i < indent_level; i++) { target << "    "; }
}
void delete_stack::write_end_statement(std::stringstream &target) {
  target << ";\n";
}
