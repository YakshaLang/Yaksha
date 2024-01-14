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
