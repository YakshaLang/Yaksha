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
// ykdatatype.h
#ifndef YKDATATYPE_H
#define YKDATATYPE_H
#include "tokenizer/token.h"
#include <sstream>
#include <vector>
namespace yaksha {
  enum class yk_primitive {
    // Numeric > 0 && < 1000
    BOOL = 1,
    HIDDEN_I4 [[maybe_unused]] = 2,// reserved
    HIDDEN_U4 [[maybe_unused]] = 3,// reserved
    I8 = 4,
    U8 = 5,
    I16 = 6,
    U16 = 7,
    I32 = 8,
    U32 = 9,
    I64 = 10,
    U64 = 11,
    HIDDEN_F8 [[maybe_unused]] = 12, // reserved
    HIDDEN_F16 [[maybe_unused]] = 13,// reserved
    F32 = 14,
    F64 = 15,
    // String >= 1000
    HIDDEN_STRING_LIT = 1000,// internal use only
    SR = 2000,
    STR = 3000,
    // None == 0
    NONE = 0,
    // Invalid < 0
    NOT_A_PRIMITIVE = -9999,// internal use only
  };
  enum class yk_builtin {
    ARRAY,
    SM_ENTRY,
    M_ENTRY,
    NOT_A_BUILTIN,
    CONSTANT,
    POINTER,
    PTR_TO_ANY,      // void *
    PTR_TO_CONST_ANY,// void const *
    TUPLE,
    // Function[In[str],Out]
    FUNCTION,
    F_IN, // ----- special metadata
    F_OUT,// ----- special metadata
    // Fixed Size Array
    // FixedArr[int, 10] // <--- 10 is the size, stored in dimension
    FIXED_ARRAY,
    DIMENSION,// ----- special metadata
  };
  struct yk_datatype_pool;
  struct yk_datatype {
    explicit yk_datatype(token *primitive_dt);
    explicit yk_datatype(std::string primitive_dt);
    explicit yk_datatype(std::string primitive_dt, std::string module);
    ~yk_datatype();
    [[nodiscard]] yk_datatype *const_unwrap();
    [[nodiscard]] yk_datatype *auto_cast(yk_datatype *rhs,
                                         yk_datatype_pool *pool,
                                         bool lhs_mutates, bool assignment);
    [[nodiscard]] std::string as_string() const;
    [[nodiscard]] std::string as_string_simplified() const;
    // meta type
    [[nodiscard]] bool is_c_primitive() const;
    [[nodiscard]] bool is_primitive() const;
    [[nodiscard]] bool is_builtin_or_primitive() const;
    // const type modifier
    [[nodiscard]] bool is_const() const;
    // number types
    [[nodiscard]] bool is_i8() const;
    [[nodiscard]] bool is_i16() const;
    [[nodiscard]] bool is_i32() const;
    [[nodiscard]] bool is_i64() const;
    [[nodiscard]] bool is_u8() const;
    [[nodiscard]] bool is_u16() const;
    [[nodiscard]] bool is_u32() const;
    [[nodiscard]] bool is_u64() const;
    [[nodiscard]] bool is_f32() const;
    [[nodiscard]] bool is_f64() const;
    // none type
    [[nodiscard]] bool is_none() const;
    // strings
    [[nodiscard]] bool is_str() const;
    [[nodiscard]] bool is_sr() const;
    [[nodiscard]] bool is_string_literal() const;
    // bool
    [[nodiscard]] bool is_bool() const;
    // containers or container parts
    [[nodiscard]] bool is_array() const;
    [[nodiscard]] bool is_ptr() const;
    [[nodiscard]] bool is_m_entry() const;
    [[nodiscard]] bool is_sm_entry() const;
    [[nodiscard]] bool is_function() const;
    [[nodiscard]] bool is_function_input() const;
    [[nodiscard]] bool is_function_output() const;
    [[nodiscard]] bool is_any_ptr() const;
    [[nodiscard]] bool is_any_ptr_to_const() const;
    [[nodiscard]] bool is_tuple() const;
    [[nodiscard]] bool is_fixed_size_array() const;
    [[nodiscard]] bool is_dimension() const;
    // match a combination of primitives
    [[nodiscard]] bool is_a_number() const;
    [[nodiscard]] bool is_an_integer() const;
    [[nodiscard]] bool is_a_signed_integer() const;
    [[nodiscard]] bool is_an_unsigned_integer() const;
    [[nodiscard]] bool is_a_string() const;
    [[nodiscard]] bool is_a_float() const;
    token *token_{};
    std::string type_{};
    std::string module_{};
    std::vector<yk_datatype *> args_;
    int dimension_{-1};
    yk_primitive primitive_type_{yk_primitive::NOT_A_PRIMITIVE};
    yk_builtin builtin_type_{yk_builtin::NOT_A_BUILTIN};
    bool widen_rhs{false};
    bool widen_lhs{false};
    size_t hits_{0};
    // for distinguishing between fixedarr(...) and variable_to_fixedarr
    bool inlinable_literal_{false};

private:
    void write_to_str(std::stringstream &s, bool write_mod = true) const;
    void find_builtin_or_primitive();
  };
  bool internal_is_identical_type(yk_datatype *required_datatype,
                                  yk_datatype *provided_datatype);
}// namespace yaksha
#endif
