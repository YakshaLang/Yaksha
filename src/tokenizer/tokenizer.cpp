// tokenizer.cpp
#include "tokenizer/tokenizer.h"
#include "token.h"
#include <utility>
using namespace yaksha;
#define NORMAL_MATCH 1
#define STRING_MATCH 2
#define TRIPLE_STRING_MATCH 3
#define NAME_MATCH 4
#define INDENT_MATCH 5
#define COMMENT_MATCH 6
#define OCT_MATCH 7
#define BIN_MATCH 8
#define HEX_MATCH 9
#define MATCH_INTEGER_OR_FLOAT 10
template<typename octet_iterator>
std::pair<int, utf8::uint32_t> yaksha::consume_string(std::string &buf,
                                                      octet_iterator &begin,
                                                      octet_iterator end) {
  octet_iterator begin_copy = begin;
  int size = 0;
  auto buf_inserter = std::back_inserter(buf);
  utf8::uint32_t current = 0;
  bool skip = false;
  while (begin_copy != end) {
    current = utf8::peek_next(begin_copy, end);
    if (skip) {
      utf8::append(static_cast<char32_t>(current), buf_inserter);
      utf8::next(begin_copy, end);// move to next character
      size++;
      skip = false;
      continue;
    } else if (current == '\\') {
      skip = true;
    } else {
      skip = false;
    }
    if (current != '\"' && current != '\n' && current != '\r') {
      utf8::append(static_cast<char32_t>(current), buf_inserter);
      utf8::next(begin_copy, end);// move to next character
      size++;
    } else {
      begin = begin_copy;
      return std::make_pair(size, current);
    }
  }
  return std::make_pair(-1, 0);
}
template<typename octet_iterator>
std::tuple<int, utf8::uint32_t, int>
yaksha::consume_triple_str(std::string &buf, octet_iterator &begin,
                           octet_iterator end) {
  int size = 0;
  int lines = 0;
  octet_iterator copy_begin = begin;
  auto buf_inserter = std::back_inserter(buf);
  utf8::uint32_t prev;
  utf8::uint32_t current = 0;
  utf8::uint32_t next;
  utf8::uint32_t after_next;
  utf8::next(copy_begin, end);
  utf8::next(copy_begin, end);
  while (copy_begin != end) {
    prev = current;
    auto characters = ::string_utils::peek3(copy_begin, end);
    current = std::get<0>(characters);
    next = std::get<1>(characters);
    after_next = std::get<2>(characters);
    if (prev != '\\' && current == '"' && next == '"' && after_next == '"') {
      utf8::next(copy_begin, end);
      utf8::next(copy_begin, end);
      utf8::next(copy_begin, end);
      // Update the iterator on success.
      begin = copy_begin;
      return {size + 2, current, lines};
    } else {
      if (current == '\n') {
        size = -1;
        lines++;
      }
      utf8::append(static_cast<char32_t>(current), buf_inserter);
      utf8::next(copy_begin, end);
      size++;
    }
  }
  return std::make_tuple(-1, 0, 0);
}
#define NUMBER_MATCH_NORMAL 0
#define NUMBER_MATCH_EXPO 1
#define CONTINUE_TO_NEXT_CHAR                                                  \
  do {                                                                         \
    mode = NORMAL_MATCH;                                                       \
    pos++;                                                                     \
    utf8::next(iterator, end);                                                 \
  } while (0)
