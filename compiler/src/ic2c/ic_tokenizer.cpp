// ic_tokenizer.cpp
#include "ic_tokenizer.h"
#include "ic_token.h"
#include "tokenizer/string_utils.h"
using namespace yaksha;
enum class ic_tokenizer_state { NORMAL, PATH_SPEC_EXPECTED };
ic_tokenizer::ic_tokenizer(std::string file, std::string data)
    : file_(std::move(file)), data_(std::move(data)), line_(0), pos_(0) {}
ic_tokenizer::~ic_tokenizer() = default;
#define skip_1()                                                               \
  do {                                                                         \
    utf8::next(iterator, end);                                                 \
    pos_++;                                                                    \
    characters = ::string_utils::peek3(iterator, end);                         \
    current = std::get<0>(characters);                                         \
    next = std::get<1>(characters);                                            \
    after_next = std::get<2>(characters);                                      \
  } while (0)
#define skip_2()                                                               \
  do {                                                                         \
    utf8::next(iterator, end);                                                 \
    pos_++;                                                                    \
    utf8::next(iterator, end);                                                 \
    pos_++;                                                                    \
    characters = ::string_utils::peek3(iterator, end);                         \
    current = std::get<0>(characters);                                         \
    next = std::get<1>(characters);                                            \
    after_next = std::get<2>(characters);                                      \
  } while (0)
#define emit_tok(str, ttype)                                                   \
  do {                                                                         \
    tokens_.emplace_back(                                                      \
        ic_token{file_, prev_line_, prev_pos_, str, ttype, str});              \
  } while (0)
#define eat(message)                                                           \
  do {                                                                         \
    utf8::next(iterator, end);                                                 \
    pos_++;                                                                    \
    if (iterator == end) {                                                     \
      std::cout << prev_line_ << ":" << prev_pos_ << "-->" << token_buf << "\n";         \
      errors_.emplace_back(message, file_, line_, pos_);                       \
      throw ic_parsing_error{message, file_, line_, pos_};                     \
    }                                                                          \
    characters = ::string_utils::peek3(iterator, end);                         \
    current = std::get<0>(characters);                                         \
    next = std::get<1>(characters);                                            \
    after_next = std::get<2>(characters);                                      \
  } while (0)
#define clear_buf()                                                            \
  do {                                                                         \
    token_buf = {};                                                            \
  } while (0)
#define collect()                                                              \
  do {                                                                         \
    utf8::append(static_cast<char32_t>(current),                               \
                 std::back_inserter(token_buf));                               \
  } while (0)
#define valid_alpha_num(c)                                                     \
  (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||             \
   (c >= '0' && c <= '9'))
// Woah, in next #define, you see why emit_nl() is needed
//    (multi line macros are the use case)
#define emit_nl()                                                              \
  do { emit_tok("\n", ic_token_type::NEWLINE); } while (0)
