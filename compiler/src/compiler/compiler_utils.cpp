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
// compiler_utils.cpp
#include "compiler_utils.h"
#include <cstdint>
#include <unordered_map>
// TODO note that this is not thread safe,
//   and we should fix this if we ever start using multi threaded compilation
static std::unordered_map<std::string, std::string> GENSYMS{};
static std::int64_t GENSYM_COUNTER = -1;
std::string yaksha::prefix(const std::string &input,
                           const std::string &prefix_val) {
  if (input.rfind('$') == 0) {
    // This is a gensym, so we should generate a new symbol for this usecase
    // But you cannot already have yk__, yy__ or YK__ in the name if so
    std::string key = prefix_val + input;
    if (GENSYMS.find(key) == GENSYMS.end()) {
      GENSYM_COUNTER++;
      // since prefix_val is unique to files, this make gensym unique
      // `$a = 1 + 2` now this $a << this will be converted to a g_[prefix]_counter
      //  $a --> g_yk__1 for example
      GENSYMS[key] = "g_" + prefix_val + std::to_string(GENSYM_COUNTER);
    }
    return GENSYMS[key];
  }
  if ((input.rfind("yk__", 0) == 0) || input.rfind("YK__", 0) == 0 ||
      input.rfind("yy__", 0) == 0) {
    return input;
  }
  return prefix_val + input;
}
void yaksha::write_indent(std::stringstream &where_to, int level) {
  for (auto i = 0; i < level; i++) { where_to << "    "; }
}
