#include "ast/ast_printer.h"
#include "ast/parser.h"
#include "btest.h"
#include "catch2/catch.hpp"
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
        ykdt_pool dt_pool{};                                                   \
        parser p{b.tokens_, &dt_pool};                                         \
        auto tree = p.parse();                                                 \
        REQUIRE(!tree.empty());                                                \
        REQUIRE(p.errors_.empty());                                            \
        ast_printer prn{};                                                     \
        auto ast_out = prn.print_to_str(tree);                                 \
        tokenizer lsp_code{"ast_out.l", ast_out};                              \
        lsp_code.tokenize();                                                   \
        auto token_snapshot = yaksha::load_token_dump(C);                      \
        yaksha::save_token_dump(C, lsp_code.tokens_);                          \
        REQUIRE(lsp_code.tokens_.size() == token_snapshot.size());             \
        for (int i = 0; i < token_snapshot.size(); i++) {                      \
          auto parsed = lsp_code.tokens_[i];                                   \
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
TEST_CASE("parser: Hello World") {
  TEST_FILE("../test_data/compiler_tests/test1.yaka", "test1.yaka",
            "../test_data/compiler_tests/test1.ast.tokens");
}
TEST_CASE("parser: Defer") {
  TEST_FILE("../test_data/compiler_tests/test2.yaka", "test2.yaka",
            "../test_data/compiler_tests/test2.ast.tokens");
}
TEST_CASE("parser: Class support") {
  TEST_FILE("../test_data/compiler_tests/test3.yaka", "test3.yaka",
            "../test_data/compiler_tests/test3.ast.tokens");
}
TEST_CASE("parser: Create object from class") {
  TEST_FILE("../test_data/compiler_tests/test4.yaka", "test4.yaka",
            "../test_data/compiler_tests/test4.ast.tokens");
}
TEST_CASE("parser: Object members") {
  TEST_FILE("../test_data/compiler_tests/test5.yaka", "test5.yaka",
            "../test_data/compiler_tests/test5.ast.tokens");
}
TEST_CASE("parser: Array access") {
  TEST_FILE("../test_data/compiler_tests/test6.yaka", "test6.yaka",
            "../test_data/compiler_tests/test6.ast.tokens");
}
TEST_CASE("parser: Nested array access") {
  TEST_FILE("../test_data/compiler_tests/test7.yaka", "test7.yaka",
            "../test_data/compiler_tests/test7.ast.tokens");
}
TEST_CASE("parser: Void function") {
  TEST_FILE("../test_data/compiler_tests/voidfunc.yaka", "voidfunc.yaka",
            "../test_data/compiler_tests/voidfunc.ast.tokens");
}
TEST_CASE("parser: Native functions") {
  TEST_FILE("../test_data/compiler_tests/nativefunc.yaka", "nativefunc.yaka",
            "../test_data/compiler_tests/nativefunc.ast.tokens");
}
TEST_CASE("parser: Unicode test") {
  TEST_FILE("../test_data/unicode_test.py", "unicode_test.py",
            "../test_data/unicode_test.py.ast.tokens");
}
TEST_CASE("parser: Negative numbers") {
  TEST_FILE("../test_data/sample_negative_numbers.yaka", "sample_negative_numbers.yaka",
            "../test_data/sample_negative_numbers.yaka.ast.tokens");
}
