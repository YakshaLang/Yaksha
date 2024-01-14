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
// ic_peek_ahead_iter.cpp
#include "ic_peek_ahead_iter.h"
using namespace yaksha;
ic_peek_ahead_iter::ic_peek_ahead_iter(ic_simple_character_iter &tt)
    : tt_(tt), current_(0), next_(0), after_next_(0), fourth_(0) {
  current_ = tt_.get_current();
  current_l_ = tt_.get_line();
  current_c_ = tt_.get_column();
  current_e_ = tt_.reached_end();
  tt_.next();
  next_ = tt_.get_current();
  next_l_ = tt_.get_line();
  next_c_ = tt_.get_column();
  next_e_ = tt_.reached_end();
  tt_.next();
  after_next_ = tt_.get_current();
  after_next_l_ = tt_.get_line();
  after_next_c_ = tt_.get_column();
  after_next_e_ = tt_.reached_end();
  tt_.next();
  fourth_ = tt_.get_current();
  fourth_l_ = tt_.get_line();
  fourth_c_ = tt_.get_column();
  fourth_e_ = tt_.reached_end();
}
void ic_peek_ahead_iter::next() {
  current_ = next_;
  current_l_ = next_l_;
  current_c_ = next_c_;
  current_e_ = next_e_;
  next_ = after_next_;
  next_l_ = after_next_l_;
  next_c_ = after_next_c_;
  next_e_ = after_next_e_;
  after_next_ = fourth_;
  after_next_l_ = fourth_l_;
  after_next_c_ = fourth_c_;
  after_next_e_ = fourth_e_;
  tt_.next();
  fourth_ = tt_.get_current();
  fourth_l_ = tt_.get_line();
  fourth_c_ = tt_.get_column();
  fourth_e_ = tt_.reached_end();
}
[[nodiscard]] bool ic_peek_ahead_iter::reached_end() { return current_e_; }
[[nodiscard]] utf8::uint32_t ic_peek_ahead_iter::get_current() {
  return current_;
}
[[nodiscard]] utf8::uint32_t ic_peek_ahead_iter::get_next() { return next_; }
[[nodiscard]] utf8::uint32_t ic_peek_ahead_iter::get_after_next() {
  return after_next_;
}
[[nodiscard]] utf8::uint32_t ic_peek_ahead_iter::get_fourth() {
  return fourth_;
}
int ic_peek_ahead_iter::get_column() { return current_c_; }
int ic_peek_ahead_iter::get_line() { return current_l_; }
ic_peek_ahead_iter::~ic_peek_ahead_iter() = default;
