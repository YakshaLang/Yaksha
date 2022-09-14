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
    multifile_compiler_result compile(const std::string &main_file,
                                      const std::string &libs_path);
    multifile_compiler_result compile(const std::string &code,
                                      bool use_code,
                                      const std::string &main_file,
                                      const std::string &libs_path);
  };
}// namespace yaksha
#endif
