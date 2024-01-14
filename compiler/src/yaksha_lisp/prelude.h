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
#ifndef YAKSHA_LISP_PRELUDE_H
#define YAKSHA_LISP_PRELUDE_H
#include <string>
const std::string YAKSHA_LISP_PRELUDE = R"<><><><>(

    (def YK_PRELUDE_INCLUDED 1)
    # =========== #
    (defun noop (&x) (ghost nil))
    # =========== #
    # Base functionality
    # =========== #
    # Is this a token?
    (def YK_OBJECT_TYPE "yk_type")
    # What kind of token is this?
    (def YK_KEY_WHAT "yk_what")
    (def YK_TYPE_TOKEN "yk_token")
    (defun yk_get_type (x) (map_get x YK_KEY_TYPE))
    (defun yk_what (x) (map_get x YK_KEY_NODE_TYPE))
    (defun yk_is_token (x) (== (yk_get_type x) YK_TYPE_TOKEN))
    (defun yk_is_expr (x) (== (yk_get_type x) YK_TYPE_EXPR))
    (defun yk_is_stmt (x) (== (yk_get_type x) YK_TYPE_STMT))
    (defun yk_register (type_name_func)
        (if (!= (len type_name_func) 3) (raise_error "yk_register: expected 3 item list"))
        (def macro_type (repr (index type_name_func 0)))
        (def macro_name (repr (index type_name_func 1)))
        (def macro_func (eval (index type_name_func 2)))
        (def target (+ "yaksha#macro#" macro_type "#" macro_name))
        (map_set (parent) target macro_func)
    )
    # =========== #
    #  Constants
    # =========== #
    (def YK_TOKEN_AND 28864)
    (def YK_TOKEN_AND_EQ 28865)
    (def YK_TOKEN_ARROW 28866)
    (def YK_TOKEN_AT 28867)
    (def YK_TOKEN_BA_DEDENT 28868)
    (def YK_TOKEN_BA_INDENT 28869)
    (def YK_TOKEN_COLON 28870)
    (def YK_TOKEN_COMMA 28871)
    (def YK_TOKEN_CURLY_BRACKET_CLOSE 28873)
    (def YK_TOKEN_CURLY_BRACKET_OPEN 28874)
    (def YK_TOKEN_DIV 28875)
    (def YK_TOKEN_DIV_EQ 28876)
    (def YK_TOKEN_DOT 28877)
    (def YK_TOKEN_DOUBLE_NUMBER 28878)
    (def YK_TOKEN_ELLIPSIS 28879)
    (def YK_TOKEN_EQ 28881)
    (def YK_TOKEN_EQ_EQ 28882)
    (def YK_TOKEN_FLOAT_NUMBER 28883)
    (def YK_TOKEN_GREAT 28884)
    (def YK_TOKEN_GREAT_EQ 28885)
    (def YK_TOKEN_INTEGER_BIN 28887)
    (def YK_TOKEN_INTEGER_BIN_16 28888)
    (def YK_TOKEN_INTEGER_BIN_64 28889)
    (def YK_TOKEN_INTEGER_BIN_8 28890)
    (def YK_TOKEN_INTEGER_DECIMAL 28891)
    (def YK_TOKEN_INTEGER_DECIMAL_16 28892)
    (def YK_TOKEN_INTEGER_DECIMAL_64 28893)
    (def YK_TOKEN_INTEGER_DECIMAL_8 28894)
    (def YK_TOKEN_INTEGER_HEX 28895)
    (def YK_TOKEN_INTEGER_HEX_16 28896)
    (def YK_TOKEN_INTEGER_HEX_64 28897)
    (def YK_TOKEN_INTEGER_HEX_8 28898)
    (def YK_TOKEN_INTEGER_OCT 28899)
    (def YK_TOKEN_INTEGER_OCT_16 28900)
    (def YK_TOKEN_INTEGER_OCT_64 28901)
    (def YK_TOKEN_INTEGER_OCT_8 28902)
    (def YK_TOKEN_INT_DIV 28903)
    (def YK_TOKEN_INT_DIV_EQ 28904)
    (def YK_TOKEN_LESS 28905)
    (def YK_TOKEN_LESS_EQ 28906)
    (def YK_TOKEN_MOD 28907)
    (def YK_TOKEN_MOD_EQ 28908)
    (def YK_TOKEN_MUL 28909)
    (def YK_TOKEN_MUL_EQ 28910)
    (def YK_TOKEN_NAME 28911)
    (def YK_TOKEN_NEW_LINE 28912)
    (def YK_TOKEN_NOT_EQ 28913)
    (def YK_TOKEN_NOT_SYMBOL 28914)
    (def YK_TOKEN_OR 28915)
    (def YK_TOKEN_OR_EQ 28916)
    (def YK_TOKEN_PAREN_CLOSE 28917)
    (def YK_TOKEN_PAREN_OPEN 28918)
    (def YK_TOKEN_PLUS 28919)
    (def YK_TOKEN_PLUS_EQ 28920)
    (def YK_TOKEN_POWER 28921)
    (def YK_TOKEN_POWER_EQ 28922)
    (def YK_TOKEN_SEMICOLON 28923)
    (def YK_TOKEN_SHL 28924)
    (def YK_TOKEN_SHL_EQ 28925)
    (def YK_TOKEN_SHR 28926)
    (def YK_TOKEN_SHR_EQ 28927)
    (def YK_TOKEN_SQUARE_BRACKET_CLOSE 28928)
    (def YK_TOKEN_SQUARE_BRACKET_OPEN 28929)
    (def YK_TOKEN_STRING 28930)
    (def YK_TOKEN_SUB 28931)
    (def YK_TOKEN_SUB_EQ 28932)
    (def YK_TOKEN_THREE_QUOTE_STRING 28933)
    (def YK_TOKEN_TILDE 28934)
    (def YK_TOKEN_UINTEGER_BIN 28935)
    (def YK_TOKEN_UINTEGER_BIN_16 28936)
    (def YK_TOKEN_UINTEGER_BIN_64 28937)
    (def YK_TOKEN_UINTEGER_BIN_8 28938)
    (def YK_TOKEN_UINTEGER_DECIMAL 28939)
    (def YK_TOKEN_UINTEGER_DECIMAL_16 28940)
    (def YK_TOKEN_UINTEGER_DECIMAL_64 28941)
    (def YK_TOKEN_UINTEGER_DECIMAL_8 28942)
    (def YK_TOKEN_UINTEGER_HEX 28943)
    (def YK_TOKEN_UINTEGER_HEX_16 28944)
    (def YK_TOKEN_UINTEGER_HEX_64 28945)
    (def YK_TOKEN_UINTEGER_HEX_8 28946)
    (def YK_TOKEN_UINTEGER_OCT 28947)
    (def YK_TOKEN_UINTEGER_OCT_16 28948)
    (def YK_TOKEN_UINTEGER_OCT_64 28949)
    (def YK_TOKEN_UINTEGER_OCT_8 28950)
    (def YK_TOKEN_XOR 28955)
    (def YK_TOKEN_XOR_EQ 28956)
    (def YK_TOKEN_KEYWORD_FALSE 28957)
    (def YK_TOKEN_KEYWORD_NONE 28958)
    (def YK_TOKEN_KEYWORD_TRUE 28959)
    (def YK_TOKEN_KEYWORD_AND 28960)
    (def YK_TOKEN_KEYWORD_AS 28961)
    (def YK_TOKEN_KEYWORD_ASSERT 28962)
    (def YK_TOKEN_KEYWORD_BREAK 28963)
    (def YK_TOKEN_KEYWORD_CCODE 28964)
    (def YK_TOKEN_KEYWORD_CLASS 28965)
    (def YK_TOKEN_KEYWORD_CONTINUE 28966)
    (def YK_TOKEN_KEYWORD_DEF 28967)
    (def YK_TOKEN_KEYWORD_DEFER 28968)
    (def YK_TOKEN_KEYWORD_DEL 28969)
    (def YK_TOKEN_KEYWORD_ELIF 28970)
    (def YK_TOKEN_KEYWORD_ELSE 28971)
    (def YK_TOKEN_KEYWORD_FOR 28972)
    (def YK_TOKEN_KEYWORD_FROM 28973)
    (def YK_TOKEN_KEYWORD_IF 28974)
    (def YK_TOKEN_KEYWORD_IMPORT 28975)
    (def YK_TOKEN_KEYWORD_IN 28976)
    (def YK_TOKEN_KEYWORD_MACROS 28977)
    (def YK_TOKEN_KEYWORD_NOT 28978)
    (def YK_TOKEN_KEYWORD_OR 28979)
    (def YK_TOKEN_KEYWORD_PASS 28980)
    (def YK_TOKEN_KEYWORD_RETURN 28981)
    (def YK_TOKEN_KEYWORD_RUNTIMEFEATURE 28982)
    (def YK_TOKEN_KEYWORD_STRUCT 28983)
    (def YK_TOKEN_KEYWORD_TRY 28984)
    (def YK_TOKEN_KEYWORD_WHILE 28985)
    # =========== #
    #  Generating tokens
    # =========== #
    (defun yk_create_token (token_type value)
        (def m @{})
        (map_set m YK_OBJECT_TYPE YK_TYPE_TOKEN)
        (map_set m YK_KEY_WHAT token_type)
        (map_set m "value" value)
        (map_set m "line" -1)
        (map_set m "pos" -1)
        m)
    (defun yk_assert_token (tok tok_type) (if (!= (map_get tok YK_KEY_WHAT) tok_type) (raise_error "invalid token type")))
    (defun ykt_integer_decimal (value) (yk_create_token YK_TOKEN_INTEGER_DECIMAL value))
    (defun ykt_float (value) (yk_create_token YK_TOKEN_FLOAT_NUMBER value))
    (defun ykt_double (value) (yk_create_token YK_TOKEN_DOUBLE_NUMBER value))
    (defun ykt_string (value) (yk_create_token YK_TOKEN_STRING value))
    (defun ykt_indent () (yk_create_token YK_TOKEN_BA_INDENT " "))
    (defun ykt_dedent () (yk_create_token YK_TOKEN_BA_DEDENT " "))
    (defun ykt_newline () (yk_create_token YK_TOKEN_NEW_LINE "\n"))
    (defun ykt_at () (yk_create_token YK_TOKEN_AT "@"))
    (defun ykt_colon () (yk_create_token YK_TOKEN_COLON ":"))
    (defun ykt_semicolon () (yk_create_token YK_TOKEN_SEMICOLON ";"))
    (defun ykt_paren_open () (yk_create_token YK_TOKEN_PAREN_OPEN "("))
    (defun ykt_paren_close () (yk_create_token YK_TOKEN_PAREN_CLOSE ")"))
    (defun ykt_square_bracket_open () (yk_create_token YK_TOKEN_SQUARE_BRACKET_OPEN "["))
    (defun ykt_square_bracket_close () (yk_create_token YK_TOKEN_SQUARE_BRACKET_CLOSE "]"))
    (defun ykt_curly_bracket_open () (yk_create_token YK_TOKEN_CURLY_BRACKET_OPEN "{"))
    (defun ykt_curly_bracket_close () (yk_create_token YK_TOKEN_CURLY_BRACKET_CLOSE "}"))
    (defun ykt_less () (yk_create_token YK_TOKEN_LESS "<"))
    (defun ykt_eq () (yk_create_token YK_TOKEN_EQ "="))
    (defun ykt_great () (yk_create_token YK_TOKEN_GREAT ">"))
    (defun ykt_or () (yk_create_token YK_TOKEN_OR "|"))
    (defun ykt_plus () (yk_create_token YK_TOKEN_PLUS "+"))
    (defun ykt_sub () (yk_create_token YK_TOKEN_SUB "-"))
    (defun ykt_mul () (yk_create_token YK_TOKEN_MUL "*"))
    (defun ykt_div () (yk_create_token YK_TOKEN_DIV "/"))
    (defun ykt_and () (yk_create_token YK_TOKEN_AND "&"))
    (defun ykt_xor () (yk_create_token YK_TOKEN_XOR "^"))
    (defun ykt_mod () (yk_create_token YK_TOKEN_MOD "%"))
    (defun ykt_int_div () (yk_create_token YK_TOKEN_INT_DIV "//"))
    (defun ykt_power () (yk_create_token YK_TOKEN_POWER "**"))
    (defun ykt_less_eq () (yk_create_token YK_TOKEN_LESS_EQ "<="))
    (defun ykt_eq_eq () (yk_create_token YK_TOKEN_EQ_EQ "=="))
    (defun ykt_great_eq () (yk_create_token YK_TOKEN_GREAT_EQ ">="))
    (defun ykt_or_eq () (yk_create_token YK_TOKEN_OR_EQ "|="))
    (defun ykt_plus_eq () (yk_create_token YK_TOKEN_PLUS_EQ "+="))
    (defun ykt_sub_eq () (yk_create_token YK_TOKEN_SUB_EQ "-="))
    (defun ykt_mul_eq () (yk_create_token YK_TOKEN_MUL_EQ "*="))
    (defun ykt_div_eq () (yk_create_token YK_TOKEN_DIV_EQ "/="))
    (defun ykt_and_eq () (yk_create_token YK_TOKEN_AND_EQ "&="))
    (defun ykt_xor_eq () (yk_create_token YK_TOKEN_XOR_EQ "^="))
    (defun ykt_mod_eq () (yk_create_token YK_TOKEN_MOD_EQ "%="))
    (defun ykt_int_div_eq () (yk_create_token YK_TOKEN_INT_DIV_EQ "//="))
    (defun ykt_power_eq () (yk_create_token YK_TOKEN_POWER_EQ "**="))
    (defun ykt_arrow () (yk_create_token YK_TOKEN_ARROW "->"))
    (defun ykt_ellipsis () (yk_create_token YK_TOKEN_ELLIPSIS "..."))
    (defun ykt_dot () (yk_create_token YK_TOKEN_DOT "."))
    (defun ykt_comma () (yk_create_token YK_TOKEN_COMMA ","))
    (defun ykt_shl () (yk_create_token YK_TOKEN_SHL "<<"))
    (defun ykt_shr () (yk_create_token YK_TOKEN_SHR ">>"))
    (defun ykt_shl_eq () (yk_create_token YK_TOKEN_SHL_EQ "<<="))
    (defun ykt_shr_eq () (yk_create_token YK_TOKEN_SHR_EQ ">>="))
    (defun ykt_not_eq () (yk_create_token YK_TOKEN_NOT_EQ "!="))
    (defun ykt_tilde () (yk_create_token YK_TOKEN_TILDE "~"))
    (defun ykt_not_symbol () (yk_create_token YK_TOKEN_NOT_SYMBOL "!"))
    (defun ykt_keyword_false () (yk_create_token YK_TOKEN_KEYWORD_FALSE "False"))
    (defun ykt_keyword_none () (yk_create_token YK_TOKEN_KEYWORD_NONE "None"))
    (defun ykt_keyword_true () (yk_create_token YK_TOKEN_KEYWORD_TRUE "True"))
    (defun ykt_keyword_and () (yk_create_token YK_TOKEN_KEYWORD_AND "and"))
    (defun ykt_keyword_as () (yk_create_token YK_TOKEN_KEYWORD_AS "as"))
    (defun ykt_keyword_assert () (yk_create_token YK_TOKEN_KEYWORD_ASSERT "assert"))
    (defun ykt_keyword_break () (yk_create_token YK_TOKEN_KEYWORD_BREAK "break"))
    (defun ykt_keyword_ccode () (yk_create_token YK_TOKEN_KEYWORD_CCODE "ccode"))
    (defun ykt_keyword_class () (yk_create_token YK_TOKEN_KEYWORD_CLASS "class"))
    (defun ykt_keyword_continue () (yk_create_token YK_TOKEN_KEYWORD_CONTINUE "continue"))
    (defun ykt_keyword_def () (yk_create_token YK_TOKEN_KEYWORD_DEF "def"))
    (defun ykt_keyword_defer () (yk_create_token YK_TOKEN_KEYWORD_DEFER "defer"))
    (defun ykt_keyword_del () (yk_create_token YK_TOKEN_KEYWORD_DEL "del"))
    (defun ykt_keyword_elif () (yk_create_token YK_TOKEN_KEYWORD_ELIF "elif"))
    (defun ykt_keyword_else () (yk_create_token YK_TOKEN_KEYWORD_ELSE "else"))
    (defun ykt_keyword_for () (yk_create_token YK_TOKEN_KEYWORD_FOR "for"))
    (defun ykt_keyword_from () (yk_create_token YK_TOKEN_KEYWORD_FROM "from"))
    (defun ykt_keyword_if () (yk_create_token YK_TOKEN_KEYWORD_IF "if"))
    (defun ykt_keyword_import () (yk_create_token YK_TOKEN_KEYWORD_IMPORT "import"))
    (defun ykt_keyword_in () (yk_create_token YK_TOKEN_KEYWORD_IN "in"))
    (defun ykt_keyword_macros () (yk_create_token YK_TOKEN_KEYWORD_MACROS "macros"))
    (defun ykt_keyword_not () (yk_create_token YK_TOKEN_KEYWORD_NOT "not"))
    (defun ykt_keyword_or () (yk_create_token YK_TOKEN_KEYWORD_OR "or"))
    (defun ykt_keyword_pass () (yk_create_token YK_TOKEN_KEYWORD_PASS "pass"))
    (defun ykt_keyword_return () (yk_create_token YK_TOKEN_KEYWORD_RETURN "return"))
    (defun ykt_keyword_runtimefeature () (yk_create_token YK_TOKEN_KEYWORD_RUNTIMEFEATURE "runtimefeature"))
    (defun ykt_keyword_struct () (yk_create_token YK_TOKEN_KEYWORD_STRUCT "struct"))
    (defun ykt_keyword_try () (yk_create_token YK_TOKEN_KEYWORD_TRY "try"))
    (defun ykt_keyword_while () (yk_create_token YK_TOKEN_KEYWORD_WHILE "while"))
    (system_enable_gc)
    (system_lock_root_scope)

)<><><><>";
#endif
