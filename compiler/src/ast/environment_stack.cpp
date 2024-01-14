// ==============================================================================================
// ╦  ┬┌─┐┌─┐┌┐┌┌─┐┌─┐    Yaksha Programming Language
// ║  ││  ├┤ │││└─┐├┤     is Licensed with GPLv3 + extra terms. Please see below.
// ╩═╝┴└─┘└─┘┘└┘└─┘└─┘
// Note: libs - MIT license, runtime/3rd - various
// ==============================================================================================
// GPLv3:
//
// Yaksha - Programming Language.
// Copyright (C) 2020 - 2024 Bhathiya Perera
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
// environment_stack.cpp
#include "environment_stack.h"
#include <utility>
using namespace yaksha;
environment_stack::environment_stack(ykdt_pool *pool) : pool_(pool) {
  // Create global environment
  scope_stack_.emplace_back(environment());
};
environment_stack::~environment_stack() = default;
bool environment_stack::is_defined(const std::string &name) {
  // If defined in global, return that
  if (scope_stack_.front().is_defined(name)) { return true; }
  if (!has_inner_scope()) { return false; }
  if (peek().is_defined(name)) { return true; }
  for (auto stack : scope_stack_) {
    if (stack.is_defined(name)) { return true; }
  }
  return false;
}
void environment_stack::define(const std::string &name, ykobject data) {
  peek().define(name, data);
}
void environment_stack::define_global(const std::string &name, ykobject data) {
  scope_stack_.front().define(name, std::move(data));
}
void environment_stack::assign(const std::string &name, ykobject data) {
  if (peek().is_defined(name)) {
    peek().assign(name, data);
    return;
  }
  for (auto stack : scope_stack_) {
    if (stack.is_defined(name)) {
      stack.assign(name, data);
      return;
    }
  }
}
ykobject environment_stack::get(const std::string &name) {
  if (scope_stack_.front().is_defined(name)) {
    return scope_stack_.front().get(name);
  }
  if (peek().is_defined(name)) { return peek().get(name); }
  for (auto stack : scope_stack_) {
    if (stack.is_defined(name)) { return stack.get(name); }
  }
  return ykobject(pool_);
}
void environment_stack::push() { scope_stack_.emplace_back(environment()); }
void environment_stack::pop() {
  if (has_inner_scope()) { scope_stack_.pop_back(); }
}
bool environment_stack::has_inner_scope() { return scope_stack_.size() > 1; }
environment &environment_stack::peek() { return scope_stack_.back(); }
bool environment_stack::is_global_level() { return scope_stack_.size() <= 1; }
