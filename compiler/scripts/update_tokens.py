# ==============================================================================================
# ╦  ┬┌─┐┌─┐┌┐┌┌─┐┌─┐    Yaksha Programming Language
# ║  ││  ├┤ │││└─┐├┤     is Licensed with GPLv3 + extra terms. Please see below.
# ╩═╝┴└─┘└─┘┘└┘└─┘└─┘
# Note: libs - MIT license, runtime/3rd - various
# ==============================================================================================
# GPLv3:
#
# Yaksha - Programming Language.
# Copyright (C) 2020 - 2024 Bhathiya Perera
#
# This program is free software: you can redistribute it and/or modify it under the terms
# of the GNU General Public License as published by the Free Software Foundation,
# either version 3 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
# or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with this program.
# If not, see https://www.gnu.org/licenses/.
#
# ==============================================================================================
# Additional Terms:
#
# Please note that any commercial use of the programming language's compiler source code
# (everything except compiler/runtime, compiler/libs and compiler/3rd) require a written agreement
# with author of the language (Bhathiya Perera).
#
# If you are using it for an open source project, please give credits.
# Your own project must use GPLv3 license with these additional terms.
#
# You may use programs written in Yaksha/YakshaLisp for any legal purpose
# (commercial, open-source, closed-source, etc) as long as it agrees
# to the licenses of linked runtime libraries (see compiler/runtime/README.md).
#
# ==============================================================================================
# !/usr/bin/env python
"""
Update token.h
Generate utility functions and enums for different types of tokens
Keyword token related functions are generated as well
Template also contains - `token` & `parsing_error` data structures.
"""
import os.path

K_TOKENS_LIST = "$TOKENS$"
K_TOKEN_TO_STR = "$TOKEN_TO_STR$"
K_STR_TO_TOKEN = "$STR_TO_TOKEN$"
K_KW_TO_TOKEN = "$KW_TO_TOKEN$"
K_KW_FUNC_TOKEN = "$KW_FUNC$"
K_NUM_TO_TOKEN = "$KW_NUM_TO_TOKEN$"
K_TOKEN_TO_NUM = "$KW_TOKEN_TO_NUM$"
UNKNOWN = "TK_UNKNOWN_TOKEN_DETECTED"
RESERVED = ["await", "except", "raise", "finally", "lambda", "nonlocal", "global", "with", "async", "yield", "in", "is"]
KEYWORDS = sorted(["False", "else", "import", "pass",
                   "None", "break",
                   "True", "class", "return",
                   "and", "continue", "for", "try",
                   "as", "def", "from", "while",
                   "assert", "del", "not",
                   "elif", "if", "or", "defer",
                   "ccode", "runtimefeature", "in",
                   "struct", "macros", "directive",
                   "enum", "decl"])
TOKENS = sorted([
    "NAME", "AT", "DOUBLE_NUMBER", "FLOAT_NUMBER", "INDENT", "BA_INDENT", "BA_DEDENT", "NEW_LINE", "COLON", "SEMICOLON",
    "COMMENT",
    "THREE_QUOTE_STRING", "STRING", "PAREN_OPEN",
    "PAREN_CLOSE", "SQUARE_BRACKET_OPEN", "SQUARE_BRACKET_CLOSE", "CURLY_BRACKET_OPEN", "CURLY_BRACKET_CLOSE", "LESS",
    "EQ", "GREAT", "OR", "PLUS", "SUB", "MUL", "DIV", "AND", "XOR", "MOD", "INT_DIV", "POWER", "LESS_EQ", "EQ_EQ",
    "GREAT_EQ", "OR_EQ", "PLUS_EQ", "SUB_EQ", "MUL_EQ", "DIV_EQ", "AND_EQ", "XOR_EQ", "MOD_EQ", "INT_DIV_EQ",
    "POWER_EQ", "ARROW", "ELLIPSIS", "DOT", "COMMA", "SHL", "SHR", "SHL_EQ", "SHR_EQ", "NOT_EQ", "TILDE", "END_OF_FILE",
    "NOT_SYMBOL",
    # i8
    "INTEGER_DECIMAL_8", "INTEGER_OCT_8", "INTEGER_HEX_8", "INTEGER_BIN_8",
    # i16
    "INTEGER_DECIMAL_16", "INTEGER_OCT_16", "INTEGER_HEX_16", "INTEGER_BIN_16",
    # i32 or int
    "INTEGER_DECIMAL", "INTEGER_OCT", "INTEGER_HEX", "INTEGER_BIN",
    # i64
    "INTEGER_DECIMAL_64", "INTEGER_OCT_64", "INTEGER_HEX_64", "INTEGER_BIN_64",
    # u8
    "UINTEGER_DECIMAL_8", "UINTEGER_OCT_8", "UINTEGER_HEX_8", "UINTEGER_BIN_8",
    # u16
    "UINTEGER_DECIMAL_16", "UINTEGER_OCT_16", "UINTEGER_HEX_16", "UINTEGER_BIN_16",
    # u32
    "UINTEGER_DECIMAL", "UINTEGER_OCT", "UINTEGER_HEX", "UINTEGER_BIN",
    # u64
    "UINTEGER_DECIMAL_64", "UINTEGER_OCT_64", "UINTEGER_HEX_64", "UINTEGER_BIN_64",
    # unknown integer?
    "UNKNOWN_DECIMAL", "UNKNOWN_OCT", "UNKNOWN_HEX", "UNKNOWN_BIN",
]) + ["KEYWORD_" + x.upper() for x in KEYWORDS]
TEMP_TOKENS = ["INDENT", "UNKNOWN_DECIMAL", "UNKNOWN_OCT", "UNKNOWN_HEX",
               "UNKNOWN_BIN", "COMMENT", "END_OF_FILE"]
