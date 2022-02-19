#include "btest.h"
#include "catch2/catch.hpp"
#include "tokenizer/string_utils.h"
using namespace yaksha;
using namespace yaksha::string_utils;
TEST_CASE("string_utils: Escape, Unescape Test") {
  REQUIRE(escape("abcd\"efg") == "abcd\\\"efg");
  REQUIRE(escape("\a\b\f\n\r\t\v") == "\\a\\b\\f\\n\\r\\t\\v");
  REQUIRE(unescape(escape("\a\b\f\n\r\t\v")) == "\a\b\f\n\r\t\v");
  std::string test_string = "\"abc\\xyz/";
  REQUIRE(unescape(escape(test_string)) == test_string);
  REQUIRE(escape(unescape(escape(test_string))) == escape(test_string));
  REQUIRE(unescape(unescape(escape(escape(test_string)))) == test_string);
}
TEST_CASE("string_utils: Repr") {
  REQUIRE(repr_string("ab\nc") == "\"ab\\nc\"");
}