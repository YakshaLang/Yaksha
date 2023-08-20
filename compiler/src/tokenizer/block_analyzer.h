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
// indent_analyzer.h
#ifndef INDENT_ANALYZER_H
#define INDENT_ANALYZER_H
#include "tokenizer/token.h"
#include "utilities/gc_pool.h"
#include <vector>
namespace yaksha {
  /**
   * Different types of indentations
   * UNKNOWN is pretty bad!
   */
  enum class indent_type { TWO_SPACES, FOUR_SPACES, TAB, UNKNOWN };
  /**
   * Convert given string to an indent type
   * @param indent_str string to examine
   * @return indent type
   */
  static inline indent_type str_to_indent_type(const std::string &indent_str) {
    if (indent_str == "  ") {
      return indent_type::TWO_SPACES;
    } else if (indent_str == "    ") {
      return indent_type::FOUR_SPACES;
    } else if (indent_str == "\t") {
      return indent_type::TAB;
    }
    return indent_type::UNKNOWN;
  }
  /**
   * Analyze indented blocks and replace INDENT tokens with
   * BA_INDENT & BA_DEDENT,
   * Additionally this cleans up extra new lines, indents & comments
   * // TODO Extract cleaning to a different class (Single Responsibility/SOLID)
   */
  struct block_analyzer {
    explicit block_analyzer(const std::vector<token *> &tokens,
                            gc_pool<token> *token_pool);
    void analyze();
    std::vector<parsing_error> errors_;
    std::vector<token *> tokens_;
    token *c_token(std::string file, int line, int pos, std::string token_buf,
                   token_type token_type_val);

private:
    void handle_error(const parsing_error &err);
    void create_dedents(std::vector<std::size_t> &indents, token *tok,
                        size_t prev_level, size_t current_level);
    const std::vector<token *> &original_tokens_;
    gc_pool<token> *token_pool_{nullptr};
  };
}// namespace yaksha
#endif
