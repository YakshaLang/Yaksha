#include "utilities/cpp_util.h"
#include "yaksha_lisp/yaksha_lisp.h"
#include <iostream>
int lisp_repl();
int lisp_execute_file(char *file_path);
#ifndef PROGRAM_NAME
#define PROGRAM_NAME "lisp"
#endif
#ifdef YAKSHA_DEBUG
#define PRINT_BUILTINS_YAKSHA_LISP
#endif
using namespace yaksha;
int main(int argc, char *argv[]) {
  if (argc != 1 && argc != 2) {
    std::cerr << "Usage: " << PROGRAM_NAME << " [script.lisp]\n";
    return EXIT_FAILURE;
  }
  if (argc == 1) { return lisp_repl(); }
  return lisp_execute_file(argv[1]);
}
int lisp_execute_file(char *file_path) {
  std::string file_name{file_path};
  std::ifstream script_file(file_name);
  if (!script_file.good()) {
    std::cerr << "Failed to read file:" << file_name << "\n";
    return EXIT_FAILURE;
  }
  std::string data((std::istreambuf_iterator<char>(script_file)),
                   std::istreambuf_iterator<char>());
  yaksha_macros mm{};
  yaksha_lisp_tokenizer tokenizer{&mm};
  tokenizer.tokenize(file_name, data, mm.get_yk_token_pool());
  if (!tokenizer.errors_.empty()) {
    errors::print_errors(tokenizer.errors_);
    return EXIT_FAILURE;
  }
  yaksha_lisp_parser parser{&tokenizer, &mm};
  parser.parse();
  if (!parser.errors_.empty()) {
    errors::print_errors(parser.errors_);
    return EXIT_FAILURE;
  }
  yaksha_envmap environment{&mm};
  environment.setup_builtins();
  environment.setup_prelude();
  try {
    environment.eval(parser.exprs_);
  } catch (parsing_error &ex) {
    errors::print_error(std::cerr, ex);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
void eval_line(const std::string &code, yaksha_envmap *environment) {
  yaksha_lisp_tokenizer tokenizer{environment->get_memory_manager()};
  tokenizer.tokenize("repl.lisp", code,
                     environment->get_memory_manager()->get_yk_token_pool());
  if (!tokenizer.errors_.empty()) {
    errors::print_errors(tokenizer.errors_);
    return;
  }
  yaksha_lisp_parser parser{&tokenizer, environment->get_memory_manager()};
  parser.parse();
  if (!parser.errors_.empty()) {
    errors::print_errors(parser.errors_);
    return;
  }
  try {
    auto result = environment->eval(parser.exprs_);
    if (result != nullptr) { std::cout << colours::cyan("-> ") << result; }
  } catch (parsing_error &ex) { errors::print_error(std::cerr, ex); }
}
int lisp_repl() {
  std::cout << colours::red("                                 \n"
                            " __ __ _____ _____     _   _____ \n"
                            "|  |  |  _  |  |  |___| |_|  _  |\n"
                            "|_   _|     |    -|_ -|   |     |\n"
                            "  |_| |__|__|__|__|___|_|_|__|__|\n");
  std::cout << colours::yellow("            (lisp)               \n"
                               "Please keep in mind this is a simple REPL.\n"
                               " This is not as advanced as CL.\n");
  std::cout << "Type in expressions to evaluate them.\n";
  std::cout << "Input " << colours::cyan("(exit)") << " to exit from repl.\n";
  yaksha_macros mm{};
  yaksha_envmap environment{&mm};
  environment.setup_builtins();
  environment.setup_prelude();
#ifdef PRINT_BUILTINS_YAKSHA_LISP
  std::cout << "Builtins:: ";
  bool first = true;
  for (auto &kv : environment.get_symbols()) {
    if (first) {
      first = false;
    } else {
      std::cout << colours::red(",") << " ";
    }
    std::cout << colours::red("\"") << colours::cyan(kv.first)
              << colours::red("\"");
  }
  std::cout << "\n";
#endif
  bool exit = false;
  while (!exit) {
    std::string line{};
    std::cout << colours::green(">> ");
    std::getline(std::cin, line);
    if (line.empty()) { continue; }
    if (line == "(exit)" || line == "exit") {
      exit = true;
      continue;
    }
    eval_line(line, &environment);
    std::cout << "\n";
  }
  return EXIT_SUCCESS;
}
