#include "ast/ast_printer.h"
#include "ast/interpreter.h"
#include "ast/parser.h"
#include "file_formats/tokens_file.h"
#include "tokenizer/block_analyzer.h"
#include "tokenizer/tokenizer.h"
#include "utilities/error_printer.h"
#include "compiler/compiler.h"
#include "compiler/type_checker.h"
using namespace yaksha;
// Simple main function to run a script and print the ast.
int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: yakshac script.yaka\n";
    return EXIT_FAILURE;
  }
  std::string file_name{argv[1]};
  std::ifstream script_file(file_name);
  if (!script_file.good()) {
    std::cerr << "Failed to read file:" << file_name << "\n";
    return EXIT_FAILURE;
  }
  std::string data((std::istreambuf_iterator<char>(script_file)),
                   std::istreambuf_iterator<char>());
  tokenizer t{file_name, data};
  t.tokenize();
  if (!t.errors_.empty()) {
    errors::print_errors(t.errors_);
    return EXIT_FAILURE;
  }
  block_analyzer b{t.tokens_};
  b.analyze();
  try {
    parser p{b.tokens_};
    auto tree = p.parse();
    if (tree.empty() || !p.errors_.empty()) {
      errors::print_errors(p.errors_);
      write_token_dump(std::cerr, b.tokens_);
      return EXIT_FAILURE;
    }

    type_checker tc{};
    tc.check(tree);
    if (!tc.errors_.empty()) {
      errors::print_errors(tc.errors_);
      return EXIT_FAILURE;
    }
    compiler comp{tc.functions_};
    std::cout << comp.compile(tree);

  } catch (parsing_error &p) {
    std::cout << "Parsing error --> " << p.message_ << "\n";
    write_token_dump(std::cerr, b.tokens_);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}