NOT_VALIDATED_SIMPLY = set(TEMP_TOKENS + ["NAME", "BA_INDENT", "BA_DEDENT", "STRING", "THREE_QUOTE_STRING",
                                          "INTEGER_DECIMAL_8", "INTEGER_OCT_8",
                                          "INTEGER_HEX_8", "INTEGER_BIN_8",
                                          "INTEGER_DECIMAL_16", "INTEGER_OCT_16", "INTEGER_HEX_16", "INTEGER_BIN_16",
                                          "INTEGER_DECIMAL", "INTEGER_OCT", "INTEGER_HEX", "INTEGER_BIN",
                                          "INTEGER_DECIMAL_64", "INTEGER_OCT_64", "INTEGER_HEX_64", "INTEGER_BIN_64",
                                          "UINTEGER_DECIMAL_8", "UINTEGER_OCT_8", "UINTEGER_HEX_8", "UINTEGER_BIN_8",
                                          "UINTEGER_DECIMAL_16", "UINTEGER_OCT_16", "UINTEGER_HEX_16",
                                          "UINTEGER_BIN_16",
                                          "UINTEGER_DECIMAL", "UINTEGER_OCT", "UINTEGER_HEX", "UINTEGER_BIN",
                                          "UINTEGER_DECIMAL_64", "UINTEGER_OCT_64", "UINTEGER_HEX_64",
                                          "UINTEGER_BIN_64",
                                          "DOUBLE_NUMBER", "FLOAT_NUMBER"])
SIMPLE_VALIDATIONS = {
    "AT": "@",
    "COLON": ":",
    "SEMICOLON": ";",
    "PAREN_OPEN": "(",
    "PAREN_CLOSE": ")",
    "SQUARE_BRACKET_OPEN": "[",
    "SQUARE_BRACKET_CLOSE": "]",
    "CURLY_BRACKET_OPEN": "{",
    "CURLY_BRACKET_CLOSE": "}",
    "LESS": "<",
    "EQ": "=",
    "GREAT": ">",
    "OR": "|",
    "PLUS": "+",
    "SUB": "-",
    "MUL": "*",
    "DIV": "/",
    "AND": "&",
    "XOR": "^",
    "MOD": "%",
    "INT_DIV": "//",
    "POWER": "**",
    "LESS_EQ": "<=",
    "EQ_EQ": "==",
    "GREAT_EQ": ">=",
    "OR_EQ": "|=",
    "PLUS_EQ": "+=",
    "SUB_EQ": "-=",
    "MUL_EQ": "*=",
    "DIV_EQ": "/=",
    "AND_EQ": "&=",
    "XOR_EQ": "^=",
    "MOD_EQ": "%=",
    "INT_DIV_EQ": "//=",
    "POWER_EQ": "**=",
    "ARROW": "->",
    "ELLIPSIS": "...",
    "DOT": ".",
    "COMMA": ",",
    "SHL": "<<",
    "SHR": ">>",
    "SHL_EQ": "<<=",
    "SHR_EQ": ">>=",
    "NOT_EQ": "!=",
    "TILDE": "~",
    "NOT_SYMBOL": "!",
}
SIMPLE_VALIDATIONS.update({"KEYWORD_" + x.upper(): x for x in KEYWORDS})

