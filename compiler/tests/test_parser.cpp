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
#include "ast/ast_printer.h"
#include "ast/parser.h"
#include "btest.h"
#include "catch2/catch.hpp"
#include "compiler/codegen_c.h"
#include "compiler/multifile_compiler.h"
#include "tokenizer/block_analyzer.h"
#include "tokenizer/tokenizer.h"
#include "utilities/error_printer.h"
#include <utility>
using namespace yaksha;
static void test_parser_yaka_file(const std::string &yaka_code_file_input) {
  std::filesystem::path code_file_path{yaka_code_file_input};
  std::string code_filename = code_file_path.filename().string();
  std::string snapshot_filename = yaka_code_file_input + ".ast.l";
  std::ifstream code_file(yaka_code_file_input);
  if (code_file.good()) {
    std::string code((std::istreambuf_iterator<char>(code_file)),
                     std::istreambuf_iterator<char>());
    try {
      gc_pool<token> token_pool{};
      yaksha::tokenizer t(std::move(code_filename), code, &token_pool);
      t.tokenize();
      REQUIRE(t.errors_.empty());
      block_analyzer b{t.tokens_, &token_pool};
      b.analyze();
      ykdt_pool dt_pool{};
      parser p{yaka_code_file_input, b.tokens_, &dt_pool};
      auto tree = p.parse();
      REQUIRE(!tree.empty());
      REQUIRE(p.errors_.empty());
      ast_printer prn{};
      // -------------------------------------------------------------------
      // AST tokens dump in memory
      auto ast_out = prn.print_to_str(tree);
      tokenizer lsp_code{"ast_out.l", ast_out, &token_pool};
      lsp_code.tokenize();
      // -------------------------------------------------------------------
      // AST tokens from snapshot
      auto snapshot_code = read_file(snapshot_filename);
#ifdef YAKSHA_OS_WINDOWS
      // fix windows line endings
      // (git might covert line endings to CRLF)
      replace_all(snapshot_code, "\r\n", "\n");
#endif
      tokenizer snapshot_code_tokenizer{"ast_out.l", snapshot_code,
                                        &token_pool};
      snapshot_code_tokenizer.tokenize();
      auto token_snapshot = snapshot_code_tokenizer.tokens_;
      // Save current tokens
      write_file(ast_out, snapshot_filename);
      // -------------------------------------------------------------------
      REQUIRE(lsp_code.tokens_.size() == token_snapshot.size());
      for (int i = 0; i < token_snapshot.size(); i++) {
        auto parsed = lsp_code.tokens_[i];
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
static void TEST_SNIPPET_FULL(const std::string &S, const std::string &E) {
  multifile_compiler mc{};
  codegen_c cg{};
  const std::string &xa = S;
  auto result = mc.compile(xa, true, "dummy.yaka", ".", &cg);
  REQUIRE(result.failed_ == true);
  REQUIRE(!yaksha::errors::error_capture.empty());
  REQUIRE(yaksha::errors::has_error(E));
}
static void TEST_SNIPPET_FULL_OK(const std::string &S) {
  multifile_compiler mc{};
  codegen_c cg{};
  const std::string &xa = S;
  auto result = mc.compile(xa, true, "dummy.yaka", ".", &cg);
  REQUIRE(result.failed_ == false);
  REQUIRE(yaksha::errors::error_capture.empty());
}
TEST_CASE("parser: Hello World") {
  test_parser_yaka_file("../test_data/compiler_tests/test1.yaka");
}
TEST_CASE("parser: Defer") {
  test_parser_yaka_file("../test_data/compiler_tests/test2.yaka");
}
TEST_CASE("parser: Class support") {
  test_parser_yaka_file("../test_data/compiler_tests/test3.yaka");
}
TEST_CASE("parser: Create object from class") {
  test_parser_yaka_file("../test_data/compiler_tests/test4.yaka");
}
TEST_CASE("parser: Object members") {
  test_parser_yaka_file("../test_data/compiler_tests/test5.yaka");
}
TEST_CASE("parser: Array access") {
  test_parser_yaka_file("../test_data/compiler_tests/test6.yaka");
}
TEST_CASE("parser: Nested array access") {
  test_parser_yaka_file("../test_data/compiler_tests/test7.yaka");
}
TEST_CASE("parser: Void function") {
  test_parser_yaka_file("../test_data/compiler_tests/voidfunc.yaka");
}
TEST_CASE("parser: Native functions") {
  test_parser_yaka_file("../test_data/compiler_tests/nativefunc.yaka");
}
TEST_CASE("parser: Unicode test") {
  test_parser_yaka_file("../test_data/unicode_test.py");
}
TEST_CASE("parser: Negative numbers") {
  test_parser_yaka_file("../test_data/sample_negative_numbers.yaka");
}
TEST_CASE("parser: break used outside loop") {
  TEST_SNIPPET_FULL("def main() -> int:\n"
                    "    break\n"
                    "    b: bool = False\n"
                    "    return 0",
                    "Invalid assignment target!");
}
TEST_CASE("parser: continue used outside loop") {
  TEST_SNIPPET_FULL("continue\n"
                    "def main() -> int:\n"
                    "    c: bool = False\n"
                    "    return 0",
                    "Invalid assignment target!");
}
TEST_CASE("parser: def in def") {
  TEST_SNIPPET_FULL("def main() -> int:\n"
                    "    def x() -> None:\n"
                    "        pass\n"
                    "    c: bool = False\n"
                    "    return 0",
                    "Blocks with nested import/def/class is not supported");
}
TEST_CASE("parser: class in def") {
  TEST_SNIPPET_FULL("def main() -> int:\n"
                    "    class X:\n"
                    "        a: int\n"
                    "    c: bool = False\n"
                    "    return 0",
                    "Blocks with nested import/def/class is not supported");
}
TEST_CASE("parser: mini blocks") {
  test_parser_yaka_file("../test_data/compiler_tests/smallest.yaka");
}
TEST_CASE("parser: parse FixedArr") {
  TEST_SNIPPET_FULL_OK("def main() -> int:\n"
                       "    a: FixedArr[int, 10]\n"
                       "    return 0");
}
TEST_CASE("parser: parse FixedArr with non integer size") {
  TEST_SNIPPET_FULL("def main() -> int:\n"
                    "    a: FixedArr[int, str]\n"
                    "    return 0",
                    "FixedArr must have a data type argument and a dimension "
                    "arg. Example: FixedArr[i8, 10]");
}
TEST_CASE("parser: parse FixedArr with integer as first arg") {
  TEST_SNIPPET_FULL("def main() -> int:\n"
                    "    a: FixedArr[10, 10]\n"
                    "    return 0",
                    "FixedArr must have a data type argument and a dimension "
                    "arg. Example: FixedArr[i8, 10]");
}
TEST_CASE("parser: parse FixedArr with MEntry") {
  TEST_SNIPPET_FULL(
      "def main() -> int:\n"
      "    a: FixedArr[MEntry[int, int], 3]\n"
      "    return 0",
      "FixedArr cannot have a SMEntry/MEntry as the data type argument.");
}
TEST_CASE("parser: function trying to return a FixedArr") {
  TEST_SNIPPET_FULL("def bad() -> FixedArr[int, 10]:\n"
                    "    a: FixedArr[int, 10]\n"
                    "    return a\n"
                    "def main() -> int:\n"
                    "    return 0",
                    "Functions cannot return fixed size arrays. Use Array or "
                    "wrap in a Tuple.");
}
TEST_CASE("parser: function data type returns FixedArr") {
  TEST_SNIPPET_FULL("def main() -> int:\n"
                    "    a: Function[In[int], Out[FixedArr[int, 10]]]\n"
                    "    return 0",
                    "A function cannot return a fixed size array. Use Array or "
                    "wrap in a Tuple.");
}
