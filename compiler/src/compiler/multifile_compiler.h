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
// multifile_compiler.h
#ifndef MULTIFILE_COMPILER_H
#define MULTIFILE_COMPILER_H
#include "ast/codefiles.h"
#include "codegen.h"
#include "compiler/comp_result.h"
#include "tokenizer/token.h"
#include "utilities/error_printer.h"
#include "utilities/gc_pool.h"
#include <string>
namespace yaksha {
  struct do_nothing_codegen : codegen {
    ~do_nothing_codegen() override = default;
    comp_result emit(codefiles *cf, gc_pool<token> *token_pool, errors::error_printer* ep) override;
  };
  struct multifile_compiler {
    multifile_compiler() = default;
    ~multifile_compiler();
    comp_result compile(const std::string &main_file, codegen *code_generator);
    comp_result compile(const std::string &main_file,
                        const std::string &libs_path, codegen *code_generator);
    comp_result compile(const std::string &code, bool use_code,
                        const std::string &main_file,
                        const std::string &libs_path, codegen *code_generator);
    [[nodiscard]] codefiles &get_codefiles() const;
    bool main_required_ = true;
    bool check_types_ = true;
    bool usage_analysis_ = true;
    errors::error_printer error_printer_{};

private:
    gc_pool<token> token_pool_{};
    void step_1_scan_macro_soup();
    void step_2_initialize_preprocessor_env();
    void step_3_macros_setup();
    void step_4_expand_macros();
    void step_5_parse();
    [[nodiscard]] bool step_6_rescan_imports() const;
    void step_7_verify_import_rescan_done() const;
    comp_result compile_all(codegen *code_generator);
    [[nodiscard]] bool has_any_failures() const;
    [[nodiscard]] bool has_invalid_main_func(file_info *main_file_info) const;
    [[nodiscard]] bool all_success() const;
    codefiles *cf_{nullptr};
  };
}// namespace yaksha
#endif
