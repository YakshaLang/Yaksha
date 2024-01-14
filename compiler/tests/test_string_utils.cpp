// ==============================================================================================
// ╦  ┬┌─┐┌─┐┌┐┌┌─┐┌─┐    Yaksha Programming Language
// ║  ││  ├┤ │││└─┐├┤     is Licensed with GPLv3 + extra terms. Please see below.
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
  REQUIRE(unescape("X\\x13").c_str()[1] == (char) 0x13);
  REQUIRE(unescape("X\\xa").c_str()[1] == (char) 0xa);
  REQUIRE(unescape("X\\xaa").c_str()[1] == (char) 0xaa);
  REQUIRE(unescape("X\\x89").c_str()[1] == (char) 0x89);
  REQUIRE(unescape("\\xe0\\xb6\\x9a\\xe0\\xb7\\x9c\\xe0\\xb7\\x84\\xe0\\xb7\\x9"
                   "c\\xe0\\xb6\\xb8\\xe0\\xb6\\xaf\\x20") == "කොහොමද ");
  REQUIRE(unescape("\\u2665") == "♥");
  REQUIRE(unescape("\\U0001F62D") == "😭");
  REQUIRE(unescape(escape("\a\b\f\n\r\t\v")) == "\a\b\f\n\r\t\v");
  std::string test_string = "\"abc\\xyz/";
  REQUIRE(unescape(escape(test_string)) == test_string);
  REQUIRE(escape(unescape(escape(test_string))) == escape(test_string));
  REQUIRE(unescape(unescape(escape(escape(test_string)))) == test_string);
}
TEST_CASE("string_utils: Repr") {
  REQUIRE(repr_string("ab\nc") == "\"ab\\nc\"");
}