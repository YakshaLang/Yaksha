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
// ----------------------------------- Tests -----------------------------------
//
#include "btest.h"
#include "catch2/catch.hpp"
#include "file_formats/tokens_file.h"
#include <utility>
using namespace yaksha;
#define TOK_REQUIRE(POS, TEXT, TYPE)                                           \
  do {                                                                         \
    REQUIRE(t.tokens_[POS]->token_ == (TEXT));                                 \
    REQUIRE(t.tokens_[POS]->type_ == (TYPE));                                  \
  } while (0)
static void test_tokenizer_yaka_file(const std::string &A, std::string B,
                                     const std::string &C) {
  std::ifstream code_file(A);
  if (code_file.good()) {
    std::string code((std::istreambuf_iterator<char>(code_file)),
                     std::istreambuf_iterator<char>());
    try {
      gc_pool<token> token_pool{};
      yaksha::tokenizer t(std::move(B), code, &token_pool);
      t.tokenize();
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
TEST_CASE("tokenizer: Names: Basic") {
  gc_pool<token> token_pool{};
  yaksha::tokenizer t("test.py", "a banana b aaaaa ", &token_pool);
  t.tokenize();
  REQUIRE(t.tokens_.size() == 4 + 1);
  REQUIRE(t.tokens_[0]->token_ == "a");
  REQUIRE(t.tokens_[0]->type_ == token_type::NAME);
  REQUIRE(t.tokens_[1]->token_ == "banana");
  REQUIRE(t.tokens_[2]->token_ == "b");
  REQUIRE(t.tokens_[3]->token_ == "aaaaa");
  REQUIRE(t.errors_.empty());
}
TEST_CASE("tokenizer: Names: With symbols") {
  gc_pool<token> token_pool{};
  yaksha::tokenizer t("test.py", "a + banana + aaaaa", &token_pool);
  t.tokenize();
  REQUIRE(t.tokens_.size() == 5 + 1);
  REQUIRE(t.tokens_[0]->token_ == "a");
  REQUIRE(t.tokens_[0]->type_ == token_type::NAME);
  REQUIRE(t.tokens_[1]->token_ == "+");
  REQUIRE(t.tokens_[1]->type_ == token_type::PLUS);
  REQUIRE(t.tokens_[2]->token_ == "banana");
  REQUIRE(t.tokens_[2]->type_ == token_type::NAME);
  REQUIRE(t.tokens_[3]->token_ == "+");
  REQUIRE(t.tokens_[4]->token_ == "aaaaa");
  REQUIRE(t.tokens_[4]->type_ == token_type::NAME);
  REQUIRE(t.errors_.empty());
}
TEST_CASE("tokenizer: Indentation") {
  gc_pool<token> token_pool{};
  yaksha::tokenizer t("test.py", "a\n    banana + aaaaa ", &token_pool);
  t.tokenize();
  REQUIRE(t.tokens_.size() == 6 + 1);
  REQUIRE(t.tokens_[0]->token_ == "a");
  REQUIRE(t.tokens_[0]->type_ == token_type::NAME);
  REQUIRE(t.tokens_[1]->token_ == "\n");
  REQUIRE(t.tokens_[1]->type_ == token_type::NEW_LINE);
  REQUIRE(t.tokens_[2]->token_ == "    ");
  REQUIRE(t.tokens_[2]->type_ == token_type::INDENT);
  REQUIRE(t.tokens_[3]->token_ == "banana");
  REQUIRE(t.tokens_[3]->type_ == token_type::NAME);
  REQUIRE(t.tokens_[4]->token_ == "+");
  REQUIRE(t.tokens_[4]->type_ == token_type::PLUS);
  REQUIRE(t.tokens_[5]->token_ == "aaaaa");
  REQUIRE(t.tokens_[5]->type_ == token_type::NAME);
  REQUIRE(t.errors_.empty());
}
TEST_CASE("tokenizer: Indentation: Mixed") {
  gc_pool<token> token_pool{};
  yaksha::tokenizer t("test.py", "a\n \t   banana + aaaaa ", &token_pool);
  t.tokenize();
  REQUIRE(t.tokens_.size() == 6 + 1);
  REQUIRE(t.tokens_[0]->token_ == "a");
  REQUIRE(t.tokens_[0]->type_ == token_type::NAME);
  REQUIRE(t.tokens_[1]->token_ == "\n");
  REQUIRE(t.tokens_[1]->type_ == token_type::NEW_LINE);
  REQUIRE(t.tokens_[2]->token_ == " \t   ");
  REQUIRE(t.tokens_[2]->type_ == token_type::INDENT);
  REQUIRE(t.tokens_[3]->token_ == "banana");
  REQUIRE(t.tokens_[3]->type_ == token_type::NAME);
  REQUIRE(t.tokens_[4]->token_ == "+");
  REQUIRE(t.tokens_[4]->type_ == token_type::PLUS);
  REQUIRE(t.tokens_[5]->token_ == "aaaaa");
  REQUIRE(t.tokens_[5]->type_ == token_type::NAME);
  REQUIRE(t.errors_.empty());
}
TEST_CASE("tokenizer: Symbols: Basic") {
  gc_pool<token> token_pool{};
  yaksha::tokenizer t("test.py", "@ : ( ) < = > | + - * / & ^ % , [ ] { }",
                      &token_pool);
  t.tokenize();
  REQUIRE(t.tokens_.size() == 20 + 1);
  TOK_REQUIRE(0, "@", token_type::AT);
  TOK_REQUIRE(1, ":", token_type::COLON);
  TOK_REQUIRE(2, "(", token_type::PAREN_OPEN);
  TOK_REQUIRE(3, ")", token_type::PAREN_CLOSE);
  TOK_REQUIRE(4, "<", token_type::LESS);
  TOK_REQUIRE(5, "=", token_type::EQ);
  TOK_REQUIRE(6, ">", token_type::GREAT);
  TOK_REQUIRE(7, "|", token_type::OR);
  TOK_REQUIRE(8, "+", token_type::PLUS);
  TOK_REQUIRE(9, "-", token_type::SUB);
  TOK_REQUIRE(10, "*", token_type::MUL);
  TOK_REQUIRE(11, "/", token_type::DIV);
  TOK_REQUIRE(12, "&", token_type::AND);
  TOK_REQUIRE(13, "^", token_type::XOR);
  TOK_REQUIRE(14, "%", token_type::MOD);
  TOK_REQUIRE(15, ",", token_type::COMMA);
  TOK_REQUIRE(16, "[", token_type::SQUARE_BRACKET_OPEN);
  TOK_REQUIRE(17, "]", token_type::SQUARE_BRACKET_CLOSE);
  TOK_REQUIRE(18, "{", token_type::CURLY_BRACKET_OPEN);
  TOK_REQUIRE(19, "}", token_type::CURLY_BRACKET_CLOSE);
  REQUIRE(t.errors_.empty());
}
TEST_CASE("tokenizer: Symbols: Multi character symbols") {
  gc_pool<token> token_pool{};
  yaksha::tokenizer t("test.py",
                      "<= == >= |= += -= *= /= &= ^= %= ** **= // //= ... ->",
                      &token_pool);
  t.tokenize();
  REQUIRE(t.tokens_.size() == 17 + 1);
  TOK_REQUIRE(0, "<=", token_type::LESS_EQ);
  TOK_REQUIRE(1, "==", token_type::EQ_EQ);
  TOK_REQUIRE(2, ">=", token_type::GREAT_EQ);
  TOK_REQUIRE(3, "|=", token_type::OR_EQ);
  TOK_REQUIRE(4, "+=", token_type::PLUS_EQ);
  TOK_REQUIRE(5, "-=", token_type::SUB_EQ);
  TOK_REQUIRE(6, "*=", token_type::MUL_EQ);
  TOK_REQUIRE(7, "/=", token_type::DIV_EQ);
  TOK_REQUIRE(8, "&=", token_type::AND_EQ);
  TOK_REQUIRE(9, "^=", token_type::XOR_EQ);
  TOK_REQUIRE(10, "%=", token_type::MOD_EQ);
  TOK_REQUIRE(11, "**", token_type::POWER);
  TOK_REQUIRE(12, "**=", token_type::POWER_EQ);
  TOK_REQUIRE(13, "//", token_type::INT_DIV);
  TOK_REQUIRE(14, "//=", token_type::INT_DIV_EQ);
  TOK_REQUIRE(15, "...", token_type::ELLIPSIS);
  TOK_REQUIRE(16, "->", token_type::ARROW);
  REQUIRE(t.errors_.empty());
}
TEST_CASE("tokenizer: String: Basic") {
  gc_pool<token> token_pool{};
  yaksha::tokenizer t("test.py", "a = \"banana\"", &token_pool);
  t.tokenize();
  REQUIRE(t.tokens_.size() == 3 + 1);
  REQUIRE(t.tokens_[0]->token_ == "a");
  REQUIRE(t.tokens_[0]->type_ == token_type::NAME);
  REQUIRE(t.tokens_[1]->token_ == "=");
  REQUIRE(t.tokens_[1]->type_ == token_type::EQ);
  REQUIRE(t.tokens_[2]->token_ == "banana");
  REQUIRE(t.tokens_[2]->type_ == token_type::STRING);
  REQUIRE(t.errors_.empty());
}
TEST_CASE("tokenizer: String: With escape") {
  gc_pool<token> token_pool{};
  yaksha::tokenizer t("test.py", R"(a = "\"ban\"ana\"")", &token_pool);
  t.tokenize();
  REQUIRE(t.tokens_.size() == 3 + 1);
  REQUIRE(t.tokens_[0]->token_ == "a");
  REQUIRE(t.tokens_[0]->type_ == token_type::NAME);
  REQUIRE(t.tokens_[1]->token_ == "=");
  REQUIRE(t.tokens_[1]->type_ == token_type::EQ);
  REQUIRE(t.tokens_[2]->token_ == "\\\"ban\\\"ana\\\"");
  REQUIRE(t.tokens_[2]->type_ == token_type::STRING);
  REQUIRE(t.errors_.empty());
}
TEST_CASE("tokenizer: String: End with escaped") {
  gc_pool<token> token_pool{};
  yaksha::tokenizer t("test.py", R"(a = "\"ban\"ana\")", &token_pool);
  t.tokenize();
  REQUIRE(!t.errors_.empty());
  REQUIRE(t.errors_[0].tok_.file_ == "test.py");
  REQUIRE(t.errors_[0].tok_.line_ == 0);
}
TEST_CASE("tokenizer: String: End with new line") {
  gc_pool<token> token_pool{};
  yaksha::tokenizer t("test.py", "a = \"\n", &token_pool);
  t.tokenize();
  REQUIRE(t.errors_.size() == 1);
  REQUIRE(t.errors_[0].message_ ==
          "Tokenizer Error : Invalid string, new line detected "
          "while parsing string");
}
TEST_CASE("tokenizer: String: Does not end") {
  gc_pool<token> token_pool{};
  yaksha::tokenizer t("test.py", "a = \"", &token_pool);
  t.tokenize();
  REQUIRE(t.errors_.size() == 1);
  REQUIRE(t.errors_[0].message_ == "Tokenizer Error : Invalid end of file");
}
TEST_CASE("tokenizer: String: Does not end after another string") {
  gc_pool<token> token_pool{};
  yaksha::tokenizer t("test.py", R"(a = "\"ban\"ana\""")", &token_pool);
  t.tokenize();
  DBGPRINT(t.tokens_.size());
  DBGPRINT(t.tokens_[0]->token_);
  DBGPRINT(t.tokens_[1]->token_);
  DBGPRINT(t.tokens_[2]->token_);
  REQUIRE(!t.errors_.empty());
}
TEST_CASE("tokenizer: String: Empty string") {
  gc_pool<token> token_pool{};
  yaksha::tokenizer t("test.py", "a = \"\"", &token_pool);
  t.tokenize();
  REQUIRE(t.tokens_.size() == 3 + 1);
  REQUIRE(t.tokens_[2]->token_.empty());
  REQUIRE(t.tokens_[2]->type_ == token_type::STRING);
}
TEST_CASE("tokenizer: Numbers: single number") {
  gc_pool<token> token_pool{};
  yaksha::tokenizer t("test.py", "123", &token_pool);
  t.tokenize();
  REQUIRE(t.tokens_.size() == 1 + 1);
  REQUIRE(t.tokens_[0]->token_ == "123");
  REQUIRE(t.tokens_[0]->type_ == token_type::INTEGER_DECIMAL);
  REQUIRE(t.errors_.empty());
}
TEST_CASE("tokenizer: Numbers: Bunch of numbers") {
  gc_pool<token> token_pool{};
  yaksha::tokenizer t("test.py",
                      "0xABCDEF0 0b1111001 "
                      "0o123456 1.2e3 123 1.2e+3 1.2e-3 1f 1.2f 1.2e1f",
                      &token_pool);
  t.tokenize();
  REQUIRE(t.tokens_.size() == 10 + 1);
  REQUIRE(t.tokens_[0]->token_ == "0xABCDEF0");
  REQUIRE(t.tokens_[0]->type_ == token_type::INTEGER_HEX);
  REQUIRE(t.tokens_[1]->token_ == "0b1111001");
  REQUIRE(t.tokens_[1]->type_ == token_type::INTEGER_BIN);
  REQUIRE(t.tokens_[2]->token_ == "0o123456");
  REQUIRE(t.tokens_[2]->type_ == token_type::INTEGER_OCT);
  REQUIRE(t.tokens_[3]->token_ == "1.2e3");
  REQUIRE(t.tokens_[3]->type_ == token_type::DOUBLE_NUMBER);
  REQUIRE(t.tokens_[4]->token_ == "123");
  REQUIRE(t.tokens_[4]->type_ == token_type::INTEGER_DECIMAL);
  REQUIRE(t.tokens_[5]->token_ == "1.2e+3");
  REQUIRE(t.tokens_[5]->type_ == token_type::DOUBLE_NUMBER);
  REQUIRE(t.tokens_[6]->token_ == "1.2e-3");
  REQUIRE(t.tokens_[6]->type_ == token_type::DOUBLE_NUMBER);
  REQUIRE(t.tokens_[7]->token_ == "1f");
  REQUIRE(t.tokens_[7]->type_ == token_type::FLOAT_NUMBER);
  REQUIRE(t.tokens_[8]->token_ == "1.2f");
  REQUIRE(t.tokens_[8]->type_ == token_type::FLOAT_NUMBER);
  REQUIRE(t.tokens_[9]->token_ == "1.2e1f");
  REQUIRE(t.tokens_[9]->type_ == token_type::FLOAT_NUMBER);
  REQUIRE(t.errors_.empty());
}
TEST_CASE("tokenizer: Comment: Basic") {
  gc_pool<token> token_pool{};
  yaksha::tokenizer t("test.py", R"(a = "" # Hello World "")", &token_pool);
  t.tokenize();
  REQUIRE(t.tokens_.size() == 4 + 1);
  REQUIRE(t.tokens_[3]->token_ == " Hello World \"\"");
  REQUIRE(t.tokens_[3]->type_ == token_type::COMMENT);
  REQUIRE(t.errors_.empty());
}
TEST_CASE("tokenizer: Comment: Two lines") {
  gc_pool<token> token_pool{};
  yaksha::tokenizer t("test.py", "a = \"\" # Hello\n# World", &token_pool);
  t.tokenize();
  REQUIRE(t.tokens_.size() == 6 + 1);
  REQUIRE(t.tokens_[3]->token_ == " Hello");
  REQUIRE(t.tokens_[3]->type_ == token_type::COMMENT);
  REQUIRE(t.tokens_[4]->token_ == "\n");
  REQUIRE(t.tokens_[4]->type_ == token_type::NEW_LINE);
  REQUIRE(t.tokens_[5]->token_ == " World");
  REQUIRE(t.tokens_[5]->type_ == token_type::COMMENT);
  REQUIRE(t.errors_.empty());
}
TEST_CASE("tokenizer: Parse test_vector_add.py") {
  test_tokenizer_yaka_file("../test_data/test_vector_add.py",
                           "test_vector_add.py",
                           "../test_data/test_vector_add.py.tokens");
}
TEST_CASE("tokenizer: Parse unicode_test.py") {
  test_tokenizer_yaka_file("../test_data/unicode_test.py", "unicode_test.py",
                           "../test_data/unicode_test.py.tokens");
}
TEST_CASE("tokenizer: Parse bad_test.py") {
  test_tokenizer_yaka_file("../test_data/bad_test.py", "bad_test.py",
                           "../test_data/bad_test.py.tokens");
}
