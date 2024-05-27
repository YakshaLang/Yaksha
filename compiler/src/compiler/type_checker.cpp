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
// type_checker.cpp
#include "type_checker.h"
#include "ast/parser.h"
#include "compiler_utils.h"
#include <utility>
using namespace yaksha;
type_checker::type_checker(std::string filepath, codefiles *cf,
                           def_class_visitor *dcv, yk_datatype_pool *pool,
                           gc_pool<token> *token_pool)
    : cf_(cf), dt_pool_(pool), scope_(pool), builtins_(pool, token_pool),
      defs_classes_(dcv), filepath_(std::move(filepath)),
      ast_pool_(new ast_pool{}), magic_return_token_(new token{}) {
  import_stmts_alias_ =
      cf->get_or_null(filepath_)->data_->parser_->import_stmts_alias_;
  // create a magic_return_token so last expression of a function can be promoted to return
  magic_return_token_->token_ = "return";
  magic_return_token_->file_ = "desugar";
  magic_return_token_->original_ = "return";
  magic_return_token_->line_ = 0;
  magic_return_token_->pos_ = 0;
  magic_return_token_->type_ = token_type::KEYWORD_RETURN;
}
type_checker::~type_checker() {
  delete ast_pool_;
  delete magic_return_token_;
}
void type_checker::visit_assign_expr(assign_expr *obj) {
  obj->right_->accept(this);
  auto rhs = pop();
  auto name = obj->name_->token_;
  yk_object object;
  if (scope_.is_defined(name)) {
    object = scope_.get(name);
  } else {
    if (rhs.is_a_function()) {
      rhs.datatype_ = function_to_datatype_or_null(rhs);
      if (rhs.datatype_ == nullptr) {
        error(obj->right_->locate(),
              "Failed to derive data type of function pointer");
        return;
      }
    }
    if (rhs.datatype_->is_none()) {
      error(obj->opr_, "Cannot infer type when RHS is None");
    }
    if (rhs.datatype_->is_string_literal()) {
      // When `a = string_lit`, then `a` should be promoted to `sr`
      object = yk_object(dt_pool_->create("sr"));
    } else {
      object = yk_object(rhs.datatype_);
    }
    obj->promoted_ = true;
  }
  if (obj->promoted_) {
    object.datatype_ = object.datatype_->const_unwrap();
    obj->promoted_data_type_ = object.datatype_;
    handle_assigns(obj->opr_, object, rhs);
    scope_.define(name, object);
  } else {
    handle_assigns(obj->opr_, object, rhs);
  }
}
template<typename Verifier>
bool dt_match_ignore_const(yk_datatype *lhs, yk_datatype *rhs, Verifier v) {
  yk_datatype *my_lhs = lhs->const_unwrap();
  yk_datatype *my_rhs = rhs->const_unwrap();
  return (internal_is_identical_type(my_lhs, my_rhs)) && v(my_lhs) && v(my_rhs);
}
#define DT_MATCH(lhs, rhs, fnc)                                                \
  dt_match_ignore_const(lhs.datatype_, rhs.datatype_,                          \
                        [](yk_datatype *a) { return fnc; })
template<typename Verifier>
bool dt_verify_ignore_const(yk_datatype *castable, yk_datatype *lhs,
                            yk_datatype *rhs, Verifier v) {
  yk_datatype *my_lhs = lhs->const_unwrap();
  yk_datatype *my_rhs = rhs->const_unwrap();
  return ((castable == nullptr && internal_is_identical_type(my_lhs, my_rhs) ||
           castable != nullptr) &&
          v(my_lhs) && v(my_rhs));
}
#define DT_VERIFY(castable, lhs, rhs, fnc)                                     \
  dt_verify_ignore_const(castable, lhs.datatype_, rhs.datatype_,               \
                         [](yk_datatype *a) { return fnc; })
template<typename Matcher>
bool dt_either_match(yk_datatype *lhs, yk_datatype *rhs, Matcher m) {
  return m(lhs) || m(rhs);
}
#define EITHER_MATCH(lhs, rhs, fnc)                                            \
  dt_either_match(lhs.datatype_, rhs.datatype_,                                \
                  [](yk_datatype *a) { return fnc; })
