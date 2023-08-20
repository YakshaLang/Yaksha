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
// ic_parser.h
#ifndef IC_PARSER_H
#define IC_PARSER_H
#include "ic_ast.h"
namespace yaksha {
  struct ic_parser {
    ic_parser(std::vector<ic_token> &tokens, ic_ast_pool *ast_pool);
    ~ic_parser();
    void parse();
    std::vector<ic_stmt *> statements_;
    std::vector<ic_parsing_error> errors_;

private:
    // ---------------------- Parsing ----------------------
    ic_stmt *preprocessor_statement();
    ic_stmt *define_st(ic_token *hash_t);
    ic_stmt *include_st(ic_token *hash_t);
    ic_stmt *line_st(ic_token *hash_t);
    ic_stmt *undef_st(ic_token *hash_t);
    ic_stmt *error_st(ic_token *hash_t);
    ic_stmt *warning_st(ic_token *hash_t);
    ic_stmt *pragma_st(ic_token *hash_t);
    ic_stmt *code_line();
    ic_stmt *block(ic_token *hash_t);
    ic_stmt *if_st(ic_token *hash_t);
    // ---------------------- State -------------------------
    ic_ast_pool *ast_pool_;
    std::vector<ic_token> &tokens_;
    std::size_t current_;
    // ----------------------- Utilities -------------------
    ic_token *advance();
    ic_token *recede();
    bool is_at_end();
    ic_token *peek();
    ic_token *previous();
    bool match(std::initializer_list<ic_token_type> types);
    bool check(ic_token_type t);
    ic_token *consume(ic_token_type t, const std::string &message);
    ic_token *consume_or_eof(ic_token_type t, const std::string &message);
    ic_parsing_error error(ic_token *tok, const std::string &message);
    std::vector<ic_token *> token_string();
  };
}// namespace yaksha
#endif
