// multifile_compiler.cpp
#include "multifile_compiler.h"
#include "ast/codefiles.h"
#include "ast/interpreter.h"
#include "ast/parser.h"
#include "compiler/compiler.h"
#include "compiler/type_checker.h"
#include "tokenizer/block_analyzer.h"
#include "utilities/error_printer.h"
using namespace yaksha;
multifile_compiler_result
multifile_compiler::compile(const std::string &main_file) {
  auto libs_path = std::filesystem::current_path().string();
  return compile(main_file, libs_path);
}
multifile_compiler_result
multifile_compiler::compile(const std::string &main_file,
                            const std::string &libs_path) {
  std::filesystem::path library_parent{libs_path};
  codefiles cf{library_parent};
  // Parse all imports by scanning given main file
  auto main_file_info = cf.scan_main(main_file);
  if (main_file_info == nullptr) {
    std::cerr << "Failed to compile:" << main_file << "\n";
    return {true, ""};
  }
  bool has_errors = false;
  // Extract defs and structs
  for (auto f : cf.files_) {
    f->data_->dsv_ = new def_class_visitor();
    f->data_->dsv_->extract(f->data_->parser_->stmts_);
    if (!f->data_->dsv_->errors_.empty()) {
      errors::print_errors(f->data_->dsv_->errors_);
      has_errors = true;
    }
  }
  if (!main_file_info->data_->dsv_->has_function("main")) {
    std::cerr << "Critical !! main() function must be present";
    has_errors = true;
  } else {
    auto main_function = main_file_info->data_->dsv_->get_function("main");
    if (!main_function->params_.empty()) {
      std::cerr << "Critical !! main() function must not have parameters";
      has_errors = true;
    }
    if (!main_function->return_type_->is_int()) {
      std::cerr << "Critical !! main() function must return an integer";
      has_errors = true;
    }
  }
  if (has_errors) { return {true, ""}; }
  // Ensure all data types have the proper module
  for (auto f : cf.files_) { f->data_->parser_->rescan_datatypes(); }
  // Type check all files
  for (auto f : cf.files_) {
    f->data_->type_checker_ =
        new type_checker(f->filepath_.string(), &cf, f->data_->dsv_, &cf.pool_);
    for (auto impo : f->data_->parser_->import_stmts_) {
      auto obj = ykobject(&cf.pool_);
      obj.object_type_ = yaksha::object_type::MODULE;
      obj.string_val_ = impo->data_->filepath_.string();
      obj.module_file_ = impo->data_->filepath_.string();
      obj.module_name_ = impo->name_->token_;
      f->data_->type_checker_->scope_.define_global(impo->name_->token_, obj);
    }
    f->data_->type_checker_->check(f->data_->parser_->stmts_);
    if (!f->data_->type_checker_->errors_.empty()) {
      errors::print_errors(f->data_->type_checker_->errors_);
      has_errors = true;
    }
  }
  if (has_errors) { return {true, ""}; }
  // Compile all files.
  std::stringstream struct_forward_decls{};
  std::stringstream function_forward_decls{};
  std::stringstream struct_body{};
  std::stringstream function_body{};
  std::stringstream global_consts{};
  int file_count = static_cast<int>(cf.files_.size());
  for (int i = file_count - 1; i >= 0; i--) {
    auto f = cf.files_[i];
    compiler c{*f->data_->dsv_, &cf.pool_};
    auto result = c.compile(&cf, f);
    struct_forward_decls << result.struct_forward_declarations_;
    function_forward_decls << result.function_forward_declarations_;
    struct_body << result.classes_;
    function_body << result.body_;
    global_consts << result.global_constants_;
  }
  std::stringstream c_code{};
  c_code << "// YK\n";
  c_code << "#include \"yk__lib.h\"\n";
  c_code << "// --forward declarations-- \n";
  c_code << global_consts.str();
  c_code << struct_forward_decls.str();
  c_code << function_forward_decls.str();
  c_code << "// --structs-- \n";
  c_code << struct_body.str();
  c_code << "// --functions-- \n";
  c_code << function_body.str();
  c_code << "#if defined(YK__MINIMAL_MAIN)\n";
  c_code << "int main(void) { return yy__main(); }\n";
  c_code << "#endif";
  return {false, c_code.str()};
}
