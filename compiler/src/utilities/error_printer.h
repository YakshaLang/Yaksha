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
// error_printer.h
#ifndef ERROR_PRINTER_H
#define ERROR_PRINTER_H
#include "tokenizer/string_utils.h"
#include "tokenizer/token.h"
#include "utilities/cpp_util.h"
#include <iostream>
#include <ostream>
#include <utilities/colours.h>
#include <vector>
namespace yaksha::errors {
  struct error_printer {
    error_printer() = default;
    /**
     * Print a problematic token
     * @param output where to write the output to
     * @param tok token object
     */
    void print_token(std::ostream &output, const token &tok);
    /**
     * Print a single error
     * @param output where to write the error message
     * @param err error object
     */
    void print_error(std::ostream &output, const parsing_error &err);
#ifdef YAKSHA_TESTING
    bool has_error(const std::string &error_message);
    bool has_any_error();
    bool has_no_errors();
#endif
    bool json_output_ = false;
    /**
     * Print a vector of errors to std::cerr
     * @param errors errors to print
     */
    void print_errors(const std::vector<parsing_error> &errors);

private:
#ifdef YAKSHA_TESTING
    // Note: this is defined in error_printer.cpp
    // This is used for type checker testing
    std::vector<std::string> error_capture{};
#endif
    std::string errors_to_json_lines(const std::vector<parsing_error> &errors);
  };
}// namespace yaksha::errors
#endif
