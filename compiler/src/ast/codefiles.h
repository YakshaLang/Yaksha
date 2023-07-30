// codefiles.h
#ifndef CODEFILES_H
#define CODEFILES_H
#include "ast/ast.h"
#include "compiler/entry_struct_func_compiler.h"
#include "tokenizer/tokenizer.h"
#include "utilities/ykdt_pool.h"
#include "yaksha_lisp/yaksha_lisp.h"
#include <filesystem>
#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
namespace yaksha {
  struct codefiles {
    explicit codefiles(std::filesystem::path &libs_path);
    ~codefiles();
    file_info *get_or_null(const std::string &f);
    file_info *initialize_parsing_or_null(const std::string &filename);
    file_info *initialize_parsing_or_null(const std::string &code,
                                          const std::string &filename);
    file_info *scan_or_null(import_stmt *st);
    std::vector<file_info *> files_;
    ykdt_pool pool_;
    yaksha_macros yaksha_macros_{};
    entry_struct_func_compiler *esc_;

private:
    file_data *parse_or_null(std::filesystem::path &file_name);
    file_data *parse_or_null(const std::string &data,
                             const std::string &file_name);
    bool has_prefix(std::string &root);
    static void print_file_not_found_error(const std::string &filepath);
    static void print_unable_to_process_error(const std::string &filepath);
    std::optional<std::filesystem::path>
    import_to_optional_file_path(import_stmt *st);
    /** -- **/
    std::unordered_map<std::string, file_info *> path_to_fi_{};
    std::unordered_set<std::string> prefixes_{};
    std::filesystem::path current_path_{};
    std::filesystem::path libs_path_{};
    std::unordered_map<std::intptr_t, std::filesystem::path>
        import_to_path_cache_{};
  };
}// namespace yaksha
#endif
