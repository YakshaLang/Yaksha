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
// def_class_visitor.cpp
#include "def_class_visitor.h"
#include "builtins/builtins.h"
#include "compiler_utils.h"
#include <regex>
using namespace yaksha;
def_class_visitor::def_class_visitor(builtins *builtins)
    : builtins_(builtins){};
def_class_visitor::~def_class_visitor() = default;
void def_class_visitor::visit_assign_expr(assign_expr *obj) {}
void def_class_visitor::visit_binary_expr(binary_expr *obj) {}
void def_class_visitor::visit_fncall_expr(fncall_expr *obj) {}
void def_class_visitor::visit_grouping_expr(grouping_expr *obj) {}
void def_class_visitor::visit_literal_expr(literal_expr *obj) {}
void def_class_visitor::visit_logical_expr(logical_expr *obj) {}
void def_class_visitor::visit_unary_expr(unary_expr *obj) {}
void def_class_visitor::visit_variable_expr(variable_expr *obj) {}
void def_class_visitor::visit_block_stmt(block_stmt *obj) {}
void def_class_visitor::visit_break_stmt(break_stmt *obj) {}
void def_class_visitor::visit_continue_stmt(continue_stmt *obj) {}
void def_class_visitor::visit_def_stmt(def_stmt *obj) {
  auto name = obj->name_->token_;
  if (builtins_->has_builtin(name)) {
    error(obj->name_, "Critical!! Redefinition of builtin function");
    return;
  }
  if (has_function(name)) {
    error(obj->name_, "Critical!! Redefinition of function");
    return;
  }
  if (has_class(name)) {
    error(obj->name_, "Critical!! Redefinition of class as a function");
    return;
  }
  if (has_const(name) || has_native_const(name)) {
    error(obj->name_, "Critical!! Redefinition of global constant");
    return;
  }
  if (obj->annotations_.varargs_ && !obj->annotations_.native_define_) {
    error(obj->name_, "@varargs must be used with @nativedefine ");
    return;
  }
  if (obj->annotations_.varargs_ && obj->params_.size() <= 1) {
    error(obj->name_,
          "@varargs only works with functions that have at least 2 arguments.");
    return;
  }
  if (obj->return_type_->const_unwrap()->is_fixed_size_array()) {
    error(obj->name_, "Functions cannot return fixed size arrays. Use Array or "
                      "wrap in a Tuple.");
    return;
  }
  function_names_.push_back(name);
  functions_.insert({name, obj});
}
void def_class_visitor::visit_expression_stmt(expression_stmt *obj) {}
void def_class_visitor::visit_if_stmt(if_stmt *obj) {}
void def_class_visitor::visit_let_stmt(let_stmt *obj) {}
void def_class_visitor::visit_pass_stmt(pass_stmt *obj) {}
void def_class_visitor::visit_return_stmt(return_stmt *obj) {}
void def_class_visitor::visit_while_stmt(while_stmt *obj) {}
void def_class_visitor::extract(const std::vector<stmt *> &statements) {
  for (auto st : statements) {
    auto statement_type = st->get_type();
    if (statement_type == ast_type::STMT_DEF ||
        statement_type == ast_type::STMT_CLASS ||
        statement_type == ast_type::STMT_CONST ||
        statement_type == ast_type::STMT_IMPORT ||
        statement_type == ast_type::STMT_RUNTIMEFEATURE ||
        statement_type == ast_type::STMT_NATIVECONST ||
        statement_type == ast_type::STMT_DIRECTIVE) {
      st->accept(this);
    } else {
      error(st->locate(),
            "Invalid statement detected."
            " Only def, class, import, runtimefeature"
            " or constant statements are supported at module level.");
    }
  }
}
void def_class_visitor::visit_const_stmt(const_stmt *obj) {
  auto name = obj->name_->token_;
  if (builtins_->has_builtin(name)) {
    error(obj->name_, "Critical!! Redefinition of builtin function");
    return;
  }
  if (has_function(name)) {
    error(obj->name_, "Critical!! Redefinition of function");
    return;
  }
  if (has_class(name)) {
    error(obj->name_, "Critical!! Redefinition of class");
    return;
  }
  if (has_const(name) || has_native_const(name)) {
    error(obj->name_, "Critical!! Redefinition of global constant");
    return;
  }
  if (obj->data_type_->args_.size() != 1) {
    error(obj->name_,
          "Should be Const[x], only single data type can be specified");
    return;
  }
  if (!obj->data_type_->args_[0]->is_a_number() &&
      !obj->data_type_->args_[0]->is_bool() &&
      !obj->data_type_->args_[0]->is_sr()) {
    error(obj->name_, "Only number/bool/sr constants are supported.");
    return;
  }
  // Note below is only at the moment --> // at the moment?
  if (obj->expression_->get_type() != ast_type::EXPR_LITERAL) {
    error(obj->name_, "Only a literal can be assigned to a constant.");
    return;
  }
  global_const_names_.push_back(name);
  global_consts_.insert({name, obj});
}
void def_class_visitor::visit_nativeconst_stmt(nativeconst_stmt *obj) {
  auto name = obj->name_->token_;
  if (builtins_->has_builtin(name)) {
    error(obj->name_, "Critical!! Redefinition of builtin function");
    return;
  }
  if (has_function(name)) {
    error(obj->name_, "Critical!! Redefinition of function");
    return;
  }
  if (has_class(name)) {
    error(obj->name_, "Critical!! Redefinition of class");
    return;
  }
  if (has_const(name) || has_native_const(name)) {
    error(obj->name_, "Critical!! Redefinition of global constant");
    return;
  }
  if (obj->data_type_->args_.size() != 1) {
    error(obj->name_,
          "Should be Const[x], only single data type can be specified");
    return;
  }
#ifdef YAKSHA_NATIVE_CONST_ONLY_NUM
  if (!obj->data_type_->args_[0]->is_a_number() &&
      !obj->data_type_->args_[0]->is_bool()) {
    error(obj->name_, "Only number and boolean constants are supported.");
    return;
  }
#endif
  global_native_const_names_.push_back(name);
  global_native_consts_.insert({name, obj});
}
void def_class_visitor::visit_defer_stmt(defer_stmt *obj) {}
void def_class_visitor::error(token *tok, const std::string &message) {
  auto err = parsing_error{message, tok};
  errors_.emplace_back(err);
}
def_stmt *def_class_visitor::get_function(const std::string &prefixed_name) {
  if (has_function(prefixed_name)) { return functions_[prefixed_name]; }
  return nullptr;
}
bool def_class_visitor::has_function(const std::string &prefixed_name) {
  return functions_.find(prefixed_name) != functions_.end();
}
void def_class_visitor::visit_class_stmt(class_stmt *obj) {
  auto name = obj->name_->token_;
  if (obj->annotations_.varargs_ || obj->annotations_.native_ ||
      obj->annotations_.template_ || obj->annotations_.native_macro_) {
    error(obj->name_, "@varargs, @native, @nativemacro and @template are not "
                      "allowed for classes.");
    return;
  }
  if (obj->annotations_.native_define_ &&
      obj->annotations_.native_define_arg_.empty()) {
    error(obj->name_, "@nativedefine must have a valid argument");
    return;
  }
  if (builtins_->has_builtin(name)) {
    error(obj->name_, "Critical!! Redefinition of builtin function");
    return;
  }
  if (has_class(name)) {
    error(obj->name_, "Critical!! Redefinition of class");
    return;
  }
  if (has_function(name)) {
    error(obj->name_, "Critical!! Redefinition of function as a class");
    return;
  }
  if (has_const(name)) {
    error(obj->name_, "Critical!! Redefinition of global constant");
    return;
  }
  class_names_.push_back(name);
  classes_.insert({name, obj});
}
class_stmt *def_class_visitor::get_class(const std::string &prefixed_name) {
  if (has_class(prefixed_name)) { return classes_[prefixed_name]; }
  return nullptr;
}
bool def_class_visitor::has_class(const std::string &prefixed_name) {
  return classes_.find(prefixed_name) != classes_.end();
}
void def_class_visitor::visit_del_stmt(del_stmt *obj) {}
void def_class_visitor::visit_get_expr(get_expr *obj) {}
void def_class_visitor::visit_set_expr(set_expr *obj) {}
void def_class_visitor::visit_assign_member_expr(assign_member_expr *obj) {}
void def_class_visitor::visit_square_bracket_access_expr(
    square_bracket_access_expr *obj) {}
