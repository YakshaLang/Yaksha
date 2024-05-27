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
// ykobject.h
#ifndef YKOBJECT_H
#define YKOBJECT_H
#include "ast/ast.h"
#include "tokenizer/string_utils.h"
#include "tokenizer/token.h"
#include "ykdatatype.h"
#include "ykdt_pool.h"
#include <string>
namespace yaksha {
  enum class const_fold_type {
    CFT_INT8,
    CFT_INT16,
    CFT_INT32,
    CFT_INT64,
    CFT_UINT8,
    CFT_UINT16,
    CFT_UINT32,
    CFT_UINT64,
    CFT_FLOAT,
    CFT_DOUBLE,
    CFT_BOOL,
    CFT_STRING, /* str, sr, string literal --> will not support strings (some optimizations are done at later stage) */
    CFT_NONE,
    CFT_NON_PRIMITIVE, /* array, map, tuple, fixed-array -> will not support */
    CFT_UNKNOWN,
    CFT_ERROR_OCCURRED
    // TODO see if we can remove unused
  };
  enum class const_fold_context_type {
    CFT_EXPR, /* this is an expression that cannot be folded */
    CFT_STMT,
    CFT_ERROR_OCCURRED,// TODO perhaps we can remove this?
    CFT_VALUE,         /* this is a folded value */
                       // TODO see if we can remove below
    CFT_GARBAGE_VALUE /* this is a garbage value, also an expression that cannot be folded */
  };
  struct const_fold_value_holder {
    intmax_t int_val_{0};
    uintmax_t uint_val_{0};
    float float_val_{0.0f};
    double double_val_{0.0};
    bool bool_val_{false};
  };
  struct expr_or_stmt {
    expr *expr_val_{nullptr};
    stmt *stmt_val_{nullptr};
  };
  struct const_fold_context {
    const_fold_type fold_type_ = const_fold_type::CFT_UNKNOWN;
    const_fold_context_type context_type_ = const_fold_context_type::CFT_VALUE;
    std::string error_msg_{};
    // values
    const_fold_value_holder value_{};
    expr_or_stmt expr_or_stmt_{};
    token *token_{nullptr};
  };
  enum class object_type {
    PRIMITIVE_OR_OBJ,// int, float, bool, string, custom object
    BUILTIN_FUNCTION,// reference to a builtin function
    FUNCTION,        // reference to a function
    CLASS,
    ENUM,
    MODULE,
    MODULE_CLASS,
    MODULE_FUNCTION,
    MODULE_ENUM,
    // --------------------
    // Only used for constant folding
    CONST_FOLD_VALUE,
    // ----
    ERROR_DETECTED,
    UNKNOWN_OBJECT
  };
  struct yk_object {
    yk_object();
    explicit yk_object(const_fold_context *cfc);
    explicit yk_object(yk_datatype *dt);
    explicit yk_object(int i, yk_datatype_pool *pool);
    explicit yk_object(bool b, yk_datatype_pool *pool);
    explicit yk_object(std::string str, yk_datatype_pool *pool);
    explicit yk_object(double dbl, yk_datatype_pool *pool);
    explicit yk_object(float dbl, yk_datatype_pool *pool);
    explicit yk_object(yk_datatype_pool *pool);
    [[nodiscard]] bool is_primitive_or_obj() const;
    [[nodiscard]] bool is_a_function() const;
    std::string string_val_{};
    std::string module_file_{};
    std::string module_name_{};
    bool desugar_rewrite_needed_{false};
    std::string desugar_rewrite_{};
    object_type object_type_{object_type::PRIMITIVE_OR_OBJ};
    yk_datatype *datatype_{nullptr};
    const_fold_context *fold_context_{nullptr};
  };
}// namespace yaksha
#endif
