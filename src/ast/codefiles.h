// codefiles.h
#ifndef CODEFILES_H
#define CODEFILES_H
#include "ast/ast.h"
#include "compiler/entry_struct_func_compiler.h"
#include "tokenizer/tokenizer.h"
#include "utilities/ykdt_pool.h"
#include <filesystem>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
namespace yaksha {
  struct codefiles {
    codefiles(std::filesystem::path &libs_path);
    ~codefiles();
    file_info *get(const std::string &filename);
    file_info *scan_main(const std::string &filename);
    file_info *scan(import_stmt *st);
    std::vector<file_info *> files_;
    ykdt_pool pool_;
    entry_struct_func_compiler *esc_;

private:
    file_data *parse(std::filesystem::path &fpath);
    bool has_prefix(std::string &root);
    std::unordered_map<std::string, file_info *> path_to_fi_{};
    std::unordered_set<std::string> prefixes_{};
    std::filesystem::path current_path_{};
    std::filesystem::path libs_path_{};
    static void print_file_not_found_error(const std::string &filepath);
    static void print_unable_to_process_error(const std::string &filepath);
  };
}// namespace yaksha
#endif
