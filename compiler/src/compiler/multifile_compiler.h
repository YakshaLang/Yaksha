// multifile_compiler.h
#ifndef MULTIFILE_COMPILER_H
#define MULTIFILE_COMPILER_H
#include "ast/codefiles.h"
#include "tokenizer/token.h"
#include "utilities/gc_pool.h"
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
    multifile_compiler_result compile(const std::string &code, bool use_code,
                                      const std::string &main_file,
                                      const std::string &libs_path);

private:
    gc_pool<token> token_pool_{};
    bool has_invalid_main_func(file_info *main_file_info) const;
    void step_1_scan_macro_soup(codefiles &cf);
    void step_2_initialize_preprocessor_env(codefiles &cf);
    void step_3_macros_setup(codefiles &cf);
    void step_4_expand_macros(codefiles &cf);
    void step_5_parse(codefiles &cf);
    multifile_compiler_result compile_all(codefiles &cf,
                                          file_info *main_file_info);
    bool step_6_rescan_imports(codefiles &cf, file_info *main_file_info) const;
    void step_7_verify_import_rescan_done(codefiles &cf) const;
    bool has_any_failures(codefiles &cf) const;
    bool all_success(codefiles &cf) const;
  };
}// namespace yaksha
#endif
