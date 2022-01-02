#include "ast/ast_printer.h"
#include "ast/interpreter.h"
#include "ast/parser.h"
#include "file_formats/tokens_file.h"
#include "tokenizer/block_analyzer.h"
#include "tokenizer/tokenizer.h"
#include "utilities/error_printer.h"
using namespace yaksha;
// Simple main function to run a script and print the ast.
int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: Yaksha script.yaka\n";
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
    if (!tree.empty() && p.errors_.empty()) {
      interpreter ip{};
      ip.calculate(tree);
      auto final_outcome = ip.result();
      if (final_outcome != nullptr) {
        if (final_outcome->object_type_ == yaksha::object_type::RUNTIME_ERROR) {
          std::cerr << final_outcome->string_val_ << "\n";
        }
      }
      std::cout << "\n\n============================\n";
      ip.debug_print_stack();
      std::cout << "\n\n============================\n";
      ast_printer pr{};
      pr.print(tree);
    } else {
      errors::print_errors(p.errors_);
      write_token_dump(std::cerr, b.tokens_);
      return EXIT_FAILURE;
    }
  } catch (parsing_error &p) {
    std::cout << "Parsing error --> " << p.message_ << "\n";
    write_token_dump(std::cerr, b.tokens_);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}