void type_checker::visit_binary_expr(binary_expr *obj) {
  auto oper = obj->opr_->type_;
  obj->left_->accept(this);
  auto lhs = pop();
  obj->right_->accept(this);
  auto rhs = pop();
  if (lhs.object_type_ != rhs.object_type_) {
    error(
        obj->opr_,
        "Binary operation between two different data types are not supported");
    push(rhs);// Try to figure out the rest
    return;
  }
  auto castable =
      lhs.datatype_->auto_cast(rhs.datatype_, dt_pool_, false, false);
  switch (oper) {
    case token_type::XOR:
    case token_type::AND:
    case token_type::OR:
    case token_type::SHL:
    case token_type::SHR:
      if (!(DT_VERIFY(castable, lhs, rhs, a->is_an_integer()))) {
        error(obj->opr_,
              "^ & | << >> operators work only for integers, (widening may "
              "occur between smaller to larger numbers, and this is not a "
              "valid case of auto widening)");
      } else if (castable != nullptr) {
        rhs.datatype_ = castable;
      }
      break;
    case token_type::MOD:
    case token_type::DIV:
    case token_type::MUL:
    case token_type::SUB:
      if (!(DT_VERIFY(castable, lhs, rhs, a->is_a_number()))) {
        error(obj->opr_, "% - * / operators work only for numbers, (widening "
                         "may occur between smaller to larger numbers, and "
                         "this is not a valid case of auto widening)");
      } else if (castable != nullptr) {
        rhs.datatype_ = castable;
      }
      break;
    case token_type::PLUS: {
      if (castable != nullptr &&
          (DT_VERIFY(castable, lhs, rhs, (a->is_a_number() || a->is_bool())) ||
           DT_VERIFY(castable, lhs, rhs, (a->is_a_string())))) {
        push(yk_object(castable));
        return;
      }
      if (!(DT_MATCH(lhs, rhs, (a->is_a_number() || a->is_a_string())))) {
        error(obj->opr_,
              "+ operator works only for numbers of same type or strings, "
              "(widening may occur between smaller to larger numbers, and this "
              "is not a valid case of auto widening)");
      }
      if (lhs.datatype_->const_unwrap()->is_sr()) {// sr + sr -> str
        push(yk_object(dt_pool_->create("str")));
        return;
      }
      break;
    }
    case token_type::LESS:
    case token_type::LESS_EQ:
    case token_type::GREAT:
    case token_type::GREAT_EQ:
      if (!(DT_VERIFY(castable, lhs, rhs, a->is_a_number()))) {
        error(obj->opr_, "< > <= >= operators work only for numbers");
      }
      push(yk_object(dt_pool_->create("bool")));
      return;
    case token_type::NOT_EQ:
    case token_type::EQ_EQ:
      if (EITHER_MATCH(
              lhs, rhs,
              (a->is_m_entry() || a->is_sm_entry() || a->is_tuple()))) {
        error(obj->opr_,
              "MEntry/SMEntry/Tuple cannot be compared with == or != operator");
        break;
      }
      // Any 2 string data types can be compared due to auto type casting
      if (lhs.datatype_->const_unwrap()->is_a_string() &&
          rhs.datatype_->const_unwrap()->is_a_string()) {
        push(yk_object(dt_pool_->create("bool")));
        return;
      }
      if (lhs.datatype_->is_none() || rhs.datatype_->is_none()) {
        // can compare with array/anyptr/pointer/none/not primitive
        yk_datatype *to_comp;
        if (lhs.datatype_->is_none()) {
          to_comp = rhs.datatype_->const_unwrap();
        } else {
          to_comp = lhs.datatype_->const_unwrap();
        }
        if (!(to_comp->is_any_ptr() || to_comp->is_array() ||
              to_comp->is_fixed_size_array() || to_comp->is_a_string() ||
              to_comp->is_ptr() || to_comp->is_any_ptr_to_const() ||
              to_comp->is_none() || !to_comp->is_builtin_or_primitive())) {
          error(obj->opr_, "Datatype cannot be compared with None");
          break;
        }
        push(yk_object(dt_pool_->create("bool")));
        return;
      }
      if (!(DT_MATCH(lhs, rhs, true))) {
        error(obj->opr_, "Cannot compare between two data types");
      }
      push(yk_object(dt_pool_->create("bool")));
      return;
    default:
      error(obj->opr_, "Unhandled boolean operator");
      break;
  }
  push(rhs);
}
void type_checker::visit_fncall_expr(fncall_expr *obj) {
  obj->name_->accept(this);
  auto name = pop();
  // Classes
  if (name.object_type_ == object_type::CLASS ||
      name.object_type_ == object_type::MODULE_CLASS) {
    if (!obj->args_.empty()) {
      error(obj->paren_token_,
            "Arguments for object creation is not supported");
    }
    auto class_name = name.string_val_;
    yk_object data;
    if (name.object_type_ == object_type::CLASS) {
      data = yk_object(dt_pool_->create(class_name, filepath_));
    } else {
      data = yk_object(dt_pool_->create(name.string_val_, name.module_file_));
    }
    push(data);
    // Creating a custom object from user defined type / class;
    return;
  }
  // Enums are not allowed to be created
  if (name.object_type_ == object_type::ENUM ||
      name.object_type_ == object_type::MODULE_ENUM) {
    error(obj->paren_token_, "Enum object creation is not supported");
    push(yk_object(dt_pool_));
    return;
  }
  // Functions
  if (name.object_type_ == object_type::FUNCTION ||
      name.object_type_ == object_type::MODULE_FUNCTION) {
    std::vector<yk_object> arguments{};
    for (auto arg : obj->args_) {
      arg->accept(this);
      arguments.push_back(pop());
    }
    def_stmt *funct;
    if (name.object_type_ == object_type::FUNCTION) {
      funct = defs_classes_->get_function(name.string_val_);
    } else {
      auto imp = cf_->get_or_null(name.module_file_);
      funct = imp->data_->dsv_->get_function(name.string_val_);
    }
    // check if it's same size
    if (funct->params_.size() != arguments.size() &&
        !funct->annotations_.varargs_) {
      error(obj->paren_token_, "Too few or too "
                               "much arguments for function call");
      push(yk_object(dt_pool_));// Push None here
      return;
    }
    if (!funct->params_.empty()) {
      auto last_param_index = funct->params_.size() - 1;
      for (auto i = 0; i < funct->params_.size(); i++) {
        auto param = funct->params_[i];
        if (i == last_param_index && funct->annotations_.varargs_) {
          for (auto j = i; j < arguments.size(); j++) {
            auto arg = arguments[j];
            if (!slot_match_with_result(param.data_type_, arg).matched_) {
              std::stringstream message{};
              message << "Variable argument: " << (j + 1) << " mismatches. ";
              message << "Expected: "
                      << param.data_type_->as_string_simplified();
              message << " Provided: " << arg.datatype_->as_string_simplified();
              error(obj->paren_token_, message.str());
            }
          }
        } else {
          auto arg = arguments[i];
          if (!slot_match_with_result(param.data_type_, arg).matched_) {
            std::stringstream message{};
            message << "Parameter & argument " << (i + 1) << " mismatches. ";
            message << "Expected: " << param.data_type_->as_string_simplified();
            message << " Provided: " << arg.datatype_->as_string_simplified();
            error(obj->paren_token_, message.str());
          }
        }
      }
    }
    push(yk_object(funct->return_type_));
    return;
  }
  if (name.object_type_ == object_type::BUILTIN_FUNCTION) {
    std::vector<yk_object> arguments{};
    for (auto arg : obj->args_) {
      arg->accept(this);
      arguments.push_back(pop());
    }
    auto result = builtins_.verify(name.string_val_, arguments, obj->args_,
                                   import_stmts_alias_, filepath_, this,
                                   cf_->directives_.no_stdlib_);
    // Error when calling builtin, if so return None as data type
    if (result.object_type_ == object_type::ERROR_DETECTED) {
      error(obj->paren_token_, result.string_val_);
      push(yk_object(dt_pool_));// Push None here
      return;
    }
    push(result);
    return;
  }
  // Callable function reference can be called
  if (name.datatype_->is_function()) {
    std::vector<yk_object> arguments{};
    for (auto arg : obj->args_) {
      arg->accept(this);
      arguments.push_back(pop());
    }
    /*Function[In[..*/
    auto &params = name.datatype_->args_[0]->args_;
    if (params.size() != arguments.size()) {
      std::stringstream message{};
      message << "Too few or too "
                 "much arguments for function call. ";
      message << "Expected: " << params.size()
              << ", Provided: " << arguments.size();
      error(obj->paren_token_, message.str());
      push(yk_object(dt_pool_));// Push None here
      return;
    }
    for (auto i = 0; i < params.size(); i++) {
      auto param = params[i];
      auto arg = arguments[i];
      if (!slot_match_with_result(param, arg).matched_) {
        std::stringstream message{};
        message << "Function[] call parameter & argument " << (i + 1)
                << " mismatches. ";
        message << "Expected: " << param->as_string_simplified()
                << ", Provided: " << arg.datatype_->as_string_simplified();
        error(obj->paren_token_, message.str());
      }
    }
    auto ret_type = name.datatype_->args_[1];
    if (ret_type->args_.empty()) {
      push(yk_object(dt_pool_));
    } else {
      push(yk_object(ret_type->args_[0]));
    }
    return;
  }
  std::stringstream message{};
  message << "Calling a non callable "
             "or a non existing function";
  auto located_name = obj->name_->locate();
  if (located_name != nullptr) {
    message << " with name: '" << located_name->token_ << "' is not allowed.";
  } else {
    message << " is not allowed.";
  }
  message << " datatype: " << name.datatype_->as_string_simplified();
  error(obj->paren_token_, message.str());
  push(yk_object(dt_pool_));// Push None here
}
void type_checker::visit_grouping_expr(grouping_expr *obj) {
  obj->expression_->accept(this);
  auto inside = pop();
  push(inside);
}
void type_checker::visit_literal_expr(literal_expr *obj) {
  auto data = yk_object(dt_pool_);
  auto literal_type = obj->literal_token_->type_;
  if (literal_type == token_type::STRING ||
      literal_type == token_type::THREE_QUOTE_STRING) {
    data = yk_object(obj->literal_token_->token_, dt_pool_);
  } else if (literal_type == token_type::KEYWORD_TRUE ||
             literal_type == token_type::KEYWORD_FALSE) {
    data = yk_object(true, dt_pool_);
  } else if (literal_type == token_type::INTEGER_BIN ||
             literal_type == token_type::INTEGER_OCT ||
             literal_type == token_type::INTEGER_DECIMAL ||
             literal_type == token_type::INTEGER_HEX) {
    data = yk_object(dt_pool_->create("int"));
  } else if (literal_type == token_type::INTEGER_BIN_8 ||
             literal_type == token_type::INTEGER_OCT_8 ||
             literal_type == token_type::INTEGER_DECIMAL_8 ||
             literal_type == token_type::INTEGER_HEX_8) {
    data = yk_object(dt_pool_->create("i8"));
  } else if (literal_type == token_type::INTEGER_BIN_16 ||
             literal_type == token_type::INTEGER_OCT_16 ||
             literal_type == token_type::INTEGER_DECIMAL_16 ||
             literal_type == token_type::INTEGER_HEX_16) {
    data = yk_object(dt_pool_->create("i16"));
  } else if (literal_type == token_type::INTEGER_BIN_64 ||
             literal_type == token_type::INTEGER_OCT_64 ||
             literal_type == token_type::INTEGER_DECIMAL_64 ||
             literal_type == token_type::INTEGER_HEX_64) {
    data = yk_object(dt_pool_->create("i64"));
  } else if (literal_type == token_type::UINTEGER_BIN ||
             literal_type == token_type::UINTEGER_OCT ||
             literal_type == token_type::UINTEGER_DECIMAL ||
             literal_type == token_type::UINTEGER_HEX) {
    data = yk_object(dt_pool_->create("u32"));
  } else if (literal_type == token_type::UINTEGER_BIN_8 ||
             literal_type == token_type::UINTEGER_OCT_8 ||
             literal_type == token_type::UINTEGER_DECIMAL_8 ||
             literal_type == token_type::UINTEGER_HEX_8) {
    data = yk_object(dt_pool_->create("u8"));
  } else if (literal_type == token_type::UINTEGER_BIN_16 ||
             literal_type == token_type::UINTEGER_OCT_16 ||
             literal_type == token_type::UINTEGER_DECIMAL_16 ||
             literal_type == token_type::UINTEGER_HEX_16) {
    data = yk_object(dt_pool_->create("u16"));
  } else if (literal_type == token_type::UINTEGER_BIN_64 ||
             literal_type == token_type::UINTEGER_OCT_64 ||
             literal_type == token_type::UINTEGER_DECIMAL_64 ||
             literal_type == token_type::UINTEGER_HEX_64) {
    data = yk_object(dt_pool_->create("u64"));
  } else if (literal_type == token_type::DOUBLE_NUMBER) {
    data = yk_object(1.2, dt_pool_);
  } else if (literal_type == token_type::FLOAT_NUMBER) {
    data = yk_object((float) 1.2f, dt_pool_);
  }// else - none data type by default
  push(data);
}
void type_checker::visit_logical_expr(logical_expr *obj) {
  obj->left_->accept(this);
  auto lhs = pop();
  obj->right_->accept(this);
  auto rhs = pop();
  if (!(lhs.is_primitive_or_obj() && lhs.datatype_->const_unwrap()->is_bool() &&
        rhs.is_primitive_or_obj() &&
        rhs.datatype_->const_unwrap()->is_bool())) {
    std::stringstream message{};
    message << "Both LHS and RHS of logical"
               " operator need to be boolean. ";
    message << "LHS: " << lhs.datatype_->as_string_simplified()
            << ", RHS: " << rhs.datatype_->as_string_simplified();
    error(obj->opr_, message.str());
  }
  push(rhs);
}
void type_checker::visit_unary_expr(unary_expr *obj) {
  // -5 - correct, -"some string" is not
  std::stringstream message{};
  obj->right_->accept(this);
  auto rhs = pop();
  if (rhs.is_primitive_or_obj() &&
      (rhs.datatype_->const_unwrap()->is_a_number() ||
       rhs.datatype_->const_unwrap()->is_bool())) {
    if (obj->opr_->type_ == token_type::KEYWORD_NOT &&
        !rhs.datatype_->const_unwrap()->is_bool()) {
      message << "Invalid unary operation. Not operator must follow a boolean.";
      message << " Provided: " << rhs.datatype_->as_string_simplified();
      error(obj->opr_, message.str());
    } else if (obj->opr_->type_ == token_type::TILDE &&
               !rhs.datatype_->is_an_integer()) {
      message << "Bitwise not (~) is only supported for integers.";
      message << " Provided: " << rhs.datatype_->as_string_simplified();
      error(obj->opr_, message.str());
    }
  } else {
    message << "Unary operator is not supported for data type: ";
    message << rhs.datatype_->as_string_simplified();
    error(obj->opr_, message.str());
  }
  push(rhs);
}
void type_checker::visit_variable_expr(variable_expr *obj) {
  auto name = obj->name_->token_;
  if (builtins_.has_builtin(name)) {
    auto b = yk_object(dt_pool_);
    b.object_type_ = object_type::BUILTIN_FUNCTION;
    b.string_val_ = name;
    push(b);
    return;
  }
  if (!scope_.is_defined(name)) {
    std::stringstream message{};
    message << "Undefined name: '" << name << "'";
    error(obj->name_, message.str());
    push(yk_object(dt_pool_));
    return;
  }
  auto value = scope_.get(name);
  // Preserve function name so we can access it
  if (value.object_type_ == object_type::FUNCTION ||
      value.object_type_ == object_type::CLASS ||
      value.object_type_ == object_type::ENUM) {
    value.string_val_ = name;
  }
  push(value);
}
void type_checker::visit_block_stmt(block_stmt *obj) {
  for (auto stm : obj->statements_) { stm->accept(this); }
}
void type_checker::visit_break_stmt(break_stmt *obj) {
  if (peek_scope_type() != ast_type::STMT_WHILE) {
    error(obj->break_token_,
          "Invalid use of break statement outside of while statement.");
  }
}
void type_checker::visit_continue_stmt(continue_stmt *obj) {
  if (peek_scope_type() != ast_type::STMT_WHILE) {
    error(obj->continue_token_, "Invalid use of continue"
                                " statement outside of while statement.");
  }
}
void type_checker::visit_def_stmt(def_stmt *obj) {
  std::stringstream message{};
  // WHY? This is so I can know I am in a function when I'm in a block statement
  push_scope_type(ast_type::STMT_DEF);
  push_function(obj->name_->token_);
  scope_.push();
  std::unordered_set<std::string> param_names{};
  for (auto param : obj->params_) {
    auto name = param.name_->token_;
    if (param_names.find(name) != param_names.end()) {
      message << "Parameter redefinition is not allowed: '" << name << "'";
      error(param.name_, message.str());
      message.str("");
    } else {
      param_names.insert(name);
    }
    if (scope_.is_defined(name)) {
      message << "Parameter shadows outer scope name: " << name;
      error(param.name_, message.str());
      message.str("");
    } else {
      auto data = yk_object(param.data_type_);
      scope_.define(name, data);
    }
  }
  auto body = dynamic_cast<block_stmt *>(obj->function_body_);
  if (obj->annotations_.native_ || obj->annotations_.native_macro_ ||
      obj->annotations_.native_define_) {
    if (body->statements_.size() != 1) {
      error(obj->name_, "@native, @nativemacro, @nativedefine function must "
                        "have only 1 statement");
    } else {
      auto st = body->statements_[0]->get_type();
      if (st != ast_type::STMT_PASS && st != ast_type::STMT_CCODE) {
        error(obj->name_, "@native, @nativemacro, @nativedefine function must "
                          "have only 1 statement,"
                          " which must be of type ccode or pass.");
      }
      if (obj->annotations_.native_ && st == ast_type::STMT_PASS &&
          obj->annotations_.native_arg_.empty()) {
        error(obj->name_,
              "@native function must have a valid argument if pass is used as "
              "the statement");
      }
      if (obj->annotations_.native_macro_ && st == ast_type::STMT_PASS &&
          obj->annotations_.native_macro_arg_.empty()) {
        error(obj->name_,
              "@nativemacro function must have a valid argument if pass is "
              "used as the statement");
      }
      if (obj->annotations_.native_define_ && st == ast_type::STMT_PASS &&
          obj->annotations_.native_define_arg_.empty()) {
        error(obj->name_,
              "@nativedefine function must have a valid argument if pass is "
              "used as the statement");
      }
      if (obj->annotations_.native_ && st == ast_type::STMT_CCODE &&
          !obj->annotations_.native_arg_.empty()) {
        error(obj->name_,
              "@native function must not have an argument if ccode is used");
      }
      if (obj->annotations_.native_macro_ && st == ast_type::STMT_CCODE &&
          !obj->annotations_.native_macro_arg_.empty()) {
        error(
            obj->name_,
            "@nativemacro function must not have an argument if ccode is used");
      }
      if (obj->annotations_.native_define_ && st == ast_type::STMT_CCODE &&
          !obj->annotations_.native_define_arg_.empty()) {
        error(obj->name_,
              "@nativedefine function must not have an argument if ccode is "
              "used");
      }
    }
  } else {
    obj->accept(&return_checker_);
    if (!return_checker_.errors_.empty()) {
      if (body->statements_.back()->get_type() == ast_type::STMT_EXPRESSION) {
        // last statement is an expression statement
        auto st_ex = dynamic_cast<expression_stmt *>(body->statements_.back());
        body->statements_.pop_back();// remove last one
        auto last_return = ast_pool_->c_return_stmt(
            magic_return_token_, st_ex->expression_, nullptr);
        body->statements_.push_back(last_return);
      } else {
        errors_.push_back(return_checker_.errors_.back());
      }
    }
    obj->function_body_->accept(this);
  }
  scope_.pop();
  pop_scope_type();
  pop_function();
}
void type_checker::visit_expression_stmt(expression_stmt *obj) {
  obj->expression_->accept(this);
}
void type_checker::visit_if_stmt(if_stmt *obj) {
  std::stringstream message{};
  // Note the parser rewrites if statement to not include elif,
  //    by structuring them in a nested structure
  obj->expression_->accept(this);
  auto bool_expression = pop();
  if (!bool_expression.is_primitive_or_obj() ||
      !bool_expression.datatype_->const_unwrap()->is_bool()) {
    message << "If statement expression must be a boolean. ";
    message << "Provided: "
            << bool_expression.datatype_->as_string_simplified();
    error(obj->if_keyword_, message.str());
  }
  scope_.push();
  obj->if_branch_->accept(this);
  scope_.pop();
  if (obj->else_branch_ != nullptr) {
    scope_.push();
    obj->else_branch_->accept(this);
    scope_.pop();
  }
}
void type_checker::visit_let_stmt(let_stmt *obj) {
  std::stringstream message{};
  auto name = obj->name_->token_;
  if (scope_.is_defined(name)) {
    message << "Redefining a variable is not allowed: '" << name << "'";
    error(obj->name_, message.str());
  }
  if (obj->data_type_->is_none()) {
    error(obj->name_, "Cannot use None as a data type here");
  }
  auto placeholder = yk_object(obj->data_type_);
  if (obj->expression_ != nullptr) {
    obj->expression_->accept(this);
    auto expression_data = pop();
    handle_assigns(obj->name_, placeholder, expression_data);
  }
  scope_.define(name, placeholder);
}
void type_checker::visit_pass_stmt(pass_stmt *obj) {
  // Nothing to do
}
void type_checker::visit_return_stmt(return_stmt *obj) {
  std::stringstream message{};
  auto function_name = peek_function();
  yk_object return_data_type = yk_object(dt_pool_);
  if (obj->expression_ != nullptr) {
    obj->expression_->accept(this);
    return_data_type = pop();
  }
  if (function_name.empty() ||
      !this->defs_classes_->has_function(function_name)) {
    message << "Invalid use of return statement. ";
    message << "Return statement can only be used inside a function.";
    error(obj->return_keyword_, message.str());
  } else {
    // func cannot be null here.
    auto func = this->defs_classes_->get_function(function_name);
    if (!slot_match_with_result(func->return_type_, return_data_type)
             .matched_) {
      message << "Invalid return data type. ";
      message << "Expected: " << func->return_type_->as_string_simplified();
      message << ", Provided: "
              << return_data_type.datatype_->as_string_simplified();
      error(obj->return_keyword_, message.str());
    }
    obj->result_type_ = func->return_type_;
  }
}
void type_checker::visit_while_stmt(while_stmt *obj) {
  obj->expression_->accept(this);
  auto exp = pop();
  if (!exp.is_primitive_or_obj() || !exp.datatype_->const_unwrap()->is_bool()) {
    error(obj->while_keyword_,
          "While statement expression need to be a boolean");
  }
  push_scope_type(ast_type::STMT_WHILE);
  scope_.push();
  obj->while_body_->accept(this);
  scope_.pop();
  pop_scope_type();
}
void type_checker::check(const std::vector<stmt *> &statements) {
  for (const auto &name : defs_classes_->function_names_) {
    auto function_definition = defs_classes_->get_function(name);
    if (function_definition->params_.size() > 100) {
      error(function_definition->name_,
            "Number of parameters cannot be larger than 100.");
    }
    auto function_placeholder_object = yk_object(dt_pool_);
    function_placeholder_object.object_type_ = object_type::FUNCTION;
    scope_.define_global(name, function_placeholder_object);
  }
  // Define classes
  for (const auto &class_name : defs_classes_->class_names_) {
    auto class_placeholder_object = yk_object(dt_pool_);
    class_placeholder_object.object_type_ = object_type::CLASS;
    scope_.define_global(class_name, class_placeholder_object);
  }
  // Define enums
  for (const auto &enum_name : defs_classes_->enum_names_) {
    auto enum_placeholder_object = yk_object(dt_pool_);
    enum_placeholder_object.object_type_ = object_type::ENUM;
    scope_.define_global(enum_name, enum_placeholder_object);
  }
  // Define global constants
  for (const auto &constant_name : defs_classes_->global_const_names_) {
    auto constant_definition = defs_classes_->get_const(constant_name);
    auto placeholder_object = yk_object(constant_definition->data_type_);
    scope_.define_global(constant_name, placeholder_object);
  }
  for (const auto &constant_name : defs_classes_->global_native_const_names_) {
    auto constant_definition = defs_classes_->get_native_const(constant_name);
    auto placeholder_object = yk_object(constant_definition->data_type_);
    scope_.define_global(constant_name, placeholder_object);
  }
  // Visit all statements
  for (auto st : statements) { st->accept(this); }
}
void type_checker::error(token *tok, const std::string &message) {
  auto err = parsing_error{message, tok};
  errors_.emplace_back(err);
}
void type_checker::error(const std::string &message) {
  auto err = parsing_error{message, "", 0, 0};
  err.token_set_ = false;
  errors_.emplace_back(err);
}
void type_checker::push(const yk_object &data_type) {
  this->object_stack_.push_back(data_type);
}
yk_object type_checker::pop() {
  if (this->object_stack_.empty()) { return yk_object(dt_pool_); }
  auto back = object_stack_.back();
  object_stack_.pop_back();
  return back;
}
void type_checker::push_scope_type(ast_type scope_type) {
  this->scope_type_stack_.emplace_back(scope_type);
}
ast_type type_checker::peek_scope_type() {
  if (this->scope_type_stack_.empty()) {
    return ast_type::STMT_PASS;// Pass is used for unknown
  }
  return this->scope_type_stack_.back();
}
void type_checker::pop_scope_type() {
  if (this->scope_type_stack_.empty()) { return; }
  this->scope_type_stack_.pop_back();
}
void type_checker::push_function(const std::string &prefixed_name) {
  this->function_name_stack_.emplace_back(prefixed_name);
}
std::string type_checker::peek_function() {
  if (this->function_name_stack_.empty()) { return ""; }
  return this->function_name_stack_.back();
}
void type_checker::pop_function() {
  if (this->function_name_stack_.empty()) { return; }
  this->function_name_stack_.pop_back();
}
void type_checker::visit_defer_stmt(defer_stmt *obj) {
  if (obj->expression_ != nullptr) {
    auto st = expression_stmt{obj->expression_};
    this->visit_expression_stmt(&st);
  } else {
    obj->del_statement_->accept(this);
  }
}
void type_checker::visit_class_stmt(class_stmt *obj) {
  // Check for duplicate fields
  std::unordered_set<std::string> members{};
  for (const auto &member : obj->members_) {
    if (members.find(member.name_->token_) != members.end()) {
      std::stringstream message{};
      message << "Duplicate member name: '" << member.name_->token_ << "' ";
      message << "in class/struct: '" << obj->name_->token_ << "'";
      error(member.name_, message.str());
    } else {
      members.insert(member.name_->token_);
    }
  }
}
void type_checker::visit_del_stmt(del_stmt *obj) {
  obj->expression_->accept(this);
  auto deletable_expression = pop();
  yk_datatype *dt = deletable_expression.datatype_->const_unwrap();
  // Cannot delete int, bool. But we can delete sr and str
  if (deletable_expression.is_primitive_or_obj() && dt->is_primitive() &&
      !dt->is_str() && !dt->is_sr()) {
    error(obj->del_keyword_, "Invalid delete statement used on primitives");
  }
  if (dt->is_m_entry() || dt->is_sm_entry() || dt->is_tuple() ||
      dt->is_function() || !deletable_expression.is_primitive_or_obj()) {
    error(obj->del_keyword_,
          "Invalid delete statement used on Tuple/MEntry/SMEntry/Function");
  }
}
void type_checker::visit_get_expr(get_expr *obj) {
  handle_dot_operator(obj->lhs_, obj->dot_, obj->item_);
}
std::string find_closest(const std::string &member,
                         const std::vector<std::string> &members) {
  std::string closest;
  std::size_t closest_distance = 9999999;
  for (const auto &member_name : members) {
    std::size_t distance = ::levenshtein_distance(member, member_name);
    if (distance < closest_distance) {
      closest = member_name;
      closest_distance = distance;
    }
  }
  return closest;
}
void type_checker::handle_dot_operator(expr *lhs_expr, token *dot,
                                       token *member_item) {
  lhs_expr->accept(this);
  auto lhs = pop();
  if (lhs.object_type_ == object_type::MODULE) {
    auto imported = cf_->get_or_null(lhs.string_val_);
    bool has_func = imported->data_->dsv_->has_function(member_item->token_);
    bool has_class = imported->data_->dsv_->has_class(member_item->token_);
    bool has_const = imported->data_->dsv_->has_const(member_item->token_);
    bool has_native_const =
        imported->data_->dsv_->has_native_const(member_item->token_);
    bool has_enum = imported->data_->dsv_->has_enum(member_item->token_);
    auto obj = yk_object(dt_pool_);
    if (has_class) {
      obj.object_type_ = object_type::MODULE_CLASS;
      /* for io.open */
      obj.string_val_ = member_item->token_; /* open */
      obj.module_file_ = lhs.string_val_;    /* file path */
      obj.module_name_ = lhs.module_name_;   /* io */
    } else if (has_func) {
      obj.object_type_ = object_type::MODULE_FUNCTION;
      obj.string_val_ = member_item->token_;
      obj.module_file_ = lhs.string_val_;
      obj.module_name_ = lhs.module_name_;
    } else if (has_enum) {
      obj.object_type_ = object_type::MODULE_ENUM;
      obj.string_val_ = member_item->token_;// enum name
      obj.module_file_ = lhs.string_val_;
      obj.module_name_ = lhs.module_name_;
    } else if (has_const || has_native_const) {
      yk_datatype *dt;
      if (has_const) {
        auto glob = imported->data_->dsv_->get_const(member_item->token_);
        dt = glob->data_type_;
      } else {
        auto glob =
            imported->data_->dsv_->get_native_const(member_item->token_);
        dt = glob->data_type_;
      }
      obj.object_type_ = object_type::PRIMITIVE_OR_OBJ;
      obj.datatype_ = dt;
      obj.string_val_ = member_item->token_;
      obj.module_file_ = lhs.string_val_;
      obj.module_name_ = lhs.module_name_;
    } else {
      auto closest = find_closest(member_item->token_,
                                  imported->data_->dsv_->get_all_names());
      error(dot, "Member not found. Perhaps '" + closest +
                     "' is what you "
                     "meant?");
    }
    push(obj);
    return;
  }
  // --- access enum values ---
  if (lhs.object_type_ == object_type::ENUM ||
      lhs.object_type_ == object_type::MODULE_ENUM) {
    enum_stmt *enum_statement;
    std::string module_file;
    if (lhs.object_type_ == object_type::ENUM) {
      enum_statement = defs_classes_->get_enum(lhs.string_val_);
      module_file = filepath_;
    } else {
      auto imp = cf_->get_or_null(lhs.module_file_);
      enum_statement = imp->data_->dsv_->get_enum(lhs.string_val_);
      module_file = lhs.module_file_;
    }
    for (const auto &member : enum_statement->members_) {
      if (member.name_->token_ == member_item->token_) {
        auto placeholder =
            yk_object(dt_pool_->create(lhs.string_val_, module_file));
        push(placeholder);
        return;
      }
    }
    // -- bad enum value --
    std::vector<std::string> members{};
    members.reserve(enum_statement->members_.size());
    for (const auto &member : enum_statement->members_) {
      members.push_back(member.name_->token_);
    }
    auto closest = find_closest(member_item->token_, members);
    if (closest.empty()) {
      error(dot, "Enum value not found");
    } else {
      error(dot, "Enum value not found. Perhaps '" + closest +
                     "' is what you "
                     "meant?");
    }
    push(yk_object(dt_pool_));
    return;
  }
  if (!lhs.is_primitive_or_obj() ||
      lhs.datatype_->const_unwrap()->is_primitive()) {
    error(dot, "Invalid dot operator, LHS need to be an object");
    push(yk_object(dt_pool_));
    return;
  }
  auto item = member_item->token_;
  bool datatype_of_lhs_found = false;
  std::string closest{};
  if (!lhs.datatype_->module_.empty()) {
    auto mod_file_info = cf_->get_or_null(lhs.datatype_->module_);
    if (mod_file_info != nullptr &&
        mod_file_info->data_->dsv_->has_class(lhs.datatype_->type_)) {
      datatype_of_lhs_found = true;
      auto class_ = mod_file_info->data_->dsv_->get_class(lhs.datatype_->type_);
      for (const auto &member : class_->members_) {
        if (item == member.name_->token_) {
          // Found the member
          auto placeholder = yk_object(dt_pool_);
          placeholder.datatype_ = member.data_type_;
          push(placeholder);
          return;
        }
      }
      std::vector<std::string> members{};
      members.reserve(class_->members_.size());
      for (const auto &member : class_->members_) {
        members.push_back(member.name_->token_);
      }
      closest = find_closest(item, members);
    }
  }
  if (!datatype_of_lhs_found) {
    error(dot, "Cannot find data type of LHS");
  } else {
    if (closest.empty()) {
      error(dot, "Member not found");
    } else {
      error(dot, "Member not found. Perhaps '" + closest +
                     "' is what you "
                     "meant?");
    }
  }
  push(yk_object(dt_pool_));
}
void type_checker::visit_set_expr(set_expr *obj) {
  handle_dot_operator(obj->lhs_, obj->dot_, obj->item_);
}
void type_checker::visit_assign_member_expr(assign_member_expr *obj) {
  obj->set_oper_->accept(this);
  auto lhs = pop();
  obj->right_->accept(this);
  auto rhs = pop();
  handle_assigns(obj->opr_, lhs, rhs);
}
void type_checker::visit_square_bracket_access_expr(
    square_bracket_access_expr *obj) {
  handle_square_access(obj->index_expr_, obj->sqb_token_, obj->name_, false);
}
void type_checker::handle_square_access(expr *index_expr, token *sqb_token,
                                        expr *name_expr, bool mutate) {
  index_expr->accept(this);
  auto index_exp = pop();
  if (!index_exp.datatype_->is_an_integer()) {
    push(yk_object(dt_pool_));
    error(sqb_token, "Invalid index expression, must be of a valid integer");
  }
  name_expr->accept(this);
  auto arr_var = pop();
  yk_datatype *arr_data_type = arr_var.datatype_->const_unwrap();
  if (arr_data_type->is_array() || arr_data_type->is_ptr() ||
      arr_data_type->is_fixed_size_array()) {
    auto placeholder = yk_object(dt_pool_);
    placeholder.datatype_ = arr_data_type->args_[0];
    // --- OK ---
    push(placeholder);
    if (placeholder.datatype_->is_const() && mutate) {
      error(sqb_token, "Mutating an immutable element");
    }
    return;
  }
  if (arr_data_type->is_tuple()) {
    if (index_expr->get_type() != ast_type::EXPR_LITERAL) {
      push(yk_object(dt_pool_));
      error(sqb_token, "Must use a literal for accessing tuple elements");
      return;
    }
    auto lexp = dynamic_cast<literal_expr *>(index_expr);
    // TODO support other literal types for tuple access.
    //   We should be able to also use a const time expression for tuple access as well.
    //   current behaviour is annoying, but it's fine for now.
    if (lexp->literal_token_->type_ != token_type::INTEGER_DECIMAL) {
      push(yk_object(dt_pool_));
      error(sqb_token,
            "Must use a integer decimal literal for accessing tuple elements");
      return;
    }
    auto item = lexp->literal_token_->token_;
    auto index = std::stoi(item);
    if (index < 0 || index >= arr_data_type->args_.size()) {
      push(yk_object(dt_pool_));
      error(sqb_token, "Tuple index out of bounds");
      return;
    }
    auto placeholder = yk_object(dt_pool_);
    placeholder.datatype_ = arr_data_type->args_[index];
    // --- OK ---
    push(placeholder);
    if (placeholder.datatype_->is_const() && mutate) {
      error(sqb_token, "Mutating an immutable element");
    }
    return;
  }
  push(yk_object(dt_pool_));
  error(sqb_token, "Not an array");
}
void type_checker::visit_assign_arr_expr(assign_arr_expr *obj) {
  obj->assign_oper_->accept(this);
  auto lhs = pop();
  obj->right_->accept(this);
  auto rhs = pop();
  handle_assigns(obj->opr_, lhs, rhs);
}
void type_checker::handle_assigns(token *oper, const yk_object &lhs,
                                  const yk_object &rhs) {
  std::stringstream message{};
  if (lhs.datatype_->const_unwrap()->is_fixed_size_array()) {
    // TODO: add support for assign to fixed array without overflowing.
    //  Basically assign as much elements as possible to LHS from RHS (FixedArr, Array, or sr/str/lit),
    //  keep any leftover as is. (We assume whoever assigns knows what they are doing) :)
    //  however, we cannot assign if the args_[0] is a const in a FixedArray, so check for this.
    message << "Cannot assign to a FixedArr[..]. FixedArr variables are not "
               "assignable. lhs: "
            << lhs.datatype_->as_string_simplified();
    message << ", rhs: " << rhs.datatype_->as_string_simplified();
    error(oper, message.str());
  }
  if (lhs.datatype_->const_unwrap()->is_tuple()) {
    // TODO verify What if lhs is a tuple? We can't assign to a tuple,
    //  but we can assign to a tuple element, so we might be able to assign between 2 tuples of exact same type?
    //  if any element in a tuple is a const, then we cannot assign to it.?
    //  we can either skip the const element, or error out. (TBD)
    message << "Cannot assign to a Tuple[..]. Tuple variables are not "
               "assignable. lhs: "
            << lhs.datatype_->as_string_simplified();
    message << ", rhs: " << rhs.datatype_->as_string_simplified();
    error(oper, message.str());
  }
  if (lhs.datatype_->is_const()) { error(oper, "Cannot assign to a constant"); }
  if (rhs.is_a_function() &&
      !slot_match_with_result(lhs.datatype_, rhs).matched_) {
    message << "You can only assign a matching function. lhs: ";
    message << lhs.datatype_->as_string_simplified();
    yk_datatype *arg_datatype = function_to_datatype_or_null(rhs);
    message << ", rhs: ";
    if (arg_datatype != nullptr) {
      message << arg_datatype->as_string_simplified();
    } else {
      message << rhs.datatype_->as_string_simplified();
    }
    error(oper, message.str());
  }
  if ((lhs.is_primitive_or_obj() && rhs.is_primitive_or_obj())) {
    auto rhs_dt = rhs.datatype_->const_unwrap();
    if (is_not_identical_type(lhs.datatype_, rhs_dt)) {
      auto castable =
          lhs.datatype_->auto_cast(rhs.datatype_, dt_pool_, true, true);
      if (castable == nullptr) {
        message << "Cannot assign between 2 different data types. lhs: ";
        message << lhs.datatype_->as_string_simplified();
        message << ", rhs: " << rhs.datatype_->as_string_simplified();
        error(oper, message.str());
      }
    }
  }
  token_type operator_type = oper->type_;
  switch (operator_type) {
    case token_type::AND_EQ:
    case token_type::XOR_EQ:
    case token_type::OR_EQ:
    case token_type::SHL_EQ:
    case token_type::SHR_EQ:
      if (!lhs.datatype_->is_an_integer()) {
        message << "Cannot augment assign for non integer values.";
        message << " lhs: " << lhs.datatype_->as_string_simplified();
        message << ", rhs: " << rhs.datatype_->as_string_simplified();
        error(oper, message.str());
      }
      break;
    case token_type::DIV_EQ:
    case token_type::MOD_EQ:
    case token_type::MUL_EQ:
    case token_type::SUB_EQ:
      if (!lhs.datatype_->is_a_number()) {
        message << "Cannot augment assign for non number values.";
        message << " lhs: " << lhs.datatype_->as_string_simplified();
        message << ", rhs: " << rhs.datatype_->as_string_simplified();
        error(oper, message.str());
      }
      break;
    case token_type::PLUS_EQ:
      // += will not be supported for string references or literals as that makes no sense
      if (!lhs.datatype_->is_a_number() && !lhs.datatype_->is_str()) {
        message << "Cannot use += for data type. lhs: ";
        message << lhs.datatype_->as_string_simplified();
        message << ", rhs: " << rhs.datatype_->as_string_simplified();
        error(oper, message.str());
      }
      break;
    default:
      break;
  }
}
void type_checker::visit_square_bracket_set_expr(square_bracket_set_expr *obj) {
  handle_square_access(obj->index_expr_, obj->sqb_token_, obj->name_, true);
}
void type_checker::visit_ccode_stmt(ccode_stmt *obj) {
  auto fname = peek_function();
  auto fn = defs_classes_->get_function(fname);
  if (!fn->annotations_.native_ && !fn->annotations_.native_macro_) {
    error(obj->ccode_keyword_,
          "Invalid use of ccode statement outside non native function");
  }
}
void type_checker::visit_import_stmt(import_stmt *obj) {
  // Not required to be type checked
}
void type_checker::visit_const_stmt(const_stmt *obj) {
  if (scope_.is_global_level() && !obj->data_type_->args_[0]->is_bool() &&
      !obj->data_type_->args_[0]->is_a_number() &&
      !obj->data_type_->args_[0]->is_sr()) {
    error(obj->name_, "Only number/bool/sr constants are supported.");
  }
  if (obj->expression_ == nullptr) {
    error(obj->name_, "Need a value for the constant");
  }
  auto name = obj->name_->token_;
  auto placeholder = yk_object(obj->data_type_);
  if (obj->expression_ != nullptr) {
    obj->expression_->accept(this);
    auto expression_data = pop();
    yk_datatype *expression_dt = expression_data.datatype_->const_unwrap();
    if (obj->data_type_->args_[0]->is_sr() &&
        !expression_dt->is_string_literal() && scope_.is_global_level()) {
      error(obj->name_, "Const[sr] must use a string literal at the RHS.");
    }
    auto match = type_match(obj->data_type_->args_[0], expression_dt, true);
    if (match.matched_) {
      placeholder = expression_data;
      placeholder.datatype_ = obj->data_type_;// Set the correct data type
    } else {
      std::stringstream message{};
      message << "Constant '" << name << "' data type mismatch. ";
      message << match.error_;
      error(obj->name_, message.str());
    }
  }
  // If this is not a global constant define it
  if (!scope_.is_global_level()) { scope_.define(name, placeholder); }
}
bool type_checker::is_identical_type(yk_datatype *required_datatype,
                                     yk_datatype *provided_datatype) {
  return internal_is_identical_type(required_datatype, provided_datatype);
}
bool type_checker::is_not_identical_type(yk_datatype *required_datatype,
                                         yk_datatype *provided_datatype) {
  return !is_identical_type(required_datatype, provided_datatype);
}
type_match_result type_checker::type_match(yk_datatype *required_datatype,
                                           yk_datatype *provided_datatype,
                                           bool primitive_or_obj) {
  // Identical types match
  if (primitive_or_obj &&
      is_identical_type(required_datatype, provided_datatype)) {
    return type_match_result{"", true, false};
  }
  // Can autocast strings
  if (primitive_or_obj && required_datatype->const_unwrap()->is_a_string() &&
      provided_datatype->const_unwrap()->is_a_string()) {
    return type_match_result{
        "", true, is_not_identical_type(required_datatype, provided_datatype)};
  }
  // Can autocast numbers and booleans
  if (primitive_or_obj && (provided_datatype->const_unwrap()->is_a_number() ||
                           provided_datatype->const_unwrap()->is_bool())) {
    auto castable =
        required_datatype->auto_cast(provided_datatype, dt_pool_, false, true);
    if (castable != nullptr) { return type_match_result{"", true, true}; }
  }
  // Pass a Type to a Const[Type] is allowed (becomes more restrictive)
  if (primitive_or_obj &&
      is_identical_type(required_datatype->const_unwrap(), provided_datatype)) {
    return type_match_result{"", true, false};
  }
  std::stringstream message{};
  message << "data type mismatch. Expected: ";
  message << required_datatype->as_string_simplified();
  message << ", Provided: ";
  message << provided_datatype->as_string_simplified();
  return type_match_result{message.str(), false, false};
}
type_match_result
type_checker::slot_match_with_result(yk_datatype *datatype,
                                     const yk_object &provided_arg) {
  std::stringstream message{};
  // If we passed in a builtin function to an argument then we cannot use that
  //  error out as this is not allowed
  if (provided_arg.object_type_ == object_type::BUILTIN_FUNCTION &&
      datatype->is_function()) {
    message
        << "Cannot use builtin functions as a function pointers. Expected: ";
    message << datatype->as_string_simplified();
    return type_match_result{message.str(), false, false};
  }
  // Type check for function passed as is
  if (provided_arg.is_a_function() && datatype->is_function()) {
    yk_datatype *arg_datatype = function_to_datatype_or_null(provided_arg);
    if (arg_datatype != nullptr) {
      return type_match(datatype, arg_datatype, true);
    } else {
      message << "Invalid function pointer provided. Expected: ";
      message << datatype->as_string_simplified();
      return type_match_result{message.str(), false, false};
    }
  }
  // Type check for primitive or object
  auto lhs = datatype;
  auto lhsu = lhs->const_unwrap();
  auto rhs = provided_arg.datatype_;
  auto rhsu = rhs->const_unwrap();
  // Both are native primitives
  if (lhsu->is_c_primitive() && rhsu->is_c_primitive()) {
    return type_match(lhsu, rhsu, true);
  }
  return type_match(datatype, provided_arg.datatype_,
                    provided_arg.is_primitive_or_obj());
}
type_match_result type_checker::rvalue_match(const yk_object &left_side,
                                             const yk_object &right_side) {
  std::stringstream message{};
  if (left_side.is_a_function() && right_side.is_a_function()) {
    yk_datatype *lhs = function_to_datatype_or_null(left_side);
    yk_datatype *rhs = function_to_datatype_or_null(right_side);
    if (lhs != nullptr && rhs != nullptr) { return type_match(lhs, rhs, true); }
  } else if (left_side.is_a_function()) {
    yk_datatype *lhs = function_to_datatype_or_null(left_side);
    if (lhs == nullptr) {
      message << "Invalid function pointer provided. Expected: ";
      message << left_side.datatype_->as_string_simplified();
      return type_match_result{message.str(), false, false};
    }
    return slot_match_with_result(lhs, right_side);
  } else if (right_side.is_a_function()) {
    yk_datatype *rhs = function_to_datatype_or_null(right_side);
    if (rhs == nullptr) {
      message << "Invalid function pointer provided. Expected: ";
      message << left_side.datatype_->as_string_simplified();
      return type_match_result{message.str(), false, false};
    }
    return type_match(left_side.datatype_, rhs, true);
  }
  return type_match(left_side.datatype_->const_unwrap(),
                    right_side.datatype_->const_unwrap(),
                    right_side.is_primitive_or_obj());
}
yk_datatype *type_checker::function_to_datatype_or_null(const yk_object &arg) {
  def_stmt *funct;
  if (arg.object_type_ == object_type::FUNCTION) {
    funct = defs_classes_->get_function(arg.string_val_);
  } else {
    auto imp = cf_->get_or_null(arg.module_file_);
    funct = imp->data_->dsv_->get_function(arg.string_val_);
  }
  if (funct->annotations_.varargs_) {
    // WHY? not yet supported
    error("@varargs function cannot be used as function pointers");
    return nullptr;
  }
  if (funct->annotations_.native_macro_ || funct->annotations_.native_define_) {
    // WHY? not possible as these are macros
    error("@nativemacro and @nativedefine functions cannot be used as function "
          "pointers");
    return nullptr;
  }
  // Create datatype out of function
  yk_datatype *fnc = dt_pool_->create("Function");
  yk_datatype *fin = dt_pool_->create("In");
  yk_datatype *fout = dt_pool_->create("Out");
  fnc->args_.emplace_back(fin);
  fnc->args_.emplace_back(fout);
  for (auto current_param : funct->params_) {
    fin->args_.emplace_back(current_param.data_type_);
  }
  if (!funct->return_type_->is_none()) {
    fout->args_.emplace_back(funct->return_type_);
  }
  // Compare now
  return fnc;
}
void type_checker::visit_runtimefeature_stmt(runtimefeature_stmt *obj) {
  // This is not required to be type checked
}
void type_checker::visit_nativeconst_stmt(nativeconst_stmt *obj) {
  if (!scope_.is_global_level()) {
    scope_.define(obj->name_->token_, yk_object(obj->data_type_));
  }
}
void type_checker::visit_foreach_stmt(foreach_stmt *obj) {
  std::stringstream message{};
  obj->expression_->accept(this);
  auto exp = pop();
  // Derive data type of foreach-s expression and fill it to AST
  obj->expr_datatype_ = exp.datatype_;
  // TODO: see if we can add similar data types to rest of the AST objects?
  //   if, while, del, defer, return?
  if (!exp.datatype_->const_unwrap()->is_array() &&
      !exp.datatype_->const_unwrap()->is_fixed_size_array()) {
    message << "Foreach statement expression must be an array. ";
    message << "Provided: " << exp.datatype_->as_string_simplified();
    error(obj->for_keyword_, message.str());
  }
  if ((exp.datatype_->const_unwrap()->is_array() &&
       !exp.datatype_->const_unwrap()->args_.empty() &&
       (exp.datatype_->const_unwrap()->args_[0]->is_sm_entry() ||
        exp.datatype_->const_unwrap()->args_[0]->is_m_entry()))) {
    message << "Cannot use foreach iteration for SMEntry and MEntry.";
    error(obj->for_keyword_, message.str());
  }
  if (scope_.is_defined(obj->name_->token_)) {
    message << "Foreach: shadows outer scope name: '" << obj->name_->token_
            << "'";
    error(obj->name_, message.str());
  }
  if (exp.datatype_->const_unwrap()->args_.empty()) {
    // We do not have any information to continue
    // continuing here will cause a segfault
    return;
  }
  // Infer data type of foreach and fill it to AST
  if (obj->data_type_ == nullptr) {
    obj->data_type_ = exp.datatype_->const_unwrap()->args_[0];
  }
  auto lhs = exp.datatype_->const_unwrap()->args_[0];
  auto rhs = obj->data_type_;
  auto match = type_match(lhs, rhs, true);
  if (!match.matched_) {
    message << "Foreach statement " << match.error_;
    error(obj->for_keyword_, message.str());
  }
  push_scope_type(ast_type::STMT_WHILE);
  scope_.push();
  scope_.define(obj->name_->token_, yk_object(obj->data_type_));
  obj->for_body_->accept(this);
  scope_.pop();
  pop_scope_type();
}
void type_checker::visit_forendless_stmt(forendless_stmt *obj) {
  push_scope_type(ast_type::STMT_WHILE);
  scope_.push();
  obj->for_body_->accept(this);
  scope_.pop();
  pop_scope_type();
}
void type_checker::visit_compins_stmt(compins_stmt *obj) {
  // Does not occur in AST
  // Does not need to be type checked at the moment
}
class_stmt *type_checker::find_class_or_null(token *tok,
                                             yk_datatype *data_type) {
  // If this is a primitive / builtin it is not a user defined class
  if (data_type->const_unwrap()->is_builtin_or_primitive()) {
    error(tok, "Primitives/builtins cannot be created as a struct literal");
    return nullptr;
  }
  auto mod = cf_->get_or_null(data_type->module_);
  if (mod == nullptr) {
    error(tok, "Module not found");
    return nullptr;
  }
  if (mod->data_->dsv_->has_class(data_type->type_)) {
    return mod->data_->dsv_->get_class(data_type->type_);
  }
  error(tok, "Class/struct not found");
  return nullptr;
}
void type_checker::validate_member(name_val &member, class_stmt *class_st) {
  std::stringstream message{};
  yk_datatype *class_member_dt = nullptr;
  std::vector<std::string> members{};
  for (auto const &para : class_st->members_) {
    if (para.name_->token_ == member.name_->token_) {
      class_member_dt = para.data_type_;
    }
    members.push_back(para.name_->token_);
  }
  if (class_member_dt == nullptr) {
    std::string closest = find_closest(member.name_->token_, members);
    message << "Member '" << member.name_->token_
            << "' not found in class/struct '";
    message << class_st->name_->token_ << "'. Perhaps '" << closest;
    message << "' is what you meant?";
    error(member.name_, message.str());
    return;
  }
  member.value_->accept(this);
  auto set_value = pop();
  yk_datatype *member_dt = set_value.datatype_->const_unwrap();
  auto match = type_match(class_member_dt, member_dt, true);
  if (!match.matched_) {
    message << "Member '" << member.name_->token_
            << "' data type mismatch for class/struct '";
    message << class_st->name_->token_ << "'." << match.error_;
    error(member.name_, message.str());
  }
}
void type_checker::visit_curly_call_expr(curly_call_expr *obj) {
  std::stringstream message{};
  obj->dt_expr_->accept(this);
  auto dt_class = pop();
  if (dt_class.object_type_ == object_type::CLASS ||
      dt_class.object_type_ == object_type::MODULE_CLASS) {
    auto class_name = dt_class.string_val_;
    yk_object data;
    if (dt_class.object_type_ == object_type::CLASS) {
      data = yk_object(dt_pool_->create(class_name, filepath_));
    } else {
      data = yk_object(
          dt_pool_->create(dt_class.string_val_, dt_class.module_file_));
    }
    /* ----------------------------------------- */
    // Member validation
    std::unordered_set<std::string> names{};
    for (auto nv : obj->values_) {
      if (names.find(nv.name_->token_) != names.end()) {
        message << "Duplicate field '" << nv.name_->token_
                << "' in class/struct literal.";
        error(nv.name_, message.str());
        break;
      }
      names.insert(nv.name_->token_);
    }
    // Match data type of each element with member data type
    auto class_stmt = find_class_or_null(obj->curly_open_, data.datatype_);
    if (class_stmt == nullptr) {
      // Note error is created in find_class, so no need to do it again here
      push(yk_object(dt_pool_));
      return;
    }
    for (auto &member : obj->values_) { validate_member(member, class_stmt); }
    /* ----------------------------------------- */
    push(data);
  } else {
    error(obj->curly_open_, "Invalid datatype for {} initialization");
  }
}
void type_checker::visit_macro_call_expr(macro_call_expr *obj) {
  // Not required to be type checked
}
void type_checker::visit_cfor_stmt(cfor_stmt *obj) {
  push_scope_type(ast_type::STMT_WHILE);
  scope_.push();
  if (obj->init_expr_ != nullptr) { obj->init_expr_->accept(this); }
  if (obj->comparison_ != nullptr) {
    obj->comparison_->accept(this);
    auto comp = pop();
    if (!comp.datatype_->const_unwrap()->is_bool()) {
      error(obj->semi1_, "Comparison must be a boolean operation");
    }
  }
  if (obj->operation_ != nullptr) { obj->operation_->accept(this); }
  obj->for_body_->accept(this);
  scope_.pop();
  pop_scope_type();
}
void type_checker::visit_enum_stmt(enum_stmt *obj) {
  std::unordered_set<std::string> names{};
  for (auto nv : obj->members_) {
    if (names.find(nv.name_->token_) != names.end()) {
      std::stringstream message{};
      message << "Duplicate enum value '" << nv.name_->token_ << "' ";
      message << "in enum '" << obj->name_->token_ << "'";
      error(nv.name_, message.str());
      break;
    }
    names.insert(nv.name_->token_);
  }
}
void type_checker::visit_directive_stmt(directive_stmt *obj) {}
