#include "ast/ast_printer.h"
#include "ast/ast_vis.h"
#include "ast/interpreter.h"
#include "ast/parser.h"
#include "compiler/compiler.h"
#include "compiler/type_checker.h"
#include "file_formats/tokens_file.h"
#include "tokenizer/block_analyzer.h"
#include "tokenizer/tokenizer.h"
#include "utilities/error_printer.h"
using namespace yaksha;
void test_interpreter(const std::string &data, const std::string &file_name) {
  tokenizer t{file_name, data};
  t.tokenize();
  if (!t.errors_.empty()) {
    errors::print_errors(t.errors_);
    return;
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
      return;
    }
  } catch (parsing_error &p) {
    std::cout << "Parsing error --> " << p.message_ << "\n";
    write_token_dump(std::cerr, b.tokens_);
    return;
  }
}
void test_compiler(const std::string &data, const std::string &file_name) {
  tokenizer t{file_name, data};
  t.tokenize();
  if (!t.errors_.empty()) {
    errors::print_errors(t.errors_);
    return;
  }
  block_analyzer b{t.tokens_};
  b.analyze();
  try {
    parser p{b.tokens_};
    auto tree = p.parse();
    if (tree.empty()) {
      errors::print_errors(p.errors_);
      return;
    }
    type_checker tc{};
    tc.check(tree);
    if (!tc.errors_.empty()) {
      errors::print_errors(tc.errors_);
      return;
    }
    compiler c{tc.functions_};
    std::cout << c.compile(tree);
  } catch (parsing_error &p) {
    std::cout << "Parsing error --> " << p.message_ << "\n";
    write_token_dump(std::cerr, b.tokens_);
    return;
  }
}
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
  test_compiler(data, file_name);
  test_interpreter(data, file_name);
  return EXIT_SUCCESS;
}