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
// colors.h
// Based on Color Terminal Output Library -- MIT Licensed Library by Ph0enixKM @ GitHub
// Bhathiya Perera - did some heavy modifications to the original library
#ifndef COLORS_H
#define COLORS_H
#include <iostream>
#include <string>
namespace yaksha {
  enum class colour {
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    NORMAL [[maybe_unused]]
  };
  bool is_stdout_a_terminal();
  void colour_print(colour c, const std::string &content, std::ostream &out);
  struct coloured_content {
    coloured_content(colour c, const std::string &content)
        : c_(c), line_(content) {}
    friend std::ostream &operator<<(std::ostream &outs,
                                    const coloured_content &p);

private:
    colour c_;
    const std::string &line_;
  };
  std::ostream &operator<<(std::ostream &outs, const coloured_content &p);
  namespace colours {
    static inline coloured_content red(const std::string &content) {
      return {colour::RED, content};
    }
    static inline coloured_content green(const std::string &content) {
      return {colour::GREEN, content};
    }
    static inline coloured_content yellow(const std::string &content) {
      return {colour::YELLOW, content};
    }
    static inline coloured_content blue(const std::string &content) {
      return {colour::BLUE, content};
    }
    static inline coloured_content magenta(const std::string &content) {
      return {colour::MAGENTA, content};
    }
    static inline coloured_content cyan(const std::string &content) {
      return {colour::CYAN, content};
    }
    static inline coloured_content normal(const std::string &content) {
      return {colour::NORMAL, content};
    }
  }// namespace colours
}// namespace yaksha
#endif
