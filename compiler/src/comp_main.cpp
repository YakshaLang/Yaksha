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
#include "compiler/codegen_c.h"
#include "compiler/multifile_compiler.h"
#include "utilities/error_printer.h"
#include <iostream>
#ifndef PROGRAM_NAME
#define PROGRAM_NAME "yakshac"
#endif
using namespace yaksha;
int main(int argc, char *argv[]) {
  if (argc != 2 && argc != 3) {
    std::cerr << "Usage: " << PROGRAM_NAME
              << " script.yaka [LIBS_PARENT_PATH]\n";
    return EXIT_FAILURE;
  }
  comp_result result;
  try {
    multifile_compiler mc{};
    codegen_c cg{};
    if (argc == 2) {// Just code.yaka is passed
      result = mc.compile(argv[1], &cg);
    } else {// code.yaka + LIBS_PARENT_PATH
      result = mc.compile(argv[1], argv[2], &cg);
    }
    if (result.failed_) { return EXIT_FAILURE; }
  } catch (parsing_error &e) { errors::print_errors({e}); }
  std::cout << result.code_;
  return EXIT_SUCCESS;
}
