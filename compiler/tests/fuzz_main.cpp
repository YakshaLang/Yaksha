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
#include "ast/ast_printer.h"
#include "ast/ast_vis.h"
#include "ast/parser.h"
#include "compiler/codegen_c.h"
#include "compiler/multifile_compiler.h"
#include "compiler/type_checker.h"
#include "file_formats/tokens_file.h"
#include "tokenizer/block_analyzer.h"
#include "tokenizer/tokenizer.h"
#include "utilities/error_printer.h"
using namespace yaksha;
void test_ast(const std::string &data, const std::string &file_name) {
  errors::error_printer ep{};
  gc_pool<token> token_pool{};
  tokenizer t{file_name, data, &token_pool};
  yk_datatype_pool dt_pool{};
  t.tokenize();
  if (!t.errors_.empty()) {
    ep.print_errors(t.errors_);
    return;
  }
  block_analyzer b{t.tokens_, &token_pool};
  b.analyze();
  try {
    parser p{file_name, b.tokens_, &dt_pool};
    auto tree = p.parse();
    if (!tree.empty()) {
      ast_printer pr{};
      pr.print(tree);
      std::cout << "\n\n============================\n";
      ast_vis vr{};
      vr.print(tree);
    } else {
      ep.print_errors(p.errors_);
      return;
    }
  } catch (parsing_error &p) {
    std::cout << "Parsing error --> " << p.message_ << "\n";
    write_token_dump(std::cerr, b.tokens_);
    return;
  }
}
void test_compiler(const std::string &filepath) {
  multifile_compiler mc{};
  codegen_c cg{};
  auto result = mc.compile(filepath, "/app/libs", &cg);
  std::cout << "Success : " << (result.failed_ ? "No\n" : "Yes\n");
  std::cout << result.code_ << "\n";
}
#ifdef YAKSHA_LLVM_FUZZ
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  std::string code{(char *) Data, Size};
  std::string fname = "fuzz_dummy.yaka";
  std::string lib_path = "/app/libs";
  test_ast(code, fname);
  multifile_compiler mc{};
  codegen_c cg{};
  mc.compile(code, true, fname, lib_path, &cg);
  return 0;
}
#else
int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: Yaksha script.yaka\n";
    return EXIT_SUCCESS;
  }
  std::string file_name{argv[1]};
  std::ifstream script_file(file_name);
  if (!script_file.good()) {
    std::cerr << "Failed to read file:" << file_name << "\n";
    return EXIT_SUCCESS;
  }
  std::string data((std::istreambuf_iterator<char>(script_file)),
                   std::istreambuf_iterator<char>());
  test_compiler(argv[1]);
  test_ast(data, file_name);
  return EXIT_SUCCESS;
}
#endif