void def_class_visitor::visit_assign_arr_expr(assign_arr_expr *obj) {}
void def_class_visitor::visit_square_bracket_set_expr(
    square_bracket_set_expr *obj) {}
void def_class_visitor::visit_ccode_stmt(ccode_stmt *obj) {}
void def_class_visitor::visit_import_stmt(import_stmt *obj) {}
const_stmt *def_class_visitor::get_const(const std::string &prefixed_name) {
  if (has_const(prefixed_name)) { return global_consts_[prefixed_name]; }
  return nullptr;
}
void def_class_visitor::visit_runtimefeature_stmt(runtimefeature_stmt *obj) {
  std::string feature = obj->feature_->token_;
  if (!std::regex_match(feature, std::regex("[a-z][a-z0-8A-Z_]*"))) {
    error(obj->runtimefeature_token_,
          "Critical!! invalid runtime feature. Must match [a-z][a-z0-8A-Z_]*");
    return;
  }
  runtime_features_.emplace(feature);
}
bool def_class_visitor::has_const(const std::string &prefixed_name) {
  return global_consts_.find(prefixed_name) != global_consts_.end();
}
bool def_class_visitor::has_native_const(const std::string &prefixed_name) {
  return global_native_consts_.find(prefixed_name) !=
         global_native_consts_.end();
}
nativeconst_stmt *
def_class_visitor::get_native_const(const std::string &prefixed_name) {
  if (has_native_const(prefixed_name)) {
    return global_native_consts_[prefixed_name];
  }
  return nullptr;
}
void def_class_visitor::visit_foreach_stmt(foreach_stmt *obj) {}
void def_class_visitor::visit_forendless_stmt(forendless_stmt *obj) {}
void def_class_visitor::visit_compins_stmt(compins_stmt *obj) {}
void def_class_visitor::visit_curly_call_expr(curly_call_expr *obj) {}
void def_class_visitor::visit_macro_call_expr(macro_call_expr *obj) {}
void def_class_visitor::visit_cfor_stmt(cfor_stmt *obj) {}
void def_class_visitor::visit_enum_stmt(enum_stmt *obj) {}
void def_class_visitor::visit_union_stmt(union_stmt *obj) {}
void def_class_visitor::visit_directive_stmt(directive_stmt *obj) {
  obj->hits_ = 1;// Always consider this to be used!
  auto directive_type = obj->directive_type_->token_;
  /* these must have no STR argument */
  bool zero_arg_directive =
      // (Global flag) No need to check for main()
      directive_type == "no_main" ||// TODO
      // (Global flag) If a function takes 'str' parameters, it is thrown as an error)
      directive_type == "ban_str_params" ||// TODO
      // (Global flag) Directly substitute '@nativedefine' or 'native constants'
      directive_type == "apply_nativedefine";// TODO
  /* ========================================================================= */
  /* these must have the argument string, and it cannot be empty */
  bool must_have_arg_directive =
      // Write this raw code directly to output!
      directive_type == "ccode" ||
      // (Global) Include path -I <arg>
      directive_type == "c_include_path" ||// TODO
      // (Global) -L <arg>
      directive_type == "c_lib_path" ||// TODO
      // Write #include "arg"
      directive_type == "c_include" ||
      // Write #include <arg>
      directive_type == "c_sys_include" ||
      // Compile and link with this '.c' file's .o file, in addition to output code
      // --> can also take, c_compile_arg, c_define parameters for that specific file
      directive_type == "c_file" ||// TODO
      // (Global) Link with this, -l<arg>, for example
      directive_type == "c_lib" ||// TODO
      // (Global) use this compilation argument for all code files
      directive_type == "c_compile_arg" ||// TODO
      // (Global) when all .o objects are linked together, use these arguments
      directive_type == "c_link_arg" ||// TODO
      // (Global) use these arguments for linking or compiling
      directive_type == "c_compile_or_link_arg" ||// TODO
      // (Global) define this when compiling. -D<arg>
      directive_type == "c_define";// TODO
  if (zero_arg_directive || must_have_arg_directive) {
    if (zero_arg_directive && obj->directive_val_ != nullptr) {
      error(obj->directive_val_,
            "Directive must not have a string literal argument");
    }
    if (must_have_arg_directive && (obj->directive_val_ == nullptr ||
                                    obj->directive_val_->token_.empty())) {
      error(obj->directive_val_,
            "Directive must have a string literal argument");
    }
  } else {
    error(obj->directive_type_,
          "Invalid directive. Only no_main, no_string and ccode are supported");
  }
  directives_.push_back(obj);
}
