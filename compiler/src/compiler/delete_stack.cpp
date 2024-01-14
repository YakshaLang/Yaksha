// ==============================================================================================
// ╦  ┬┌─┐┌─┐┌┐┌┌─┐┌─┐    Yaksha Programming Language
// ║  ││  ├┤ │││└─┐├┤     is Licensed with GPLv3 + extra terms. Please see below.
// ╩═╝┴└─┘└─┘┘└┘└─┘└─┘
// Note: libs - MIT license, runtime/3rd - various
// ==============================================================================================
// GPLv3:
//
// Yaksha - Programming Language.
// Copyright (C) 2020 - 2023 Bhathiya Perera
//
// This program is free software: you can redistribute it and/or modify it under the terms
// of the GNU General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with this program.
// If not, see https://www.gnu.org/licenses/.
//
// ==============================================================================================
// Additional Terms:
//
// Please note that any commercial use of the programming language's compiler source code
// (everything except compiler/runtime, compiler/libs and compiler/3rd) require a written agreement
// with author of the language (Bhathiya Perera).
//
// If you are using it for an open source project, please give credits.
// Your own project must use GPLv3 license with these additional terms.
//
// You may use programs written in Yaksha/YakshaLisp for any legal purpose
// (commercial, open-source, closed-source, etc) as long as it agrees
// to the licenses of linked runtime libraries (see compiler/runtime/README.md).
//
// ==============================================================================================
// delete_stack.cpp
#include "delete_stack.h"
using namespace yaksha;
delete_stack::delete_stack(ast_type stack_type) : stack_type_(stack_type) {}
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
