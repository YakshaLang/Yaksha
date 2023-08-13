#include "btest.h"
#include "catch2/catch.hpp"
#include "ic2c/ic_tokenizer.h"
#include "utilities/cpp_util.h"
#include <iostream>
using namespace yaksha;
#if defined(IC_TOKENIZER_PRINT_TOKENS) || defined(SLOW_TESTS)
#include "file_formats/ic_tokens_file.h"
#include "tokenizer/string_utils.h"
#define TOKENS_PRINT()                                                         \
  do {                                                                         \
    for (auto const &to : t.tokens_) {                                         \
      if (to.token_.empty()) {                                                 \
        std::cout << "T_EMPTY(ic_token_type::" << ic_token_to_str(to.type_)    \
                  << ");\n";                                                   \
      } else {                                                                 \
        std::cout << "T_V(\"" << string_utils::escape(to.token_)               \
                  << "\", ic_token_type::" << ic_token_to_str(to.type_)        \
                  << ");\n";                                                   \
      }                                                                        \
    }                                                                          \
  } while (0)
#else
#define TOKENS_PRINT()
#endif
#define TOKENS_BEGIN() int token_pos = -1
#define T_V(item, type)                                                        \
  do {                                                                         \
    REQUIRE(t.tokens_[++token_pos].token_ == item);                            \
    REQUIRE(t.tokens_[token_pos].type_ == type);                               \
  } while (0)
#define T_EMPTY(type)                                                          \
  do {                                                                         \
    REQUIRE(t.tokens_[++token_pos].token_.empty());                            \
    REQUIRE(t.tokens_[token_pos].type_ == type);                               \
  } while (0)
#define TOKENS_END()                                                           \
  do {                                                                         \
  } while (0)
#define TEST_FILE(A, B, C)                                                     \
  do {                                                                         \
    std::ifstream code_file(A);                                                \
    if (code_file.good()) {                                                    \
      std::string code((std::istreambuf_iterator<char>(code_file)),            \
                       std::istreambuf_iterator<char>());                      \
      try {                                                                    \
        yaksha::ic_tokenizer t(B, code);                                       \
        t.tokenize();                                                          \
        REQUIRE(t.errors_.empty());                                            \
        auto token_snapshot = yaksha::ic_load_token_dump(C);                   \
        yaksha::ic_save_token_dump(C, t.tokens_);                              \
        REQUIRE(t.tokens_.size() == token_snapshot.size());                    \
        for (int i = 0; i < token_snapshot.size(); i++) {                      \
          auto parsed = t.tokens_[i];                                          \
          auto snapshot = token_snapshot[i];                                   \
          REQUIRE(parsed.file_ == snapshot.file_);                             \
          REQUIRE(parsed.line_ == snapshot.line_);                             \
          REQUIRE(parsed.pos_ == snapshot.pos_);                               \
          REQUIRE(parsed.token_ == snapshot.token_);                           \
          REQUIRE(parsed.type_ == snapshot.type_);                             \
          REQUIRE(parsed.itype_ == snapshot.itype_);                           \
          REQUIRE(parsed.ibase_ == snapshot.ibase_);                           \
          REQUIRE(parsed.stype_ == snapshot.stype_);                           \
          REQUIRE(parsed.ftype_ == snapshot.ftype_);                           \
        }                                                                      \
      } catch (ic_parsing_error & e) {                                         \
        DBGPRINT(e.message_);                                                  \
        REQUIRE(false);                                                        \
      }                                                                        \
    } else {                                                                   \
      REQUIRE(false);                                                          \
    }                                                                          \
  } while (0)
