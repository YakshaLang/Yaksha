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
// ic_tokens_file.cpp
#include "file_formats/ic_tokens_file.h"
#include "tokenizer/string_utils.h"
#include <fstream>
#include <iostream>
#include <utf8.h>
#include <vector>
using namespace yaksha;
bool yaksha::ic_save_token_dump(const std::string &file,
                                const std::vector<ic_token> &tokens) {
  std::ofstream save_file(file);
  if (!save_file.is_open()) { return false; }
  ic_write_token_dump(save_file, tokens);
  return true;
}
void yaksha::ic_write_token_dump(std::ostream &output,
                                 const std::vector<ic_token> &tokens) {
  bool comma = false;
  output << "[";
  for (auto &tok : tokens) {
    if (comma) {
      output << ",\n";
    } else {
      output << "\n";
      comma = true;
    }
    output << "    [" << ::string_utils::repr_string(tok.file_) << ","
           << tok.line_ << "," << tok.pos_ << ","
           << ::string_utils::repr_string(tok.token_) << ","
           << ::string_utils::repr_string(ic_token_to_str(tok.type_)) << ","
           << ic_integer_type_to_str(tok.itype_) << ","
           << ic_integer_base_to_str(tok.ibase_) << ","
           << ic_string_literal_type_to_str(tok.stype_) << ","
           << ic_float_type_to_str(tok.ftype_) << "]";
  }
  output << "\n]";
}
template<typename token_iterator>
static inline bool consume_tokens_for_token_dump(
    std::vector<ic_token> &target, token_iterator &iterator, token_iterator end,
    const std::initializer_list<ic_token_type> &to_match) {
  token_iterator copy_iter = iterator;
  int steps = 0;
  auto tok_type_iterator = to_match.begin();
  auto tok_type_end = to_match.end();
  while (tok_type_iterator != tok_type_end) {
    if (copy_iter == end) {
      target.clear();
      return false;
    }
    ic_token tk = *copy_iter;
    copy_iter++;
    steps++;
    if (tk.type_ == ic_token_type::COMMENT ||
        tk.type_ == ic_token_type::NEWLINE) {
      continue;
    }
    if (tk.type_ != *tok_type_iterator) {
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
std::vector<ic_token> yaksha::ic_load_token_dump(const std::string &file) {
  // Note we do not care about the last closing square bracket in tokens file
  std::vector<ic_token> tokens{};
  std::vector<ic_token> temp_buffer{};
  temp_buffer.reserve(10);
  tokens.reserve(100);
  std::ifstream t(file);
  if (!t.is_open()) { return {}; }
  std::string str((std::istreambuf_iterator<char>(t)),
                  std::istreambuf_iterator<char>());
  ic_tokenizer token_list{file, str};
  token_list.tokenize();
  if (!token_list.errors_.empty()) { return {}; }
  auto iterator = token_list.tokens_.begin();
  auto end = token_list.tokens_.end();
  char mode = TK_NORMAL;
  while (iterator != end) {
    auto tk = *iterator;
    iterator++;
    if (tk.type_ == ic_token_type::COMMENT ||
        tk.type_ == ic_token_type::NEWLINE ||
        tk.type_ == ic_token_type::TC_EOF) {
      continue;
    }
    if (mode == TK_END) { return {}; }
    if (mode == TK_NORMAL) {
      if (tk.type_ == ic_token_type::OPEN_BRACKET) {
        mode = TK_FIRST_BRACKET_FOUND;
        continue;
      } else {
        return {};
      }
    }
    if (tk.type_ == ic_token_type::OPEN_BRACKET) {
      mode = TK_INSIDE_TOKEN;
    } else {
      return {};
    }
    temp_buffer.clear();
    if (!consume_tokens_for_token_dump(
            temp_buffer, iterator, end,
            {ic_token_type::STRING_LITERAL, ic_token_type::COMMA,  // file - 0
             ic_token_type::INTEGER_CONSTANT, ic_token_type::COMMA,// line - 2
             ic_token_type::INTEGER_CONSTANT, ic_token_type::COMMA,// pos - 4
             ic_token_type::STRING_LITERAL, ic_token_type::COMMA,  // token - 6
             ic_token_type::STRING_LITERAL, ic_token_type::COMMA,  // type - 8
             ic_token_type::IDENTIFIER, ic_token_type::COMMA,// i_type - 10
             ic_token_type::IDENTIFIER, ic_token_type::COMMA,// i_base - 12
             ic_token_type::IDENTIFIER, ic_token_type::COMMA,// s_type - 14
             ic_token_type::IDENTIFIER,                      // f_type - 16
             ic_token_type::CLOSE_BRACKET})) {
      return {};
    }
    tokens.emplace_back(ic_token{
        temp_buffer[0].token_,
        std::stoi(
            temp_buffer[2].token_),// INTEGER_DECIMAL can be safely converted
        std::stoi(temp_buffer[4].token_),
        string_utils::unescape(temp_buffer[6].token_),
        ic_str_to_token(temp_buffer[8].token_),
        string_utils::unescape(
            temp_buffer[6]
                .token_),// We do not save this, so? this does not matter really
        str_to_ic_integer_type(temp_buffer[10].token_),
        str_to_ic_integer_base(temp_buffer[12].token_),
        str_to_ic_string_literal_type(temp_buffer[14].token_),
        str_to_ic_float_type(temp_buffer[16].token_),
    });
    mode = TK_FIRST_BRACKET_FOUND;
    temp_buffer.clear();
    if (consume_tokens_for_token_dump(temp_buffer, iterator, end,
                                      {ic_token_type::COMMA})) {
      continue;
    } else if (consume_tokens_for_token_dump(temp_buffer, iterator, end,
                                             {ic_token_type::CLOSE_BRACKET})) {
      mode = TK_END;
      continue;
    } else {
      return {};
    }
  }
  return tokens;
}
