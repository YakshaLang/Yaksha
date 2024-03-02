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
// codefiles.h
#ifndef CODEFILES_H
#define CODEFILES_H
#include "ast/ast.h"
#include "compiler/entry_struct_func_compiler.h"
#include "tokenizer/tokenizer.h"
#include "utilities/error_printer.h"
#include "utilities/ykdt_pool.h"
#include "yaksha_lisp/yaksha_lisp.h"
#include <filesystem>
#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
namespace yaksha {
  struct codefiles {
    codefiles(std::filesystem::path &libs_path, errors::error_printer *ep);
    ~codefiles();
    file_info *get_or_null(const std::string &f);
    file_info *initialize_parsing_or_null(const std::string &filename);
    file_info *initialize_parsing_or_null(const std::string &code,
                                          const std::string &filename);
    file_info *scan_or_null(import_stmt *st);
    std::vector<file_info *> files_;
    file_info *main_file_info_{nullptr};
    ykdt_pool pool_;
    yaksha_macros yaksha_macros_{};
    entry_struct_func_compiler *esc_;

private:
    file_data *parse_or_null(std::filesystem::path &file_name);
    file_data *parse_or_null(const std::string &data,
                             const std::string &file_name);
    bool has_prefix(std::string &root);
    static void print_file_not_found_error(const std::string &filepath);
    static void print_unable_to_process_error(const std::string &filepath);
    std::optional<std::filesystem::path>
    import_to_optional_file_path(import_stmt *st);
    /** -- **/
    std::unordered_map<std::string, file_info *> path_to_fi_{};
    std::unordered_set<std::string> prefixes_{};
    std::filesystem::path current_path_{};
    std::filesystem::path libs_path_{};
    std::unordered_map<std::intptr_t, std::filesystem::path>
        import_to_path_cache_{};
    errors::error_printer *ep_{nullptr};
  };
}// namespace yaksha
#endif
