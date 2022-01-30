#include "ast/parser.h"
#include "btest.h"
#include "catch2/catch.hpp"
#include "compiler/compiler.h"
#include "compiler/type_checker.h"
#include "file_formats/tokens_file.h"
#include "tokenizer/block_analyzer.h"
#include "tokenizer/tokenizer.h"
using namespace yaksha;
#define TEST_FILE(A, B, C)                                                     \
  do {                                                                         \
    std::ifstream code_file(A);                                                \
    if (code_file.good()) {                                                    \
      std::string code((std::istreambuf_iterator<char>(code_file)),            \
                       std::istreambuf_iterator<char>());                      \
      try {                                                                    \
        yaksha::tokenizer t(B, code);                                          \
        t.tokenize();                                                          \
        REQUIRE(t.errors_.empty());                                            \
        block_analyzer b{t.tokens_};                                           \
        b.analyze();                                                           \
        parser p{b.tokens_};                                                   \
        auto tree = p.parse();                                                 \
        REQUIRE(!tree.empty());                                                \
        REQUIRE(p.errors_.empty());                                            \
        type_checker tc{};                                                     \
        tc.check(tree);                                                        \
        REQUIRE(tc.errors_.empty());                                           \
        compiler comp{tc.functions_};                                          \
        auto compiler_output = comp.compile(tree);                             \
        tokenizer c_code{"output.c", compiler_output};                         \
        c_code.tokenize();                                                     \
        auto token_snapshot = yaksha::load_token_dump(C);                      \
        REQUIRE(c_code.tokens_.size() == token_snapshot.size());               \
        for (int i = 0; i < token_snapshot.size(); i++) {                      \
          auto parsed = c_code.tokens_[i];                                     \
          auto snapshot = token_snapshot[i];                                   \
          REQUIRE(parsed.file_ == snapshot.file_);                             \
          REQUIRE(parsed.line_ == snapshot.line_);                             \
          REQUIRE(parsed.pos_ == snapshot.pos_);                               \
          REQUIRE(parsed.token_ == snapshot.token_);                           \
          REQUIRE(parsed.type_ == snapshot.type_);                             \
        }                                                                      \
      } catch (parsing_error & e) {                                            \
        DBGPRINT(e.message_);                                                  \
        REQUIRE(false);                                                        \
      }                                                                        \
    } else {                                                                   \
      REQUIRE(false);                                                          \
    }                                                                          \
  } while (0)
TEST_CASE("compiler: Hello World") {
  TEST_FILE("../test_data/compiler_tests/test1.yaka", "test1.yaka",
            "../test_data/compiler_tests/test1.tokens");
}
TEST_CASE("compiler: Defer") {
  TEST_FILE("../test_data/compiler_tests/test2.yaka", "test2.yaka",
            "../test_data/compiler_tests/test2.tokens");
}
