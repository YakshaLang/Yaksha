// ==============================================================================================
// ╦  ┬┌─┐┌─┐┌┐┌┌─┐┌─┐    Yaksha Programming Language
// ║  ││  ├┤ │││└─┐├┤     is Licensed with GPLv3 + exta terms. Please see below.
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
// delete_stack_stack.cpp
#include "delete_stack_stack.h"
using namespace yaksha;
delete_stack_stack::delete_stack_stack() : delete_stack(ast_type::STMT_PASS) {
  delete_levels_.emplace_back(delete_stack{ast_type::STMT_PASS});
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
void delete_stack_stack::push_delete_stack(ast_type stack_type) {
  delete_levels_.emplace_back(delete_stack{stack_type});
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
void delete_stack_stack::write_upto_loop(std::stringstream &target,
                                         int indent_level) {
  this->write_upto_loop(target, indent_level, "");
}
void delete_stack_stack::write_upto_loop(std::stringstream &target,
                                         int indent_level,
                                         const std::string &return_name) {
  auto size = delete_levels_.size();
  if (size == 0) { return; }
  for (auto i = 0; i < size; i++) {
    auto index = size - 1 - i;
    auto stack = delete_levels_[index];
    stack.write(target, indent_level, return_name);
    if (stack.stack_type_ == ast_type::STMT_WHILE) { break; }
  }
}
