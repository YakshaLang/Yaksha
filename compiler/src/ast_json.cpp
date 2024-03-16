// ==============================================================================================
// ╦  ┬┌─┐┌─┐┌┐┌┌─┐┌─┐    Yaksha Programming Language
// ║  ││  ├┤ │││└─┐├┤     is Licensed with GPLv3 + exta terms. Please see below.
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
#include "compiler/codegen_json.h"
#include "compiler/multifile_compiler.h"
#include "utilities/error_printer.h"
#include <iostream>
#ifndef PROGRAM_NAME
#define PROGRAM_NAME "ast"
#endif
#include "utilities/argparser.h"
using namespace yaksha;
int main(int argc, char *argv[]) {
  auto args = argparser::ARGS(PROGRAM_NAME, "Compile Yaksha AST to Json", "");
  auto help = argparser::OP_BOOL('h', "--help", "Print this help message");
  auto check_main =
      argparser::OP_BOOL('c', "--check-main", "Enable main() check");
  auto check_types =
      argparser::OP_BOOL('t', "--check-types", "Enable type checking");
  args.optional_ = {&help, &check_main, &check_types};
  auto code = argparser::PO("mainfile.yaka", "Yaksha code file.");
  auto lib = argparser::PO_OPT("[LIBS_PARENT_PATH]",
                               "Path to the parent directory of the libraries");
  args.positional_ = {&code, &lib};
  argparser::parse_args(argc, argv, args);
  if (help.is_set_) {
    argparser::print_help(args);
    return EXIT_SUCCESS;
  }
  if (!args.errors_.empty()) {
    argparser::print_errors(args);
    argparser::print_help(args);
    return EXIT_FAILURE;
  }
  comp_result result;
  multifile_compiler mc{};
  try {
    mc.main_required_ = check_main.is_set_;
    mc.check_types_ = check_types.is_set_;
    mc.usage_analysis_ = false;// disable usage analysis as JSON will dump all
    codegen_json cg{};
    if (!lib.is_set_) {// Just code.yaka is passed
      result = mc.compile(code.value_, &cg);
    } else {// code.yaka + LIBS_PARENT_PATH
      result = mc.compile(code.value_, lib.value_, &cg);
    }
    if (result.failed_) { return EXIT_FAILURE; }
  } catch (parsing_error &e) { mc.error_printer_.print_error(std::cerr, e); }
  std::cout << result.code_;
  return EXIT_SUCCESS;
}
