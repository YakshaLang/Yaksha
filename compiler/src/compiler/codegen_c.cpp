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
// codegen_c.cpp
#include "codegen_c.h"
#include "ast/codefiles.h"
#include "comp_result.h"
#include "to_c_compiler.h"
#include "utilities/error_printer.h"
using namespace yaksha;
codegen_c::codegen_c() = default;
codegen_c::~codegen_c() = default;
comp_result codegen_c::emit(codefiles *cf, gc_pool<token> *token_pool,
                            errors::error_printer *ep) {
  // Compile all files.
  bool has_errors = false;
  std::stringstream function_forward_decls{};
  std::stringstream function_body{};
  std::stringstream global_consts{};
  std::stringstream header{};
  std::unordered_set<std::string> runtime_features{};
  std::vector<parsing_error> compiler_errors_{};
  int file_count = static_cast<int>(cf->files_.size());
  for (int i = file_count - 1; i >= 0; i--) {
    auto f = cf->files_[i];
    to_c_compiler c{*f->data_->dsv_, &cf->pool_, cf->esc_, token_pool};
    auto result = c.compile(cf, f);
    function_forward_decls << result.function_forward_declarations_;
    function_body << result.body_;
    global_consts << result.global_constants_;
    header << result.header_;
    for (const std::string &feature : f->data_->dsv_->runtime_features_) {
      runtime_features.insert(feature);
    }
    if (!result.errors_.empty()) {
      has_errors = true;
      for (const auto &err : result.errors_) {
        compiler_errors_.emplace_back(err);
      }
    }
  }
  // Check if there are any errors in entry_struct_fn_compiler
  if (!cf->esc_->errors_.empty()) {
    has_errors = true;
    for (const auto &err : cf->esc_->errors_) {
      compiler_errors_.emplace_back(err);
    }
  }
  // We found errors during compile time
  if (has_errors) {
    ep->print_errors(compiler_errors_);
    LOG_COMP("found compile time errors");
    return {true, ""};
  }
  std::vector<std::string> rf{};
  rf.insert(rf.end(), runtime_features.begin(), runtime_features.end());
  std::sort(rf.begin(), rf.end());
  std::stringstream c_code{};
  // TODO deprecate runtimefeature
  // Write the feature requirements
  // ---
  // Format: // YK --> no requirements
  // Format: // YK:a,b,c# --> 'a', 'b', 'c' are requirements
  // Format: // YK:a# --> 'a' is the only requirement
  // ---
  // carpntr (or yaksha build) will check these requirements
  //   and link with correct runtime dependency files.
  c_code << "// YK";
  if (!rf.empty()) {
    c_code << ":";
    bool first = true;
    for (auto &feature : rf) {
      if (first) {
        first = false;
      } else {
        c_code << ",";
      }
      c_code << feature;
    }
    c_code << "#";
  }
  c_code << "\n";
  if (!cf->directives_.no_stdlib_) {
    LOG_COMP("stdlib is used");
    c_code << "#include \"yk__lib.h\"\n";
  }
  // ----------------------------------------------------------------
  //   ╔═╗┌─┐┌┐┌┌─┐┌┬┐┌─┐┌┐┌┌┬┐┌─┐
  //   ║  │ ││││└─┐ │ ├─┤│││ │ └─┐
  //   ╚═╝└─┘┘└┘└─┘ ┴ ┴ ┴┘└┘ ┴ └─┘
  // ----------------------------------------------------------------
  c_code << header.str();
  c_code << global_consts.str();
  if (cf->esc_->has_bin_data()) { cf->esc_->compile_binary_data_to(c_code); }
  // ----------------------------------------------------------------
  //   ╔═╗┌┬┐┬─┐┬ ┬┌─┐┌┬┐┬ ┬┬─┐┌─┐┌─┐   ╔╦╗┬ ┬┌─┐┌─┐┌┬┐┌─┐┌─┐┌─┐
  //   ╚═╗ │ ├┬┘│ ││   │ │ │├┬┘├┤ └─┐    ║ └┬┘├─┘├┤  ││├┤ ├┤ └─┐
  //   ╚═╝ ┴ ┴└─└─┘└─┘ ┴ └─┘┴└─└─┘└─┘┘   ╩  ┴ ┴  └─┘─┴┘└─┘└  └─┘
  // ----------------------------------------------------------------
  cf->esc_->compile_structures(c_code);
  // ----------------------------------------------------------------
  //  ╔═╗┬ ┬┌┐┌┌─┐┌┬┐┬┌─┐┌┐┌┌─┐
  //  ╠╣ │ │││││   │ ││ ││││└─┐
  //  ╚  └─┘┘└┘└─┘ ┴ ┴└─┘┘└┘└─┘
  // ----------------------------------------------------------------
  c_code << function_forward_decls.str();
  c_code << function_body.str();
  // ----------------------------------------------------------------
  // Generate main() if required
  if (!cf->directives_.no_main_) {
    LOG_COMP("main() function is required");
    c_code << "#if defined(YK__MINIMAL_MAIN)\n";
    c_code << "int main(void) { return yy__main(); }\n";
    c_code << "#endif";
  }
  LOG_COMP("c code generated");
  return {false, c_code.str()};
}
// Text ART -> https://patorjk.com/software/taag/#p=display&f=Calvin%20S&t=Functions