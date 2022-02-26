// multifile_compiler.h
#ifndef MULTIFILE_COMPILER_H
#define MULTIFILE_COMPILER_H
#include <string>
namespace yaksha {
  struct multifile_compiler_result {
    bool failed_;
    std::string code_;
  };
  struct multifile_compiler {
    multifile_compiler_result compile(const std::string &main_file);
  };
}// namespace yaksha
#endif
