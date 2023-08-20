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
// ic_line_splicer.cpp
#include "ic_line_splicer.h"
using namespace yaksha;
ic_line_splicer::ic_line_splicer(ic_trigraph_translater &tt)
    : tt_(tt), current_(0), consumed_extra_(false) {
  read();
}
void ic_line_splicer::next() {
  if (consumed_extra_) {
    read();
    return;
  }
  if (!reached_end()) { tt_.next(); }
  read();
}
[[nodiscard]] bool ic_line_splicer::reached_end() { return tt_.reached_end(); }
[[nodiscard]] uint32_t ic_line_splicer::get_current() { return current_; }
[[nodiscard]] int ic_line_splicer::get_column() {
  return consumed_extra_ ? tt_.get_column() - 1 : tt_.get_column();
}
[[nodiscard]] int ic_line_splicer::get_line() { return tt_.get_line(); }
ic_line_splicer::~ic_line_splicer() = default;
void ic_line_splicer::read() {
  consumed_extra_ = false;
  current_ = tt_.get_current();
  if (current_ != '\\') return;
  if (tt_.reached_end()) return;
  tt_.next();
  if (tt_.get_current() == '\r' && !tt_.reached_end()) {
    tt_.next();
    if (tt_.get_current() == '\n') {
      if (tt_.reached_end()) {
        current_ = 0;
      } else {
        tt_.next();
        current_ = tt_.get_current();
      }
    } else {
      current_ = tt_.get_current();
    }
  } else if (tt_.get_current() == '\n' && !tt_.reached_end()) {
    tt_.next();
    current_ = tt_.get_current();
  } else if (tt_.reached_end()) {
    current_ = 0;
  } else {
    consumed_extra_ = true;
  }
}
