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
// ic_parser.cpp
#include "ic_parser.h"
#include "utilities/cpp_util.h"
#include <algorithm>
#include <cassert>
using namespace yaksha;
// TODO add a dummy token for comments to ensure it is theoretically replaced by a single space
//  we can not do it if it is not really required, I do not think this is required as line_splicer takes care of this!
//  newline after comment is also preserved
ic_parser::~ic_parser() = default;
ic_parser::ic_parser(std::vector<ic_token> &tokens, ic_ast_pool *ast_pool)
    : tokens_(tokens), ast_pool_(ast_pool), errors_(), current_(0) {}
void ic_parser::parse() {
  while (!is_at_end()) {
    try {
      statements_.emplace_back(preprocessor_statement());
    } catch (ic_parsing_error &ex) {
      intentionally_ignored(ex);
      // synchronize
      while (peek()->type_ != ic_token_type::NEWLINE && !is_at_end()) {
        advance();
      }
    }
  }
}
ic_token *ic_parser::advance() {
  if (!is_at_end()) { current_++; }
  return previous();
}
ic_token *ic_parser::recede() {
  if (current_ != 0) { current_--; }
  return peek();
}
bool ic_parser::is_at_end() { return peek()->type_ == ic_token_type::TC_EOF; }
ic_token *ic_parser::peek() { return &tokens_[current_]; }
ic_token *ic_parser::previous() {
  assert(current_ > 0);
  return &tokens_[current_ - 1];
}
bool ic_parser::match(std::initializer_list<ic_token_type> types) {
  return std::any_of(types.begin(), types.end(), [this](ic_token_type t) {
    if (this->check(t)) {
      this->advance();
      return true;
    }
    return false;
  });
}
bool ic_parser::check(ic_token_type t) {
  if (is_at_end()) { return false; }
  return peek()->type_ == t;
}
ic_token *ic_parser::consume(ic_token_type t, const std::string &message) {
  if (check(t)) return advance();
  throw error(peek(), message);
}
ic_parsing_error ic_parser::error(ic_token *tok, const std::string &message) {
  auto err = ic_parsing_error{message, tok};
  errors_.push_back(err);
  return err;
}
ic_token *ic_parser::consume_or_eof(ic_token_type t,
                                    const std::string &message) {
  if (check(t)) return advance();
  if (is_at_end()) return peek();
  throw error(peek(), message);
}
ic_stmt *ic_parser::preprocessor_statement() {
  if (peek()->type_ == ic_token_type::HASH) {
    auto hash_t = advance();
    if (peek()->type_ != ic_token_type::IDENTIFIER) {
      throw ic_parsing_error("Invalid token after #", hash_t);
    }
    auto identifier = peek()->token_;
    if (identifier == "define") { return define_st(hash_t); }
    if (identifier == "include") { return include_st(hash_t); }
    if (identifier == "line") { return line_st(hash_t); }
    if (identifier == "undef") { return undef_st(hash_t); }
    if (identifier == "error") { return error_st(hash_t); }
    if (identifier == "warning") { return warning_st(hash_t); }
    if (identifier == "pragma") { return pragma_st(hash_t); }
    if (identifier == "if" || identifier == "ifdef" || identifier == "ifndef") {
      return if_st(hash_t);
    }
    throw ic_parsing_error("Unknown preprocessor statement", hash_t);
  }
  return code_line();
}
ic_stmt *ic_parser::define_st(ic_token *hash_t) {
  auto define_tok = advance();
  if (!check(ic_token_type::IDENTIFIER)) {
    throw ic_parsing_error("Expected a valid identifier after #define", hash_t);
  }
  std::vector<ic_token *> replacement_{};
  auto identifier_tok = advance();
  std::vector<ic_token *> args{};
  if (check(ic_token_type::OPEN_PAREN)) {
    auto paren_open = advance();
    // parse macro #define
    if (!check(ic_token_type::CLOSE_PAREN)) {
      do {
        args.emplace_back(advance());
      } while (match({ic_token_type::COMMA}));
    }
    auto paren_close = consume(ic_token_type::CLOSE_PAREN,
                               "#define macro must have a valid ')'");
    std::vector<ic_token *> tok_string = token_string();
    consume(ic_token_type::NEWLINE, "new line is expected after #define");
    return ast_pool_->ic_c_pp_define_function_stmt(
        hash_t, define_tok, identifier_tok, paren_open, args, paren_close,
        tok_string);
  }
  // parse simple #define
  std::vector<ic_token *> tok_string = token_string();
  consume(ic_token_type::NEWLINE, "new line is expected after #define");
  return ast_pool_->ic_c_pp_define_normal_stmt(hash_t, define_tok,
                                               identifier_tok, tok_string);
}
ic_stmt *ic_parser::include_st(ic_token *hash_t) {
  auto include_tok = advance();
  auto path_spec = consume(ic_token_type::STRING_LITERAL,
                           "Expected an integer constant after #line");
  consume(ic_token_type::NEWLINE, "New line expected after #include");
  return ast_pool_->ic_c_pp_include_stmt(hash_t, include_tok, path_spec);
}
ic_stmt *ic_parser::line_st(ic_token *hash_t) {
  auto line_tok = advance();
  auto integer_const_tok = consume(ic_token_type::STRING_LITERAL,
                                   "Expected an integer constant after #line");
  auto path_tok = consume(ic_token_type::STRING_LITERAL,
                          "Expected a valid path token after #line");
  consume(ic_token_type::NEWLINE, "New line expected after #line");
  return ast_pool_->ic_c_pp_line_stmt(hash_t, line_tok, integer_const_tok,
                                      path_tok);
}
ic_stmt *ic_parser::undef_st(ic_token *hash_t) {
  auto undef_tok = advance();
  auto identifier_tok =
      consume(ic_token_type::IDENTIFIER, "Expected an identifier after #undef");
  consume(ic_token_type::NEWLINE, "New line expected after #undef");
  return ast_pool_->ic_c_pp_undef_stmt(hash_t, undef_tok, identifier_tok);
}
ic_stmt *ic_parser::error_st(ic_token *hash_t) { return nullptr; }
ic_stmt *ic_parser::warning_st(ic_token *hash_t) { return nullptr; }
ic_stmt *ic_parser::pragma_st(ic_token *hash_t) { return nullptr; }
ic_stmt *ic_parser::code_line() { return nullptr; }
ic_stmt *ic_parser::block(ic_token *hash_t) { return nullptr; }
ic_stmt *ic_parser::if_st(ic_token *hash_t) { return nullptr; }
std::vector<ic_token *> ic_parser::token_string() {
  return std::vector<ic_token *>{};
}