TEST_CASE("ic_tokenizer: Simple file") {
  yaksha::ic_tokenizer t("test.c", "void main() { return 0; }");
  t.tokenize();
  REQUIRE(t.tokens_.size() == 9 + 2);
  TOKENS_BEGIN();
  T_V("void", ic_token_type::IDENTIFIER);
  T_V("main", ic_token_type::IDENTIFIER);
  T_V("(", ic_token_type::OPEN_PAREN);
  T_V(")", ic_token_type::CLOSE_PAREN);
  T_V("{", ic_token_type::OPEN_CURLY);
  T_V("return", ic_token_type::IDENTIFIER);
  T_V("0", ic_token_type::INTEGER_CONSTANT);
  T_V(";", ic_token_type::SEMICOLON);
  T_V("}", ic_token_type::CLOSE_CURLY);
  T_V("\n", ic_token_type::NEWLINE);
  T_EMPTY(ic_token_type::TC_EOF);
  TOKENS_END();
  REQUIRE(t.errors_.empty());
}
// Below example is obtained from here --> https://en.wikipedia.org/wiki/Digraphs_and_trigraphs
// Notice that ? mark is escaped below ! so trigraph is preserved in the string
// So I can see if it works as expected
// We can also disable the trigraph support if needed.
TEST_CASE("ic_tokenizer: Trigraphs + Line splicer return 1 test") {
  yaksha::ic_tokenizer t("test.c", "int trigraphsavailable() // returns 0 or "
                                   "1; language standard C99 or later\n"
                                   "{\n"
                                   "\t// are trigraphs available\?\?/\n"
                                   "\treturn 0;\n"
                                   "\treturn 1;\n"
                                   "}");
  t.tokenize();
  TOKENS_PRINT();
  REQUIRE(t.tokens_.size() == 13 + 2);
  TOKENS_BEGIN();
  T_V("int", ic_token_type::IDENTIFIER);
  T_V("trigraphsavailable", ic_token_type::IDENTIFIER);
  T_V("(", ic_token_type::OPEN_PAREN);
  T_V(")", ic_token_type::CLOSE_PAREN);
  T_V("\n", ic_token_type::NEWLINE);
  T_V("{", ic_token_type::OPEN_CURLY);
  T_V("\n", ic_token_type::NEWLINE);
  T_V("\n", ic_token_type::NEWLINE);
  T_V("return", ic_token_type::IDENTIFIER);
  T_V("1", ic_token_type::INTEGER_CONSTANT);
  T_V(";", ic_token_type::SEMICOLON);
  T_V("\n", ic_token_type::NEWLINE);
  T_V("}", ic_token_type::CLOSE_CURLY);
  T_V("\n", ic_token_type::NEWLINE);
  T_EMPTY(ic_token_type::TC_EOF);
  TOKENS_END();
  REQUIRE(t.errors_.empty());
}
TEST_CASE("ic_tokenizer: Simple string escape - single slash") {
  yaksha::ic_tokenizer t("test.c", R"("\\")");
  t.tokenize();
  REQUIRE(t.tokens_.size() == 1 + 2);
  TOKENS_BEGIN();
  T_V("\\\\", ic_token_type::STRING_LITERAL);
  T_V("\n", ic_token_type::NEWLINE);
  T_EMPTY(ic_token_type::TC_EOF);
  TOKENS_END();
  REQUIRE(t.errors_.empty());
}
TEST_CASE("ic_tokenizer: Single character string / char literals") {
  yaksha::ic_tokenizer t("test.c", "void main() {"
                                   " char x1 =  'b';"
                                   " char x2 = L';';"
                                   " char* y1 = u8\"W\";"
                                   " char* y2 =  u\"A\";"
                                   " char* y3 =  U\"S\";"
                                   " char* y4 =  L\"D\";"
                                   " return 0; "
                                   "}");
  t.tokenize();
  TOKENS_PRINT();
  REQUIRE(t.tokens_.size() == 45);
  TOKENS_BEGIN();
  T_V("void", ic_token_type::IDENTIFIER);
  T_V("main", ic_token_type::IDENTIFIER);
  T_V("(", ic_token_type::OPEN_PAREN);
  T_V(")", ic_token_type::CLOSE_PAREN);
  T_V("{", ic_token_type::OPEN_CURLY);
  T_V("char", ic_token_type::IDENTIFIER);
  T_V("x1", ic_token_type::IDENTIFIER);
  T_V("=", ic_token_type::EQ);
  T_V("b", ic_token_type::INTEGER_CONSTANT);
  T_V(";", ic_token_type::SEMICOLON);
  T_V("char", ic_token_type::IDENTIFIER);
  T_V("x2", ic_token_type::IDENTIFIER);
  T_V("=", ic_token_type::EQ);
  T_V(";", ic_token_type::INTEGER_CONSTANT);
  T_V(";", ic_token_type::SEMICOLON);
  T_V("char", ic_token_type::IDENTIFIER);
  T_V("*", ic_token_type::MUL);
  T_V("y1", ic_token_type::IDENTIFIER);
  T_V("=", ic_token_type::EQ);
  T_V("W", ic_token_type::STRING_LITERAL);
  T_V(";", ic_token_type::SEMICOLON);
  T_V("char", ic_token_type::IDENTIFIER);
  T_V("*", ic_token_type::MUL);
  T_V("y2", ic_token_type::IDENTIFIER);
  T_V("=", ic_token_type::EQ);
  T_V("A", ic_token_type::STRING_LITERAL);
  T_V(";", ic_token_type::SEMICOLON);
  T_V("char", ic_token_type::IDENTIFIER);
  T_V("*", ic_token_type::MUL);
  T_V("y3", ic_token_type::IDENTIFIER);
  T_V("=", ic_token_type::EQ);
  T_V("S", ic_token_type::STRING_LITERAL);
  T_V(";", ic_token_type::SEMICOLON);
  T_V("char", ic_token_type::IDENTIFIER);
  T_V("*", ic_token_type::MUL);
  T_V("y4", ic_token_type::IDENTIFIER);
  T_V("=", ic_token_type::EQ);
  T_V("D", ic_token_type::STRING_LITERAL);
  T_V(";", ic_token_type::SEMICOLON);
  T_V("return", ic_token_type::IDENTIFIER);
  T_V("0", ic_token_type::INTEGER_CONSTANT);
  T_V(";", ic_token_type::SEMICOLON);
  T_V("}", ic_token_type::CLOSE_CURLY);
  T_V("\n", ic_token_type::NEWLINE);
  T_EMPTY(ic_token_type::TC_EOF);
  TOKENS_END();
  REQUIRE(t.errors_.empty());
}
TEST_CASE("ic_tokenizer: Empty character string / char literals") {
  yaksha::ic_tokenizer t("test.c", "void main() {"
                                   " char x1 =  '';"
                                   " char x2 = L'';"
                                   " char* y1 = u8\"\";"
                                   " char* y2 =  u\"\";"
                                   " char* y3 =  U\"\";"
                                   " char* y4 =  L\"\";"
                                   " return 0; "
                                   "}");
  t.tokenize();
  TOKENS_PRINT();
  REQUIRE(t.tokens_.size() == 43);
  TOKENS_BEGIN();
  T_V("void", ic_token_type::IDENTIFIER);
  T_V("main", ic_token_type::IDENTIFIER);
  T_V("(", ic_token_type::OPEN_PAREN);
  T_V(")", ic_token_type::CLOSE_PAREN);
  T_V("{", ic_token_type::OPEN_CURLY);
  T_V("char", ic_token_type::IDENTIFIER);
  T_V("x1", ic_token_type::IDENTIFIER);
  T_V("=", ic_token_type::EQ);
  T_V(";", ic_token_type::SEMICOLON);
  T_V("char", ic_token_type::IDENTIFIER);
  T_V("x2", ic_token_type::IDENTIFIER);
  T_V("=", ic_token_type::EQ);
  T_V(";", ic_token_type::SEMICOLON);
  T_V("char", ic_token_type::IDENTIFIER);
  T_V("*", ic_token_type::MUL);
  T_V("y1", ic_token_type::IDENTIFIER);
  T_V("=", ic_token_type::EQ);
  T_EMPTY(ic_token_type::STRING_LITERAL);
  T_V(";", ic_token_type::SEMICOLON);
  T_V("char", ic_token_type::IDENTIFIER);
  T_V("*", ic_token_type::MUL);
  T_V("y2", ic_token_type::IDENTIFIER);
  T_V("=", ic_token_type::EQ);
  T_EMPTY(ic_token_type::STRING_LITERAL);
  T_V(";", ic_token_type::SEMICOLON);
  T_V("char", ic_token_type::IDENTIFIER);
  T_V("*", ic_token_type::MUL);
  T_V("y3", ic_token_type::IDENTIFIER);
  T_V("=", ic_token_type::EQ);
  T_EMPTY(ic_token_type::STRING_LITERAL);
  T_V(";", ic_token_type::SEMICOLON);
  T_V("char", ic_token_type::IDENTIFIER);
  T_V("*", ic_token_type::MUL);
  T_V("y4", ic_token_type::IDENTIFIER);
  T_V("=", ic_token_type::EQ);
  T_EMPTY(ic_token_type::STRING_LITERAL);
  T_V(";", ic_token_type::SEMICOLON);
  T_V("return", ic_token_type::IDENTIFIER);
  T_V("0", ic_token_type::INTEGER_CONSTANT);
  T_V(";", ic_token_type::SEMICOLON);
  T_V("}", ic_token_type::CLOSE_CURLY);
  T_V("\n", ic_token_type::NEWLINE);
  T_EMPTY(ic_token_type::TC_EOF);
  TOKENS_END();
  REQUIRE(t.errors_.size() == 2);// two errors for the ''
}
#ifdef SLOW_TESTS
TEST_CASE("ic_tokenizer: Tokenize simple native function output from Yaksha") {
  TEST_FILE("../test_data/ic2c_tests/0_native_functions.c",
            "0_native_functions.c",
            "../test_data/ic2c_tests/0_native_functions.c.tokens");
}
TEST_CASE("ic_tokenizer: Tokenize real world C code - utf8proc.c") {
  TEST_FILE("../runtime/utf8proc.c", "utf8proc.c",
            "../test_data/ic2c_tests/0_utf8proc.c.tokens");
}
TEST_CASE("ic_tokenizer: Tokenize real world C code - whereami.c") {
  TEST_FILE("../runtime/whereami.c", "whereami.c",
            "../test_data/ic2c_tests/0_whereami.c.tokens");
}
TEST_CASE(
    "ic_tokenizer: Tokenize real world C code - carpntr -> program_code.c") {
  TEST_FILE("../carpntr/build/program_code.c", "carpntr_program_code.c",
            "../test_data/ic2c_tests/0_carpntr_program_code.c.tokens");
}
TEST_CASE("ic_tokenizer: Tokenize real world C code - yk__graphic_utils.c") {
  TEST_FILE("../runtime/yk__graphic_utils.c", "yk__graphic_utils.c",
            "../test_data/ic2c_tests/0_yk__graphic_utils.c.tokens");
}
#endif
