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
#include "cpp_util.h"
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#else
// NOTE: These needs to be properly wrapped like we do for Yaksha runtime
// Better to just use these for unix for now
#include "../../runtime/subprocess.h"
#include "../../runtime/whereami.h"
#endif
#if defined(YAKSHA_OS_WINDOWS)
std::string yaksha::get_my_exe_path() {
  char rawPathName[MAX_PATH];
  GetModuleFileNameA(NULL, rawPathName, MAX_PATH);
  return {rawPathName};
}
#else
std::string yaksha::get_my_exe_path() {
  int length = wai_getModulePath(nullptr, 0, nullptr);
  char *path = (char *) malloc(length + 1);
  if (path == nullptr) { return ""; }
  wai_getModulePath(path, length, nullptr);
  path[length] = '\0';
  auto exe_path = std::string{
      path, static_cast<std::basic_string<char>::size_type>(length)};
  free(path);
  return exe_path;
}
#endif
