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
// usage_analyser.cpp
#include "usage_analyser.h"
#include "ast/parser.h"
#include "def_class_visitor.h"
#include <utility>
using namespace yaksha;
usage_analyser::~usage_analyser() = default;
usage_analyser::usage_analyser(file_info *main_file_info)
    : main_(main_file_info) {
  import_stack_.push_back(main_);
}
void usage_analyser::analyse() {
  std::vector<std::string> functions = {"main", "del_state", "init_state",
                                        "game_step"};
  for (std::string &name : functions) {
    if (main_->data_->dsv_->has_function(name)) {
      LOG_COMP("usage_analyser - found : " << name);
      main_->data_->dsv_->get_function(name)->accept(this);
    }
  }
  import_stack_.clear();
  object_stack_.clear();
}
void usage_analyser::visit_assign_expr(assign_expr *obj) {
  obj->hits_++;
  obj->right_->accept(this);
  pop_object();
}
void usage_analyser::visit_assign_arr_expr(assign_arr_expr *obj) {
  obj->hits_++;
  obj->assign_oper_->accept(this);
  obj->right_->accept(this);
  pop_object();
}
void usage_analyser::visit_assign_member_expr(assign_member_expr *obj) {
  obj->hits_++;
  obj->set_oper_->accept(this);
  obj->right_->accept(this);
  pop_object();
}
void usage_analyser::visit_binary_expr(binary_expr *obj) {
  obj->hits_++;
  obj->left_->accept(this);
  auto lhs = pop_object();
  obj->right_->accept(this);
  auto rhs = pop_object();
  auto o = ykobject();
  o.object_type_ = object_type::PRIMITIVE_OR_OBJ;
  object_stack_.emplace_back(o);
}
void usage_analyser::visit_curly_call_expr(curly_call_expr *obj) {
  obj->hits_++;
  obj->dt_expr_->accept(this);
  for (auto &v : obj->values_) { v.value_->accept(this); }
}
void usage_analyser::visit_fncall_expr(fncall_expr *obj) {
  obj->hits_++;
  obj->name_->accept(this);
  auto name = pop_object();
  for (auto &v : obj->args_) { v->accept(this); }
}
void usage_analyser::visit_get_expr(get_expr *obj) {
  obj->hits_++;
  obj->lhs_->accept(this);
  auto lhs = pop_object();
  if (lhs.object_type_ == object_type::MODULE) {
    // try and get from module
    auto imp = find_import(lhs.module_file_,
                           peek_file_info()->data_->parser_->import_stmts_);
    if (imp.first == nullptr && !imp.second) {
      error(obj->dot_, "cannot find imported file: " + lhs.module_file_);
      auto o = ykobject();
      o.object_type_ = object_type::PRIMITIVE_OR_OBJ;
      push_object(o);
      return;
    }
    if (imp.first == nullptr && imp.second) {
      error(obj->dot_, "current file imported? " + lhs.module_file_);
      return;//
    }
    // --
    auto import_st = imp.first;
    if (import_st->data_->data_->dsv_->has_function(obj->item_->token_)) {
      auto fnc =
          import_st->data_->data_->dsv_->get_function(obj->item_->token_);
      push_import(import_st);
      fnc->accept(this);
      pop_import();
      auto o = ykobject();
      o.object_type_ = object_type::MODULE_FUNCTION;
      o.module_file_ = import_st->data_->filepath_.string();
      o.string_val_ = obj->item_->token_;
      push_object(o);
    } else if (import_st->data_->data_->dsv_->has_class(obj->item_->token_)) {
      auto cls = import_st->data_->data_->dsv_->get_class(obj->item_->token_);
      push_import(import_st);
      cls->accept(this);
      pop_import();
      auto o = ykobject();
      o.object_type_ = object_type::MODULE_CLASS;
      o.module_file_ = import_st->data_->filepath_.string();
      o.string_val_ = obj->item_->token_;
      push_object(o);
    } else if (import_st->data_->data_->dsv_->has_const(obj->item_->token_)) {
      auto c = import_st->data_->data_->dsv_->get_const(obj->item_->token_);
      push_import(import_st);
      c->accept(this);
      pop_import();
      auto o = ykobject();
      o.object_type_ = object_type::PRIMITIVE_OR_OBJ;
      o.module_file_ = import_st->data_->filepath_.string();
      o.string_val_ = obj->item_->token_;
      push_object(o);
    } else if (import_st->data_->data_->dsv_->has_native_const(
                   obj->item_->token_)) {
      auto c =
          import_st->data_->data_->dsv_->get_native_const(obj->item_->token_);
      push_import(import_st);
      c->accept(this);
      pop_import();
      auto o = ykobject();
      o.object_type_ = object_type::PRIMITIVE_OR_OBJ;
      o.module_file_ = import_st->data_->filepath_.string();
      o.string_val_ = obj->item_->token_;
      push_object(o);
    } else {
      auto o = ykobject();
      o.object_type_ = object_type::PRIMITIVE_OR_OBJ;
      push_object(o);
    }
    return;
  }
  auto o = ykobject();
  o.object_type_ = object_type::PRIMITIVE_OR_OBJ;
  push_object(o);
}
void usage_analyser::visit_grouping_expr(grouping_expr *obj) {
  obj->hits_++;
  obj->expression_->accept(this);
}
void usage_analyser::visit_literal_expr(literal_expr *obj) {
  obj->hits_++;
  auto o = ykobject();
  o.object_type_ = object_type::PRIMITIVE_OR_OBJ;
  push_object(o);
}
void usage_analyser::visit_logical_expr(logical_expr *obj) {
  obj->hits_++;
  obj->left_->accept(this);
  auto lhs = pop_object();
  obj->right_->accept(this);
  auto rhs = pop_object();
  auto o = ykobject();
  o.object_type_ = object_type::PRIMITIVE_OR_OBJ;
  push_object(o);
}
void usage_analyser::visit_macro_call_expr(macro_call_expr *obj) {
  obj->hits_++;
}
void usage_analyser::visit_set_expr(set_expr *obj) {
  obj->hits_++;
  obj->lhs_->accept(this);
  auto lhs = pop_object();
}
void usage_analyser::visit_square_bracket_access_expr(
    square_bracket_access_expr *obj) {
  obj->hits_++;
  obj->name_->accept(this);
  ykobject lhs = pop_object();
  if (lhs.is_primitive_or_obj()) {
    push_object(lhs);
  } else {
    // Class[X] -- not required for now as this is when we add template support
  }
}
void usage_analyser::push_object(const ykobject &lhs) {
  object_stack_.push_back(lhs);
}
ykobject usage_analyser::pop_object() {
  if (object_stack_.empty()) { return {}; }
  auto lhs = object_stack_.back();
  object_stack_.pop_back();
  return lhs;
}
void usage_analyser::visit_square_bracket_set_expr(
    square_bracket_set_expr *obj) {
  obj->hits_++;
  obj->name_->accept(this);
  auto lhs = object_stack_.back();
}
void usage_analyser::visit_unary_expr(unary_expr *obj) {
  obj->hits_++;
  obj->right_->accept(this);
}
void usage_analyser::visit_variable_expr(variable_expr *obj) {
  obj->hits_++;
  auto name = obj->name_->token_;
  auto o = ykobject();
  if (peek_file_info()->data_->dsv_->has_class(name)) {
    o.string_val_ = name;
    o.object_type_ = object_type::CLASS_ITSELF;
    peek_file_info()->data_->dsv_->get_class(name)->accept(this);
    o.module_file_ = "!class";
  } else if (peek_file_info()->data_->dsv_->has_const(name)) {
    o.string_val_ = name;
    o.object_type_ = object_type::PRIMITIVE_OR_OBJ;
    peek_file_info()->data_->dsv_->get_const(name)->accept(this);
    o.module_file_ = "!const";
  } else if (peek_file_info()->data_->dsv_->has_function(name)) {
    o.string_val_ = name;
    o.object_type_ = object_type::FUNCTION;
    peek_file_info()->data_->dsv_->get_function(name)->accept(this);
    o.module_file_ = "!function";
  } else if (peek_file_info()->data_->dsv_->has_native_const(name)) {
    o.string_val_ = name;
    o.object_type_ = object_type::PRIMITIVE_OR_OBJ;
    peek_file_info()->data_->dsv_->get_native_const(name)->accept(this);
    o.module_file_ = "!native";
  } else if (peek_file_info()->data_->parser_->import_stmts_alias_.find(name) !=
             peek_file_info()->data_->parser_->import_stmts_alias_.end()) {
    o.string_val_ = name;
    o.object_type_ = object_type::MODULE;
    auto imp = peek_file_info()->data_->parser_->import_stmts_alias_[name];
    o.module_file_ = imp->data_->filepath_.string();
    imp->accept(this);
  } else {
    o.string_val_ = name;
    o.object_type_ = object_type::PRIMITIVE_OR_OBJ;
    o.module_file_ = "!variable";
  }
  push_object(o);
}
void usage_analyser::visit_block_stmt(block_stmt *obj) {
  obj->hits_++;
  for (auto o : obj->statements_) { o->accept(this); }
}
void usage_analyser::visit_break_stmt(break_stmt *obj) { obj->hits_++; }
void usage_analyser::visit_ccode_stmt(ccode_stmt *obj) { obj->hits_++; }
void usage_analyser::visit_class_stmt(class_stmt *obj) {
  obj->hits_++;
  for (auto &member : obj->members_) {
    this->visit_data_type(member.data_type_, member.name_);
  }
}
void usage_analyser::visit_compins_stmt(compins_stmt *obj) {
  this->visit_data_type(obj->data_type_, obj->name_);
  obj->hits_++;
}
void usage_analyser::visit_const_stmt(const_stmt *obj) {
  obj->hits_++;
  this->visit_data_type(obj->data_type_, obj->name_);
  obj->expression_->accept(this);
  pop_object();
}
void usage_analyser::visit_continue_stmt(continue_stmt *obj) { obj->hits_++; }
void usage_analyser::visit_def_stmt(def_stmt *obj) {
  LOG_COMP("usage_analyser: def - " << obj->name_->token_
                                    << " hits = " << obj->hits_);
  if (obj->hits_ > 0) { return; }
  obj->hits_++;
  for (auto &p : obj->params_) { this->visit_data_type(p.data_type_, p.name_); }
  obj->function_body_->accept(this);
}
void usage_analyser::visit_defer_stmt(defer_stmt *obj) {
  obj->hits_++;
  if (obj->expression_ != nullptr) { obj->expression_->accept(this); }
}
void usage_analyser::visit_del_stmt(del_stmt *obj) {
  obj->hits_++;
  obj->expression_->accept(this);
}
void usage_analyser::visit_expression_stmt(expression_stmt *obj) {
  obj->hits_++;
  obj->expression_->accept(this);
}
void usage_analyser::visit_foreach_stmt(foreach_stmt *obj) {
  obj->hits_++;
  obj->expression_->accept(this);
  obj->for_body_->accept(this);
}
void usage_analyser::visit_forendless_stmt(forendless_stmt *obj) {
  obj->hits_++;
  obj->for_body_->accept(this);
}
void usage_analyser::visit_if_stmt(if_stmt *obj) {
  obj->hits_++;
  obj->expression_->accept(this);
  obj->if_branch_->accept(this);
  if (obj->else_branch_ != nullptr) { obj->else_branch_->accept(this); }
}
void usage_analyser::visit_import_stmt(import_stmt *obj) {
  // do not go into the import, we let that happen when we do . access
  obj->hits_++;
}
void usage_analyser::visit_let_stmt(let_stmt *obj) {
  obj->hits_++;
  if (obj->expression_ != nullptr) { obj->expression_->accept(this); }
  this->visit_data_type(obj->data_type_, obj->name_);
}
void usage_analyser::visit_nativeconst_stmt(nativeconst_stmt *obj) {
  obj->hits_++;
}
void usage_analyser::visit_pass_stmt(pass_stmt *obj) { obj->hits_++; }
void usage_analyser::visit_return_stmt(return_stmt *obj) {
  obj->hits_++;
  if (obj->expression_ != nullptr) { obj->expression_->accept(this); }
}
void usage_analyser::visit_runtimefeature_stmt(runtimefeature_stmt *obj) {
  obj->hits_++;
}
void usage_analyser::visit_while_stmt(while_stmt *obj) {
  obj->hits_++;
  obj->expression_->accept(this);
  pop_object();
  obj->while_body_->accept(this);
}
void usage_analyser::visit_data_type(ykdatatype *dt, token *token_for_err) {
  if (dt == nullptr) { return; }
  if (dt->hits_ > 0) { return; }
  dt->hits_++;
  if (dt->is_primitive()) { return; }
  if (dt->is_array() || dt->is_sm_entry() || dt->is_const() || dt->is_ptr() ||
      dt->is_fixed_size_array()) {
    visit_data_type(dt->args_[0], token_for_err);
    return;
  }
  if (dt->is_m_entry()) {
    visit_data_type(dt->args_[0], token_for_err);
    visit_data_type(dt->args_[1], token_for_err);
    return;
  }
  if (dt->is_tuple()) {
    for (auto arg : dt->args_) { visit_data_type(arg, token_for_err); }
    return;
  }
  if (dt->is_function()) {
    auto fi = dt->args_[0];
    for (auto arg : fi->args_) { visit_data_type(arg, token_for_err); }
    auto fo = dt->args_[1];
    for (auto arg : fo->args_) { visit_data_type(arg, token_for_err); }
    return;
  }
  if (dt->is_builtin_or_primitive()) { return; }
  def_class_visitor *dsv = peek_file_info()->data_->dsv_;
  bool pop_import_stack = false;
  if (!dt->module_.empty()) {
    auto &import_statements = peek_file_info()->data_->parser_->import_stmts_;
    auto imp = find_import(dt->module_, import_statements);
    if (!imp.second) {
      if (imp.first == nullptr) {
        error(token_for_err, "cannot find imported file: " + dt->module_);
        return;
      }
      auto import_st = imp.first;
      import_st->accept(this);
      push_import(import_st);
      pop_import_stack = true;
      dsv = import_st->data_->data_->dsv_;
    }
  }
  if (!dsv->has_class(dt->type_)) {
    error(token_for_err,
          "cannot find class " + dt->type_ + " in " + dt->module_);
    if (pop_import_stack) { pop_import(); }
    return;
  }
  dsv->get_class(dt->type_)->accept(this);
  if (pop_import_stack) { pop_import(); }
}
void usage_analyser::push_import(const import_stmt *import_st) {
  import_stack_.push_back(import_st->data_);
}
void usage_analyser::error(token *t, std::string message) {
  if (t == nullptr) {
    errors_.emplace_back(std::move(message),
                         peek_file_info()->filepath_.string(), 0, 0);
  } else {
    errors_.emplace_back(message, t);
  }
}
std::pair<import_stmt *, bool> /* bool -> is current file? */
usage_analyser::find_import(std::string &filepath,
                            std::vector<import_stmt *> &import_statements) {
  if (filepath == peek_file_info()->filepath_.string()) {
    return {nullptr, true};
  }
  for (auto x : import_statements) {
    if (x->data_->filepath_.string() == filepath) { return {x, false}; }
  }
  return {nullptr, false};
}
file_info *usage_analyser::peek_file_info() {
  if (import_stack_.empty()) { return main_; }
  return import_stack_.back();
}
void usage_analyser::pop_import() {
  if (import_stack_.empty()) { return; }
  import_stack_.pop_back();
}
void usage_analyser::visit_cfor_stmt(cfor_stmt *obj) {
  obj->hits_++;
  if (obj->init_expr_ != nullptr) { obj->init_expr_->accept(this); }
  if (obj->comparison_ != nullptr) { obj->comparison_->accept(this); }
  if (obj->operation_ != nullptr) { obj->operation_->accept(this); }
  obj->for_body_->accept(this);
}
void usage_analyser::visit_enum_stmt(enum_stmt *obj) { obj->hits_++; }
void usage_analyser::visit_union_stmt(union_stmt *obj) { obj->hits_++; }
