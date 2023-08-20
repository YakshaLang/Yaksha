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
// macro_processor.h
#ifndef MACRO_PROCESSOR_H
#define MACRO_PROCESSOR_H
#include "ast/ast.h"
#include "tokenizer/token.h"
#include <string>
#include <unordered_map>
#include <vector>
namespace yaksha {
  struct macro_processor {
    virtual ~macro_processor() = default;
    virtual void
    init_env(std::string filepath,
             std::unordered_map<std::string, import_stmt *> &imports) = 0;
    /**
     * Execute a macros!{} block, and create
     * @param filepath current file path
     * @param lisp_code lisp code tokens
     * @param imports import map
     */
    virtual void
    execute(std::string &filepath, std::vector<token *> &lisp_code,
            std::unordered_map<std::string, import_stmt *> &imports) = 0;
    /**
     * After macros!{} are executed, it will define dsl macros
     *  Now we can then execute this dsl defun and expand given tokens
     * @param filepath current file path
     * @param imports import map
     * @param dsl_macro_name name of the DSL macro name such as magic!{}
     * @param dsl_macro_input tokens as input
     * @return resulting tokens
     */
    virtual std::vector<token *>
    expand_dsl(std::string &filepath,
               std::unordered_map<std::string, import_stmt *> &imports,
               std::string &dsl_macro_name,
               std::vector<token *> &dsl_macro_input,
               std::string imported_macro, token *macro_name) = 0;

private:
  };
}// namespace yaksha
#endif
