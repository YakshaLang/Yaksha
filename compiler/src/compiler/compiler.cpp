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
// compiler.cpp
#include "compiler.h"
#include "ast/parser.h"
#include <cinttypes>
using namespace yaksha;
compiler::compiler(def_class_visitor &defs_classes, ykdt_pool *pool,
                   entry_struct_func_compiler *esc, gc_pool<token> *token_pool)
    : defs_classes_(defs_classes), scope_(pool), dt_pool_(pool),
      builtins_(pool, token_pool), ast_pool_(new ast_pool()), esc_(esc),
      desugar_(new desugaring_compiler{ast_pool_, dt_pool_}) {}
compiler::~compiler() {
  delete ast_pool_;
  delete desugar_;
}
void compiler::visit_assign_expr(assign_expr *obj) {
  if (obj->promoted_) {
    auto let_st = ast_pool_->c_let_stmt(obj->name_, nullptr, obj->right_);
    let_st->accept(this);
    return;
  }
  obj->right_->accept(this);
  auto rhs = pop();
  auto name = prefix(obj->name_->token_, prefix_val_);
  auto object = scope_.get(name);
  auto o = std::make_pair(name, object);
  perform_assign(o, rhs, obj->opr_, true, true);
}
void compiler::perform_assign(std::pair<std::string, ykobject> &lhs,
                              std::pair<std::string, ykobject> &rhs,
                              token *operator_token, bool assign_variable,
                              bool lhs_mutates) {
  auto castable = lhs.second.datatype_->auto_cast(rhs.second.datatype_,
                                                  dt_pool_, lhs_mutates, true);
  write_indent(body_);
  if (castable != nullptr &&
      (lhs.second.datatype_->const_unwrap()->is_a_number() ||
       lhs.second.datatype_->const_unwrap()->is_bool())) {
    // Number cast that we can do here
    body_ << lhs.first << " " << operator_token->token_ << " ";
    cast_numbers(castable, lhs, rhs);
    if (lhs.second.is_primitive_or_obj() &&
        lhs.second.datatype_->const_unwrap()->is_f32() &&
        operator_token->type_ == token_type::MOD_EQ) {// Float %=
      body_ << "remainderf(" << lhs.first << ", " << rhs.first << ")";
    } else if (lhs.second.is_primitive_or_obj() &&
               lhs.second.datatype_->const_unwrap()->is_f64() &&
               operator_token->type_ == token_type::MOD_EQ) {// Double %=
      body_ << "remainder(" << lhs.first << ", " << rhs.first << ")";
    } else {
      body_ << rhs.first;
    }
    LOG_COMP("cast assign:" << lhs.first << " " << operator_token->token_ << " "
                            << rhs.first);
  } else if (rhs.second.is_primitive_or_obj() &&
             rhs.second.datatype_->const_unwrap()->is_a_string() &&
             operator_token->type_ == token_type::EQ) {
    // if lhs is str, we need to free the current value here --
    if (assign_variable && lhs.second.datatype_->const_unwrap()->is_str()) {
      body_ << "yk__sdsfree(" << lhs.first << ")";
      write_end_statement(body_);
      write_indent(body_);
    }
    // duplicate the input.
    // do assignment of the duplicate
    body_ << lhs.first << " = ";
    compile_string_assign(operator_token, body_, rhs,
                          rhs.second.datatype_->const_unwrap(),
                          lhs.second.datatype_->const_unwrap());
  } else if (rhs.second.is_primitive_or_obj() &&
             rhs.second.datatype_->const_unwrap()->is_a_string() &&
             operator_token->type_ == token_type::PLUS_EQ) {
    // -- str +=
    if (rhs.second.datatype_->const_unwrap()->is_str()) {
      body_ << lhs.first << " = yk__append_sds_sds(" << lhs.first << ", "
            << rhs.first << ")";
    } else if (rhs.second.datatype_->const_unwrap()->is_sr()) {
      body_ << lhs.first << " = yk__append_sds_bstr(" << lhs.first << ", "
            << rhs.first << ")";
    } else if (rhs.second.datatype_->const_unwrap()->is_string_literal()) {
      auto u = string_utils::unescape(rhs.second.string_val_);
      body_ << lhs.first << " = "
            << "yk__append_sds_lit(" << lhs.first << ", \""
            << string_utils::escape(u) << "\" , " << u.size() << ")";
    } else {
      error("Cannot compile += for str");
    }
  } else if (rhs.second.is_a_function()) {
    body_ << lhs.first << " = " << prefix_function_arg(rhs);
  } else if (rhs.second.is_primitive_or_obj() &&
             operator_token->type_ == token_type::MOD_EQ &&
             rhs.second.datatype_->const_unwrap()->is_f32()) {
    // f32 %=
    body_ << lhs.first << " = "
          << "remainderf(" << lhs.first + ", " + rhs.first + ")";
  } else if (rhs.second.is_primitive_or_obj() &&
             operator_token->type_ == token_type::MOD_EQ &&
             rhs.second.datatype_->const_unwrap()->is_f64()) {
    // f64 %=
    body_ << lhs.first << " = "
          << "remainder(" << lhs.first + ", " + rhs.first + ")";
  } else {// usual case
    body_ << lhs.first << " " << operator_token->token_ << " " << rhs.first;
  }
  write_end_statement(body_);
}
void compiler::visit_binary_expr(binary_expr *obj) {
  token_type operator_type = obj->opr_->type_;
  // Vist left side of the binary expression and right side.
  // This should give us the data types from the 2 stacks we maintain.
  obj->left_->accept(this);
  auto lhs = pop();
  obj->right_->accept(this);
  auto rhs = pop();
  LOG_COMP("binary: " << lhs.first << " " << obj->opr_->token_ << " "
                      << rhs.first);
  // Note: we are assuming data type to be same as first,
  // Since this will be type checked using type_checker.
  //  auto data_type = lhs.second;
  bool both_sr = lhs.second.datatype_->const_unwrap()->is_sr() &&
                 rhs.second.datatype_->const_unwrap()->is_sr();
  bool different_types = (*(lhs.second.datatype_->const_unwrap()) !=
                          *(rhs.second.datatype_->const_unwrap()));
  if (lhs.second.datatype_->is_none() || rhs.second.datatype_->is_none()) {
    // both null
    if (lhs.second.datatype_->is_none() && rhs.second.datatype_->is_none()) {
      // None == None -> True
      // None !- None -> False
      push(operator_type == token_type::EQ_EQ ? "true" : "false",
           ykobject(dt_pool_->create("bool")));
    } else if (lhs.second.datatype_->is_none()) {
      // rhs is not None
      if (rhs.second.datatype_->const_unwrap()->is_sr()) {
        push("(NULL " + obj->opr_->token_ + " yk__bstr_get_reference(" +
                 rhs.first + "))",
             ykobject(dt_pool_->create("bool")));
      } else if (rhs.second.datatype_->const_unwrap()->is_string_literal()) {
        push(operator_type != token_type::EQ_EQ ? "true" : "false",
             ykobject(dt_pool_->create("bool")));
      } else {
        push("(NULL " + obj->opr_->token_ + " " + rhs.first + ")",
             ykobject(dt_pool_->create("bool")));
      }
    } else {
      // lhs is not None
      if (lhs.second.datatype_->const_unwrap()->is_sr()) {
        push("(yk__bstr_get_reference(" + lhs.first + ") " + obj->opr_->token_ +
                 " NULL)",
             ykobject(dt_pool_->create("bool")));
      } else if (lhs.second.datatype_->const_unwrap()->is_string_literal()) {
        push(operator_type != token_type::EQ_EQ ? "true" : "false",
             ykobject(dt_pool_->create("bool")));
      } else {
        push("(" + lhs.first + " " + obj->opr_->token_ + " NULL)",
             ykobject(dt_pool_->create("bool")));
      }
    }
  } else if (lhs.second.is_primitive_or_obj() &&
             rhs.second.is_primitive_or_obj() && (both_sr || different_types)) {
    // we are in an auto cast scenario
    if (lhs.second.datatype_->const_unwrap()->is_a_string() &&
        rhs.second.datatype_->const_unwrap()->is_a_string()) {
      auto lhsd = lhs.second.datatype_->const_unwrap();
      auto lhsdn = lhsd->is_sr() ? "bstr" : (lhsd->is_str() ? "sds" : "lit");
      std::string lhs_code = lhs.first;
      if (lhsd->is_string_literal()) {
        auto s = string_utils::unescape(lhs.second.string_val_);
        lhs_code =
            "\"" + string_utils::escape(s) + "\", " + std::to_string(s.size());
      }
      auto rhsd = rhs.second.datatype_->const_unwrap();
      auto rhsdn = rhsd->is_sr() ? "bstr" : (rhsd->is_str() ? "sds" : "lit");
      std::string rhs_code = rhs.first;
      if (rhsd->is_string_literal()) {
        auto s = string_utils::unescape(rhs.second.string_val_);
        rhs_code =
            "\"" + string_utils::escape(s) + "\", " + std::to_string(s.size());
      }
      if (operator_type == token_type::EQ_EQ ||
          operator_type == token_type::NOT_EQ) {
        std::string code = std::string{"(yk__cmp_"} + lhsdn + "_" + rhsdn +
                           "(" + lhs_code + ", " + rhs_code + ")";
        if (operator_type == token_type::EQ_EQ) {
          code += " == 0)";
        } else {
          code += " != 0)";
        }
        push(code, ykobject(dt_pool_->create("bool")));
      } else if (operator_type ==
                 token_type::PLUS) {// :s:|str|lit + :s:|str|lit --> str
        auto temporary_string = temp();
        // put the temp to the deletions stack
        deletions_.push(temporary_string,
                        "yk__sdsfree(" + temporary_string + ")");
        // duplicate lhs
        // call sdscatsds
        // assign to the temp
        write_indent(body_);
        body_ << "yk__sds " << temporary_string << " = "
              << "yk__concat_" << lhsdn << "_" << rhsdn << "(" << lhs_code
              << ", " << rhs_code << ")";
        write_end_statement(body_);
        push(temporary_string, ykobject(dt_pool_->create("str")));
      } else {
        error(obj->opr_, "Failed to compile string binary operation");
        push("<><>", rhs.second);
      }
    } else {
      auto castable = lhs.second.datatype_->auto_cast(rhs.second.datatype_,
                                                      dt_pool_, false, false);
      LOG_COMP("binary castable: " << castable->as_string());
      LOG_COMP("binary castable widen lhs: " << castable->widen_lhs);
      LOG_COMP("binary castable widen rhs: " << castable->widen_rhs);
      if (castable == nullptr) {
        error(obj->opr_, "Failed to compile binary operation");
        push("<><>", rhs.second);
      } else {
        LOG_COMP("binary before lhs: " << lhs.first);
        LOG_COMP("binary before lhs: " << lhs.second.datatype_->as_string());
        LOG_COMP("binary before rhs: " << rhs.first);
        LOG_COMP("binary before rhs: " << rhs.second.datatype_->as_string());
        cast_numbers(castable, lhs, rhs);
        LOG_COMP("binary after lhs: " << lhs.first);
        LOG_COMP("binary after lhs: " << lhs.second.datatype_->as_string());
        LOG_COMP("binary after rhs: " << rhs.first);
        LOG_COMP("binary after rhs: " << rhs.second.datatype_->as_string());
        compile_simple_bin_op(obj, operator_type, lhs, rhs);
      }
    }
  } else if (lhs.second.is_primitive_or_obj() &&
             lhs.second.datatype_->is_str()) {// str +|==|!= str
    if (obj->opr_->type_ == token_type::EQ_EQ) {
      push("(yk__sdscmp(" + lhs.first + " , " + rhs.first + ") == 0)",
           ykobject(dt_pool_->create("bool")));
    } else if (obj->opr_->type_ == token_type::NOT_EQ) {
      push("(yk__sdscmp(" + lhs.first + " , " + rhs.first + ") != 0)",
           ykobject(dt_pool_->create("bool")));
    } else {// String concat using + operator
      // new temp needs to be created
      auto temporary_string = temp();
      // put the temp to the deletions stack
      deletions_.push(temporary_string,
                      "yk__sdsfree(" + temporary_string + ")");
      // duplicate lhs
      // call sdscatsds
      // assign to the temp
      write_indent(body_);
      body_ << "yk__sds " << temporary_string << " = yk__sdscatsds(yk__sdsdup("
            << lhs.first << "), " << rhs.first << ")";
      write_end_statement(body_);
      // push the temp
      push(temporary_string, lhs.second);
    }
  } else if (lhs.second.is_primitive_or_obj() &&
             lhs.second.datatype_->is_string_literal()) {// :s: +|==|!= :s:
    // compile time +,==,!=
    auto lhsu = string_utils::unescape(lhs.second.string_val_);
    auto rhsu = string_utils::unescape(rhs.second.string_val_);
    if (operator_type == token_type::PLUS) {
      std::string result = string_utils::escape(lhsu + rhsu);
      // just keep rhs and update its string value by combining 2 strings together
      rhs.second.string_val_ = result;
      push(rhs.first, rhs.second);
    } else if (operator_type == token_type::EQ_EQ) {
      bool eq = lhsu == rhsu;
      push(eq ? "true" : "false", ykobject(dt_pool_->create("bool")));
    } else if (operator_type == token_type::NOT_EQ) {
      bool neq = lhsu != rhsu;
      push(neq ? "true" : "false", ykobject(dt_pool_->create("bool")));
    } else {
      error("Failed to compile literal string binary operation");
      push("<><>", rhs.second);
    }
  } else {
    compile_simple_bin_op(obj, operator_type, lhs, rhs);
  }
  // Note: type checker prevents compiler coming here with non integer data types
}
void compiler::cast_numbers(
    const ykdatatype *castable, std::pair<std::string, ykobject> &lhs,
    std::pair<std::string, ykobject> &rhs) {// --- number casting ---
  std::pair<std::string, ykobject> &wider_dt =
      (castable->widen_rhs) ? lhs : rhs;
  std::pair<std::string, ykobject> &to_widen =
      (castable->widen_rhs) ? rhs : lhs;
  auto code = to_widen.first;
  LOG_COMP("cast to widen: " << to_widen.first);
  LOG_COMP("cast to widen: " << to_widen.second.datatype_->as_string());
  LOG_COMP("cast to keep: " << wider_dt.first);
  LOG_COMP("cast to keep: " << wider_dt.second.datatype_->as_string());
  if (to_widen.second.datatype_->const_unwrap()->is_bool()) {
    // bool to integer -->
    code = "((" + code + ") ? 1 : 0)";
  }
  to_widen.first = "((" +
                   convert_dt(wider_dt.second.datatype_->const_unwrap()) +
                   ")(" + code + "))";
  to_widen.second.datatype_ = wider_dt.second.datatype_->const_unwrap();
  LOG_COMP("cast_num: " << lhs.second.datatype_->as_string() << "--"
                        << lhs.first << " <bin> "
                        << rhs.second.datatype_->as_string() << "--"
                        << rhs.first);
}
void compiler::compile_simple_bin_op(
    const binary_expr *obj, const token_type &operator_type,
    const std::pair<std::string, ykobject> &lhs,
    const std::pair<std::string, ykobject> &rhs) {
  if (lhs.second.is_primitive_or_obj() &&
      lhs.second.datatype_->const_unwrap()->is_f32() &&
      obj->opr_->type_ == token_type::MOD) {// Float %
    push("remainderf(" + lhs.first + ", " + rhs.first + ")", lhs.second);
  } else if (lhs.second.is_primitive_or_obj() &&
             lhs.second.datatype_->const_unwrap()->is_f64() &&
             obj->opr_->type_ == token_type::MOD) {// Double %
    push("remainder(" + lhs.first + ", " + rhs.first + ")", lhs.second);
  } else if (operator_type == token_type::LESS ||
             operator_type == token_type::LESS_EQ ||
             operator_type == token_type::GREAT ||
             operator_type == token_type::GREAT_EQ ||
             operator_type == token_type::NOT_EQ ||
             operator_type == token_type::EQ_EQ) {
    push("(" + lhs.first + " " + obj->opr_->token_ + " " + rhs.first + ")",
         ykobject(dt_pool_->create("bool")));
  } else {// Other number stuff
    push("(" + lhs.first + " " + obj->opr_->token_ + " " + rhs.first + ")",
         lhs.second);
  }
}
void compiler::visit_fncall_expr(fncall_expr *obj) {
  obj->name_->accept(this);
  auto name_pair = pop();
  auto name = name_pair.first;
  std::stringstream code{};
  // Depending on the fact that this is a function or class, we will call or create object
  if (name_pair.second.object_type_ == object_type::BUILTIN_FUNCTION) {
    std::vector<std::pair<std::string, ykobject>> args{};
    int i = 0;
    for (auto arg : obj->args_) {
      arg->accept(this);
      auto val = pop();
      if (val.second.is_a_function()) {
        args.emplace_back(prefix_function_arg(val), val.second);
      } else {
        args.emplace_back(val);
      }
      i++;
    }
    auto result =
        builtins_.compile(name, args, obj->args_, this, import_stmts_alias_,
                          filepath_, this, this, esc_);
    push(result.first, result.second);
  } else if (name_pair.second.object_type_ == object_type::MODULE_CLASS) {
    auto module_file = name_pair.second.module_file_;
    auto module_class = name_pair.second.string_val_;
    auto module_prefix = cf_->get_or_null(module_file)->prefix_;
    auto class_ =
        cf_->get_or_null(module_file)->data_->dsv_->get_class(module_class);
    if (class_->annotations_.on_stack_) {
      error(obj->paren_token_, "Cannot construct an @onstack object");
    }
    auto prefixed_class_name = prefix(module_class, module_prefix);
    compile_obj_creation(prefixed_class_name, code,
                         dt_pool_->create(module_class, module_file));
  } else if (name_pair.second.object_type_ == object_type::MODULE_FUNCTION) {
    auto module_file = name_pair.second.module_file_;
    auto module_fn = name_pair.second.string_val_;
    auto module_info = cf_->get_or_null(module_file);
    auto module_prefix = module_info->prefix_;
    auto prefixed_fn_name = prefix(module_fn, module_prefix);
    auto fndef = module_info->data_->dsv_->get_function(module_fn);
    auto fn_return = fndef->return_type_;
    std::vector<ykdatatype *> params{};
    params.reserve(fndef->params_.size());
    for (auto &p : fndef->params_) { params.emplace_back(p.data_type_); }
    compile_function_call(obj, prefixed_fn_name, code, fn_return, params,
                          fndef->annotations_.varargs_);
  } else if (defs_classes_.has_function(name)) {
    auto fn_def = defs_classes_.get_function(name);
    auto return_type = fn_def->return_type_;
    std::vector<ykdatatype *> params{};
    params.reserve(fn_def->params_.size());
    for (auto &p : fn_def->params_) { params.emplace_back(p.data_type_); }
    compile_function_call(obj, prefix(name, prefix_val_), code, return_type,
                          params, fn_def->annotations_.varargs_);
  } else if (defs_classes_.has_class(name)) {
    auto class_ = defs_classes_.get_class(name);
    if (class_->annotations_.on_stack_) {
      error(obj->paren_token_, "Cannot construct an @onstack object");
    }
    compile_obj_creation(prefix(name, prefix_val_), code,
                         dt_pool_->create(name));
  } else if (name_pair.second.datatype_->is_function()) {
    auto ret_type = name_pair.second.datatype_->args_[1];
    ykdatatype *return_type;
    if (ret_type->args_.empty()) {
      return_type = dt_pool_->create("None");
    } else {
      return_type = ret_type->args_[0];
    }
    compile_function_call(obj, prefix(name, prefix_val_), code, return_type,
                          name_pair.second.datatype_->args_[0]->args_, false);
  } else {
    error(obj->paren_token_, "Invalid function call compilation");
  }
}
void compiler::compile_obj_creation(const std::string &name,
                                    std::stringstream &code,
                                    ykdatatype *return_type) {
  obj_calloc(name, code);
  auto data = ykobject(return_type);
  push(code.str(), data);
}
void compiler::obj_calloc(const std::string &name, std::stringstream &code) {
  code << "calloc(1, sizeof(struct " << name << "))";
}
void compiler::compile_function_call(
    fncall_expr *obj, const std::string &name, std::stringstream &code,
    ykdatatype *return_type, const std::vector<ykdatatype *> &parameters,
    bool varargs_fnc) {
  // Note: no need to check here as type_checker & def_class_visitor ensure this is present.
  code << name << "(";
  bool first = true;
  size_t arg_size = obj->args_.size();
  size_t param_size = parameters.size();
  for (size_t i = 0; i < arg_size; i++) {
    auto arg = obj->args_[i];
    ykdatatype *param;
    if (i >= param_size) {
      param = parameters[param_size - 1];
    } else {
      param = parameters[i];
    }
    arg->accept(this);
    auto arg_val = pop();
    if (!first) {
      code << ", ";
    } else {
      first = false;
    }
    if (arg_val.second.is_primitive_or_obj() &&
        arg_val.second.datatype_->const_unwrap()->is_a_string()) {
      auto ad = arg_val.second.datatype_->const_unwrap();
      auto pd = param->const_unwrap();
      compile_string_assign(obj->paren_token_, code, arg_val, ad, pd);
    } else if (arg_val.second.is_a_function()) {
      code << prefix_function_arg(arg_val);
    } else {
      code << arg_val.first;
    }
  }
  code << ")";
  if (return_type->is_str()) {
    auto temp_name = temp();
    write_indent(body_);
    body_ << "yk__sds " << temp_name << " = " << code.str();
    write_end_statement(body_);
    deletions_.push(temp_name, "yk__sdsfree(" + temp_name + ")");
    push(wrap_in_paren(temp_name), ykobject(return_type));
  } else {
    push(code.str(), ykobject(return_type));
  }
}
void compiler::compile_string_assign(
    token *t, std::stringstream &code,
    const std::pair<std::string, ykobject> &rhs, const ykdatatype *rhs_datatype,
    const ykdatatype *lhs_datatype) {// param - sr, arg - sr
  if (lhs_datatype->is_sr() && rhs_datatype->is_sr()) {
    code << rhs.first;
  }
  // param - sr, arg - lit
  else if (lhs_datatype->is_sr() && rhs_datatype->is_string_literal()) {
    auto u = string_utils::unescape(rhs.second.string_val_);
    code << "yk__bstr_s(\"" << string_utils::escape(u) << "\", " << u.size()
         << ")";
  }
  // param - sr, arg - str
  else if (lhs_datatype->is_sr() && rhs_datatype->is_str()) {
    code << "yk__bstr_h(" << rhs.first << ")";
  }
  // param - str, arg - sr
  else if (lhs_datatype->is_str() && rhs_datatype->is_sr()) {
    code << "yk__bstr_copy_to_sds(" << rhs.first << ")";
  }
  // param - str, arg - lit
  else if (lhs_datatype->is_str() && rhs_datatype->is_string_literal()) {
    auto u = string_utils::unescape(rhs.second.string_val_);
    code << "yk__sdsnewlen(\"" << string_utils::escape(u) << "\", " << u.size()
         << ")";
  }
  // param - str, arg - str
  else if (lhs_datatype->is_str() && rhs_datatype->is_str()) {
    code << "yk__sdsdup(" << rhs.first << ")";
  } else {
    if (t != nullptr) {
      error(t, "Invalid string passing/assignment operation");
    } else {
      error("Invalid string passing/assignment operation");
    }
    code << "yk__sdsdup(" << rhs.first << ")";// pretend it is fine?
  }
}
std::string
compiler::prefix_function_arg(const std::pair<std::string, ykobject> &arg_val) {
  if (arg_val.second.object_type_ == object_type::MODULE_FUNCTION) {
    auto module_file = arg_val.second.module_file_;
    auto module_fn = arg_val.second.string_val_;
    auto module_info = cf_->get_or_null(module_file);
    auto module_prefix = module_info->prefix_;
    return prefix(module_fn, module_prefix);
  } else {
    return prefix(arg_val.first, prefix_val_);
  }
}
void compiler::visit_grouping_expr(grouping_expr *obj) {
  obj->expression_->accept(this);
  auto exp = pop();
  if (exp.second.datatype_->is_string_literal()) {
    push(exp.first, exp.second);
    return;
  }
  std::string code{};
  if (exp.second.is_a_function()) {
    code = prefix_function_arg(exp);
  } else {
    code = exp.first;
  }
  push(wrap_in_paren(code), exp.second);
}
std::string compiler::wrap_in_paren(const std::string &code) const {
  if (!should_wrap_in_paren(code)) { return code; }
  return "(" + code + ")";
}
bool compiler::should_wrap_in_paren(const std::string &code) {
  bool should_group = false;
  // seems scary
  for (std::string::size_type i = 1; i < code.size() - 1; ++i) {
    auto c = code[i];
    if (c == ' ' || c == '*' || c == '=' || c == '+' || c == '-' || c == '%' ||
        c == '&' || c == '^' || c == '~' || c == '(' || c == ')' || c == '{' ||
        c == '}' || c == '|' || c == '/' || c == ':' || c == ';' || c == '<' ||
        c == '>') {
      should_group = true;
      break;
    }
  }
  // already in paren ()
  if (should_group && code.size() >= 3 && code[0] == '(' &&
      code[code.size() - 1] == ')') {
    int paren = 0;
    for (std::string::size_type i = 1; i < code.size() - 1; ++i) {
      if (code[i] == '(') {
        paren++;
      } else if (code[i] == ')' && paren > 1) {
        paren--;
      }
    }
    if (paren == 0) { should_group = false; }
  }
  return should_group;
}
std::string compiler::conv_integer_literal(token_type token_type_val,
                                           token *literal_token) {
  switch (token_type_val) {
    case token_type::INTEGER_DECIMAL:
    case token_type::INTEGER_HEX:
    case token_type::INTEGER_DECIMAL_8:
    case token_type::INTEGER_HEX_8:
    case token_type::INTEGER_DECIMAL_16:
    case token_type::INTEGER_HEX_16:
    case token_type::INTEGER_DECIMAL_64:
    case token_type::INTEGER_HEX_64:
    case token_type::UINTEGER_DECIMAL:
    case token_type::UINTEGER_HEX:
    case token_type::UINTEGER_DECIMAL_8:
    case token_type::UINTEGER_HEX_8:
    case token_type::UINTEGER_DECIMAL_16:
    case token_type::UINTEGER_HEX_16:
    case token_type::UINTEGER_DECIMAL_64:
    case token_type::UINTEGER_HEX_64:
      return literal_token->token_;// no need to modify
    case token_type::INTEGER_BIN:
    case token_type::INTEGER_BIN_8:
    case token_type::INTEGER_BIN_16:
    case token_type::INTEGER_BIN_64: {
      std::string part = literal_token->token_.substr(2);
      std::intmax_t number = std::strtoimax(part.c_str(), nullptr, 2);
      return std::to_string(number);
    }
    case token_type::UINTEGER_BIN:
    case token_type::UINTEGER_BIN_8:
    case token_type::UINTEGER_BIN_16:
    case token_type::UINTEGER_BIN_64: {
      std::string part = literal_token->token_.substr(2);
      std::uintmax_t number = std::strtoumax(part.c_str(), nullptr, 2);
      return std::to_string(number);
    }
    case token_type::INTEGER_OCT:
    case token_type::INTEGER_OCT_8:
    case token_type::INTEGER_OCT_16:
    case token_type::INTEGER_OCT_64: {
      std::string part = literal_token->token_.substr(2);
      std::intmax_t number = std::strtoimax(part.c_str(), nullptr, 8);
      return std::to_string(number);
    }
    case token_type::UINTEGER_OCT:
    case token_type::UINTEGER_OCT_8:
    case token_type::UINTEGER_OCT_16:
    case token_type::UINTEGER_OCT_64: {
      std::string part = literal_token->token_.substr(2);
      std::uintmax_t number = std::strtoumax(part.c_str(), nullptr, 8);
      return std::to_string(number);
    }
    default:
      error(literal_token, "Failed to compile integer literal");
      return "<><>";
  }
}
void compiler::visit_literal_expr(literal_expr *obj) {
  auto data_type_tok = obj->literal_token_->type_;
  if (data_type_tok == token_type::STRING ||
      data_type_tok == token_type::THREE_QUOTE_STRING) {
    ykobject str_lit_object = ykobject(obj->literal_token_->token_, dt_pool_);
    push("<><>", str_lit_object);
  } else if (obj->literal_token_->type_ == token_type::KEYWORD_TRUE) {
    push("true", ykobject(dt_pool_->create("bool")));
  } else if (obj->literal_token_->type_ == token_type::KEYWORD_FALSE) {
    push("false", ykobject(dt_pool_->create("bool")));
  } else if (obj->literal_token_->type_ == token_type::KEYWORD_NONE) {
    push("NULL", ykobject(dt_pool_));
  } else if (data_type_tok == token_type::INTEGER_BIN ||
             data_type_tok == token_type::INTEGER_DECIMAL ||
             data_type_tok == token_type::INTEGER_OCT ||
             data_type_tok == token_type::INTEGER_HEX) {
    push("INT32_C(" + conv_integer_literal(data_type_tok, obj->literal_token_) +
             ")",
         ykobject(dt_pool_->create("int")));
  } else if (data_type_tok == token_type::INTEGER_BIN_8 ||
             data_type_tok == token_type::INTEGER_DECIMAL_8 ||
             data_type_tok == token_type::INTEGER_OCT_8 ||
             data_type_tok == token_type::INTEGER_HEX_8) {
    push("INT8_C(" + conv_integer_literal(data_type_tok, obj->literal_token_) +
             ")",
         ykobject(dt_pool_->create("i8")));
  } else if (data_type_tok == token_type::INTEGER_BIN_16 ||
             data_type_tok == token_type::INTEGER_DECIMAL_16 ||
             data_type_tok == token_type::INTEGER_OCT_16 ||
             data_type_tok == token_type::INTEGER_HEX_16) {
    push("INT16_C(" + conv_integer_literal(data_type_tok, obj->literal_token_) +
             ")",
         ykobject(dt_pool_->create("i16")));
  } else if (data_type_tok == token_type::INTEGER_BIN_64 ||
             data_type_tok == token_type::INTEGER_DECIMAL_64 ||
             data_type_tok == token_type::INTEGER_OCT_64 ||
             data_type_tok == token_type::INTEGER_HEX_64) {
    push("INT64_C(" + conv_integer_literal(data_type_tok, obj->literal_token_) +
             ")",
         ykobject(dt_pool_->create("i64")));
  } else if (data_type_tok == token_type::UINTEGER_BIN ||
             data_type_tok == token_type::UINTEGER_DECIMAL ||
             data_type_tok == token_type::UINTEGER_OCT ||
             data_type_tok == token_type::UINTEGER_HEX) {
    push("UINT32_C(" +
             conv_integer_literal(data_type_tok, obj->literal_token_) + ")",
         ykobject(dt_pool_->create("u32")));
  } else if (data_type_tok == token_type::UINTEGER_BIN_8 ||
             data_type_tok == token_type::UINTEGER_DECIMAL_8 ||
             data_type_tok == token_type::UINTEGER_OCT_8 ||
             data_type_tok == token_type::UINTEGER_HEX_8) {
    push("UINT8_C(" + conv_integer_literal(data_type_tok, obj->literal_token_) +
             ")",
         ykobject(dt_pool_->create("u8")));
  } else if (data_type_tok == token_type::UINTEGER_BIN_16 ||
             data_type_tok == token_type::UINTEGER_DECIMAL_16 ||
             data_type_tok == token_type::UINTEGER_OCT_16 ||
             data_type_tok == token_type::UINTEGER_HEX_16) {
    push("UINT16_C(" +
             conv_integer_literal(data_type_tok, obj->literal_token_) + ")",
         ykobject(dt_pool_->create("u16")));
  } else if (data_type_tok == token_type::UINTEGER_BIN_64 ||
             data_type_tok == token_type::UINTEGER_DECIMAL_64 ||
             data_type_tok == token_type::UINTEGER_OCT_64 ||
             data_type_tok == token_type::UINTEGER_HEX_64) {
    push("UINT64_C(" +
             conv_integer_literal(data_type_tok, obj->literal_token_) + ")",
         ykobject(dt_pool_->create("u64")));
  } else if (data_type_tok == token_type::FLOAT_NUMBER) {
    push(obj->literal_token_->token_, ykobject(dt_pool_->create("float")));
  } else if (data_type_tok == token_type::DOUBLE_NUMBER) {
    push(obj->literal_token_->token_, ykobject(dt_pool_->create("f64")));
  } else {
    error(obj->literal_token_, "Failed to compile literal");
    push("<><>", ykobject(dt_pool_));
  }
}
void compiler::visit_logical_expr(logical_expr *obj) {
  obj->left_->accept(this);
  auto lhs = pop();
  obj->right_->accept(this);
  auto rhs = pop();
  std::string operator_token;
  if (obj->opr_->type_ == token_type::KEYWORD_AND) {
    operator_token = " && ";
  } else {
    operator_token = " || ";
  }
  push("(" + lhs.first + operator_token + rhs.first + ")",
       ykobject(true, dt_pool_));
}
void compiler::visit_unary_expr(unary_expr *obj) {
  // Note: this is not supported by strings only numbers/floats
  // Type checker should find an error if we use unary with a string.
  obj->right_->accept(this);
  auto rhs = pop();
  std::string operator_token = obj->opr_->token_;
  if (obj->opr_->type_ == token_type::KEYWORD_NOT) { operator_token = "!"; }
  push(wrap_in_paren(operator_token + wrap_in_paren(rhs.first)), rhs.second);
}
void compiler::visit_variable_expr(variable_expr *obj) {
  // Compiler is visiting a variable, can get data type from scope_
  auto name = prefix(obj->name_->token_, prefix_val_);
  if (builtins_.has_builtin(obj->name_->token_)) {
    auto b = ykobject(dt_pool_);
    b.object_type_ = object_type::BUILTIN_FUNCTION;
    push(obj->name_->token_, b);
    return;
  } else if (defs_classes_.has_function(obj->name_->token_)) {
    auto b = ykobject(dt_pool_);
    b.object_type_ = object_type::FUNCTION;
    b.string_val_ = obj->name_->token_;
    push(obj->name_->token_, b);
    return;
  } else if (defs_classes_.has_class(obj->name_->token_)) {
    auto b = ykobject(dt_pool_);
    b.object_type_ = object_type::CLASS_ITSELF;
    push(obj->name_->token_, b);
    return;
  }
  auto object = scope_.get(name);
  if (object.desugar_rewrite_needed_) {
    push(object.desugar_rewrite_, object);
  } else {
    push(name, object);
  }
}
void compiler::visit_block_stmt(block_stmt *obj) {
  // block will be compiled to '{' + statements + '}'
  body_ << "\n";
  write_prev_indent(body_);
  body_ << "{\n";
  for (auto st : obj->statements_) { st->accept(this); }
  // Clean out what we create inside while scope or if scope blocks
  // For defs, deletion happen before return
  if (peek_scope_type() == ast_type::STMT_WHILE ||
      peek_scope_type() == ast_type::STMT_IF) {
    defers_.write_one(this);
    deletions_.write_one(body_, indent_);
  }
  write_prev_indent(body_);
  body_ << "}\n";
}
void compiler::visit_break_stmt(break_stmt *obj) {
  defers_.write_upto_loop(this);
  deletions_.write_upto_loop(body_, indent_);
  write_indent(body_);
  body_ << "break";
  write_end_statement(body_);
}
void compiler::visit_continue_stmt(continue_stmt *obj) {
  defers_.write_upto_loop(this);
  deletions_.write_upto_loop(body_, indent_);
  write_indent(body_);
  body_ << "continue";
  write_end_statement(body_);
}
void compiler::visit_def_stmt(def_stmt *obj) {
#ifdef YAKSHA_DEADCODE_ELIMINATION
  if (obj->hits_ == 0) { return; }
#endif
  auto name = prefix(obj->name_->token_, prefix_val_);
  if (obj->annotations_.native_define_) {
    struct_forward_declarations_ << "#define " << name << " "
                                 << obj->annotations_.native_define_arg_
                                 << "\n";
    return;
  }
  bool first = false;
  // ::================================::
  // Compile @nativemacro if present
  // ::================================::
  if (obj->annotations_.native_macro_) {
    struct_forward_declarations_ << "#define " << name << "(";
    first = true;
    for (auto para : obj->params_) {
      if (!first) {
        struct_forward_declarations_ << ", ";
      } else {
        first = false;
      }
      struct_forward_declarations_ << prefix(para.name_->token_, "nn__");
    }
    struct_forward_declarations_ << ") ";
    if (obj->annotations_.native_macro_arg_.empty()) {
      // #define yy__name ccode..
      auto b = dynamic_cast<block_stmt *>(obj->function_body_);
      auto st = b->statements_[0];
      auto stn = dynamic_cast<ccode_stmt *>(st);
      struct_forward_declarations_
          << ::string_utils::unescape(stn->code_str_->token_);
    } else {
      // #define yy__name arg
      struct_forward_declarations_ << obj->annotations_.native_macro_arg_;
    }
    struct_forward_declarations_ << "\n";
    return;
  }
  // ::================================::
  // Create declaration in header section
  // ::================================::
  auto return_type = convert_dt(obj->return_type_);
  function_forward_declarations_ << return_type << " " << name << "(";
  first = true;
  for (auto para : obj->params_) {
    if (!first) {
      function_forward_declarations_ << ", ";
    } else {
      first = false;
    }
    function_forward_declarations_ << convert_dt(para.data_type_);
  }
  function_forward_declarations_ << ")";
  write_end_statement(function_forward_declarations_);
  // ::================================::
  // Create first part of method body
  //       datatype name (..params..)
  // ::================================::
  body_ << return_type << " " << name << "(";
  first = true;
  for (auto para : obj->params_) {
    if (!first) {
      body_ << ", ";
    } else {
      first = false;
    }
    body_ << convert_dt(para.data_type_) << " "
          << prefix(para.name_->token_,
                    obj->annotations_.native_ ? "nn__" : prefix_val_);
  }
  body_ << ") ";
  // ::================================::
  // Create @native code
  // ::================================::
  if (obj->annotations_.native_ && !obj->annotations_.native_arg_.empty()) {
    body_ << "{ ";
    if (!obj->return_type_->is_none()) { body_ << "return "; }
    body_ << obj->annotations_.native_arg_ << "(";
    first = true;
    for (auto para : obj->params_) {
      if (!first) {
        body_ << ", ";
      } else {
        first = false;
      }
      body_ << prefix(para.name_->token_, "nn__");
    }
    body_ << "); }\n";
    return;
  }
  // ::================================::
  // Create code body
  // ::================================::
  // Define parameters in nested scope for function
  ykobject func_placeholder{dt_pool_};
  func_placeholder.object_type_ = object_type::FUNCTION;
  scope_.define_global(name, func_placeholder);
  scope_.push();
  auto function_def = obj;
  for (auto param : function_def->params_) {
    auto placeholder = ykobject(param.data_type_);
    scope_.define(prefix(param.name_->token_, prefix_val_), placeholder);
  }
  indent();
  // ::================================::
  // Visit function body
  //       {
  //            ..
  //       }
  // ::================================::
  push_scope_type(ast_type::STMT_DEF);
  deletions_.push_delete_stack(ast_type::STMT_DEF);
  defers_.push_defer_stack(ast_type::STMT_DEF);
  // Schedule string argument deletions.
  for (auto param : function_def->params_) {
    if (param.data_type_->is_str()) {
      auto to_delete = prefix(param.name_->token_, prefix_val_);
      deletions_.push(to_delete, "yk__sdsfree(" + to_delete + ")");
    }
  }
  obj->function_body_->accept(this);
  defers_.pop_defer_stack();
  deletions_.pop_delete_stack();
  dedent();
  scope_.pop();
  pop_scope_type();
}
void compiler::visit_expression_stmt(expression_stmt *obj) {
  obj->expression_->accept(this);
  if (expr_stack_.empty()) { return; }
  auto exp = pop();
  write_indent(body_);
  body_ << exp.first;
  write_end_statement(body_);
}
void compiler::visit_if_stmt(if_stmt *obj) {
  // if () -> block
  obj->expression_->accept(this);
  auto if_expr = pop();
  write_indent(body_);
  auto boolean_expr = if_expr.first;
  if (boolean_expr.size() > 2 && boolean_expr[0] == '(' &&
      boolean_expr[boolean_expr.size() - 1] == ')') {
    body_ << "if " << boolean_expr << "";
  } else {
    body_ << "if (" << boolean_expr << ")";
  }
  scope_.push();
  deletions_.push_delete_stack(ast_type::STMT_IF);
  defers_.push_defer_stack(ast_type::STMT_IF);
  push_scope_type(ast_type::STMT_IF);
  indent();
  obj->if_branch_->accept(this);
  dedent();
  pop_scope_type();
  defers_.pop_defer_stack();
  deletions_.pop_delete_stack();
  scope_.pop();
  if (obj->else_branch_ != nullptr) {
    write_indent(body_);
    body_ << "else";
    scope_.push();
    deletions_.push_delete_stack(ast_type::STMT_IF);
    defers_.push_defer_stack(ast_type::STMT_IF);
    push_scope_type(ast_type::STMT_IF);
    indent();
    obj->else_branch_->accept(this);
    dedent();
    pop_scope_type();
    defers_.pop_defer_stack();
    deletions_.pop_delete_stack();
    scope_.pop();
  }
}
void compiler::visit_let_stmt(let_stmt *obj) {
  auto name = prefix(obj->name_->token_, prefix_val_);
  auto object = ykobject(dt_pool_);
  std::pair<std::string, ykobject> resulting_pair;
  bool visited_expr = false;
  LOG_COMP("let lhs: " << name);
  // infer data type based on RHS if we do not have a data type here
  if (obj->data_type_ == nullptr) {
    visited_expr = true;
    resulting_pair = compile_expression(obj->expression_);
    if (resulting_pair.second.is_a_function()) {
      obj->data_type_ = function_to_datatype(resulting_pair.second);
    } else {
      obj->data_type_ = resulting_pair.second.datatype_
                            ->const_unwrap(); /* set our data type here */
    }
    LOG_COMP("type infer let: " << obj->data_type_->as_string());
    LOG_COMP("let rhs: " << resulting_pair.first);
  }
  if (obj->data_type_->is_none()) {
    error(obj->name_,
          "Failed to compile let statement. (Use of non compilable data type)");
  }
  if (obj->data_type_->const_unwrap()->is_str()) {
    object = ykobject(obj->data_type_);
    if (obj->expression_ != nullptr) {
      auto exp = (visited_expr) ? resulting_pair
                                : compile_expression(obj->expression_);
      write_indent(body_);
      if (exp.second.datatype_->const_unwrap()->is_str()) {
        body_ << convert_dt(object.datatype_) << " " << name << " = "
              << "yk__sdsdup(" << exp.first << ")";
      } else if (exp.second.datatype_->const_unwrap()->is_sr()) {
        body_ << convert_dt(object.datatype_) << " " << name << " = "
              << "yk__bstr_copy_to_sds(" << exp.first << ")";
      } else if (exp.second.datatype_->const_unwrap()->is_string_literal()) {
        auto u = string_utils::unescape(exp.second.string_val_);
        body_ << convert_dt(object.datatype_) << " " << name << " = "
              << "yk__sdsnewlen(\"" << string_utils::escape(u) << "\" , "
              << u.size() << ")";
      } else {
        error("Failed to compile assign to string.");
      }
    } else {
      body_ << convert_dt(object.datatype_) << " " << name << " = "
            << "yk__sdsempty()";
    }
    // If there is an expression, go to that, pop(), duplicate and assign.
    // If there is not an expression, assign yk__sdsempty()
    // Add to deletions
    deletions_.push(name, "yk__sdsfree(" + name + ")");
  } else if (obj->data_type_->const_unwrap()->is_sr() ||
             obj->data_type_->const_unwrap()->is_string_literal()) {
    if (obj->data_type_->is_const()) {
      auto const_wrapper = dt_pool_->create("Const");
      const_wrapper->args_.emplace_back(dt_pool_->create("sr"));
      object = ykobject(const_wrapper);
    } else {
      object = ykobject(dt_pool_->create("sr"));
    }
    if (obj->expression_ != nullptr) {
      auto exp = (visited_expr) ? resulting_pair
                                : compile_expression(obj->expression_);
      write_indent(body_);
      if (exp.second.datatype_->const_unwrap()->is_str()) {
        body_ << convert_dt(object.datatype_) << " " << name << " = yk__bstr_h("
              << exp.first << ")";
      } else if (exp.second.datatype_->const_unwrap()->is_sr()) {
        body_ << convert_dt(object.datatype_) << " " << name << " = "
              << exp.first;
      } else if (exp.second.datatype_->const_unwrap()->is_string_literal()) {
        auto u = string_utils::unescape(exp.second.string_val_);
        body_ << convert_dt(object.datatype_) << " " << name << " = "
              << "yk__bstr_s(\"" << string_utils::escape(u) << "\" , "
              << u.size() << ")";
      } else {
        error("Failed to compile assign to sr.");
      }
    } else {
      body_ << convert_dt(object.datatype_) << " " << name
            << " = ((struct yk__bstr){.s = YK__EMPTY_STRING_BSTR,"
               " .l = 0, .t = yk__bstr_static})";
    }
  } else if (obj->data_type_->is_array()) {
    object = ykobject(obj->data_type_);
    if (obj->expression_ != nullptr) {
      auto exp = (visited_expr) ? resulting_pair
                                : compile_expression(obj->expression_);
      write_indent(body_);
      body_ << convert_dt(obj->data_type_) << " " << name;
      body_ << " = " << exp.first;
    } else {
      write_indent(body_);
      body_ << convert_dt(obj->data_type_) << " " << name;
      body_ << " = NULL";
    }
  } else {
    object = ykobject(obj->data_type_);
    if (obj->expression_ != nullptr) {
      auto exp = (visited_expr) ? resulting_pair
                                : compile_expression(obj->expression_);
      auto castable = obj->data_type_->const_unwrap()->auto_cast(
          exp.second.datatype_, dt_pool_, false, true);
      write_indent(body_);
      body_ << convert_dt(obj->data_type_) << " " << name;
      if (exp.second.is_a_function()) {
        body_ << " = " << prefix_function_arg(exp);
      } else if (castable == nullptr) {
        body_ << " = " << exp.first;
      } else {
        auto lhsu = obj->data_type_->const_unwrap();
        write_casted_rhs(body_, exp, lhsu);
      }
    } else {
      write_indent(body_);
      body_ << convert_dt(obj->data_type_) << " " << name;
    }
  }
  write_end_statement(body_);
  scope_.define(name, object);
}
void compiler::write_casted_rhs(
    std::stringstream &stream, std::pair<std::string, ykobject> &rhs,
    ykdatatype *lhsu) {// We need to cast RHS to appropriate DT
  stream << " = ";
  stream << "((";
  stream << convert_dt(lhsu) << ")(";
  if (rhs.second.datatype_->const_unwrap()->is_bool()) {
    stream << "((" << rhs.first << ") ? 1 : 0)";
  } else {
    stream << rhs.first;
  }
  stream << "))";
}
void compiler::visit_pass_stmt(pass_stmt *obj) {
  write_indent(body_);
  body_ << "// pass";
  write_end_statement(body_);
}
void compiler::visit_return_stmt(return_stmt *obj) {
  if (obj->expression_ != nullptr) {
    obj->expression_->accept(this);
    auto rhs = pop();
    std::string return_val = rhs.first;
    ykdatatype *result_type = nullptr;
    if (obj->result_type_ != nullptr) {
      result_type = obj->result_type_->const_unwrap();
    }
    if (result_type != nullptr &&
        *result_type != *rhs.second.datatype_->const_unwrap()) {
      // different data types are here
      if (result_type->is_a_string()) {
        std::stringstream code_ss{};
        compile_string_assign(obj->return_keyword_, code_ss, rhs,
                              rhs.second.datatype_->const_unwrap(),
                              result_type);
        return_val = code_ss.str();
      }
    } else if (obj->expression_->get_type() != ast_type::EXPR_LITERAL) {
      // First we assign return value to a temp variable
      std::string temp_name = temp();
      write_indent(body_);
      body_ << convert_dt(rhs.second.datatype_) << " " << temp_name << " = "
            << rhs.first;
      write_end_statement(body_);
      return_val = temp_name;
    }
    // Literals are safe to return as it is
    // Generate deletions, defers
    defers_.write(this);
    deletions_.write(body_, indent_, rhs.first);
    // Now we return the temp value
    write_indent(body_);
    body_ << "return " << return_val;
    write_end_statement(body_);
  } else {
    defers_.write(this);
    deletions_.write(body_, indent_, "");
    write_indent(body_);
    body_ << "return";
    write_end_statement(body_);
  }
}
void compiler::visit_while_stmt(while_stmt *obj) {
  // NOTE: desugar compiler rewrites all loops to
  // while True|False:
  //    if not expr:
  //        break
  //    rest of the stuff
  obj->expression_->accept(this);
  auto code = pop();
  write_indent(body_);
  body_ << "while (" << code.first << ")";
  push_scope_type(ast_type::STMT_WHILE);
  scope_.push();
  deletions_.push_delete_stack(ast_type::STMT_WHILE);
  defers_.push_defer_stack(ast_type::STMT_WHILE);
  indent();
  obj->while_body_->accept(this);
  dedent();
  pop_scope_type();
  scope_.pop();
  defers_.pop_defer_stack();
  deletions_.pop_delete_stack();
}
void compiler::write_indent(std::stringstream &where) const {
  if (inline_mode_) { return; }
  ::write_indent(where, indent_);
}
void compiler::write_end_statement(std::stringstream &where) {
  statements_++;
  if (inline_mode_) { return; }
  where << ";\n";
}
void compiler::indent() { indent_++; }
void compiler::dedent() {
  if (indent_ == 0) { return; }
  indent_--;
}
std::string compiler::temp() {
  // temp names will start with t__, so they will look like t__0, t__1, ...
  std::string name = "t__";
  name += std::to_string(temp_);
  temp_++;
  return name;
}
std::string compiler::temp(const std::string &custom_prefix) {
  // temp names will start with prefix, so they will look like prefix0, prefix1, ...
  std::string name = custom_prefix;
  name += std::to_string(temp_);
  temp_++;
  return name;
}
std::string compiler::convert_dt(ykdatatype *basic_dt) {
  if (basic_dt->is_array() || basic_dt->is_ptr()) {
    // int32_t*, yk__sds*, etc
    return convert_dt(basic_dt->args_[0]) + "*";
  } else if (basic_dt->is_const()) {
    return convert_dt(basic_dt->args_[0]) + " const ";
  } else if (basic_dt->is_str()) {
    return "yk__sds";
  } else if (basic_dt->is_sr()) {
    return "struct yk__bstr";
  } else if (basic_dt->is_string_literal()) {
    return "char const*";
  } else if (basic_dt->is_i8()) {
    return "int8_t";
  } else if (basic_dt->is_i16()) {
    return "int16_t";
  } else if (basic_dt->is_i32()) {
    return "int32_t";
  } else if (basic_dt->is_i64()) {
    return "int64_t";
  } else if (basic_dt->is_u8()) {
    return "uint8_t";
  } else if (basic_dt->is_u16()) {
    return "uint16_t";
  } else if (basic_dt->is_u32()) {
    return "uint32_t";
  } else if (basic_dt->is_u64()) {
    return "uint64_t";
  } else if (basic_dt->is_bool()) {
    return "bool";
  } else if (basic_dt->is_none()) {
    return "void";
  } else if (basic_dt->is_f32()) {
    return "float";
  } else if (basic_dt->is_f64()) {
    return "double";
  } else if (basic_dt->is_any_ptr()) {
    return "void*";
  } else if (basic_dt->is_any_ptr_to_const()) {
    return "void const*";
  } else if (basic_dt->is_sm_entry() || basic_dt->is_m_entry()) {
    // Handle SMEntry and Entry
    return esc_->compile(basic_dt, this);
  } else if (basic_dt->is_function()) {
    return esc_->compile_function_dt(basic_dt, this);
  } else if (basic_dt->is_tuple()) {
    return esc_->compile_tuple(basic_dt, this);
  }
  auto dt = basic_dt->token_->token_;
  if (!basic_dt->module_.empty() && cf_ != nullptr) {
    auto module = cf_->get_or_null(basic_dt->module_);
    auto imported_module_prefix = module->prefix_;
    auto class_info = module->data_->dsv_->get_class(dt);
    if (class_info != nullptr) {
      auto class_name = prefix(dt, imported_module_prefix);
      if (class_info->annotations_.native_define_) { return class_name; }
      if (class_info->annotations_.on_stack_) { return "struct " + class_name; }
      return "struct " + class_name + "*";
    }
  }
  error("Failed to compile data type:" + basic_dt->as_string());
  return "<data type unknown>";
}
compiler_output compiler::compile(codefiles *cf, file_info *fi) {
  // ------ Set to members for ease of access ---------
  this->cf_ = cf;
  this->prefix_val_ = fi->prefix_;
  // -------- Define forward declarations ---------------
  for (const auto &name : this->defs_classes_.global_const_names_) {
    auto cls = defs_classes_.get_const(name);
    auto obj = ykobject(cls->data_type_);
    scope_.define_global(prefix(cls->name_->token_, prefix_val_), obj);
  }
  for (const auto &name : this->defs_classes_.global_native_const_names_) {
    auto cls = defs_classes_.get_native_const(name);
    auto obj = ykobject(cls->data_type_);
    scope_.define_global(prefix(cls->name_->token_, prefix_val_), obj);
  }
  for (auto imp_st : fi->data_->parser_->import_stmts_) {
    auto obj = ykobject(dt_pool_);
    obj.object_type_ = yaksha::object_type::MODULE;
    obj.string_val_ = imp_st->data_->filepath_.string();
    obj.module_file_ = imp_st->data_->filepath_.string();
    obj.module_name_ = imp_st->name_->token_;
    scope_.define_global(prefix(imp_st->name_->token_, prefix_val_), obj);
  }
  // ---------- Create a copy of import information -------------
  import_stmts_alias_ = fi->data_->parser_->import_stmts_alias_;
  filepath_ = fi->filepath_.string();
  //
  // ----- Compile structure forward declarations ------
  for (const auto &name : this->defs_classes_.class_names_) {
    auto cls = defs_classes_.get_class(name);
#ifdef YAKSHA_DEADCODE_ELIMINATION
    if (cls->hits_ == 0) { continue; }
#endif
    if (!cls->annotations_.native_define_) {
      struct_forward_declarations_ << "struct " << prefix(name, prefix_val_)
                                   << ";\n";
    }
  }
  // -------- Desugar statements -------------------
  auto desugared = desugar_->desugar(fi->data_->parser_->stmts_, this);
  // ------- Compile statements ---------------------
  for (auto st : desugared) { st->accept(this); }
  // ---------- Produce result object -------------
  return {struct_forward_declarations_.str(),
          function_forward_declarations_.str(),
          classes_.str(),
          body_.str(),
          global_constants_.str(),
          errors_};
}
void compiler::push(const std::string &expr, const ykobject &data_type) {
  expr_stack_.push_back(expr);
  type_stack_.push_back(data_type);
}
std::pair<std::string, ykobject> compiler::pop() {
  auto p = std::make_pair(expr_stack_.back(), type_stack_.back());
  expr_stack_.pop_back();
  type_stack_.pop_back();
  return p;
}
void compiler::write_prev_indent(std::stringstream &where) const {
  if (inline_mode_) { return; }
  auto indent = indent_ - 1;
  ::write_indent(where, indent);
}
void compiler::push_scope_type(ast_type scope_type) {
  this->scope_type_stack_.emplace_back(scope_type);
}
ast_type compiler::peek_scope_type() {
  if (this->scope_type_stack_.empty()) {
    return ast_type::STMT_PASS;// Pass is used for unknown
  }
  return this->scope_type_stack_.back();
}
void compiler::pop_scope_type() {
  if (this->scope_type_stack_.empty()) { return; }
  this->scope_type_stack_.pop_back();
}
void compiler::visit_defer_stmt(defer_stmt *obj) { defers_.push(obj); }
void compiler::visit_class_stmt(class_stmt *obj) {
#ifdef YAKSHA_DEADCODE_ELIMINATION
  if (obj->hits_ == 0) { return; }
#endif
  /**
   *    struct foo {
   *       int abc;
   *    };
   */
  auto name = prefix(obj->name_->token_, prefix_val_);
  if (obj->annotations_.native_define_) {
    struct_forward_declarations_ << "#define " << name << " "
                                 << obj->annotations_.native_define_arg_
                                 << "\n";
    return;
  }
  write_indent(classes_);
  classes_ << "struct " << name << " {\n";
  indent();
  //
  for (auto member : obj->members_) {
    write_indent(classes_);
    auto member_name = prefix(member.name_->token_, prefix_val_);
    auto dt = convert_dt(member.data_type_);
    classes_ << dt << " " << member_name;
    write_end_statement(classes_);
  }
  //
  dedent();
  write_indent(classes_);
  classes_ << "}";
  write_end_statement(classes_);
}
void compiler::visit_del_stmt(del_stmt *obj) {
  obj->expression_->accept(this);
  auto name = pop();
  if (name.second.is_primitive_or_obj() &&
      name.second.datatype_->const_unwrap()->is_primitive() &&
      !name.second.datatype_->const_unwrap()->is_str() &&
      !name.second.datatype_->const_unwrap()->is_sr()) {
    return;
  }
  write_indent(body_);
  if (name.second.datatype_->is_array()) {
    if (name.second.datatype_->args_[0]->is_sm_entry()) {
      body_ << "yk__shfree(" << name.first << ")";
    } else if (name.second.datatype_->args_[0]->is_m_entry()) {
      body_ << "yk__hmfree(" << name.first << ")";
    } else {
      body_ << "yk__arrfree(" << name.first << ")";
    }
  } else if (name.second.is_primitive_or_obj() &&
             name.second.datatype_->is_str()) {
    body_ << "yk__sdsfree(" << name.first << ")";
  } else if (name.second.is_primitive_or_obj() &&
             name.second.datatype_->const_unwrap()->is_sr()) {
    body_ << "yk__bstr_free_underlying(" << name.first << ")";
  } else {
    body_ << "free(" << name.first << ")";
  }
  write_end_statement(body_);
}
void compiler::visit_get_expr(get_expr *obj) {
  obj->lhs_->accept(this);
  auto lhs = pop();
  if (lhs.second.object_type_ == object_type::MODULE) {
    auto member_item = obj->item_;
    auto imported = cf_->get_or_null(lhs.second.string_val_);
    bool has_func = imported->data_->dsv_->has_function(member_item->token_);
    bool has_class = imported->data_->dsv_->has_class(member_item->token_);
    bool has_const = imported->data_->dsv_->has_const(member_item->token_);
    bool has_native_const =
        imported->data_->dsv_->has_native_const(member_item->token_);
    auto mod_obj = ykobject(dt_pool_);
    if (has_class) {
      mod_obj.object_type_ = object_type::MODULE_CLASS;
      /* for jungle.Banana */
      mod_obj.string_val_ = member_item->token_;      /* Banana */
      mod_obj.module_file_ = lhs.second.string_val_;  /* file path */
      mod_obj.module_name_ = lhs.second.module_name_; /* jungle */
    } else if (has_func) {
      mod_obj.object_type_ = object_type::MODULE_FUNCTION;
      mod_obj.string_val_ = member_item->token_;
      mod_obj.module_file_ = lhs.second.string_val_;
      mod_obj.module_name_ = lhs.second.module_name_;
    } else if (has_const) {
      auto glob = imported->data_->dsv_->get_const(member_item->token_);
      mod_obj.object_type_ = object_type::PRIMITIVE_OR_OBJ;
      mod_obj.datatype_ = glob->data_type_;
      mod_obj.string_val_ = member_item->token_;
      mod_obj.module_file_ = lhs.second.string_val_;
      mod_obj.module_name_ = lhs.second.module_name_;
      auto module_info = cf_->get_or_null(mod_obj.module_file_);
      auto prefixed_name = prefix(mod_obj.string_val_, module_info->prefix_);
      push(prefixed_name, mod_obj);
      return;
    } else if (has_native_const) {
      auto glob = imported->data_->dsv_->get_native_const(member_item->token_);
      mod_obj.object_type_ = object_type::PRIMITIVE_OR_OBJ;
      mod_obj.datatype_ = glob->data_type_;
      mod_obj.string_val_ = member_item->token_;
      mod_obj.module_file_ = lhs.second.string_val_;
      mod_obj.module_name_ = lhs.second.module_name_;
      auto module_info = cf_->get_or_null(mod_obj.module_file_);
      auto prefixed_name = prefix(mod_obj.string_val_, module_info->prefix_);
      push(prefixed_name, mod_obj);
      return;
    } else {
      error(obj->dot_, "Failed to compile dot access");
    }
    push("<><>", mod_obj);
    return;
  }
  auto item = obj->item_->token_;
  auto user_defined_type = lhs.second.datatype_->type_;
  auto module_file = lhs.second.datatype_->module_;
  class_stmt *class_;
  std::string item_prefix = prefix_val_;
  std::string access_ = "->";
  file_info *module_info = cf_->get_or_null(module_file);
  class_ = module_info->data_->dsv_->get_class(user_defined_type);
  item_prefix = module_info->prefix_;
  if (class_->annotations_.native_define_) { item_prefix = ""; }
  if (class_->annotations_.on_stack_) { access_ = "."; }
  for (const auto &member : class_->members_) {
    if (item == member.name_->token_) {
      auto placeholder = ykobject(dt_pool_);
      placeholder.datatype_ = member.data_type_;
      push(lhs.first + access_ + prefix(item, item_prefix), placeholder);
      return;
    }
  }
  error(obj->dot_, "Failed to compile dot access");
}
void compiler::visit_set_expr(set_expr *obj) {
  obj->lhs_->accept(this);
  auto lhs = pop();
  auto item = obj->item_->token_;
  auto user_defined_type = lhs.second.datatype_->type_;
  auto module_file = lhs.second.datatype_->module_;
  class_stmt *class_;
  std::string item_prefix = prefix_val_;
  std::string access_ = "->";
  file_info *module_info = cf_->get_or_null(module_file);
  class_ = module_info->data_->dsv_->get_class(user_defined_type);
  item_prefix = module_info->prefix_;
  if (class_->annotations_.native_define_) { item_prefix = ""; }
  if (class_->annotations_.on_stack_) { access_ = "."; }
  for (const auto &member : class_->members_) {
    if (item == member.name_->token_) {
      auto placeholder = ykobject(dt_pool_);
      placeholder.datatype_ = member.data_type_;
      push(lhs.first + access_ + prefix(item, item_prefix), placeholder);
      return;
    }
  }
}
void compiler::visit_assign_member_expr(assign_member_expr *obj) {
  obj->set_oper_->accept(this);// before  a.b, after a->b
  auto lhs = pop();
  obj->right_->accept(this);
  auto rhs = pop();
  perform_assign(lhs, rhs, obj->opr_, false, true);
}
void compiler::visit_square_bracket_access_expr(
    square_bracket_access_expr *obj) {
  obj->index_expr_->accept(this);
  auto rhs = pop();
  obj->name_->accept(this);
  auto lhs = pop();
  if (lhs.second.datatype_->is_array()) {
    auto b = ykobject(lhs.second.datatype_->args_[0]);
    push(lhs.first + "[" + rhs.first + "]", b);
  } else if (lhs.second.datatype_->is_tuple()) {
    auto int_expr = dynamic_cast<literal_expr *>(obj->index_expr_);
    auto index = std::stoi(int_expr->literal_token_->token_);
    auto b = ykobject(lhs.second.datatype_->args_[index]);
    index++;
    push(lhs.first + ".e" + std::to_string(index), b);
  } else {
    error(obj->sqb_token_, "Failed to compile [] access");
    push("<><>", ykobject(dt_pool_));
  }
}
void compiler::visit_square_bracket_set_expr(square_bracket_set_expr *obj) {
  obj->index_expr_->accept(this);
  auto rhs = pop();
  obj->name_->accept(this);
  auto lhs = pop();
  if (lhs.second.datatype_->is_array()) {
    auto b = ykobject(lhs.second.datatype_->args_[0]);
    push(lhs.first + "[" + rhs.first + "]", b);
  } else if (lhs.second.datatype_->is_tuple()) {
    auto int_expr = dynamic_cast<literal_expr *>(obj->index_expr_);
    auto index = std::stoi(int_expr->literal_token_->token_);
    auto b = ykobject(lhs.second.datatype_->args_[index]);
    index++;
    push(lhs.first + ".e" + std::to_string(index), b);
  } else {
    error(obj->sqb_token_, "Failed to compile [] set");
    push("<><>", ykobject(dt_pool_));
  }
}
void compiler::visit_assign_arr_expr(assign_arr_expr *obj) {
  obj->assign_oper_->accept(this);
  auto lhs = pop();
  obj->right_->accept(this);
  auto rhs = pop();
  if (rhs.second.is_primitive_or_obj() && rhs.second.datatype_->is_str()) {
    // Note: Do not free the array value, only duplicate input string
    // Array/Tuple value freeing is left to user to handle for str
    // As we do not know if it has garbage value or a proper value at comp time
    write_indent(body_);
    body_ << lhs.first << " = yk__sdsdup(" << rhs.first << ")";
    write_end_statement(body_);
  } else {
    perform_assign(lhs, rhs, obj->opr_, false, true);
  }
}
void compiler::visit_ccode_stmt(ccode_stmt *obj) {
  write_indent(body_);
  body_ << ::string_utils::unescape(obj->code_str_->token_);
  write_end_statement(body_);
}
void compiler::visit_import_stmt(import_stmt *obj) {}
void compiler::visit_const_stmt(const_stmt *obj) {
  if (scope_.is_global_level()) {
    // constant is global
#ifdef YAKSHA_DEADCODE_ELIMINATION
    if (obj->hits_ == 0) { return; }
#endif
    auto name = prefix(obj->name_->token_, prefix_val_);
    auto *literal_expression = dynamic_cast<literal_expr *>(obj->expression_);
    if (obj->data_type_->const_unwrap()->is_sr()) {
      if (obj->expression_ != nullptr) {
        auto exp = compile_expression(obj->expression_);
        if (exp.second.datatype_->const_unwrap()->is_string_literal()) {
          auto u = string_utils::unescape(exp.second.string_val_);
          global_constants_ << "struct yk__bstr const " << name << " = "
                            << "((struct yk__bstr){.data.s = "
                            << "\"" << string_utils::escape(u) << "\""
                            << ", .l = " << u.size()
                            << ", .t = yk__bstr_static})";
          write_end_statement(global_constants_);
          return;
        }
      }
    }
    literal_expression->accept(this);
    auto exp = pop();
    auto castable = obj->data_type_->const_unwrap()->auto_cast(
        exp.second.datatype_, dt_pool_, false, true);
    global_constants_ << this->convert_dt(obj->data_type_) << " " << name;
    if (castable == nullptr) {
      global_constants_ << " = " << exp.first;
    } else {
      write_casted_rhs(global_constants_, exp, obj->data_type_->const_unwrap());
    }
    write_end_statement(global_constants_);
  } else {// Compile as you would compile a let statement
    auto let_stmt_obj =
        ast_pool_->c_let_stmt(obj->name_, obj->data_type_, obj->expression_);
    let_stmt_obj->accept(this);
  }
}
void compiler::write_statement(std::string code_line) {
  write_indent(body_);
  body_ << code_line;
  write_end_statement(body_);
}
void compiler::write_statement_no_end(std::string code_line) {
  write_indent(body_);
  body_ << code_line << "\n";
}
void compiler::visit_runtimefeature_stmt(runtimefeature_stmt *obj) {}
ykdatatype *compiler::function_to_datatype(const ykobject &arg) {
  def_stmt *funct;
  if (arg.object_type_ == object_type::FUNCTION) {
    funct = defs_classes_.get_function(arg.string_val_);
  } else {
    auto imp = cf_->get_or_null(arg.module_file_);
    funct = imp->data_->dsv_->get_function(arg.string_val_);
  }
  if (funct->annotations_.varargs_ || funct->annotations_.native_macro_ ||
      funct->annotations_.native_define_) {
    return nullptr;
  }
  ykdatatype *fnc = dt_pool_->create("Function");
  ykdatatype *fin = dt_pool_->create("In");
  ykdatatype *fout = dt_pool_->create("Out");
  fnc->args_.emplace_back(fin);
  fnc->args_.emplace_back(fout);
  for (auto current_param : funct->params_) {
    fin->args_.emplace_back(current_param.data_type_);
  }
  if (!funct->return_type_->is_none()) {
    fout->args_.emplace_back(funct->return_type_);
  }
  return fnc;
}
void compiler::visit_nativeconst_stmt(nativeconst_stmt *obj) {
  auto name = prefix(obj->name_->token_, prefix_val_);
  if (scope_.is_global_level()) {// constant is global
#ifdef YAKSHA_DEADCODE_ELIMINATION
    if (obj->hits_ == 0) { return; }
#endif
    global_constants_ << "#define " << name << " (";
    global_constants_ << ::string_utils::unescape(obj->code_str_->token_);
    global_constants_ << ")\n";
  } else {
    auto object = ykobject(obj->data_type_);
    write_indent(body_);
    // something like
    // a: Const[int] = ccode """1 + 1"""
    // int yk__a = 1 + 1
    body_ << convert_dt(obj->data_type_) << " " << name;
    body_ << " = " << ::string_utils::unescape(obj->code_str_->token_);
    write_end_statement(body_);
    scope_.define(name, object);
  }
}
void compiler::error(token *tok, const std::string &message) {
  auto err = parsing_error{message, tok};
  errors_.emplace_back(err);
}
void compiler::error(const std::string &message) {
  auto err = parsing_error{message, "", 0, 0};
  err.token_set_ = false;
  errors_.emplace_back(err);
}
void compiler::visit_foreach_stmt(foreach_stmt *obj) {
  // Not supported directly by compiler
}
void compiler::visit_forendless_stmt(forendless_stmt *obj) {
  // Not supported directly by compiler
}
std::string compiler::prefix_token(token *p_token) {
  return ::prefix(p_token->token_, prefix_val_);
}
void compiler::visit_compins_stmt(compins_stmt *obj) {
  // Add given item to scope
  auto name = prefix(obj->name_->token_, prefix_val_);
  auto object = ykobject(obj->data_type_);
  if (obj->meta1_ != nullptr) {
    object.desugar_rewrite_ = obj->meta1_->token_;
    object.desugar_rewrite_needed_ = true;
  }
  scope_.define(name, object);
}
std::pair<std::string, ykobject> compiler::compile_expression(expr *ex) {
  ex->accept(this);
  auto p = std::make_pair(expr_stack_.back(), type_stack_.back());
  expr_stack_.pop_back();
  type_stack_.pop_back();
  return p;
}
void compiler::visit_curly_call_expr(curly_call_expr *obj) {
  obj->dt_expr_->accept(this);
  auto name_pair = pop();
  auto name = name_pair.first;
  std::stringstream code{};
  class_stmt *class_info;
  ykdatatype *dt;
  std::string c_mod_prefix;
  std::string prefixed_class_name;
  if (name_pair.second.object_type_ == object_type::MODULE_CLASS) {
    auto module_file = name_pair.second.module_file_;
    auto module_class = name_pair.second.string_val_;
    auto module_prefix = cf_->get_or_null(module_file)->prefix_;
    c_mod_prefix = module_prefix;
    class_info =
        cf_->get_or_null(module_file)->data_->dsv_->get_class(module_class);
    dt = dt_pool_->create(module_class, module_file);
    prefixed_class_name = prefix(module_class, c_mod_prefix);
  } else if (defs_classes_.has_class(name)) {
    class_info = defs_classes_.get_class(name);
    dt = dt_pool_->create(name, filepath_);
    c_mod_prefix = prefix_val_;
    prefixed_class_name = prefix(name, c_mod_prefix);
  } else {
    error(obj->curly_open_, "Invalid {} initialization");
    push("<><>", ykobject(dt_pool_));
    return;
  }
  if (class_info != nullptr) {
    if (class_info->annotations_.native_define_) {
      error(obj->curly_open_, "Cannot create a native structure");
      push("<><>", ykobject(dt_pool_));
      return;
    }
    if (class_info->annotations_.on_stack_) {
      // ---------- On stack --------
      code << "((" << convert_dt(dt) << ")"
           << "{";
      bool first = true;
      for (auto const &para : obj->values_) {
        para.value_->accept(this);
        auto val = pop();
        if (first) {
          first = false;
        } else {
          code << ", ";
        }
        code << "." << c_mod_prefix << para.name_->token_ << " = (" << val.first
             << ")";
      }
      code << "})";
      push(code.str(), ykobject(dt));
      return;
    } else {
      // ---------- On heap --------
      auto temp_name = temp();
      write_indent(body_);
      body_ << convert_dt(dt) << " " << temp_name << " = ";
      obj_calloc(prefixed_class_name, body_);
      write_end_statement(body_);
      for (auto const &para : obj->values_) {
        para.value_->accept(this);
        auto val = pop();
        write_indent(body_);
        body_ << temp_name << "->" << c_mod_prefix << para.name_->token_
              << " = (" << val.first << ")";
        write_end_statement(body_);
      }
      push(temp_name, ykobject(dt));
      return;
    }
  }
  error(obj->curly_open_, "Failed to compile struct literal");
  push("<><>", ykobject(dt_pool_));
}
void compiler::visit_macro_call_expr(macro_call_expr *obj) {
  // Not supported directly by compiler
}
void compiler::visit_cfor_stmt(cfor_stmt *obj) {
  write_indent(body_);
  push_scope_type(ast_type::STMT_WHILE);
  scope_.push();
  deletions_.push_delete_stack(ast_type::STMT_WHILE);
  defers_.push_defer_stack(ast_type::STMT_WHILE);
  indent();
  body_ << "for (";
  if (obj->init_expr_ != nullptr) {
    inline_mode_ = true;
    auto current = statements_;
    obj->init_expr_->accept(this);
    inline_mode_ = false;
    if (statements_ >= current + 2) {
      error(obj->open_paren_, "Failed to compile c like for loop, this "
                              "initialization expression cannot be used here.");
    }
    if (obj->init_expr_->get_type() != ast_type::EXPR_ASSIGN) {
      auto code = pop();
      body_ << code.first;
    }
  }
  body_ << ";";
  if (obj->comparison_ != nullptr) {
    inline_mode_ = true;
    auto current = statements_;
    obj->comparison_->accept(this);
    inline_mode_ = false;
    if (statements_ >= current + 1) {
      error(obj->semi1_, "Failed to compile c like for loop, this comparison "
                         "expression cannot be used here.");
    }
    if (obj->comparison_->get_type() != ast_type::EXPR_ASSIGN) {
      auto code = pop();
      body_ << code.first;
    }
  }
  body_ << ";";
  if (obj->operation_ != nullptr) {
    inline_mode_ = true;
    auto current = statements_;
    obj->operation_->accept(this);
    inline_mode_ = false;
    if (statements_ >= current + 2) {
      error(obj->semi2_, "Failed to compile c like for loop, this operation "
                         "expression cannot be used here.");
    }
    if (obj->operation_->get_type() != ast_type::EXPR_ASSIGN) {
      auto code = pop();
      body_ << code.first;
    }
  }
  body_ << ")";
  obj->for_body_->accept(this);
  dedent();
  pop_scope_type();
  scope_.pop();
  defers_.pop_defer_stack();
  deletions_.pop_delete_stack();
}
void compiler::visit_enum_stmt(enum_stmt *obj) {}
void compiler::visit_union_stmt(union_stmt *obj) {}
