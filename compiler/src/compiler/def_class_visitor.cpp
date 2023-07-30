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
        statement_type == ast_type::STMT_NATIVECONST) {
      st->accept(this);
    } else {
      // TODO can we find out if there's a token for this statement type?
      error(nullptr, "Invalid statement detected."
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
      !obj->data_type_->args_[0]->is_bool()) {
    error(obj->name_, "Only number and boolean constants are supported.");
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
  // TODO should we support more? // think!
  if (!obj->data_type_->args_[0]->is_a_number() &&
      !obj->data_type_->args_[0]->is_bool()) {
    error(obj->name_, "Only number and boolean constants are supported.");
    return;
  }
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
