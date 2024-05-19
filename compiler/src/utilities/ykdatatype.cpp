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
ykdatatype::ykdatatype(token *primitive_dt) {
  token_ = new token();
  type_ = primitive_dt->token_;
  token_->token_ = primitive_dt->token_;
  token_->type_ = primitive_dt->type_;
  token_->pos_ = primitive_dt->pos_;
  token_->line_ = primitive_dt->line_;
  token_->file_ = primitive_dt->file_;
  find_builtin_or_primitive();
}
void ykdatatype::find_builtin_or_primitive() {
  if (token_->type_ == token_type::INTEGER_DECIMAL) {
    builtin_type_ = ykbuiltin::DIMENSION;
  } else if (token_->token_ == "i8") {
    primitive_type_ = ykprimitive::I8;
  } else if (token_->token_ == "i16") {
    primitive_type_ = ykprimitive::I16;
  } else if (token_->token_ == "i64") {
    primitive_type_ = ykprimitive::I64;
  } else if (token_->token_ == "u8") {
    primitive_type_ = ykprimitive::U8;
  } else if (token_->token_ == "u16") {
    primitive_type_ = ykprimitive::U16;
  } else if (token_->token_ == "u32") {
    primitive_type_ = ykprimitive::U32;
  } else if (token_->token_ == "u64") {
    primitive_type_ = ykprimitive::U64;
  } else if (token_->token_ == "int" || token_->token_ == "i32") {
    primitive_type_ = ykprimitive::I32;
  } else if (token_->token_ == "float" || token_->token_ == "f32") {
    primitive_type_ = ykprimitive::F32;
  } else if (token_->token_ == "f64") {
    primitive_type_ = ykprimitive::F64;
  } else if (token_->token_ == "str") {
    primitive_type_ = ykprimitive::STR;
  } else if (token_->token_ == "sr") {
    primitive_type_ = ykprimitive::SR;
  } else if (token_->token_ == ":s:") {
    primitive_type_ = ykprimitive::HIDDEN_STRING_LIT;
  } else if (token_->token_ == "bool") {
    primitive_type_ = ykprimitive::BOOL;
  } else if (token_->token_ == "None") {
    primitive_type_ = ykprimitive::NONE;
  } else if (token_->token_ == "Array") {
    builtin_type_ = ykbuiltin::ARRAY;
  } else if (token_->token_ == "Const") {
    builtin_type_ = ykbuiltin::CONSTANT;
  } else if (token_->token_ == "Ptr") {
    builtin_type_ = ykbuiltin::POINTER;
  } else if (token_->token_ == "SMEntry") {
    builtin_type_ = ykbuiltin::SM_ENTRY;
  } else if (token_->token_ == "MEntry") {
    builtin_type_ = ykbuiltin::M_ENTRY;
  } else if (token_->token_ == "Function") {
    builtin_type_ = ykbuiltin::FUNCTION;
  } else if (token_->token_ == "In") {
    builtin_type_ = ykbuiltin::F_IN;
  } else if (token_->token_ == "Out") {
    builtin_type_ = ykbuiltin::F_OUT;
  } else if (token_->token_ == "AnyPtr") {
    builtin_type_ = ykbuiltin::ANY_PTR;
  } else if (token_->token_ == "AnyPtrToConst") {
    builtin_type_ = ykbuiltin::ANY_PTR_TO_CONST;
  } else if (token_->token_ == "Tuple") {
    builtin_type_ = ykbuiltin::TUPLE;
  } else if (token_->token_ == "FixedArr") {
    builtin_type_ = ykbuiltin::FIXED_ARRAY;
  }
}
ykdatatype::~ykdatatype() { delete (token_); }
bool ykdatatype::is_i8() const { return primitive_type_ == ykprimitive::I8; }
bool ykdatatype::is_i16() const { return primitive_type_ == ykprimitive::I16; }
bool ykdatatype::is_i32() const { return primitive_type_ == ykprimitive::I32; }
bool ykdatatype::is_i64() const { return primitive_type_ == ykprimitive::I64; }
bool ykdatatype::is_u8() const { return primitive_type_ == ykprimitive::U8; }
bool ykdatatype::is_u16() const { return primitive_type_ == ykprimitive::U16; }
bool ykdatatype::is_u32() const { return primitive_type_ == ykprimitive::U32; }
bool ykdatatype::is_u64() const { return primitive_type_ == ykprimitive::U64; }
bool ykdatatype::is_str() const { return primitive_type_ == ykprimitive::STR; }
bool ykdatatype::is_sr() const { return primitive_type_ == ykprimitive::SR; }
bool ykdatatype::is_f32() const { return primitive_type_ == ykprimitive::F32; }
bool ykdatatype::is_f64() const { return primitive_type_ == ykprimitive::F64; }
bool ykdatatype::is_bool() const {
  return primitive_type_ == ykprimitive::BOOL;
}
bool ykdatatype::is_none() const {
  return primitive_type_ == ykprimitive::NONE;
}
void ykdatatype::write_to_str(std::stringstream &s, bool write_mod) const {
  std::vector<std::pair<const ykdatatype *, std::string>> stack{};
  stack.emplace_back(this, "");
  while (!stack.empty()) {
    auto item = stack.back();
    const ykdatatype *dt = item.first;
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
    s << dt->token_->token_;
    // arguments
    if (!dt->args_.empty()) {
      stack.emplace_back(
          std::make_pair<const ykdatatype *, std::string>(nullptr, "]"));
      int length = (int) dt->args_.size();
      for (int i = length; i > 0; --i) {
        const ykdatatype *arg = dt->args_[i - 1];
        stack.emplace_back(arg, "");
        if (i > 1) {
          stack.emplace_back(
              std::make_pair<const ykdatatype *, std::string>(nullptr, ", "));
        }
      }
      stack.emplace_back(
          std::make_pair<const ykdatatype *, std::string>(nullptr, "["));
    }
  }
}
std::string ykdatatype::as_string() const {
  std::stringstream s{};
  this->write_to_str(s);
  return s.str();
}
std::string ykdatatype::as_string_simplified() const {
  std::stringstream s{};
  this->write_to_str(s, false);
  return s.str();
}
bool ykdatatype::is_primitive() const {
  return is_str() || is_sr() || is_string_literal() || is_bool() || is_f32() ||
         is_f64() || is_i8() || is_i16() || is_i32() || is_i64() || is_u8() ||
         is_u16() || is_u32() || is_u64() || is_none();
}
bool ykdatatype::is_c_primitive() const {
  return is_bool() || is_f32() || is_f64() || is_i8() || is_i16() || is_i32() ||
         is_i64() || is_u8() || is_u16() || is_u32() || is_u64();
}
ykdatatype::ykdatatype(std::string primitive) : type_(std::move(primitive)) {
  token_ = new token();
  token_->token_ = type_;
  token_->type_ = token_type::NAME;
  token_->pos_ = -1;
  token_->line_ = -1;
  token_->file_ = "";
  find_builtin_or_primitive();
}
ykdatatype::ykdatatype(std::string primitive_dt, std::string module)
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
bool ykdatatype::is_a_number() const { return is_an_integer() || is_a_float(); }
bool ykdatatype::is_an_integer() const {
  return is_i8() || is_i16() || is_i32() || is_i64() || is_u8() || is_u16() ||
         is_u32() || is_u64();
}
bool ykdatatype::is_array() const {
  return !is_primitive() && builtin_type_ == ykbuiltin::ARRAY;
}
bool ykdatatype::is_const() const {
  return !is_primitive() && builtin_type_ == ykbuiltin::CONSTANT;
}
bool ykdatatype::is_a_signed_integer() const {
  return is_i8() || is_i16() || is_i32() || is_i64();
}
bool ykdatatype::is_an_unsigned_integer() const {
  return is_u8() || is_u16() || is_u32() || is_u64();
}
bool ykdatatype::is_a_float() const { return is_f32() || is_f64(); }
bool ykdatatype::is_builtin_or_primitive() const {
  return this->primitive_type_ != ykprimitive::NOT_A_PRIMITIVE ||
         this->builtin_type_ != ykbuiltin::NOT_A_BUILTIN;
}
bool ykdatatype::is_ptr() const {
  return !is_primitive() && builtin_type_ == ykbuiltin::POINTER;
}
bool ykdatatype::is_m_entry() const {
  return !is_primitive() && builtin_type_ == ykbuiltin::M_ENTRY;
}
bool ykdatatype::is_sm_entry() const {
  return !is_primitive() && builtin_type_ == ykbuiltin::SM_ENTRY;
}
bool ykdatatype::is_function() const {
  return !is_primitive() && builtin_type_ == ykbuiltin::FUNCTION;
}
bool ykdatatype::is_function_input() const {
  return !is_primitive() && builtin_type_ == ykbuiltin::F_IN;
}
bool ykdatatype::is_function_output() const {
  return !is_primitive() && builtin_type_ == ykbuiltin::F_OUT;
}
bool ykdatatype::is_any_ptr() const {
  return !is_primitive() && builtin_type_ == ykbuiltin::ANY_PTR;
}
bool ykdatatype::is_any_ptr_to_const() const {
  return !is_primitive() && builtin_type_ == ykbuiltin::ANY_PTR_TO_CONST;
}
bool ykdatatype::is_tuple() const {
  return !is_primitive() && builtin_type_ == ykbuiltin::TUPLE;
}
ykdatatype *ykdatatype::const_unwrap() {
  if (is_const()) { return args_[0]; }
  return this;
}
bool ykdatatype::is_string_literal() const {
  return primitive_type_ == ykprimitive::HIDDEN_STRING_LIT;
}
bool ykdatatype::is_a_string() const { return +primitive_type_ >= 1000; }
ykdatatype *ykdatatype::auto_cast(ykdatatype *rhs, ykdt_pool *pool,
                                  bool lhs_mutates, bool assignment) {
  ykdatatype *castable = nullptr;
  if ((lhs_mutates || assignment) && is_const()) { return nullptr; }
  ykdatatype *lhsu = const_unwrap();
  ykdatatype *rhsu = rhs->const_unwrap();
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
bool ykdatatype::is_fixed_size_array() const {
  return !is_primitive() && builtin_type_ == ykbuiltin::FIXED_ARRAY;
}
bool ykdatatype::is_dimension() const {
  return !is_primitive() && builtin_type_ == ykbuiltin::DIMENSION;
}
bool yaksha::internal_is_identical_type(ykdatatype *required_datatype,
                                        ykdatatype *provided_datatype) {
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
