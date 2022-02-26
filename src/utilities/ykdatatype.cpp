// ykdatatype.cpp
#include "ykdatatype.h"
#include "compiler/compiler_utils.h"
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
  if (token_->token_ == "i8") {
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
  } else if (token_->token_ == "bool") {
    primitive_type_ = ykprimitive::BOOL;
  } else if (token_->token_ == "None") {
    primitive_type_ = ykprimitive::NONE;
  } else if (token_->token_ == "Array") {
    builtin_type_ = ykbuiltin::ARRAY;
  }
}
ykdatatype::~ykdatatype() { delete (token_); }
bool ykdatatype::is_int() const { return primitive_type_ == ykprimitive::I32; }
bool ykdatatype::is_i8() const { return primitive_type_ == ykprimitive::I8; }
bool ykdatatype::is_i16() const { return primitive_type_ == ykprimitive::I16; }
bool ykdatatype::is_i32() const { return primitive_type_ == ykprimitive::I32; }
bool ykdatatype::is_i64() const { return primitive_type_ == ykprimitive::U64; }
bool ykdatatype::is_u8() const { return primitive_type_ == ykprimitive::U8; }
bool ykdatatype::is_u16() const { return primitive_type_ == ykprimitive::U16; }
bool ykdatatype::is_u32() const { return primitive_type_ == ykprimitive::U32; }
bool ykdatatype::is_u64() const { return primitive_type_ == ykprimitive::U64; }
bool ykdatatype::is_str() const { return primitive_type_ == ykprimitive::STR; }
bool ykdatatype::is_float() const {
  return primitive_type_ == ykprimitive::F32;
}
bool ykdatatype::is_f32() const { return primitive_type_ == ykprimitive::F32; }
bool ykdatatype::is_f64() const { return primitive_type_ == ykprimitive::F64; }
bool ykdatatype::is_bool() const {
  return primitive_type_ == ykprimitive::BOOL;
}
bool ykdatatype::is_none() const {
  return primitive_type_ == ykprimitive::NONE;
}
void ykdatatype::write_to_str(std::stringstream &s) const {
  if (!module_.empty()) { s << module_ << ":::"; }
  s << token_->token_;
  if (!args_.empty()) {
    s << "[";
    bool first = true;
    for (auto arg : args_) {
      if (first) {
        first = false;
      } else {
        s << ", ";
      }
      arg->write_to_str(s);
    }
    s << "]";
  }
}
std::string ykdatatype::as_string() const {
  std::stringstream s{};
  this->write_to_str(s);
  return s.str();
}
bool ykdatatype::is_primitive() const {
  return is_str() || is_int() || is_float() || is_bool() || is_f32() ||
         is_f64() || is_i8() || is_i16() || is_i32() || is_i64() || is_u8() ||
         is_u16() || is_u32() || is_u64() || is_none();
}
bool ykdatatype::matches(const yaksha::ykdatatype &template_) const {
  return *this == template_;
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
bool ykdatatype::support_plus() const {
  return is_str() || is_int() || is_float() || is_f32() || is_f64() ||
         is_i8() || is_i16() || is_i32() || is_i64() || is_u8() || is_u16() ||
         is_u32() || is_u64();
}
bool ykdatatype::is_a_number() const {
  return is_int() || is_float() || is_f32() || is_f64() || is_i8() ||
         is_i16() || is_i32() || is_i64() || is_u8() || is_u16() || is_u32() ||
         is_u64();
}
bool ykdatatype::is_an_integer() const {
  return is_int() || is_i8() || is_i16() || is_i32() || is_i64() || is_u8() ||
         is_u16() || is_u32() || is_u64();
}
bool ykdatatype::is_an_array() const {
  return !is_primitive() && builtin_type_ == ykbuiltin::ARRAY;
}
bool ykdatatype::is_a_signed_integer() const {
  return is_int() || is_i8() || is_i16() || is_i32() || is_i64();
}
bool ykdatatype::is_an_unsigned_integer() const {
  return is_u8() || is_u16() || is_u32() || is_u64();
}
bool ykdatatype::is_a_float() const {
  return is_float() || is_f32() || is_f64();
}
bool ykdatatype::is_builtin_or_primitive() const {
  return this->primitive_type_ != ykprimitive::NOT_A_PRIMITIVE ||
         this->builtin_type_ != ykbuiltin::NOT_A_BUILTIN;
}
