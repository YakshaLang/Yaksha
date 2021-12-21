#include "ast/ast_printer.h"
#include "ast/ast_vis.h"
#include "ast/interpreter.h"
#include "ast/parser.h"
#include "file_formats/tokens_file.h"
#include "tokenizer/block_analyzer.h"
#include "tokenizer/tokenizer.h"
#include "utilities/error_printer.h"
using namespace yaksha;
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
    return EXIT_SUCCESS;
  }
  block_analyzer b{t.tokens_};
  b.analyze();
  try {
    parser p{b.tokens_};
    auto tree = p.parse();
    if (!tree.empty()) {
      interpreter ip{};
      ip.calculate(tree);
      std::cout << "\n\n============================\n";
      ast_printer pr{};
      pr.print(tree);
      std::cout << "\n\n============================\n";
      ast_vis vr{};
      vr.print(tree);
    } else {
      errors::print_errors(p.errors_);
      return EXIT_SUCCESS;
    }
  } catch (parsing_error &p) {
    std::cout << "Parsing error --> " << p.message_ << "\n";
    write_token_dump(std::cerr, b.tokens_);
    return EXIT_SUCCESS;
  }
  return EXIT_SUCCESS;
}