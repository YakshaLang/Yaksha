// literal_utils.h
#ifndef LITERAL_UTILS_H
#define LITERAL_UTILS_H
#include "tokenizer/token.h"
#include <cstdint>
namespace yaksha {
  enum class literal_type {
    LT_INT,
    LT_UINT,
    LT_F32,
    LT_F64,
    LT_INVALID,
  };
  union literal_number {
    intmax_t i64_;
    uintmax_t u64_;
    double f64_;
    float f32_;
  };
  struct literal_conversion_result {
    literal_type type_ = literal_type::LT_INVALID;
    literal_number number_ = {.i64_ = 0};
    std::string error_{};
    std::string decimal_string_{};
  };
  literal_conversion_result convert_literal(token_type token_type_val,
                                            token *literal_token);
}// namespace yaksha
#endif
