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
// colors.cpp
#include "colours.h"
#include "cpp_util.h"
using namespace yaksha;
#include <iostream>
#if defined(_WIN32) || defined(_WIN64)
#include <conio.h>
#include <cstdio>
#include <io.h>
#include <windows.h>
#define ISATTY _isatty
#define FILENO _fileno
void yaksha::colour_print(colour c, const std::string &content,
                          std::ostream &outs) {
  int col = 7;
  if (c == colour::BLUE) {
    col = 1;
  } else if (c == colour::GREEN) {
    col = 2;
  } else if (c == colour::CYAN) {
    col = 3;
  } else if (c == colour::RED) {
    col = 4;
  } else if (c == colour::MAGENTA) {
    col = 5;
  } else if (c == colour::YELLOW) {
    col = 6;
  } else {
    outs << content;
    return;
  }
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, col);
  outs << content;
  SetConsoleTextAttribute(hConsole, 7);
}
#else
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif
#include <cstdio>
#include <unistd.h>
#define ISATTY isatty
#define FILENO fileno
void yaksha::colour_print(colour c, const std::string &content,
                          std::ostream &outs) {
  std::string col{};
  if (c == colour::BLUE) {
    col = "\033[0;34m";
  } else if (c == colour::GREEN) {
    col = "\033[0;32m";
  } else if (c == colour::CYAN) {
    col = "\033[0;36m";
  } else if (c == colour::RED) {
    col = "\033[0;31m";
  } else if (c == colour::MAGENTA) {
    col = "\033[0;35m";
  } else if (c == colour::YELLOW) {
    col = "\033[0;33m";
  } else {
    outs << content;
    return;
  }
  outs << col << content << "\033[0m";
}
#endif
bool yaksha::is_stdout_a_terminal() {
#if defined(YAKSHA_DEBUG)
  return false;
#else
  return ISATTY(FILENO(stdout));
#endif
}
std::ostream &yaksha::operator<<(std::ostream &outs,
                                 const coloured_content &p) {
  if (is_stdout_a_terminal()) {
    colour_print(p.c_, p.line_, outs);
  } else {
    outs << p.line_;
  }
  return outs;
}
