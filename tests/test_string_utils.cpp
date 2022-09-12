#include "btest.h"
#include "catch2/catch.hpp"
#include "tokenizer/string_utils.h"
using namespace yaksha;
using namespace yaksha::string_utils;
TEST_CASE("string_utils: Escape, Unescape Test") {
  REQUIRE(escape("abcd\"efg") == "abcd\\\"efg");
  REQUIRE(escape("\a\b\f\n\r\t\v") == "\\a\\b\\f\\n\\r\\t\\v");
  REQUIRE(escape(unescape("\\0")) == "\\0");
  REQUIRE(unescape("\\12") == "\12");
  REQUIRE(unescape("\\12G") == "\12G");
  REQUIRE(unescape("\\123") == "\123");
  REQUIRE(unescape("\\1234") == "\1234");
  REQUIRE(unescape("\\123G") == "\123G");
  REQUIRE(unescape("\\007") == "\007");
  REQUIRE(unescape("Bond\\007") == "Bond\007");
  REQUIRE(unescape("James\\007Bond") == "James\007Bond");
  REQUIRE(unescape("\\0").c_str()[0] == (char) 0);
  REQUIRE(unescape("X\\0X").c_str()[1] == (char) 0);
  REQUIRE(unescape("X\\000X").c_str()[1] == (char) 0);
  REQUIRE(unescape("X\\00X").c_str()[1] == (char) 0);
  REQUIRE(unescape(escape("\a\b\f\n\r\t\v")) == "\a\b\f\n\r\t\v");
  std::string test_string = "\"abc\\xyz/";
  REQUIRE(unescape(escape(test_string)) == test_string);
  REQUIRE(escape(unescape(escape(test_string))) == escape(test_string));
  REQUIRE(unescape(unescape(escape(escape(test_string)))) == test_string);
}
TEST_CASE("string_utils: Repr") {
  REQUIRE(repr_string("ab\nc") == "\"ab\\nc\"");
}