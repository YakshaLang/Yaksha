// ==============================================================================================
// ╦  ┬┌─┐┌─┐┌┐┌┌─┐┌─┐    Yaksha Programming Language
// ║  ││  ├┤ │││└─┐├┤     is Licensed with GPLv3 + extra terms. Please see below.
// ╩═╝┴└─┘└─┘┘└┘└─┘└─┘
// Note: libs - MIT license, runtime/3rd - various
// ==============================================================================================
// GPLv3:
//
// Yaksha - Programming Language.
// Copyright (C) 2020 - 2024 Bhathiya Perera
//
// This program is free software: you can redistribute it and/or modify it under the terms
// of the GNU General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with this program.
// If not, see https://www.gnu.org/licenses/.
//
// ==============================================================================================
// Additional Terms:
//
// Please note that any commercial use of the programming language's compiler source code
// (everything except compiler/runtime, compiler/libs and compiler/3rd) require a written agreement
// with author of the language (Bhathiya Perera).
//
// If you are using it for an open source project, please give credits.
// Your own project must use GPLv3 license with these additional terms.
//
// You may use programs written in Yaksha/YakshaLisp for any legal purpose
// (commercial, open-source, closed-source, etc) as long as it agrees
// to the licenses of linked runtime libraries (see compiler/runtime/README.md).
//
// ==============================================================================================
// codefiles.cpp
#include "codefiles.h"
#include "ast/parser.h"
#include "compiler/type_checker.h"
#include "tokenizer/block_analyzer.h"
#include "utilities/error_printer.h"
#include <optional>
using namespace yaksha;
codefiles::codefiles(std::filesystem::path &libs_path,
                     errors::error_printer *ep)
    : current_path_(std::filesystem::current_path()), prefixes_(),
      path_to_fi_(), libs_path_{libs_path}, pool_(), ep_{ep} {
  esc_ = new entry_struct_func_compiler(&pool_);
}
codefiles::~codefiles() {
  for (auto f : files_) {
    if (f->data_ != nullptr) {
      delete (f->data_->parser_);
      delete (f->data_->type_checker_);
      delete (f->data_->dsv_);
      delete (f->data_->block_analyzer_);
      delete (f->data_->tokenizer_);
    }
    delete (f->data_);
    delete (f);
  }
  delete esc_;
}
file_info *codefiles::initialize_parsing_or_null(const std::string &code,
                                                 const std::string &filename) {
  std::error_code err{};
  std::filesystem::path f{filename};
  auto path = std::filesystem::absolute(f, err);
  std::string str_path = path.string();
  auto p = parse_or_null(code, filename);
  if (p == nullptr) {
    print_unable_to_process_error(str_path);
    return nullptr;
  }
  auto fi = new file_info{path, "yy__", p};
  fi->step_ = scanning_step::SOUP_SCAN_DONE;
  path_to_fi_[str_path] = fi;
  prefixes_.insert({"yy__"});
  files_.emplace_back(fi);
  this->main_file_info_ = fi;
  for (auto imp : fi->data_->parser_->import_stmts_) {
    auto import_data = scan_or_null(imp);
    if (import_data == nullptr) { return nullptr; }
    imp->data_ = import_data;
  }
  return fi;
}
file_info *codefiles::initialize_parsing_or_null(const std::string &filename) {
  std::error_code err{};
  std::filesystem::path f{filename};
  auto path = std::filesystem::absolute(f, err);
  path = scratch_file_path(path.string());
  std::string str_path = path.string();
  if (err) {
    print_file_not_found_error(str_path);
    return nullptr;
  }
  if (!std::filesystem::exists(path, err)) {
    print_file_not_found_error(str_path);
    return nullptr;
  }
  if (err) {
    print_file_not_found_error(str_path);
    return nullptr;
  }
  current_path_ = path.parent_path();
  if (path_to_fi_.find(str_path) != path_to_fi_.end()) {// not found
    return path_to_fi_[str_path];
  }
  auto p = parse_or_null(path);
  if (p == nullptr) {
    print_unable_to_process_error(str_path);
    return nullptr;
  }
  auto fi = new file_info{path, "yy__", p};
  fi->step_ = scanning_step::SOUP_SCAN_DONE;
  path_to_fi_[str_path] = fi;
  prefixes_.insert({"yy__"});
  files_.emplace_back(fi);
  this->main_file_info_ = fi;
  for (auto imp : fi->data_->parser_->import_stmts_) {
    auto import_data = scan_or_null(imp);
    if (import_data == nullptr) { return nullptr; }
    imp->data_ = import_data;
  }
  return fi;
}
file_info *codefiles::scan_or_null(import_stmt *st) {
  auto optional_path = import_to_optional_file_path(st);
  if (!optional_path.has_value()) { return nullptr; }
#ifdef YAKSHA_DEBUG
  std::cout << "@@@@@@@@@@ found file:" << optional_path.value() << std::endl;
#endif
  auto path = optional_path.value();
  // if we have it in our map we return that
  if (path_to_fi_.find(path.string()) != path_to_fi_.end()) {
    return path_to_fi_[path.string()];
  }
  auto parsed_data = parse_or_null(path);
  if (parsed_data == nullptr) {
    print_unable_to_process_error(path.string());
    return nullptr;
  }
  auto nm = st->import_names_.back();
  std::string prefix = "yy__" + nm->token_;
  std::string cur_prefix = prefix + "_";
  unsigned int count = 1;
  while (has_prefix(cur_prefix)) {
    cur_prefix = prefix + std::to_string(count) + "_";
    count++;
  }
  auto fi = new file_info{path, cur_prefix, parsed_data};
  fi->step_ = scanning_step::SOUP_SCAN_DONE;
  prefixes_.insert(std::string{cur_prefix});
  path_to_fi_.insert({path.string(), fi});
  files_.emplace_back(fi);
  for (auto imp : fi->data_->parser_->import_stmts_) {
    auto import_data = scan_or_null(imp);
    if (import_data == nullptr) { return nullptr; }
    imp->data_ = import_data;
  }
  return path_to_fi_[path.string()];
}
std::optional<std::filesystem::path>
codefiles::import_to_optional_file_path(import_stmt *st) {
  auto key = reinterpret_cast<std::intptr_t>(st);
  if (import_to_path_cache_.find(key) != import_to_path_cache_.end()) {
    auto path = import_to_path_cache_[key];
    return {path};
  }
  auto original_path = std::filesystem::path{current_path_};
  std::vector<token *> names = st->import_names_;
  if (names.front()->token_ == "libs" || names.front()->token_ == "raylib" ||
      names.front()->token_ == "w4") {
    original_path = std::filesystem::path{libs_path_};
  }
  std::error_code err{};
  auto p = original_path;
  for (auto name_tok : names) {
    auto name = name_tok->token_;
    p /= name; /* equal to path join with '/' */
  }
  p += ".yaka"; /* add .yaka file extension */
  p = std::filesystem::absolute(p, err);
  p = scratch_file_path(p.string()); // check for scratch files
  if (err) {
    print_file_not_found_error(p.string());
    return {};
  }
  if (!std::filesystem::exists(p, err)) {
    print_file_not_found_error(p.string());
    return {};
  }
  if (err) {
    print_file_not_found_error(p.string());
    return {};
  }
  import_to_path_cache_[key] = p;
  return {p};
}
bool codefiles::has_prefix(std::string &root) {
  return prefixes_.find(root) != prefixes_.end();
}
file_data *codefiles::parse_or_null(std::filesystem::path &file_name) {
  std::ifstream script_file(file_name);
  if (!script_file.good()) {
    std::cerr << "Failed to read file:" << file_name << "\n";
    return nullptr;
  }
  std::string data((std::istreambuf_iterator<char>(script_file)),
                   std::istreambuf_iterator<char>());
  script_file.close(); // close the file
  std::string fname = file_name.string();
  return parse_or_null(data, fname);
}
std::filesystem::path codefiles::scratch_file_path(const std::string &filename) const {
  if (!this->use_scratch_files_) {
    return std::filesystem::path{filename};
  }
  std::filesystem::path f{filename};
  auto path = f.parent_path();
  auto name = f.stem();
  // Already a scratch file
  if (name.string().find("_.") == 0) {
    return std::filesystem::path{filename};
  }
  auto ext = f.extension();
  auto scratch_path = path / ("_." + name.string() + ext.string());
  std::error_code err{};
  if (std::filesystem::exists(scratch_path, err)) {
    if (!err) {
      return scratch_path;
    }
  }
  return std::filesystem::path{filename};
}
file_data *codefiles::parse_or_null(const std::string &data,
                                    const std::string &file_name) {
  auto *t = new tokenizer{file_name, data, yaksha_macros_.get_yk_token_pool()};
  t->tokenize();
  if (!t->errors_.empty()) {
    ep_->print_errors(t->errors_);
    delete (t);
    return nullptr;
  }
  auto *b = new block_analyzer{t->tokens_, yaksha_macros_.get_yk_token_pool()};
  b->analyze();
  if (!b->errors_.empty()) {
    ep_->print_errors(b->errors_);
    delete (t);
    delete (b);
    return nullptr;
  }
  auto *p = new parser(file_name, b->tokens_, &pool_);
  p->step_1_parse_token_soup();
  if (!b->errors_.empty()) {
    ep_->print_errors(b->errors_);
    delete (t);
    delete (b);
    delete (p);
    return nullptr;
  }
  return new file_data{p, t, b};
}
file_info *codefiles::get_or_null(const std::string &f) {
  if (path_to_fi_.find(f) == path_to_fi_.end()) return nullptr;
  return path_to_fi_[f];
}
void codefiles::print_file_not_found_error(const std::string &filepath) {
  std::cerr << "File not found or unable to read:" << filepath << "\n";
}
void codefiles::print_unable_to_process_error(const std::string &filepath) {
  std::cerr << "Unable to parse file:" << filepath << "\n";
}
