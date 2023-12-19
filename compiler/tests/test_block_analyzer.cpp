// ==============================================================================================
// ╦  ┬┌─┐┌─┐┌┐┌┌─┐┌─┐    Yaksha Programming Language
// ║  ││  ├┤ │││└─┐├┤     is Licensed with GPLv3 + exta terms. Please see below.
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
#include "btest.h"
#include "catch2/catch.hpp"
#include "file_formats/tokens_file.h"
#include "tokenizer/block_analyzer.h"
#include <utility>
using namespace yaksha;
std::ostream &operator<<(std::ostream &o, const token &t) {
  std::string x = t.token_;
  if (t.type_ == token_type::NEW_LINE) { x = "\\n"; }
  o << t.file_ << ":" << t.line_ + 1 << ":" << t.pos_ << ":";
  if (t.type_ == token_type::NEW_LINE || t.type_ == token_type::BA_INDENT ||
      t.type_ == token_type::BA_DEDENT) {
    o << KYEL << token_to_str(t.type_) << RST;
  } else {
    o << token_to_str(t.type_);
  }
  o << ":[" << KRED << ::string_utils::repr_string(x) << RST << "]";
  return o;
}
static void test_block_analyzer_yaka_file(const std::string &A, std::string B,
                                          const std::string &C) {
  std::ifstream code_file(A);
  if (code_file.good()) {
    std::string code((std::istreambuf_iterator<char>(code_file)),
                     std::istreambuf_iterator<char>());
    try {
      gc_pool<token> token_pool{};
      yaksha::tokenizer tt(std::move(B), code, &token_pool);
      tt.tokenize();
      yaksha::block_analyzer t(tt.tokens_, &token_pool);
      t.analyze();
      auto token_snapshot = yaksha::load_token_dump(C, &token_pool);
      yaksha::save_token_dump(C, t.tokens_);
      REQUIRE(t.tokens_.size() == token_snapshot.size());
      for (int i = 0; i < token_snapshot.size(); i++) {
        auto parsed = t.tokens_[i];
        auto snapshot = token_snapshot[i];
        REQUIRE(parsed->file_ == snapshot->file_);
        REQUIRE(parsed->line_ == snapshot->line_);
        REQUIRE(parsed->pos_ == snapshot->pos_);
        REQUIRE(parsed->token_ == snapshot->token_);
        REQUIRE(parsed->type_ == snapshot->type_);
      }
    } catch (parsing_error &e) {
      DBGPRINT(e.message_);
      REQUIRE(false);
    }
  } else {
    REQUIRE(false);
  }
}
TEST_CASE("block_analyzer: Test block_analyzer_test.py") {
  test_block_analyzer_yaka_file(
      "../test_data/block_analyzer_test.py", "block_analyzer_test.py",
      "../test_data/block_analyzer_test.py.block_tokens");
}
TEST_CASE("block_analyzer: Test weird_file.py") {
  test_block_analyzer_yaka_file("../test_data/weird_file.py", "weird_file.py",
                                "../test_data/weird_file.py.block_tokens");
}
