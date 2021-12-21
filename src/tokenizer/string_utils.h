// string_utils.h
#ifndef STRING_UTILS_H
#define STRING_UTILS_H
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
  consume(const std::function<bool(utf8::uint32_t, uint32_t)> &func,
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