template<typename octet_iterator>
std::tuple<int, utf8::uint32_t, token_type>
yaksha::consume_number(std::string &buf, octet_iterator &begin,
                       octet_iterator end) {
  auto buf_inserter = std::back_inserter(buf);
  char mode = NUMBER_MATCH_NORMAL;
  bool dot_found = false;
  bool exponent_found = false;
  int size = 0;
  int expo_size = 0;
  utf8::uint32_t current = 0;
  utf8::uint32_t next;
  while (begin != end) {
    auto characters = ::string_utils::peek3(begin, end);
    current = std::get<0>(characters);
    next = std::get<1>(characters);
    if (mode == NUMBER_MATCH_NORMAL) {
      if (current == '.') {
        if (dot_found) { return {-1, 0, token_type::INTEGER_DECIMAL}; }
        dot_found = true;
        utf8::append(static_cast<char32_t>(current), buf_inserter);
        size++;
      } else if (::string_utils::is_digit(current)) {
        utf8::append(static_cast<char32_t>(current), buf_inserter);
        size++;
      } else if (current == 'e' || current == 'E') {
        exponent_found = true;
        utf8::append(static_cast<char32_t>(current), buf_inserter);
        size++;
        if (next == '+' || next == '-') {
          utf8::append(static_cast<char32_t>(next), buf_inserter);
          utf8::next(begin, end);
          size++;
        }
        mode = NUMBER_MATCH_EXPO;
      } else {// Any other character, EOF
        break;
      }
    } else {// NUMBER_MATCH_EXPO
      if (::string_utils::is_digit(current)) {
        utf8::append(static_cast<char32_t>(current), buf_inserter);
        size++;
        expo_size++;
      } else {
        break;
      }
    }
    utf8::next(begin, end);
  }
  // Cannot end with eE+-
  if ((mode == NUMBER_MATCH_EXPO && (current == 'e' || current == 'E' ||
                                     current == '+' || current == '-'))) {
    return {-1, 0, token_type::INTEGER_DECIMAL};
  }
  // Exponent must follow a number
  if (exponent_found && expo_size <= 0) {
    return {-1, 0, token_type::INTEGER_DECIMAL};
  }
  if (current == 'f') {
    utf8::next(begin, end);
    size++;
    utf8::append(static_cast<char32_t>(current), buf_inserter);
    current = next;
    return {size, current, token_type::FLOAT_NUMBER};
  }
  return {size, current,
          (dot_found || exponent_found) ? token_type::DOUBLE_NUMBER
                                        : token_type::INTEGER_DECIMAL};
}
tokenizer::tokenizer(std::string file, std::string data)
    : tokens_(), file_(std::move(file)), data_(std::move(data)), errors_() {}