TEMPLATE = r"""
// token.h
// generated by update_tokens.py
#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <filesystem>
#include <vector>
namespace yaksha {
/**
 * Most simple types of tokens we can match with tokenizing
 */
enum class token_type {
$TOKENS$
};
static inline bool is_keyword(const token_type &t) {
$KW_FUNC$
}
/**
 * Convert a token to a string
 * @param t token type
 * @return token type as a std::string
 */
static inline std::string token_to_str(const token_type &t) {
$TOKEN_TO_STR$
}
static inline token_type str_to_token(const std::string &t) {
$STR_TO_TOKEN$
}
static inline token_type str_to_keyword(const std::string &t) {
$KW_TO_TOKEN$
}
static inline token_type numeric_id_to_token(const int64_t n) {
$KW_NUM_TO_TOKEN$
}
static inline int64_t token_to_numeric_id(const token_type &t) {
$KW_TOKEN_TO_NUM$
}
static inline bool is_number_token(const token_type &t) {
return ($KW_IS_NUMTOK$);
}
static inline bool is_valid_complex(const std::string& value, const token_type &t) {
if (t == token_type::STRING || t == token_type::THREE_QUOTE_STRING ||
        t == token_type::COMMENT || t == token_type::NEW_LINE ||
        t == token_type::END_OF_FILE || t == token_type::BA_INDENT ||
        t == token_type::BA_DEDENT || t == token_type::INDENT) {
      return true;
    }
    if (t == token_type::DOUBLE_NUMBER) {
      try {
        std::stod(value);
        return true;
      } catch (...) { return false; }
    }
    if (t == token_type::FLOAT_NUMBER) {
      if (value.size() > 2 &&
          (value[value.size() - 1] == 'f' || value[value.size() - 1] == 'F')) {
        for (size_t i = 0; i < value.size() - 1; i++) {
          if (value[i] < '0' || value[i] > '9') {
            std::string new_value = value.substr(0, value.size() - 1);
            return is_valid_complex(new_value, token_type::DOUBLE_NUMBER);
          }
        }
        return true;// This is a short float - 1f, 2f, etc
      }
      return false;
    }
    if (t == token_type::INTEGER_BIN || t == token_type::INTEGER_BIN_8 ||
        t == token_type::INTEGER_BIN_16 || t == token_type::INTEGER_BIN_64 ||
        t == token_type::UINTEGER_BIN || t == token_type::UINTEGER_BIN_8 ||
        t == token_type::UINTEGER_BIN_16 || t == token_type::UINTEGER_BIN_64) {
      if (value.size() < 3) return false;
      if (value[0] != '0' || (value[1] != 'b' && value[1] != 'B')) return false;
      for (size_t i = 2; i < value.size(); i++) {
        if (value[i] != '0' && value[i] != '1') return false;
      }
      return true;
    }
    if (t == token_type::INTEGER_DECIMAL ||
        t == token_type::INTEGER_DECIMAL_8 ||
        t == token_type::INTEGER_DECIMAL_16 ||
        t == token_type::INTEGER_DECIMAL_64 || 
        t == token_type::UINTEGER_DECIMAL ||
        t == token_type::UINTEGER_DECIMAL_8 ||
        t == token_type::UINTEGER_DECIMAL_16 ||
        t == token_type::UINTEGER_DECIMAL_64) {
      if (value.empty()) return false;
      if (value == "0") return true;
      if (value[0] < '1' || value[0] > '9') return false;
      for (size_t i = 1; i < value.size(); i++) {
        if (value[i] < '0' || value[i] > '9') return false;
      }
      return true;
    }
    if (t == token_type::INTEGER_HEX || t == token_type::INTEGER_HEX_8 ||
        t == token_type::INTEGER_HEX_16 || t == token_type::INTEGER_HEX_64 ||
        t == token_type::UINTEGER_HEX || t == token_type::UINTEGER_HEX_8 ||
        t == token_type::UINTEGER_HEX_16 || t == token_type::UINTEGER_HEX_64) {
      if (value.size() < 3) return false;
      if (value[0] != '0' || (value[1] != 'x' && value[1] != 'X')) return false;
      for (size_t i = 2; i < value.size(); i++) {
        if ((value[i] < '0' || value[i] > '9') &&
            (value[i] < 'a' || value[i] > 'f') &&
            (value[i] < 'A' || value[i] > 'F'))
          return false;
      }
      return true;
    }
    if (t == token_type::INTEGER_OCT || t == token_type::INTEGER_OCT_8 ||
        t == token_type::INTEGER_OCT_16 || t == token_type::INTEGER_OCT_64 ||
        t == token_type::UINTEGER_OCT || t == token_type::UINTEGER_OCT_8 ||
        t == token_type::UINTEGER_OCT_16 || t == token_type::UINTEGER_OCT_64) {
      if (value.size() < 3) return false;
      if (value[0] != '0' || (value[1] != 'o' && value[1] != 'O')) return false;
      for (size_t i = 2; i < value.size(); i++) {
        if (value[i] < '0' || value[i] > '7') return false;
      }
      return true;
    }
    if (t == token_type::NAME) {
      if (value.empty()) return false;
      std::string new_value = value;
      // Can start with a $ for gensym
      if (value[0] == '$') new_value = value.substr(1);
      if (new_value.empty()) return false;
      if (new_value[0] != '_' && (new_value[0] < 'a' || new_value[0] > 'z') &&
          (new_value[0] < 'A' || new_value[0] > 'Z'))
        return false;
      for (size_t i = 1; i < new_value.size(); i++) {
        if (new_value[i] != '_' && (new_value[i] < 'a' || new_value[i] > 'z') &&
            (new_value[i] < 'A' || new_value[i] > 'Z') &&
            (new_value[i] < '0' || new_value[i] > '9'))
          return false;
      }
      return true;
    }
    return false;
}
static inline bool is_valid(const std::string& value, const token_type &t) {
$SIMPLE_VALIDATIONS$
    return is_valid_complex(value, t);
}
/**
 * Single token
 */
struct token {
  std::string file_;  // filename
  int line_;          // line in file
  int pos_;           // position in line
  std::string token_;
  token_type type_;   // type of the token
  std::string original_;
  // For gc_pool
  token *next_{nullptr};
  token *prev_{nullptr};
  std::uint8_t mark_{0};
  void clean_state();
};
/**
 * Content of an error message
 */
struct parsing_error  : public std::exception {
  std::string message_; // content of the line this error occurred
  token tok_;
  bool token_set_{};
  parsing_error(std::string message, token* at);
  parsing_error(std::string message, std::string file, int line, int pos);
};
struct parser;
struct tokenizer;
struct block_analyzer;
struct type_checker;
struct def_class_visitor;
struct file_data {
  parser* parser_{};
  tokenizer* tokenizer_{};
  block_analyzer* block_analyzer_{};
  type_checker* type_checker_{nullptr};
  def_class_visitor* dsv_{nullptr};
};
  enum class scanning_step {
    /** Step 0) At the begining when we scan main, or find import */
    NOTHING_DONE = 0,
    /** Step 1) Scan macro soup */
    SOUP_SCAN_DONE = 1,
    /** Step 2) Create an environment for the file's macro's to be excuted */
    ENV_CREATED = 2,
    /** Step 3) Execute macros!{} */
    MACROS_SETUP_DONE = 3,
    /** Step 4) Expand dsl!{} + parse again */
    MACROS_EXPANDED = 4,
    /** Step 5) Parse the file */
    PARSE_DONE = 5,
    /** Step 7) If all above are done, and no imports are left */
    ALL_PARSING_SUCCESSFUL = 7,
    /** If any of above fails */
    FAILURE = -999,
  };
  struct file_info {
    std::filesystem::path filepath_;
    std::string prefix_;
    file_data *data_{nullptr};
    scanning_step step_{scanning_step::NOTHING_DONE};
  };
} // namespace yaksha
#endif
""".strip()
STR_TOK_TEMPLATE = r"""
  if (t == "$K$")
    return token_type::$K$;
""".strip()
TOK_STR_TEMPLATE = r"""
  if (t == token_type::$K$)
    return "$K$";
""".strip()
KW_TO_TOKEN = r"""
  if (t == "$K$")
    return token_type::KEYWORD_$KU$;
""".strip()
NUMBER_TO_TOKEN = r"""
  if (n == $C$)
    return token_type::$KU$;
""".strip()
TOKEN_TO_NUMBER = r"""
  if (t == token_type::$KU$)
    return $C$;
""".strip()
KW_FUNC_TEMPLATE = r"""
bool is_kw = false;
switch (t) {
$KW_CASES$
is_kw = true;
default:
break;
}
return is_kw;
""".strip()
KW_CASE_TEMPLATE = r"""
    case token_type::KEYWORD_$KU$: 
""".strip()
PRELUDE_TEMPLATE = r"""    (def YK_TOKEN_$KU$ $C$)"""


