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
// ic_line_splicer.h
#ifndef IC_LINE_SPLICER_H
#define IC_LINE_SPLICER_H
#include "ic_simple_character_iter.h"
#include "ic_trigraph_translater.h"
namespace yaksha {
  struct ic_line_splicer : public ic_simple_character_iter {
    explicit ic_line_splicer(ic_trigraph_translater &tt);
    void next() override;
    [[nodiscard]] bool reached_end() override;
    [[nodiscard]] uint32_t get_current() override;
    [[nodiscard]] int get_column() override;
    [[nodiscard]] int get_line() override;
    ~ic_line_splicer() override;

private:
    void read();
    ic_trigraph_translater &tt_;
    utf8::uint32_t current_;
    bool consumed_extra_;
  };
}// namespace yaksha
#endif
