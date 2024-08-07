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
// ykdatatype.cpp
#include "ykdatatype.h"
#include "compiler/compiler_utils.h"
#include "utilities/cpp_util.h"
#include "ykdt_pool.h"
#include <utility>
using namespace yaksha;
yk_datatype::yk_datatype(token *primitive_dt) {
  token_ = new token();
  type_ = primitive_dt->token_;
  token_->token_ = primitive_dt->token_;
  token_->type_ = primitive_dt->type_;
  token_->pos_ = primitive_dt->pos_;
  token_->line_ = primitive_dt->line_;
  token_->file_ = primitive_dt->file_;
  find_builtin_or_primitive();
}
void yk_datatype::find_builtin_or_primitive() {
  if (token_->type_ == token_type::INTEGER_DECIMAL) {
    builtin_type_ = yk_builtin::DIMENSION;
  } else if (token_->token_ == "i8") {
    primitive_type_ = yk_primitive::I8;
  } else if (token_->token_ == "i16") {
    primitive_type_ = yk_primitive::I16;
  } else if (token_->token_ == "i64") {
    primitive_type_ = yk_primitive::I64;
  } else if (token_->token_ == "u8") {
    primitive_type_ = yk_primitive::U8;
  } else if (token_->token_ == "u16") {
    primitive_type_ = yk_primitive::U16;
  } else if (token_->token_ == "u32") {
    primitive_type_ = yk_primitive::U32;
  } else if (token_->token_ == "u64") {
    primitive_type_ = yk_primitive::U64;
  } else if (token_->token_ == "int" || token_->token_ == "i32") {
    primitive_type_ = yk_primitive::I32;
  } else if (token_->token_ == "float" || token_->token_ == "f32") {
    primitive_type_ = yk_primitive::F32;
  } else if (token_->token_ == "f64") {
    primitive_type_ = yk_primitive::F64;
  } else if (token_->token_ == "str") {
    primitive_type_ = yk_primitive::STR;
  } else if (token_->token_ == "sr") {
    primitive_type_ = yk_primitive::SR;
  } else if (token_->token_ == ":s:") {
    primitive_type_ = yk_primitive::HIDDEN_STRING_LIT;
  } else if (token_->token_ == "bool") {
    primitive_type_ = yk_primitive::BOOL;
  } else if (token_->token_ == "None") {
    primitive_type_ = yk_primitive::NONE;
  } else if (token_->token_ == "Array") {
    builtin_type_ = yk_builtin::ARRAY;
  } else if (token_->token_ == "Const") {
    builtin_type_ = yk_builtin::CONSTANT;
  } else if (token_->token_ == "Ptr") {
    builtin_type_ = yk_builtin::POINTER;
  } else if (token_->token_ == "SMEntry") {
    builtin_type_ = yk_builtin::SM_ENTRY;
  } else if (token_->token_ == "MEntry") {
    builtin_type_ = yk_builtin::M_ENTRY;
  } else if (token_->token_ == "Function") {
    builtin_type_ = yk_builtin::FUNCTION;
  } else if (token_->token_ == "In") {
    builtin_type_ = yk_builtin::F_IN;
  } else if (token_->token_ == "Out") {
    builtin_type_ = yk_builtin::F_OUT;
  } else if (token_->token_ == "AnyPtr") {
    builtin_type_ = yk_builtin::PTR_TO_ANY;
  } else if (token_->token_ == "AnyPtrToConst") {
    builtin_type_ = yk_builtin::PTR_TO_CONST_ANY;
  } else if (token_->token_ == "Tuple") {
    builtin_type_ = yk_builtin::TUPLE;
  } else if (token_->token_ == "FixedArr") {
    builtin_type_ = yk_builtin::FIXED_ARRAY;
  }
}
yk_datatype::~yk_datatype() { delete (token_); }
bool yk_datatype::is_i8() const { return primitive_type_ == yk_primitive::I8; }
bool yk_datatype::is_i16() const {
  return primitive_type_ == yk_primitive::I16;
}
bool yk_datatype::is_i32() const {
  return primitive_type_ == yk_primitive::I32;
}
bool yk_datatype::is_i64() const {
  return primitive_type_ == yk_primitive::I64;
}
bool yk_datatype::is_u8() const { return primitive_type_ == yk_primitive::U8; }
bool yk_datatype::is_u16() const {
  return primitive_type_ == yk_primitive::U16;
}
bool yk_datatype::is_u32() const {
  return primitive_type_ == yk_primitive::U32;
}
bool yk_datatype::is_u64() const {
  return primitive_type_ == yk_primitive::U64;
}
bool yk_datatype::is_str() const {
  return primitive_type_ == yk_primitive::STR;
}
bool yk_datatype::is_sr() const { return primitive_type_ == yk_primitive::SR; }
bool yk_datatype::is_f32() const {
  return primitive_type_ == yk_primitive::F32;
}
bool yk_datatype::is_f64() const {
  return primitive_type_ == yk_primitive::F64;
}
bool yk_datatype::is_bool() const {
  return primitive_type_ == yk_primitive::BOOL;
}
bool yk_datatype::is_none() const {
  return primitive_type_ == yk_primitive::NONE;
}
void yk_datatype::write_to_str(std::stringstream &s, bool write_mod) const {
  std::vector<std::pair<const yk_datatype *, std::string>> stack{};
  stack.emplace_back(this, "");
  while (!stack.empty()) {
    auto item = stack.back();
    const yk_datatype *dt = item.first;
    auto text = item.second;
    stack.pop_back();
    // text node, write it
    if (dt == nullptr) {
      s << text;
      continue;
    }
    // actual datatype or datatype arg (also a datatype)
    if (!dt->module_.empty() && write_mod && !dt->is_dimension()) {
      s << dt->module_ << ":::";
    }
    // i32 == int, f32 == float.
    // so avoid writing the token for these 2 types
    if (dt->is_i32()) {
      s << "i32";
    } else if (dt->is_f32()) {
      s << "f32";
    } else {
      s << dt->token_->token_;
    }
    // arguments
    if (!dt->args_.empty()) {
      stack.emplace_back(
          std::make_pair<const yk_datatype *, std::string>(nullptr, "]"));
      int length = (int) dt->args_.size();
      for (int i = length; i > 0; --i) {
        const yk_datatype *arg = dt->args_[i - 1];
        stack.emplace_back(arg, "");
        if (i > 1) {
          stack.emplace_back(
              std::make_pair<const yk_datatype *, std::string>(nullptr, ", "));
        }
      }
      stack.emplace_back(
          std::make_pair<const yk_datatype *, std::string>(nullptr, "["));
    }
  }
}
std::string yk_datatype::as_string() const {
  std::stringstream s{};
  this->write_to_str(s);
  return s.str();
}
std::string yk_datatype::as_string_simplified() const {
  std::stringstream s{};
  this->write_to_str(s, false);
  return s.str();
}
bool yk_datatype::is_primitive() const {
  return is_str() || is_sr() || is_string_literal() || is_bool() || is_f32() ||
         is_f64() || is_i8() || is_i16() || is_i32() || is_i64() || is_u8() ||
         is_u16() || is_u32() || is_u64() || is_none();
}
bool yk_datatype::is_c_primitive() const {
  return is_bool() || is_f32() || is_f64() || is_i8() || is_i16() || is_i32() ||
         is_i64() || is_u8() || is_u16() || is_u32() || is_u64();
}
yk_datatype::yk_datatype(std::string primitive) : type_(std::move(primitive)) {
  token_ = new token();
  token_->token_ = type_;
  token_->type_ = token_type::NAME;
  token_->pos_ = -1;
  token_->line_ = -1;
  token_->file_ = "";
  find_builtin_or_primitive();
}
yk_datatype::yk_datatype(std::string primitive_dt, std::string module)
    : type_(std::move(primitive_dt)), module_(std::move(module)) {
  token_ = new token();
  token_->token_ = type_;
  token_->type_ = token_type::NAME;
  token_->pos_ = -1;
  token_->line_ = -1;
  token_->file_ = "";
  find_builtin_or_primitive();
  if (is_builtin_or_primitive()) {
    module_ = "";// Do not store module if it's a primitive
  }
}
bool yk_datatype::is_a_number() const {
  return is_an_integer() || is_a_float();
}
bool yk_datatype::is_an_integer() const {
  return is_i8() || is_i16() || is_i32() || is_i64() || is_u8() || is_u16() ||
         is_u32() || is_u64();
}
bool yk_datatype::is_array() const {
  return !is_primitive() && builtin_type_ == yk_builtin::ARRAY;
}
bool yk_datatype::is_const() const {
  return !is_primitive() && builtin_type_ == yk_builtin::CONSTANT;
}
bool yk_datatype::is_a_signed_integer() const {
  return is_i8() || is_i16() || is_i32() || is_i64();
}
bool yk_datatype::is_an_unsigned_integer() const {
  return is_u8() || is_u16() || is_u32() || is_u64();
}
bool yk_datatype::is_a_float() const { return is_f32() || is_f64(); }
bool yk_datatype::is_builtin_or_primitive() const {
  return this->primitive_type_ != yk_primitive::NOT_A_PRIMITIVE ||
         this->builtin_type_ != yk_builtin::NOT_A_BUILTIN;
}
bool yk_datatype::is_ptr() const {
  return !is_primitive() && builtin_type_ == yk_builtin::POINTER;
}
bool yk_datatype::is_m_entry() const {
  return !is_primitive() && builtin_type_ == yk_builtin::M_ENTRY;
}
bool yk_datatype::is_sm_entry() const {
  return !is_primitive() && builtin_type_ == yk_builtin::SM_ENTRY;
}
bool yk_datatype::is_function() const {
  return !is_primitive() && builtin_type_ == yk_builtin::FUNCTION;
}
bool yk_datatype::is_function_input() const {
  return !is_primitive() && builtin_type_ == yk_builtin::F_IN;
}
bool yk_datatype::is_function_output() const {
  return !is_primitive() && builtin_type_ == yk_builtin::F_OUT;
}
bool yk_datatype::is_any_ptr() const {
  return !is_primitive() && builtin_type_ == yk_builtin::PTR_TO_ANY;
}
bool yk_datatype::is_any_ptr_to_const() const {
  return !is_primitive() && builtin_type_ == yk_builtin::PTR_TO_CONST_ANY;
}
bool yk_datatype::is_tuple() const {
  return !is_primitive() && builtin_type_ == yk_builtin::TUPLE;
}
yk_datatype *yk_datatype::const_unwrap() {
  if (is_const()) { return args_[0]; }
  return this;
}
bool yk_datatype::is_string_literal() const {
  return primitive_type_ == yk_primitive::HIDDEN_STRING_LIT;
}
bool yk_datatype::is_a_string() const { return +primitive_type_ >= 1000; }
yk_datatype *yk_datatype::auto_cast(yk_datatype *rhs, yk_datatype_pool *pool,
                                    bool lhs_mutates, bool assignment) {
  yk_datatype *castable = nullptr;
  if ((lhs_mutates || assignment) && is_const()) { return nullptr; }
  yk_datatype *lhsu = const_unwrap();
  yk_datatype *rhsu = rhs->const_unwrap();
  // Identical type cannot be cast as they are already same
  if (internal_is_identical_type(lhsu, rhsu)) { return nullptr; }
  auto li = +lhsu->primitive_type_;
  auto ri = +rhsu->primitive_type_;
  if (lhsu->is_a_string() && rhsu->is_a_string()) {
    castable = pool->create("str");
  } else if (li > 0 && li < 1000 && ri > 0 && ri < 1000) {
    if (assignment && li < ri) { return nullptr; }
    if (li > ri) {
      if (lhsu->is_an_unsigned_integer() && rhsu->is_a_signed_integer()) {
        // WHY?
        // If the bigger number is an unsigned, we cannot auto widen other number to match.
        return nullptr;
      }
      castable = pool->create(lhsu->type_);
      castable->widen_rhs = true;
      castable->widen_lhs = false;
    } else {
      if (rhsu->is_an_unsigned_integer() && lhsu->is_a_signed_integer()) {
        return nullptr;
      }
      castable = pool->create(rhsu->type_);
      castable->widen_rhs = false;
      castable->widen_lhs = true;
    }
  }
  return castable;
}
bool yk_datatype::is_fixed_size_array() const {
  return !is_primitive() && builtin_type_ == yk_builtin::FIXED_ARRAY;
}
bool yk_datatype::is_dimension() const {
  return !is_primitive() && builtin_type_ == yk_builtin::DIMENSION;
}
bool yaksha::internal_is_identical_type(yk_datatype *required_datatype,
                                        yk_datatype *provided_datatype) {
  if (required_datatype != nullptr && provided_datatype != nullptr) {
    if (required_datatype->is_primitive() &&
        provided_datatype->is_primitive()) {
      return required_datatype->primitive_type_ ==
             provided_datatype->primitive_type_;
    }
    return required_datatype->as_string() == provided_datatype->as_string();
  }
  return false;
}
