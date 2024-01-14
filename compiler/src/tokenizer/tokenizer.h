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
// tokenizer.h
#ifndef TOKENIZER_H
#define TOKENIZER_H
#include "tokenizer/string_utils.h"
#include "tokenizer/token.h"
#include "utilities/gc_pool.h"
#include <fstream>
#include <functional>
#include <iostream>
#include <unordered_set>
#include <utf8.h>
#include <vector>
namespace yaksha {
  template<typename octet_iterator>
  static std::pair<int, utf8::uint32_t>
  consume_string(std::string &buf, octet_iterator &begin, octet_iterator end);
  /**
 * Consume a triple quoted string
 * @tparam octet_iterator iterator data type
 * @param buf buffer to write the string to
 * @param begin current position in iterator
 * @param end last position in iterator
 * @return <matched size, last character, line_count>
 */
  template<typename octet_iterator>
  std::tuple<int, utf8::uint32_t, int> consume_triple_str(std::string &buf,
                                                          octet_iterator &begin,
                                                          octet_iterator end);
  /**
 * Consume a number (decimal integer or a float)
 * Hex, Oct, Bin is handled separately
 * @tparam octet_iterator iterator data type
 * @param buf buffer to write the string to
 * @param begin current position in iterator
 * @param end last position in iterator
 * @return <matched size, last character,
 *      token_type::INTEGER_DECIMAL or token_type::FLOAT_NUMBER>
 */
  template<typename octet_iterator>
  std::tuple<int, utf8::uint32_t, token_type>
  consume_number(std::string &buf, octet_iterator &begin, octet_iterator end);
  /**
 * Tokenize a string to vector of tokens
 */
  struct tokenizer {
    explicit tokenizer(std::string file, std::string data,
                       gc_pool<token> *token_pool);
    std::vector<token *> tokens_;
    std::vector<parsing_error> errors_;
    /**
   * Parse given string to a list of tokens accessible in tokens_
   * parsing errors will be present in errors_ field.
   */
    void tokenize();
    static bool is_integer_token(token_type token_type_value);
    token *c_token(std::string file, int line, int pos, std::string token_buf,
                   token_type token_type_val);

private:
    std::string file_;
    std::string data_;
    token_type specalize_integer_token(token_type token_type_value,
                                       int integer_size_value);
    static bool is_unknown_integer_token(token_type token_type_value);
    void handle_error(const parsing_error &err);
    void tokenize_actual();
    std::pair<int, bool> consider_integer_suffix(uint32_t current,
                                                 uint32_t next,
                                                 uint32_t after_next);
    gc_pool<token> *token_pool_{nullptr};
  };
}// namespace yaksha
#endif
