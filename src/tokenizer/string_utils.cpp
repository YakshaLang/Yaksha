// string_utils.cpp
#include "tokenizer/string_utils.h"
const auto STR_ESCAPE_CHAR = '\\';
std::string yaksha::string_utils::unescape(const std::string &escaped_string) {
  // TODO \xh..., \uxxxx, \Uxxxxxxxx -- this is a must before any public release
  std::string buf_{};
  auto buf = std::back_inserter(buf_);
  auto iterator = escaped_string.begin();
  auto end = escaped_string.end();
  while (iterator != end) {
    auto characters = peek3(iterator, end);
    auto current = std::get<0>(characters);
    auto next = std::get<1>(characters);
    auto after_next = std::get<2>(characters);
    if (current == STR_ESCAPE_CHAR) {
      if (next == '\n') {
        // ignored
      } else if (next == '\r' &&// windows line format, ignored
                 after_next == '\n') {
        utf8::next(iterator, end);
      } else if (next == STR_ESCAPE_CHAR || next == '\'' || next == '\"') {
        utf8::append(static_cast<char32_t>(next), buf);
      } else if (next == 'a') {
        utf8::append(static_cast<char32_t>('\a'), buf);
      } else if (next == 'b') {
        utf8::append(static_cast<char32_t>('\b'), buf);
      } else if (next == 'f') {
        utf8::append(static_cast<char32_t>('\f'), buf);
      } else if (next == 'n') {
        utf8::append(static_cast<char32_t>('\n'), buf);
      } else if (next == 'r') {
        utf8::append(static_cast<char32_t>('\r'), buf);
      } else if (next == 't') {
        utf8::append(static_cast<char32_t>('\t'), buf);
      } else if (next == 'v') {
        utf8::append(static_cast<char32_t>('\v'), buf);
      } else if (is_oct_digit(next)) {
        int skip = 2;// skip \o
        std::string octal{};
        octal += static_cast<char>(next);
        if (is_oct_digit(after_next)) {
          skip++;// skip \oo
          octal += static_cast<char>(after_next);
          utf8::next(iterator, end);// skipped one
          auto oct_chars = peek3(iterator, end);
          if (is_oct_digit(std::get<2>(oct_chars))) {
            // just skip 3 to skip \ooo (1 skipped already)
            octal += static_cast<char>(std::get<2>(oct_chars));
          } else {
            skip--;// just skip 2 to skip \oo (1 skipped already)
          }
        }
        for (int i = 0; i < skip; i++) {
          if (iterator == end) { break; }
          utf8::next(iterator, end);
        }
        unsigned long long oct_num = std::stoull(octal, nullptr, 8);
        utf8::append(static_cast<char32_t>(oct_num), buf);
        // /ooo
        continue;
      }
      utf8::next(iterator, end);
    } else {
      utf8::append(static_cast<char32_t>(current), buf);
    }
    utf8::next(iterator, end);
  }
  return buf_;
}
std::string yaksha::string_utils::escape(const std::string &raw_string) {
  std::string buf_{};
  auto buf = std::back_inserter(buf_);
  auto iterator = raw_string.begin();
  auto end = raw_string.end();
  while (iterator != end) {
    auto current = utf8::peek_next(iterator, end);
    if (current == STR_ESCAPE_CHAR || current == '\'' || current == '\"') {
      utf8::append(static_cast<char32_t>(STR_ESCAPE_CHAR), buf);
      utf8::append(static_cast<char32_t>(current), buf);
    } else if (current == '\a') {
      utf8::append(static_cast<char32_t>(STR_ESCAPE_CHAR), buf);
      utf8::append(static_cast<char32_t>('a'), buf);
    } else if (current == '\b') {
      utf8::append(static_cast<char32_t>(STR_ESCAPE_CHAR), buf);
      utf8::append(static_cast<char32_t>('b'), buf);
    } else if (current == '\f') {
      utf8::append(static_cast<char32_t>(STR_ESCAPE_CHAR), buf);
      utf8::append(static_cast<char32_t>('f'), buf);
    } else if (current == '\n') {
      utf8::append(static_cast<char32_t>(STR_ESCAPE_CHAR), buf);
      utf8::append(static_cast<char32_t>('n'), buf);
    } else if (current == '\r') {
      utf8::append(static_cast<char32_t>(STR_ESCAPE_CHAR), buf);
      utf8::append(static_cast<char32_t>('r'), buf);
    } else if (current == '\t') {
      utf8::append(static_cast<char32_t>(STR_ESCAPE_CHAR), buf);
      utf8::append(static_cast<char32_t>('t'), buf);
    } else if (current == '\v') {
      utf8::append(static_cast<char32_t>(STR_ESCAPE_CHAR), buf);
      utf8::append(static_cast<char32_t>('v'), buf);
    } else if (current == 0) {
      utf8::append(static_cast<char32_t>(STR_ESCAPE_CHAR), buf);
      utf8::append(static_cast<char32_t>('0'), buf);
    } else {
      utf8::append(static_cast<char32_t>(current), buf);
    }
    utf8::next(iterator, end);
  }
  return buf_;
}
std::string yaksha::string_utils::repr_string(const std::string &raw_string) {
  return '"' + escape(raw_string) + '"';
}
bool yaksha::string_utils::is_alpha(utf8::uint32_t c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}
bool yaksha::string_utils::is_digit(utf8::uint32_t c) {
  return (c >= '0' && c <= '9');
}
bool yaksha::string_utils::is_non_zero_digit(utf8::uint32_t c) {
  return (c >= '1' && c <= '9');
}
bool yaksha::string_utils::is_hex_digit(utf8::uint32_t c) {
  return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') ||
          (c >= 'A' && c <= 'F'));
}
bool yaksha::string_utils::is_bin_digit(utf8::uint32_t c) {
  return c == '0' || c == '1';
}
bool yaksha::string_utils::is_oct_digit(utf8::uint32_t c) {
  return (c >= '0' && c <= '7');
}
bool yaksha::string_utils::allowed_in_hex(utf8::uint32_t p, utf8::uint32_t c) {
  return is_hex_digit(c);
}
bool yaksha::string_utils::allowed_in_bin(utf8::uint32_t p, utf8::uint32_t c) {
  return is_bin_digit(c);
}
bool yaksha::string_utils::allowed_in_oct(utf8::uint32_t p, utf8::uint32_t c) {
  return is_oct_digit(c);
}
bool yaksha::string_utils::allowed_in_decimal(utf8::uint32_t p,
                                              utf8::uint32_t c) {
  return is_digit(c);
}
bool yaksha::string_utils::allowed_in_string(utf8::uint32_t p,
                                             utf8::uint32_t c) {
  if (c == '\r' || c == '\n') {
    return false;// new line characters are not allowed in string
  }
  return (c != '"' || p == '\\');
}
bool yaksha::string_utils::allowed_in_name(utf8::uint32_t p, utf8::uint32_t c) {
  return (is_alpha(c) || is_digit(c));
}
bool yaksha::string_utils::allowed_in_comment(utf8::uint32_t p,
                                              utf8::uint32_t c) {
  return !(c == '\r' || c == '\n');
}
bool yaksha::string_utils::allowed_in_indent(utf8::uint32_t p,
                                             utf8::uint32_t c) {
  return c == ' ' || c == '\t';
}
std::string yaksha::string_utils::html_escape(const std::string &raw_string) {
  std::string buf_{};
  auto buf = std::back_inserter(buf_);
  auto iterator = raw_string.begin();
  auto end = raw_string.end();
  while (iterator != end) {
    auto current = utf8::peek_next(iterator, end);
    if (current == '&') {
      buf_.append("&amp;");
    } else if (current == '\"') {
      buf_.append("&quot;");
    } else if (current == '\'') {
      buf_.append("&apos;");
    } else if (current == '<') {
      buf_.append("&lt;");
    } else if (current == '>') {
      buf_.append("&gt;");
    } else {
      utf8::append(static_cast<char32_t>(current), buf);
    }
    utf8::next(iterator, end);
  }
  return buf_;
}