void tokenizer::tokenize() {
  try {
    tokenize_actual();
  } catch (utf8::exception &ignored) {
    errors_.emplace_back(parsing_error{
        "Invalid UTF-8 detected for input file. Will not continue.", nullptr});
  }
}
void tokenizer::tokenize_actual() {
  auto iterator = data_.begin();
  auto end = data_.end();
  utf8::uint32_t current;
  utf8::uint32_t next;
  utf8::uint32_t after_next;
  int line = 0;
  int pos = 1;
  int mode = NORMAL_MATCH;
  std::string token_buf{};
  while (iterator != end) {
    auto characters = ::string_utils::peek3(iterator, end);
    current = std::get<0>(characters);
    next = std::get<1>(characters);
    after_next = std::get<2>(characters);
    if (mode == NORMAL_MATCH) {
      if (::string_utils::is_alpha(current)) {
        mode = NAME_MATCH;
        continue;
      } else if (current == '0' && (next == 'o' || next == 'O')) {
        mode = OCT_MATCH;
        continue;
      } else if (current == '0' && (next == 'x' || next == 'X')) {
        mode = HEX_MATCH;
        continue;
      } else if (current == '0' && (next == 'b' || next == 'B')) {
        mode = BIN_MATCH;
        continue;
      } else if (::string_utils::is_digit(current) ||
                 (current == '.' && ::string_utils::is_digit(next))) {
        mode = MATCH_INTEGER_OR_FLOAT;
        continue;
      }
      switch (current) {
        case '\n':
          tokens_.emplace_back(
              token{file_, line, pos, "\n", token_type::NEW_LINE});
          line++;
          pos = 0;
          break;
        case '@':
          tokens_.emplace_back(token{file_, line, pos, "@", token_type::AT});
          break;
        case '(':
          tokens_.emplace_back(
              token{file_, line, pos, "(", token_type::PAREN_OPEN});
          break;
        case ')':
          tokens_.emplace_back(
              token{file_, line, pos, ")", token_type::PAREN_CLOSE});
          break;
        case '[':
          tokens_.emplace_back(
              token{file_, line, pos, "[", token_type::SQUARE_BRACKET_OPEN});
          break;
        case ']':
          tokens_.emplace_back(
              token{file_, line, pos, "]", token_type::SQUARE_BRACKET_CLOSE});
          break;
        case '{':
          tokens_.emplace_back(
              token{file_, line, pos, "{", token_type::CURLY_BRACKET_OPEN});
          break;
        case '}':
          tokens_.emplace_back(
              token{file_, line, pos, "}", token_type::CURLY_BRACKET_CLOSE});
          break;
        case '.':
          if (next == '.' && after_next == '.') {
            tokens_.emplace_back(
                token{file_, line, pos, "...", token_type::ELLIPSIS});
            utf8::next(iterator, end);
            utf8::next(iterator, end);
            pos += 2;
          } else {
            tokens_.emplace_back(token{file_, line, pos, ".", token_type::DOT});
          }
          break;
        case '<':
          if (next == '=') {
            tokens_.emplace_back(
                token{file_, line, pos, "<=", token_type::LESS_EQ});
            utf8::next(iterator, end);
            pos++;
          } else if (next == '<') {
            tokens_.emplace_back(
                token{file_, line, pos, "<<", token_type::SHL});
            utf8::next(iterator, end);
            pos++;
          } else {
            tokens_.emplace_back(
                token{file_, line, pos, "<", token_type::LESS});
          }
          break;
        case '=':
          if (next == '=') {
            tokens_.emplace_back(
                token{file_, line, pos, "==", token_type::EQ_EQ});
            utf8::next(iterator, end);
            pos++;
          } else {
            tokens_.emplace_back(token{file_, line, pos, "=", token_type::EQ});
          }
          break;
        case '>':
          if (next == '=') {
            tokens_.emplace_back(
                token{file_, line, pos, ">=", token_type::GREAT_EQ});
            utf8::next(iterator, end);
            pos++;
          } else if (next == '>') {
            tokens_.emplace_back(
                token{file_, line, pos, ">>", token_type::SHR});
            utf8::next(iterator, end);
            pos++;
          } else {
            tokens_.emplace_back(
                token{file_, line, pos, ">", token_type::GREAT});
          }
          break;
        case '!':
          if (next == '=') {
            tokens_.emplace_back(
                token{file_, line, pos, "!=", token_type::NOT_EQ});
            utf8::next(iterator, end);
            pos++;
          } else {
            handle_error(parsing_error{
                "Tokenizer Error : did you mean to write `!=` here?", file_,
                line, pos});
          }
          break;
        case '+':
          if (next == '=') {
            tokens_.emplace_back(
                token{file_, line, pos, "+=", token_type::PLUS_EQ});
            utf8::next(iterator, end);
            pos++;
          } else {
            tokens_.emplace_back(
                token{file_, line, pos, "+", token_type::PLUS});
          }
          break;
        case '-':
          if (next == '=') {
            tokens_.emplace_back(
                token{file_, line, pos, "-=", token_type::SUB_EQ});
            utf8::next(iterator, end);
            pos++;
          } else if (next == '>') {
            tokens_.emplace_back(
                token{file_, line, pos, "->", token_type::ARROW});
            utf8::next(iterator, end);
            pos++;
          } else {
            tokens_.emplace_back(token{file_, line, pos, "-", token_type::SUB});
          }
          break;
        case '*': {
          if (next == '=') {
            tokens_.emplace_back(
                token{file_, line, pos, "*=", token_type::MUL_EQ});
            utf8::next(iterator, end);
            pos++;
          } else if (next == '*') {
            if (after_next == '=') {
              tokens_.emplace_back(
                  token{file_, line, pos, "**=", token_type::POWER_EQ});
              utf8::next(iterator, end);
              pos++;
            } else {
              tokens_.emplace_back(
                  token{file_, line, pos, "**", token_type::POWER});
            }
            utf8::next(iterator, end);
            pos++;
          } else {
            tokens_.emplace_back(token{file_, line, pos, "*", token_type::MUL});
          }
        } break;
        case '/': {
          if (next == '=') {
            tokens_.emplace_back(
                token{file_, line, pos, "/=", token_type::DIV_EQ});
            utf8::next(iterator, end);
            pos++;
          } else if (next == '/') {
            if (after_next == '=') {
              tokens_.emplace_back(
                  token{file_, line, pos, "//=", token_type::INT_DIV_EQ});
              utf8::next(iterator, end);
              pos++;
            } else {
              tokens_.emplace_back(
                  token{file_, line, pos, "//", token_type::INT_DIV});
            }
            utf8::next(iterator, end);
            pos++;
          } else {
            tokens_.emplace_back(token{file_, line, pos, "/", token_type::DIV});
          }
        } break;
        case '&':
          if (next == '=') {
            tokens_.emplace_back(
                token{file_, line, pos, "&=", token_type::AND_EQ});
            utf8::next(iterator, end);
            pos++;
          } else {
            tokens_.emplace_back(token{file_, line, pos, "&", token_type::AND});
          }
          break;
        case '|':
          if (next == '=') {
            tokens_.emplace_back(
                token{file_, line, pos, "|=", token_type::OR_EQ});
            utf8::next(iterator, end);
            pos++;
          } else {
            tokens_.emplace_back(token{file_, line, pos, "|", token_type::OR});
          }
          break;
        case '^':
          if (next == '=') {
            tokens_.emplace_back(
                token{file_, line, pos, "^=", token_type::XOR_EQ});
            utf8::next(iterator, end);
            pos++;
          } else {
            tokens_.emplace_back(token{file_, line, pos, "^", token_type::XOR});
          }
          break;
        case '%':
          if (next == '=') {
            tokens_.emplace_back(
                token{file_, line, pos, "%=", token_type::MOD_EQ});
            utf8::next(iterator, end);
            pos++;
          } else {
            tokens_.emplace_back(token{file_, line, pos, "%", token_type::MOD});
          }
          break;
        case ':':
          tokens_.emplace_back(token{file_, line, pos, ":", token_type::COLON});
          break;
        case ',':
          tokens_.emplace_back(token{file_, line, pos, ",", token_type::COMMA});
          break;
        case '~':
          tokens_.emplace_back(token{file_, line, pos, "~", token_type::TILDE});
          break;
        // Unicode Spaces will not be supported, only space or tab
        case ' ':
        case '\t':
          // Either first line may start with an indent (not allowed, but allowed
          // in tokenizer) or need to be just after new line
          if (tokens_.empty() || tokens_.back().type_ == token_type::NEW_LINE) {
            // Indent
            mode = INDENT_MATCH;
            continue;
          }
          // Spaces in the middle of context can be ignored safely
          break;
        case '\r':
          break;
        case '"':
          if (next == '"' && after_next == '"') {
            mode = TRIPLE_STRING_MATCH;
            break;
          }
          mode = STRING_MATCH;
          break;
        case '#':
          mode = COMMENT_MATCH;
          break;
        default:
          handle_error(parsing_error{"Tokenizer Error : Invalid character",
                                     file_, line, pos});
      }
      utf8::next(iterator, end);
      pos++;
    } else if (mode == TRIPLE_STRING_MATCH) {
      token_buf = {};
      auto result = ::consume_triple_str(token_buf, iterator, end);
      if (std::get<0>(result) == -1) {
        handle_error(
            parsing_error{"Tokenizer Error : Invalid string, end of file "
                          "reached before end of string",
                          file_, line, pos});
        CONTINUE_TO_NEXT_CHAR;
        continue;
      }
      tokens_.emplace_back(token{file_, line, pos - 1, token_buf,
                                 token_type::THREE_QUOTE_STRING});
      auto lines_in_str = std::get<2>(result);
      pos += std::get<0>(result);
      if (lines_in_str == 0) {
        pos += 3;// add prefix
      }
      line += lines_in_str;
      mode = NORMAL_MATCH;
    } else if (mode == STRING_MATCH) {
      token_buf = {};
      auto result = consume_string(token_buf, iterator, end);
      if (result.first == -1) {
        handle_error(
            parsing_error{"Tokenizer Error : Invalid string, end of file "
                          "reached before end of string",
                          file_, line, pos});
        CONTINUE_TO_NEXT_CHAR;
        continue;
      } else if (result.second == '\r' || result.second == '\n') {
        handle_error(parsing_error{"Tokenizer Error : Invalid string, new line "
                                   "detected while parsing string",
                                   file_, line, pos});
        CONTINUE_TO_NEXT_CHAR;
        continue;
      }
      tokens_.emplace_back(
          token{file_, line, pos, token_buf, token_type::STRING});
      pos += result.first;
      pos++;
      utf8::next(iterator, end);// skip last " in string
      mode = NORMAL_MATCH;
    } else if (mode == NAME_MATCH) {
      token_buf = {};
      auto result = ::string_utils::consume(::string_utils::allowed_in_name,
                                            token_buf, iterator, end, true);
      token_type kw = str_to_keyword(token_buf);
      if (kw == token_type::TK_UNKNOWN_TOKEN_DETECTED) {
        tokens_.emplace_back(
            token{file_, line, pos, token_buf, token_type::NAME});
      } else {
        tokens_.emplace_back(token{file_, line, pos, token_buf, kw});
      }
      pos += result.first;
      mode = NORMAL_MATCH;
    } else if (mode == INDENT_MATCH) {
      token_buf = {};
      auto result = ::string_utils::consume(::string_utils::allowed_in_indent,
                                            token_buf, iterator, end, true);
      if (result.first > 0) {
        tokens_.emplace_back(
            token{file_, line, pos, token_buf, token_type::INDENT});
        pos += result.first;
      }
      mode = NORMAL_MATCH;
    } else if (mode == COMMENT_MATCH) {
      token_buf = {};
      auto result = ::string_utils::consume(::string_utils::allowed_in_comment,
                                            token_buf, iterator, end, true);
      tokens_.emplace_back(
          token{file_, line, pos - 1, token_buf, token_type::COMMENT});
      if (result.first > 0) { pos += result.first; }
      mode = NORMAL_MATCH;
    } else if (mode == HEX_MATCH || mode == OCT_MATCH || mode == BIN_MATCH) {
      token_buf = {};
      utf8::append(static_cast<char32_t>(current),
                   std::back_inserter(token_buf));
      utf8::append(static_cast<char32_t>(next), std::back_inserter(token_buf));
      auto iterator_copy = iterator;
      utf8::next(iterator_copy, end);
      utf8::next(iterator_copy, end);
      std::pair<int, uint32_t> result;
      token_type token_type_number;
      if (mode == HEX_MATCH) {
        result = ::string_utils::consume(::string_utils::allowed_in_hex,
                                         token_buf, iterator_copy, end, false);
        token_type_number = token_type::INTEGER_HEX;
      } else if (mode == OCT_MATCH) {
        result = ::string_utils::consume(::string_utils::allowed_in_oct,
                                         token_buf, iterator_copy, end, false);
        token_type_number = token_type::INTEGER_OCT;
      } else {
        result = ::string_utils::consume(::string_utils::allowed_in_bin,
                                         token_buf, iterator_copy, end, false);
        token_type_number = token_type::INTEGER_BIN;
      }
      if (result.first <= 0) {
        handle_error(
            parsing_error{"Tokenizer Error : Invalid number, end of file "
                          "reached before end of name",
                          file_, line, pos});
        CONTINUE_TO_NEXT_CHAR;
        continue;
      } else {
        iterator = iterator_copy;
      }
      tokens_.emplace_back(
          token{file_, line, pos, token_buf, token_type_number});
      pos += result.first + 1;
      mode = NORMAL_MATCH;
    } else {// MATCH_INTEGER_OR_FLOAT
      token_buf = {};
      auto result = ::consume_number(token_buf, iterator, end);
      int size = std::get<0>(result);
      token_type number_type = std::get<2>(result);
      tokens_.emplace_back(token{file_, line, pos, token_buf, number_type});
      pos += size;
      mode = NORMAL_MATCH;
    }
  }
  if (mode != NORMAL_MATCH && mode != COMMENT_MATCH) {
    handle_error(parsing_error{"Tokenizer Error : Invalid end of file", file_,
                               line, pos});
  }
  bool last_new_ln =
      !tokens_.empty() && tokens_.back().type_ == token_type::NEW_LINE;
  tokens_.emplace_back(token{file_, line, pos + (last_new_ln ? 0 : 1), "",
                             token_type::END_OF_FILE});
  for (auto &t : tokens_) { t.original_ = t.token_; }
}
void tokenizer::handle_error(const parsing_error &t) {
  errors_.emplace_back(t);
}
parsing_error::parsing_error(std::string message, token *token_)
    : message_(std::move(message)) {
  if (token_ == nullptr) {
    tok_ = {};
    token_set_ = false;
  } else {
    tok_ = {token_->file_,  token_->line_, token_->pos_,
            token_->token_, token_->type_, token_->original_};
    token_set_ = true;
  }
}
parsing_error::parsing_error(std::string message, std::string file, int line,
                             int pos)
    : message_{std::move(message)}, tok_{std::move(file),
                                         line,
                                         pos,
                                         "",
                                         token_type::TK_UNKNOWN_TOKEN_DETECTED,
                                         ""},
      token_set_(true) {}
