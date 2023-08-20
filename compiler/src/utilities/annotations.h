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
// annotations.h
#ifndef ANNOTATIONS_H
#define ANNOTATIONS_H
#include "tokenizer/token.h"
#include "utilities/annotation.h"
#include <vector>
namespace yaksha {
  struct annotations {
    void add(const annotation &a);
    bool native_{false};
    bool native_macro_{false};
    bool native_define_{false};
    bool template_{false};
    bool varargs_{false};
    bool on_stack_{false};
    std::string native_arg_{};
    std::string native_macro_arg_{};
    std::string native_define_arg_{};
    std::string template_arg_{};
    std::string error_{};

private:
    std::vector<annotation> annotations_{};
    void validate_native_arg(std::string &arg, bool arg_set);
    void validate_template(std::string &arg, bool arg_set);
  };
}// namespace yaksha
#endif
