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
// return_checker.cpp
#include "return_checker.h"
using namespace yaksha;
return_checker::return_checker() = default;
return_checker::~return_checker() = default;
void return_checker::visit_block_stmt(block_stmt *obj) {
  for (auto st : obj->statements_) {
    st->accept(this);
    if (found_return()) { return; }
  }
}
void return_checker::visit_break_stmt(break_stmt *obj) {}
void return_checker::visit_ccode_stmt(ccode_stmt *obj) {}
void return_checker::visit_cfor_stmt(cfor_stmt *obj) {
  if (obj->comparison_ == nullptr) { obj->for_body_->accept(this); }
}
void return_checker::visit_class_stmt(class_stmt *obj) {}
void return_checker::visit_compins_stmt(compins_stmt *obj) {}
void return_checker::visit_const_stmt(const_stmt *obj) {}
void return_checker::visit_continue_stmt(continue_stmt *obj) {}
void return_checker::visit_def_stmt(def_stmt *obj) {
  errors_.clear();
  found_returns_.clear();
  if (obj->return_type_->is_none()) {
    return;// We will add a return for anything that return none
  }
  obj->function_body_->accept(this);
  if (!found_return()) {
    errors_.emplace_back("Did not find a return statement", obj->name_);
  }
}
void return_checker::visit_defer_stmt(defer_stmt *obj) {}
void return_checker::visit_del_stmt(del_stmt *obj) {}
void return_checker::visit_enum_stmt(enum_stmt *obj) {}
void return_checker::visit_expression_stmt(expression_stmt *obj) {}
void return_checker::visit_foreach_stmt(foreach_stmt *obj) {}
void return_checker::visit_forendless_stmt(forendless_stmt *obj) {
  obj->for_body_->accept(this);
}
void return_checker::visit_if_stmt(if_stmt *obj) {
  if (obj->else_branch_ == nullptr) { return; }
  obj->if_branch_->accept(this);
  if (!found_return()) { return; }
  pop();
  obj->else_branch_->accept(this);
  if (!found_return()) { return; }
  pop();
  found_returns_.push_back(true);// since both sides return
}
void return_checker::visit_import_stmt(import_stmt *obj) {}
void return_checker::visit_let_stmt(let_stmt *obj) {}
void return_checker::visit_nativeconst_stmt(nativeconst_stmt *obj) {}
void return_checker::visit_pass_stmt(pass_stmt *obj) {}
void return_checker::visit_return_stmt(return_stmt *obj) {
  found_returns_.push_back(true);
}
void return_checker::visit_runtimefeature_stmt(runtimefeature_stmt *obj) {}
void return_checker::visit_while_stmt(while_stmt *obj) {}
bool return_checker::found_return() {
  if (found_returns_.empty()) { return false; }
  return found_returns_.back();
}
void return_checker::pop() {
  if (found_returns_.empty()) { return; }
  found_returns_.pop_back();
}
void return_checker::visit_directive_stmt(directive_stmt *obj) {}
