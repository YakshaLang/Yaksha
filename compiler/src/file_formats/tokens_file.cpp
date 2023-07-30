// tokens_file.cpp
#include "file_formats/tokens_file.h"
using namespace yaksha;
bool yaksha::save_token_dump(const std::string &file,
                             const std::vector<token *> &tokens) {
  std::ofstream save_file(file);
  if (!save_file.is_open()) { return false; }
  write_token_dump(save_file, tokens);
  return true;
}
void yaksha::write_token_dump(std::ostream &output,
                              const std::vector<token *> &tokens) {
  bool comma = false;
  output << "[";
  for (auto &tok : tokens) {
    if (comma) {
      output << ",\n";
    } else {
      output << "\n";
      comma = true;
    }
    output << "    [" << ::string_utils::repr_string(tok->file_) << ","
           << tok->line_ << "," << tok->pos_ << ","
           << ::string_utils::repr_string(tok->token_) << ","
           << ::string_utils::repr_string(token_to_str(tok->type_)) << "]";
  }
  output << "\n]";
}
template<typename token_iterator>
static inline bool consume_tokens_for_token_dump(
    std::vector<token *> &target, token_iterator &iterator, token_iterator end,
    const std::initializer_list<token_type> &to_match) {
  token_iterator copy_iter = iterator;
  int steps = 0;
  auto tok_type_iterator = to_match.begin();
  auto tok_type_end = to_match.end();
  while (tok_type_iterator != tok_type_end) {
    if (copy_iter == end) {
      target.clear();
      return false;
    }
    token *tk = *copy_iter;
    copy_iter++;
    steps++;
    if (tk->type_ == token_type::COMMENT || tk->type_ == token_type::INDENT ||
        tk->type_ == token_type::NEW_LINE) {
      continue;
    }
    if (tk->type_ != *tok_type_iterator) {
      target.clear();
      return false;
    }
    tok_type_iterator++;
    target.push_back(tk);
  }
  if (target.size() != to_match.size()) { return false; }
  std::advance(iterator, steps);
  return true;
}
#define TK_FIRST_BRACKET_FOUND 1
#define TK_INSIDE_TOKEN 2
#define TK_NORMAL 3
#define TK_END 4
std::vector<token *> yaksha::load_token_dump(const std::string &file,
                                             gc_pool<token> *token_pool) {
  // Note we do not care about the last closing square bracket in tokens file
  std::vector<token *> tokens{};
  std::vector<token *> temp_buffer{};
  temp_buffer.reserve(10);
  tokens.reserve(100);
  std::ifstream t(file);
  if (!t.is_open()) { return {}; }
  std::string str((std::istreambuf_iterator<char>(t)),
                  std::istreambuf_iterator<char>());
  tokenizer token_list{file, str, token_pool};
  token_list.tokenize();
  if (!token_list.errors_.empty()) { return {}; }
  auto iterator = token_list.tokens_.begin();
  auto end = token_list.tokens_.end();
  char mode = TK_NORMAL;
  while (iterator != end) {
    auto tk = *iterator;
    iterator++;
    if (tk->type_ == token_type::COMMENT || tk->type_ == token_type::INDENT ||
        tk->type_ == token_type::NEW_LINE ||
        tk->type_ == token_type::END_OF_FILE) {
      continue;
    }
    if (mode == TK_END) { return {}; }
    if (mode == TK_NORMAL) {
      if (tk->type_ == token_type::SQUARE_BRACKET_OPEN) {
        mode = TK_FIRST_BRACKET_FOUND;
        continue;
      } else {
        return {};
      }
    }
    if (tk->type_ == token_type::SQUARE_BRACKET_OPEN) {
      mode = TK_INSIDE_TOKEN;
    } else {
      return {};
    }
    temp_buffer.clear();
    if (!consume_tokens_for_token_dump(
            temp_buffer, iterator, end,
            {token_type::STRING, token_type::COMMA, token_type::INTEGER_DECIMAL,
             token_type::COMMA, token_type::INTEGER_DECIMAL, token_type::COMMA,
             token_type::STRING, token_type::COMMA, token_type::STRING,
             token_type::SQUARE_BRACKET_CLOSE})) {
      return {};
    }
    tokens.push_back(token_list.c_token(
        temp_buffer[0]->token_,
        std::stoi(
            temp_buffer[2]->token_),// INTEGER_DECIMAL can be safely converted
        std::stoi(temp_buffer[4]->token_),
        string_utils::unescape(temp_buffer[6]->token_),
        str_to_token(temp_buffer[8]->token_)));
    mode = TK_FIRST_BRACKET_FOUND;
    temp_buffer.clear();
    if (consume_tokens_for_token_dump(temp_buffer, iterator, end,
                                      {token_type::COMMA})) {
      continue;
    } else if (consume_tokens_for_token_dump(
                   temp_buffer, iterator, end,
                   {token_type::SQUARE_BRACKET_CLOSE})) {
      mode = TK_END;
      continue;
    } else {
      return {};
    }
  }
  return tokens;
}
