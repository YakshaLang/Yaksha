#include "compiler/multifile_compiler.h"
#include <iostream>
using namespace yaksha;
int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: yakshac script.yaka\n";
    return EXIT_FAILURE;
  }
  multifile_compiler mc{};
  auto result = mc.compile(argv[1]);
  if (result.failed_) { return EXIT_FAILURE; }
  std::cout << result.code_;
  return EXIT_SUCCESS;
}