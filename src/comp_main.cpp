#include "compiler/multifile_compiler.h"
#include <iostream>
using namespace yaksha;
int main(int argc, char *argv[]) {
  if (argc != 2 && argc != 3) {
    std::cerr << "Usage: yakshac script.yaka [LIBS_PARENT_PATH]\n";
    return EXIT_FAILURE;
  }
  multifile_compiler mc{};
  multifile_compiler_result result;
  if (argc == 2) { // Just script is passed
    result = mc.compile(argv[1]);
  } else { // Script + LIBS_PARENT_PATH
    result = mc.compile(argv[1], argv[2]);
  }

  if (result.failed_) { return EXIT_FAILURE; }
  std::cout << result.code_;
  return EXIT_SUCCESS;
}