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
  // TODO can we reuse context data type? or make this usable in constant folding context?
  struct literal_number {
    intmax_t i64_{0};
    uintmax_t u64_{0};
    float f32_{0.0f};
    double f64_{0.0};
  };
  struct literal_conversion_result {
    literal_type type_ = literal_type::LT_INVALID;
    literal_number number_{};
    std::string error_{};
    std::string decimal_string_{};
  };
  literal_conversion_result convert_literal(token_type token_type_val,
                                            token *literal_token);
}// namespace yaksha
#endif