void ic_tokenizer::tokenize() {
  try {
    tokenize_internal();
  } catch (utf8::exception &ignored) {
    errors_.emplace_back(
        "Invalid UTF-8 detected for input file. Will not continue.", nullptr);
  } catch (string_utils::string_error &ex) {
    errors_.emplace_back("Invalid String:" + ex.message_, nullptr);
  } catch (ic_parsing_error &ignored) {}
}
void ic_tokenizer::tokenize_internal() {
  line_ = 0;
  pos_ = 1;
  auto iterator = data_.begin();
  auto end = data_.end();
  utf8::uint32_t current;
  utf8::uint32_t next;
  utf8::uint32_t after_next;
  std::string token_buf{};
  ic_tokenizer_state state = ic_tokenizer_state::NORMAL;
  while (iterator != end) {
    prev_line_ = line_;
    prev_pos_ = pos_;
    auto characters = ::string_utils::peek3(iterator, end);
    current = std::get<0>(characters);
    next = std::get<1>(characters);
    after_next = std::get<2>(characters);
    if (current == '!' && next == '=') {
      emit_tok("!=", ic_token_type::NE_OP);
      skip_1();
    } else if (current == '!') {
      emit_tok("!", ic_token_type::BOOL_NOT);
    } else if (current == '#' && next == '#') {
      emit_tok("##", ic_token_type::HASH_HASH);
      skip_1();
    } else if (current == '#') {
      emit_tok("#", ic_token_type::HASH);
    } else if (current == '%' && next == '=') {
      emit_tok("%=", ic_token_type::MOD_ASSIGN);
      skip_1();
    } else if (current == '%' && next == '>') {
      emit_tok("}", ic_token_type::CLOSE_CURLY);// NOTE %> -> }
      skip_1();
    } else if (current == '%') {
      emit_tok("%", ic_token_type::MOD);
    } else if (current == '&' && next == '=') {
      emit_tok("&=", ic_token_type::AND_ASSIGN);
      skip_1();
    } else if (current == '&' && next == '&') {
      emit_tok("&&", ic_token_type::AND_OP);
      skip_1();
    } else if (current == '&') {
      emit_tok("&", ic_token_type::AMPERSAND);
    } else if (current == '(') {
      emit_tok("(", ic_token_type::OPEN_PAREN);
    } else if (current == ')') {
      emit_tok(")", ic_token_type::CLOSE_PAREN);
    } else if (current == '*' && next == '=') {
      emit_tok("*=", ic_token_type::MUL_ASSIGN);
      skip_1();
    } else if (current == '*') {
      emit_tok("*", ic_token_type::MUL);
    } else if (current == '+' && next == '=') {
      emit_tok("+=", ic_token_type::ADD_ASSIGN);
      skip_1();
    } else if (current == '+' && next == '+') {
      emit_tok("++", ic_token_type::INC_OP);
      skip_1();
    } else if (current == '+') {
      emit_tok("+", ic_token_type::ADD);
    } else if (current == ',') {
      emit_tok(",", ic_token_type::COMMA);
    } else if (current == '-' && next == '=') {
      emit_tok("-=", ic_token_type::SUB_ASSIGN);
      skip_1();
    } else if (current == '-' && next == '-') {
      emit_tok("--", ic_token_type::DEC_OP);
      skip_1();
    } else if (current == '-' && next == '>') {
      emit_tok("->", ic_token_type::PTR_OP);
      skip_1();
    } else if (current == '-') {
      emit_tok("-", ic_token_type::SUB);
    } else if (current == '.' && next == '.' && after_next == '.') {
      emit_tok("...", ic_token_type::ELLIPSIS);
      skip_2();
    } else if (current == '.') {
      emit_tok(".", ic_token_type::DOT);
    } else if (current == '/' && next == '=') {
      emit_tok("/=", ic_token_type::DIV_ASSIGN);
      skip_1();
    } else if (current == '/' && next == '*') {
      while (!(current == '*' && next == '/')) {
        eat("Reached end of file while capturing multi line comment");
        if (current == '\r' && next == '\n') {
          eat("cannot error here");
          line_++;
          pos_ = 0;
        } else if (current == '\r' || current == '\n') {
          line_++;
          pos_ = 0;
        }
      }
      skip_1();
    } else if (current == '/' && next == '/') {
      while (!(current == '\r' || current == '\n')) {
        eat("Reached end of file while capturing single line comment");
      }
      if (current == '\r' && next == '\n') { skip_1(); }
      prev_line_ = line_;
      prev_pos_ = pos_;
      emit_nl();
      line_++;
      pos_ = 0;
    } else if (current == '/') {
      emit_tok("/", ic_token_type::DIV);
    } else if (current == ':' && next == '>') {// NOTE :> -> ]
      emit_tok("]", ic_token_type::CLOSE_BRACKET);
      skip_1();
    } else if (current == ':') {
      emit_tok(":", ic_token_type::COLON);
    } else if (current == ';') {
      emit_tok(";", ic_token_type::SEMICOLON);
    } else if (current == '<' and
               state == ic_tokenizer_state::PATH_SPEC_EXPECTED) {
      // -------------------- Handle #include <...> ----------------------
      skip_1();
      clear_buf();
      utf8::uint32_t prev = 0;
      if (current == '>') {
        emit_tok("", ic_token_type::STRING_LITERAL);
      } else {
        while (!(current == '>' && prev != '\\')) {
          prev = current;
          collect();
          eat("Reached end of file while capturing path spec string literal");
        }
        emit_tok(token_buf, ic_token_type::STRING_LITERAL);
      }
      state = ic_tokenizer_state::NORMAL;
    } else if (current == '<' && next == '<' && after_next == '=') {
      emit_tok("<<=", ic_token_type::LEFT_ASSIGN);
      skip_2();
    } else if (current == '<' && next == '<') {
      emit_tok("<<", ic_token_type::LEFT_OP);
      skip_1();
    } else if (current == '<' && next == '=') {
      emit_tok("<=", ic_token_type::LE_OP);
      skip_1();
    } else if (current == '<' && next == '%') {// NOTE <% -> {
      emit_tok("<%", ic_token_type::OPEN_CURLY);
      skip_1();
    } else if (current == '<' && next == ':') {// NOTE <: -> [
      emit_tok("[", ic_token_type::OPEN_BRACKET);
      skip_1();
    } else if (current == '<') {
      emit_tok("<", ic_token_type::LESS);
    } else if (current == '=' && next == '=') {
      emit_tok("==", ic_token_type::EQ_OP);
      skip_1();
    } else if (current == '=') {
      emit_tok("=", ic_token_type::EQ);
    } else if (current == '>' && next == '>' && after_next == '=') {
      emit_tok(">>=", ic_token_type::RIGHT_ASSIGN);
      skip_2();
    } else if (current == '>' && next == '>') {
      emit_tok(">>", ic_token_type::RIGHT_OP);
      skip_1();
    } else if (current == '>' && next == '=') {
      emit_tok(">=", ic_token_type::GE_OP);
      skip_1();
    } else if (current == '>') {
      emit_tok(">", ic_token_type::GREATER);
    } else if (current == '?') {
      emit_tok("?", ic_token_type::QUESTION);
    } else if (current == '[') {
      emit_tok("[", ic_token_type::OPEN_BRACKET);
    } else if (current == ']') {
      emit_tok("]", ic_token_type::CLOSE_BRACKET);
    } else if (current == '^' && next == '=') {
      emit_tok("^=", ic_token_type::XOR_ASSIGN);
      skip_1();
    } else if (current == '^') {
      emit_tok("^", ic_token_type::XOR);
    } else if (current == '{') {
      emit_tok("{", ic_token_type::OPEN_CURLY);
    } else if (current == '|' && next == '=') {
      emit_tok("|=", ic_token_type::OR_ASSIGN);
      skip_1();
    } else if (current == '|' && next == '|') {
      emit_tok("||", ic_token_type::OR_OP);
      skip_1();
    } else if (current == '|') {
      emit_tok("|", ic_token_type::OR);
    } else if (current == '}') {
      emit_tok("}", ic_token_type::CLOSE_CURLY);
    } else if (current == '~') {
      emit_tok("~", ic_token_type::BITWISE_NOT);
    } else if (current == '\\') {
      emit_tok("\\", ic_token_type::BACKSLASH);
    } else if (current == '\r' && next == '\n') {
      line_++;
      pos_ = 0;
      skip_1();
      emit_nl();
    } else if (current == '\r' || current == '\n') {
      line_++;
      pos_ = 0;
      emit_nl();
    } else if (current == '\t' || current == ' ') {
      // ignored
    } else if (current == '\'' || (current == 'L' && next == '\'')) {
      if (current == 'L') { skip_1(); }// TODO capture type
      skip_1();
      clear_buf();
      utf8::uint32_t prev = 0;
      if (current == '\'') {
        errors_.emplace_back("Empty character literal is invalid.", file_,
                             line_, pos_);
      } else {
        while (current != '\'') {
          if (current == '\\') {
            collect();
            eat("Expected a character after escape in char literal");
            collect();
            eat("Expected a second character after escape sequence in char literal");
          } else {
            collect();
            eat("Reached end of file while capturing char literal");
          }
        }
        emit_tok(token_buf, ic_token_type::INTEGER_CONSTANT);
      }
    } else if (current == '\"' ||
               (current == 'u' && next == '8' && after_next == '\"') ||
               ((current == 'u' || current == 'U' || current == 'L') &&
                next == '\"')) {
      if (current == 'u' && next == '8') {
        skip_2();// TODO capture type
      } else if (current == 'u' || current == 'U' || current == 'L') {
        skip_1();// TODO capture type
      }
      skip_1();
      clear_buf();
      if (current == '\"') {
        emit_tok("", ic_token_type::STRING_LITERAL);
      } else {
        while (current != '\"') {
          if (current == '\\') {
            collect();
            eat("Expected a character after escape");
            collect();
            eat("Expected a second character after escape sequence");
          } else {
            collect();
            eat("Reached end of file while capturing string literal");
          }
        }
        emit_tok(token_buf, ic_token_type::STRING_LITERAL);
      }
      if (state == ic_tokenizer_state::PATH_SPEC_EXPECTED) {
        state = ic_tokenizer_state::NORMAL;
      }
    } else if (current >= '0' && current <= '9') {
      // TODO do proper number capturing.. this is just basic?
      clear_buf();
      while ((current >= '0' && current <= '9') &&
             (next >= '0' && next <= '9')) {
        collect();
        eat("Reached end of file while capturing number");
      }
      collect();
      emit_tok(token_buf, ic_token_type::INTEGER_CONSTANT);
    } else if (current == '_' || (current >= 'a' && current <= 'z') ||
               (current >= 'A' && current <= 'Z')) {
      clear_buf();
      while (valid_alpha_num(current) && valid_alpha_num(next)) {
        collect();
        eat("Reached end of file while capturing identifier");
      }
      collect();
      // ------------------- Handle Special #include --------------
      if (!tokens_.empty() && tokens_.back().type_ == ic_token_type::HASH &&
          token_buf == "include") {
        state = ic_tokenizer_state::PATH_SPEC_EXPECTED;
      }
      emit_tok(token_buf, ic_token_type::IDENTIFIER);
    } else {
      errors_.emplace_back("Invalid character", file_, line_, pos_);
    }
    utf8::next(iterator, end);
    pos_++;
  }
  prev_line_ = line_;
  prev_pos_ = pos_;
  // Have a new line at the end to indicate end of last line!
  if (!tokens_.empty() && tokens_.back().type_ != ic_token_type::NEWLINE) {
    emit_tok("\n", ic_token_type::NEWLINE);
  }
  // Have an EOF at the end to indicate file end
  emit_tok("", ic_token_type::TC_EOF);
}
ic_parsing_error::ic_parsing_error(std::string message, ic_token *token_)
    : message_(std::move(message)) {
  if (token_ == nullptr) {
    tok_ = {};
    token_set_ = false;
  } else {
    tok_ = {token_->file_,  token_->line_,     token_->pos_,   token_->token_,
            token_->type_,  token_->original_, token_->itype_, token_->ibase_,
            token_->stype_, token_->ftype_};
    token_set_ = true;
  }
}
ic_parsing_error::ic_parsing_error(std::string message, std::string file,
                                   int line, int pos)
    : message_{std::move(message)},
      tok_{std::move(file),
           line,
           pos,
           "",
           ic_token_type::TK_UNKNOWN_TOKEN_DETECTED,
           ""},
      token_set_(true) {}
