// ==============================================================================================
// ╦  ┬┌─┐┌─┐┌┐┌┌─┐┌─┐    Yaksha Programming Language
// ║  ││  ├┤ │││└─┐├┤     is Licensed with GPLv3 + extra terms. Please see below.
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
#include <chrono>
#include <filesystem>
#include <iostream>
#include <thread>
#ifndef PROGRAM_NAME
#define PROGRAM_NAME "ykreload"
#endif
#ifdef YK__CR_DEBUG
#define CR_DEBUG
#endif
#define CR_HOST CR_DISABLE
#include "../runtime/cr.h"
#include "../runtime/cr_userdata.h"
int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Invalid usage. Use as: " << PROGRAM_NAME << " libgame.so"
              << std::endl;
    return -1;
  }
  std::filesystem::path plugin_file{argv[1]};
  auto abs_path = std::filesystem::absolute(plugin_file);
  if (!std::filesystem::exists(abs_path)) {
    std::cerr << "[YKRELOAD] File not found. File:" << abs_path.string()
              << std::endl;
    return -1;
  }
  auto plugin_str = abs_path.string();
  std::cout << "[YKRELOAD] Loading plugin:" << plugin_str << "\n";
  cr_plugin ctx{};
  yk__user_data my_userdata{(void *) 0, true, 0, 0,
                            false,      false};// NOLINT(modernize-use-nullptr)
  ctx.userdata = &my_userdata;
  bool success = cr_plugin_open(ctx, plugin_str.c_str());
  std::cout << "[YKRELOAD] Initial load completed \n";
  while (success) {
    cr_plugin_update(ctx);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    auto *data = static_cast<yk__user_data *>(ctx.userdata);
    if (data != nullptr && data->should_die) {
      std::cout << "[YKRELOAD] Should die received\n";
      break;
    }
  }
  cr_plugin_close(ctx);
  return 0;
}
