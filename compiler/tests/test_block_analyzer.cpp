#include <utility>
#include "btest.h"
#include "catch2/catch.hpp"
#include "file_formats/tokens_file.h"
#include "tokenizer/block_analyzer.h"
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
