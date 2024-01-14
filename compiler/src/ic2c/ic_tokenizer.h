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
// ic_tokenizer.h
#ifndef IC_TOKENIZER_H
#define IC_TOKENIZER_H
#include "ic_line_splicer.h"
#include "ic_peek_ahead_iter.h"
#include "ic_token.h"
#include "ic_trigraph_translater.h"
#include <string>
#include <vector>
namespace yaksha {
  struct ic_token;
  struct ic_parsing_error;
  struct ic_tokenizer {
    ic_tokenizer(std::string file, std::string data);
    ~ic_tokenizer();
    void tokenize();
    std::vector<ic_token> tokens_;
    std::vector<ic_parsing_error> errors_;

private:
    void tokenize_internal();
    std::string file_;
    std::string data_;
    int prev_line_;
    int prev_pos_;
    ic_trigraph_translater iter_tt_;
    ic_line_splicer iter_ls_;
    ic_peek_ahead_iter character_iterator_;
  };
}// namespace yaksha
#endif