def counter(start):
    counter_ = start

    def inner():
        nonlocal counter_
        counter_ += 1
        return counter_

    return inner


if __name__ == "__main__":
    os.chdir(os.path.dirname(os.path.dirname(__file__)))
    c = counter(0x70BF)
    tc = {x: c() for x in TOKENS}
    with open(os.path.join(".", "src", "tokenizer", "token.h"), "w+") as h:
        token_list = ",\n".join(["  " + x for x in TOKENS]) + ",\n  " + UNKNOWN
        str_to_tok = "\n".join(["  " + STR_TOK_TEMPLATE.replace("$K$", x) for x in TOKENS]) \
                     + "\n  return token_type::" + UNKNOWN + ";"
        kw_to_tok = "\n".join(["  " + KW_TO_TOKEN.replace("$K$", x).replace("$KU$", x.upper()) for x in KEYWORDS]) \
                    + "\n  return token_type::" + UNKNOWN + ";"
        num_to_tok = "\n".join(
            [NUMBER_TO_TOKEN.replace("$KU$", token).replace("$C$", str(count)) for token, count in tc.items() if
             token not in TEMP_TOKENS]) \
                     + "\n  return token_type::" + UNKNOWN + ";"
        tok_to_num = "\n".join(
            [TOKEN_TO_NUMBER.replace("$KU$", token).replace("$C$", str(count)) for token, count in tc.items() if
             token not in TEMP_TOKENS]) \
                     + "\n  return 0;"
        kw_cases = "\n".join(["  " + KW_CASE_TEMPLATE.replace("$K$", x).replace("$KU$", x.upper()) for x in KEYWORDS])
        kw_func = KW_FUNC_TEMPLATE.replace("$KW_CASES$", kw_cases)
        tok_to_str = "\n".join(["  " + TOK_STR_TEMPLATE.replace("$K$", x) for x in TOKENS]) \
                     + "\n  return \"" + UNKNOWN + "\";"
        number_tokens = [x for x in TOKENS if "INTEGER" in x or "NUMBER" in x]
        simple_validations = "\n".join(
            ["  if (t == token_type::" + tt + ")\n    return (value == \"" + vv + "\"); " for tt, vv in
             SIMPLE_VALIDATIONS.items()])
        code = TEMPLATE.replace(K_TOKENS_LIST, token_list) \
            .replace(K_TOKEN_TO_STR, tok_to_str).replace(K_STR_TO_TOKEN, str_to_tok) \
            .replace(K_KW_TO_TOKEN, kw_to_tok) \
            .replace(K_KW_FUNC_TOKEN, kw_func) \
            .replace(K_NUM_TO_TOKEN, num_to_tok) \
            .replace(K_TOKEN_TO_NUM, tok_to_num) \
            .replace("$KW_IS_NUMTOK$", " || ".join(["t == token_type::" + x for x in number_tokens])) \
            .replace("$SIMPLE_VALIDATIONS$", simple_validations)
        h.write(code)

    with open(os.path.join(".", "src", "yaksha_lisp", "prelude_tokens.yaka"), "w+") as f:
        f.write("\n".join(
            [PRELUDE_TEMPLATE.replace("$KU$", token).replace("$C$", str(count)) for token, count in tc.items() if
             token not in TEMP_TOKENS]))

    with open(os.path.join(".", "src", "yaksha_lisp", "prelude_token_gen.yaka"), "w+") as f:
        f.write("\n".join(["    (defun ykt_$n$ () (yk_create_token YK_TOKEN_$N$ \"$V$\"))"
                          .replace("$N$", nn)
                          .replace("$n$", nn.lower()).replace("$V$", vv) for nn, vv in SIMPLE_VALIDATIONS.items()]))
