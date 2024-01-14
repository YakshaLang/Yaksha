// ==============================================================================================
// ╦  ┬┌─┐┌─┐┌┐┌┌─┐┌─┐    Yaksha Programming Language
// ║  ││  ├┤ │││└─┐├┤     is Licensed with GPLv3 + extra terms. Please see below.
// ╩═╝┴└─┘└─┘┘└┘└─┘└─┘
// Note: libs - MIT license, runtime/3rd - various
// ==============================================================================================
// GPLv3:
//
// Yaksha - Programming Language.
// Copyright (C) 2020 - 2023 Bhathiya Perera
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
// string_utils.h
#ifndef STRING_UTILS_H
#define STRING_UTILS_H
#include <cstdint>
#include <exception>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_set>
#include <utf8.h>
#include <vector>
/**
 * String utilities
 */
namespace yaksha::string_utils {
  struct string_error : std::exception {
    explicit string_error(std::string s);
    std::string message_;
  };
  bool is_alpha(utf8::uint32_t c);
  bool is_digit(utf8::uint32_t c);
  bool is_non_zero_digit(utf8::uint32_t c);
  bool is_hex_digit(utf8::uint32_t c);
  bool is_bin_digit(utf8::uint32_t c);
  bool is_oct_digit(utf8::uint32_t c);
  bool allowed_in_hex(utf8::uint32_t p, utf8::uint32_t c);
  bool allowed_in_bin(utf8::uint32_t p, utf8::uint32_t c);
  bool allowed_in_oct(utf8::uint32_t p, utf8::uint32_t c);
  bool allowed_in_decimal(utf8::uint32_t p, utf8::uint32_t c);
  bool allowed_in_string(utf8::uint32_t p, utf8::uint32_t c);
  bool allowed_in_name(utf8::uint32_t p, utf8::uint32_t c);
  bool allowed_in_comment(utf8::uint32_t p, utf8::uint32_t c);
  bool allowed_in_indent(utf8::uint32_t p, utf8::uint32_t c);
  /**
 * Get next 3 characters in octet iterator, 0 is returned if nothing is there
 * @tparam octet_iterator iterator data type
 * @param it current level of iterator
 * @param end end of iterator
 * @return tuple of 3 utf8::uint32_t
 */
  template<typename octet_iterator>
  std::tuple<utf8::uint32_t, utf8::uint32_t,
             utf8::uint32_t> static inline peek3(octet_iterator it,
                                                 octet_iterator end) {
    utf8::uint32_t a = 0;
    utf8::uint32_t b = 0;
    utf8::uint32_t c = 0;
    if (it == end) { return {a, b, c}; }
    a = utf8::next(it, end);
    if (it == end) { return {a, b, c}; }
    b = utf8::next(it, end);
    if (it == end) { return {a, b, c}; }
    c = utf8::next(it, end);
    return {a, b, c};
  }
  /**
 * Get next 4 characters in octet iterator, 0 is returned if nothing is there
 * @tparam octet_iterator iterator data type
 * @param it current level of iterator
 * @param end end of iterator
 * @return tuple of 4 utf8::uint32_t
 */
  template<typename octet_iterator>
  std::tuple<utf8::uint32_t, utf8::uint32_t, utf8::uint32_t,
             utf8::uint32_t> static inline peek4(octet_iterator it,
                                                 octet_iterator end) {
    utf8::uint32_t a = 0;
    utf8::uint32_t b = 0;
    utf8::uint32_t c = 0;
    utf8::uint32_t d = 0;
    if (it == end) { return {a, b, c, d}; }
    a = utf8::next(it, end);
    if (it == end) { return {a, b, c, d}; }
    b = utf8::next(it, end);
    if (it == end) { return {a, b, c, d}; }
    c = utf8::next(it, end);
    if (it == end) { return {a, b, c, d}; }
    d = utf8::next(it, end);
    return {a, b, c, d};
  }
  /**
 * Get next 12 characters in octet iterator, 0 is returned if nothing is there
 * @tparam octet_iterator iterator data type
 * @param it current level of iterator
 * @param end end of iterator
 * @return tuple of 12 utf8::uint32_t
 */
  template<typename octet_iterator>
  std::tuple<utf8::uint32_t, utf8::uint32_t, utf8::uint32_t, utf8::uint32_t,
             utf8::uint32_t, utf8::uint32_t, utf8::uint32_t, utf8::uint32_t,
             utf8::uint32_t, utf8::uint32_t, utf8::uint32_t,
             utf8::uint32_t> static inline peek12(octet_iterator it,
                                                  octet_iterator end) {
    utf8::uint32_t a = 0;
    utf8::uint32_t b = 0;
    utf8::uint32_t c = 0;
    utf8::uint32_t d = 0;
    utf8::uint32_t e = 0;
    utf8::uint32_t f = 0;
    utf8::uint32_t g = 0;
    utf8::uint32_t h = 0;
    utf8::uint32_t i = 0;
    utf8::uint32_t j = 0;
    utf8::uint32_t k = 0;
    utf8::uint32_t l = 0;
    if (it == end) { return {a, b, c, d, e, f, g, h, i, j, k, l}; }
    a = utf8::next(it, end);
    if (it == end) { return {a, b, c, d, e, f, g, h, i, j, k, l}; }
    b = utf8::next(it, end);
    if (it == end) { return {a, b, c, d, e, f, g, h, i, j, k, l}; }
    c = utf8::next(it, end);
    if (it == end) { return {a, b, c, d, e, f, g, h, i, j, k, l}; }
    d = utf8::next(it, end);
    if (it == end) { return {a, b, c, d, e, f, g, h, i, j, k, l}; }
    e = utf8::next(it, end);
    if (it == end) { return {a, b, c, d, e, f, g, h, i, j, k, l}; }
    f = utf8::next(it, end);
    if (it == end) { return {a, b, c, d, e, f, g, h, i, j, k, l}; }
    g = utf8::next(it, end);
    if (it == end) { return {a, b, c, d, e, f, g, h, i, j, k, l}; }
    h = utf8::next(it, end);
    if (it == end) { return {a, b, c, d, e, f, g, h, i, j, k, l}; }
    i = utf8::next(it, end);
    if (it == end) { return {a, b, c, d, e, f, g, h, i, j, k, l}; }
    j = utf8::next(it, end);
    if (it == end) { return {a, b, c, d, e, f, g, h, i, j, k, l}; }
    k = utf8::next(it, end);
    if (it == end) { return {a, b, c, d, e, f, g, h, i, j, k, l}; }
    l = utf8::next(it, end);
    return {a, b, c, d, e, f, g, h, i, j, k, l};
  }
  utf8::uint32_t static inline t12get(
      std::tuple<utf8::uint32_t, utf8::uint32_t, utf8::uint32_t, utf8::uint32_t,
                 utf8::uint32_t, utf8::uint32_t, utf8::uint32_t, utf8::uint32_t,
                 utf8::uint32_t, utf8::uint32_t, utf8::uint32_t, utf8::uint32_t>
          &v,
      int index) {
    switch (index) {
      case 0:
        return std::get<0>(v);
      case 1:
        return std::get<1>(v);
      case 2:
        return std::get<2>(v);
      case 3:
        return std::get<3>(v);
      case 4:
        return std::get<4>(v);
      case 5:
        return std::get<5>(v);
      case 6:
        return std::get<6>(v);
      case 7:
        return std::get<7>(v);
      case 8:
        return std::get<8>(v);
      case 9:
        return std::get<9>(v);
      case 10:
        return std::get<10>(v);
      case 11:
        return std::get<11>(v);
      default:
        return 0;
    }
  }
  /**
 * Consume function that can parse a string until given function is satisfied
 * @tparam octet_iterator iterator data type
 * @param func function to check character
 * @param buf buffer to append
 * @param begin current position in octet_iterator
 * @param end last position in iterator
 * @param allow_end allow stopping at end (not considered an issue)
 * @return <matched size, last character>
 */
  template<typename octet_iterator>
  static inline std::pair<int, utf8::uint32_t>
  consume(const std::function<bool(utf8::uint32_t, std::uint32_t)> &func,
          std::string &buf, octet_iterator &begin, octet_iterator end,
          bool allow_end) {
    octet_iterator begin_copy = begin;
    int size = 0;
    auto buf_inserter = std::back_inserter(buf);
    utf8::uint32_t prev;
    utf8::uint32_t current = 0;
    while (begin_copy != end) {
      prev = current;
      current = utf8::peek_next(begin_copy, end);
      if (func(prev, current)) {
        utf8::append(static_cast<char32_t>(current), buf_inserter);
        utf8::next(begin_copy, end);// move to next character
        size++;
      } else {
        begin = begin_copy;
        return std::make_pair(size, current);
      }
    }
    if (allow_end) {
      begin = begin_copy;
      return std::make_pair(size, current);
    }
    return std::make_pair(-1, 0);
  }
  /**
 * Convert a raw string to an escaped string
 * @param raw_string String with newlines, etc
 * @return escaped string (newlines -> \n)
 */
  std::string escape(const std::string &raw_string);
  std::string escape_binary_string(const std::string &raw_string,
                                   bool escape_question_mark);
  std::string escape(const std::string &raw_string, bool escape_question_mark);
  /**
 * Convert a raw string to an escaped string
 * @param raw_string String with newlines, etc
 * @return escaped string (newlines -> \n)
 */
  std::string html_escape(const std::string &raw_string);
  /**
 * Convert an escaped string Ex: Hello\nWorld to unescaped (\n becomes a new
 * line)
 * @param escaped_string escaped string
 * @return unescaped string
 */
  std::string unescape(const std::string &escaped_string);
  /**
 * Convert a string to a string literal
 * Ex: "Hello\nBanana" -> "\"Hello\\nBanana\""
 * @param raw_string raw string to convert to repr
 * @return repr string
 */
  std::string repr_string(const std::string &raw_string);
}// namespace yaksha::string_utils
#endif
