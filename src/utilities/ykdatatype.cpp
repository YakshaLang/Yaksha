// ykdatatype.cpp
#include "ykdatatype.h"
using namespace yaksha;
ykdatatype::ykdatatype() = default;
ykdatatype::~ykdatatype() = default;
bool ykdatatype::is_int() const { return name_->token_ == "int"; }
bool ykdatatype::is_i8() const { return name_->token_ == "i8"; }
bool ykdatatype::is_i16() const { return name_->token_ == "i16"; }
bool ykdatatype::is_i32() const { return name_->token_ == "i32"; }
bool ykdatatype::is_i64() const { return name_->token_ == "i64"; }
bool ykdatatype::is_u8() const { return name_->token_ == "u8"; }
bool ykdatatype::is_u16() const { return name_->token_ == "u16"; }
bool ykdatatype::is_u32() const { return name_->token_ == "u32"; }
bool ykdatatype::is_u64() const { return name_->token_ == "u64"; }
bool ykdatatype::is_str() const { return name_->token_ == "str"; }
bool ykdatatype::is_float() const { return name_->token_ == "float"; }
bool ykdatatype::is_f32() const { return name_->token_ == "f32"; }
bool ykdatatype::is_f64() const { return name_->token_ == "f64"; }
bool ykdatatype::is_bool() const { return name_->token_ == "bool"; }
bool ykdatatype::is_none() const { return name_->token_ == "None"; }
void ykdatatype::write_to_str(std::stringstream &s) const {
  s << name_->token_;
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
