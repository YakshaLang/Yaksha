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
// tokens_file.h
#ifndef TOKENS_FILE_H
#define TOKENS_FILE_H
#include "tokenizer/tokenizer.h"
// Collection of tokens that can be used for snapshot testing of tokenizer
namespace yaksha {
  /**
 * Load vector of tokens from given file
 * @param file file with token data
 * @return list of tokens
 */
  std::vector<token *> load_token_dump(const std::string &file,
                                       gc_pool<token> *token_pool);
  /**
 * Save vector of tokens to given file
 * @param file file with token data
 * @param tokens list of tokens
 */
  [[maybe_unused]] bool save_token_dump(const std::string &file,
                                        const std::vector<token *> &tokens);
  void write_token_dump(std::ostream &output,
                        const std::vector<token *> &tokens);
}// namespace yaksha
#endif
