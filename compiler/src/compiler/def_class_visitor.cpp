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
#include "ast/codefiles.h"
#include "builtins/builtins.h"
#include "compiler_utils.h"
#include <regex>
using namespace yaksha;
def_class_visitor::def_class_visitor(builtins *builtins, codefiles *cf)
    : builtins_(builtins), cf_(cf){};
def_class_visitor::~def_class_visitor() = default;
void def_class_visitor::visit_block_stmt(block_stmt *obj) {}
void def_class_visitor::visit_break_stmt(break_stmt *obj) {}
void def_class_visitor::visit_continue_stmt(continue_stmt *obj) {}
void def_class_visitor::visit_def_stmt(def_stmt *obj) {
  auto name = obj->name_->token_;
  if (is_redefined(name, obj->name_)) { return; }
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
        statement_type == ast_type::STMT_DIRECTIVE ||
        statement_type == ast_type::STMT_ENUM) {
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
  if (is_redefined(name, obj->name_)) { return; }
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
  if (is_redefined(name, obj->name_)) { return; }
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
  if (is_redefined(name, obj->name_)) { return; }
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
bool def_class_visitor::has_enum(const std::string &prefixed_name) {
  return enums_.find(prefixed_name) != enums_.end();
}
enum_stmt *def_class_visitor::get_enum(const std::string &prefixed_name) {
  if (has_enum(prefixed_name)) { return enums_[prefixed_name]; }
  return nullptr;
}
void def_class_visitor::visit_foreach_stmt(foreach_stmt *obj) {}
void def_class_visitor::visit_forendless_stmt(forendless_stmt *obj) {}
void def_class_visitor::visit_compins_stmt(compins_stmt *obj) {}
void def_class_visitor::visit_cfor_stmt(cfor_stmt *obj) {}
void def_class_visitor::visit_enum_stmt(enum_stmt *obj) {
  if (obj->annotations_.native_ || obj->annotations_.native_define_ ||
      obj->annotations_.native_macro_ || obj->annotations_.on_stack_ ||
      obj->annotations_.template_) {
    error(obj->name_, "Annotations are not allowed for enums");
    return;
  }
  auto name = obj->name_->token_;
  if (is_redefined(name, obj->name_)) { return; }
  enum_names_.push_back(name);
  enums_.insert({name, obj});
}
bool def_class_visitor::is_redefined(const std::string &name, token *tok) {
  bool redefined = false;
  if (builtins_->has_builtin(name)) {
    error(tok, "Critical!! Redefinition of builtin function");
    redefined = true;
  }
  if (has_function(name)) {
    error(tok, "Critical!! Redefinition of function");
    redefined = true;
  }
  if (has_class(name)) {
    error(tok, "Critical!! Redefinition of class");
    redefined = true;
  }
  if (has_const(name) || has_native_const(name)) {
    error(tok, "Critical!! Redefinition of global constant");
    redefined = true;
  }
  if (has_enum(name)) {
    error(tok, "Critical!! Redefinition of enum");
    redefined = true;
  }
  return redefined;
}
void def_class_visitor::visit_directive_stmt(directive_stmt *obj) {
  obj->hits_ = 1;// Always consider this to be used!
  auto directive_type = obj->directive_type_->token_;
  bool zero_arg_directive = has_zero_arg_directive(obj);
  bool must_have_arg_directive = has_one_arg_directive(obj);
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
}
bool def_class_visitor::has_one_arg_directive(directive_stmt *obj) {
  auto directive_type = obj->directive_type_->token_;
  /* these must have the argument string, and it cannot be empty */
  bool must_have_arg_directive = false;
  // Write this raw code (unescaped) directly to output!  🟡
  // Write #include "arg"                                 🟡
  // Write #include <arg>                                 🟡
  if (directive_type == "ccode" || directive_type == "c_include" ||
      directive_type == "c_sys_include") {
    must_have_arg_directive = true;
  }
  // (Global) Include path -I <arg>                       🔴
  if (directive_type == "c_include_path") {
    must_have_arg_directive = true;
    cf_->directives_.include_paths_.emplace_back(obj);
  }
  // (Global) Library path -L <arg>                       🔴
  if (directive_type == "c_lib_path") {
    must_have_arg_directive = true;
    cf_->directives_.library_paths_.emplace_back(obj);
  }
  // Compile and link with this '.c' file's .o file, in addition to output code
  // --> can also take, c_compile_arg, c_define parameters for that specific file
  //  will support following parameter                    🔴
  //  os 1,arch 1,c_define *,c_compile_arg *,inherit_compile_args
  if (directive_type == "c_file") {
    must_have_arg_directive = true;
    cf_->directives_.c_files_.emplace_back(obj);
  }
  // (Global) Link with this, -l<arg>, for example        🔴
  if (directive_type == "c_lib") {
    must_have_arg_directive = true;
    cf_->directives_.libraries_.emplace_back(obj);
  }
  // (Global) compilation argument for all code files     🔴
  if (directive_type == "c_compile_arg") {
    must_have_arg_directive = true;
    cf_->directives_.compile_args_.emplace_back(obj);
  }
  // (Global) use this arg during link time               🔴
  if (directive_type == "c_link_arg") {
    must_have_arg_directive = true;
    cf_->directives_.compile_args_.emplace_back(obj);
  }
  // (Global) use this define during compilation time of all .c files
  //                                                      🔴
  if (directive_type == "c_define") {
    must_have_arg_directive = true;
    cf_->directives_.defines_.emplace_back(obj);
  }
  return must_have_arg_directive;
}
bool def_class_visitor::has_zero_arg_directive(directive_stmt *obj) {
  auto directive_type = obj->directive_type_->token_;
  /* these must have no STR argument */
  bool zero_arg_directive = false;
  // (Global flag) No need to check for main()            🟡
  if (directive_type == "no_main") {
    // TODO verify parameter count is zero
    zero_arg_directive = true;
    cf_->directives_.no_main_ = true;
  }
  // (Global flag) Directly substitute '@nativedefine' or 'native constants'
  if (directive_type == "apply_nativedefine") {//        🔴
    zero_arg_directive = true;
    cf_->directives_.apply_native_define_ = true;
  }
  // (Global flag) no yaksha runtime / libs,              🟡
  if (directive_type == "no_stdlib") {
    zero_arg_directive = true;
    cf_->directives_.no_stdlib_ = true;
  }
  return zero_arg_directive;
}
std::vector<std::string> def_class_visitor::get_all_names() {
  std::vector<std::string> all_names{};
  all_names.insert(all_names.end(), function_names_.begin(),
                   function_names_.end());
  all_names.insert(all_names.end(), class_names_.begin(), class_names_.end());
  all_names.insert(all_names.end(), global_const_names_.begin(),
                   global_const_names_.end());
  all_names.insert(all_names.end(), global_native_const_names_.begin(),
                   global_native_const_names_.end());
  all_names.insert(all_names.end(), enum_names_.begin(), enum_names_.end());
  return all_names;
}
