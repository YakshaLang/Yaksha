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
#include <filesystem>
#include <iostream>
#ifndef PROGRAM_NAME
#define PROGRAM_NAME "ykreload"
#endif
#include <windows.h>
std::string get_exe_path() {
  char rawPathName[MAX_PATH];
  GetModuleFileNameA(NULL, rawPathName, MAX_PATH);
  return {rawPathName};
}
int execute_program(LPCSTR lpApplicationName, LPSTR arg) {
  // additional information
  STARTUPINFOA si;
  PROCESS_INFORMATION pi;
  DWORD exit_code;
  // set the size of the structures
  ZeroMemory(&si, sizeof(si));
  si.cb = sizeof(si);
  ZeroMemory(&pi, sizeof(pi));
  // start the program up
  if (!CreateProcessA(lpApplicationName,// the path
                      arg,              // Command line
                      NULL,             // Process handle not inheritable
                      NULL,             // Thread handle not inheritable
                      FALSE,            // Set handle inheritance to FALSE
                      0,                // No configuration
                      NULL,             // Use parent's environment block
                      NULL,             // Use parent's starting directory
                      &si,              // Pointer to STARTUPINFO structure
                      &pi// Pointer to PROCESS_INFORMATION structure
                      )) {
    return -1;
  }
  WaitForSingleObject(pi.hProcess, INFINITE);
  GetExitCodeProcess(pi.hProcess, &exit_code);
  // Close process and thread handles.
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);
  return (int) exit_code;
}
int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Invalid usage. Use as: " << PROGRAM_NAME << " libgame.so"
              << std::endl;
    return -1;
  }
  auto reloader = std::filesystem::path(get_exe_path()) / "ykreload.exe";
  auto argument = std::string("\"") + argv[1] + "\"";
  auto cstr = std::make_unique<char[]>(argument.length() + 1);
  strcpy(cstr.get(), argument.c_str());
  return execute_program(reinterpret_cast<LPCSTR>(reloader.c_str()),
                         cstr.get());
}
