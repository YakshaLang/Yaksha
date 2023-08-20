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
#include "ast/ast_vis.h"
#include "ast/parser.h"
#include "compiler/type_checker.h"
#include "file_formats/tokens_file.h"
#include "tokenizer/block_analyzer.h"
#include "tokenizer/tokenizer.h"
#include "utilities/error_printer.h"
using namespace yaksha;
#ifndef PROGRAM_NAME
#define PROGRAM_NAME "yakshavz"
#endif
// Simple main function to run a script and print the ast.
int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << PROGRAM_NAME << " script.yaka\n";
    return EXIT_FAILURE;
  }
  std::string file_name{argv[1]};
  std::ifstream script_file(file_name);
  if (!script_file.good()) {
    std::cerr << "Failed to read file:" << file_name << "\n";
    return EXIT_FAILURE;
  }
  std::string data((std::istreambuf_iterator<char>(script_file)),
                   std::istreambuf_iterator<char>());
  gc_pool<token> token_pool{};
  tokenizer t{file_name, data, &token_pool};
  t.tokenize();
  if (!t.errors_.empty()) {
    errors::print_errors(t.errors_);
    return EXIT_FAILURE;
  }
  block_analyzer b{t.tokens_, &token_pool};
  b.analyze();
  ykdt_pool dt_pool{};
  try {
    parser p{file_name, b.tokens_, &dt_pool};
    auto tree = p.parse();
    if (tree.empty() || !p.errors_.empty()) {
      errors::print_errors(p.errors_);
      write_token_dump(std::cerr, b.tokens_);
      return EXIT_FAILURE;
    }
    ast_vis v{};
    v.print(tree);
  } catch (parsing_error &p) {
    std::cerr << "Parsing error --> " << p.message_ << "\n";
    write_token_dump(std::cerr, b.tokens_);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
