#include "codegen_json.h"
#include "ast/codefiles.h"
#include "ast/parser.h"
#include "compiler/comp_result.h"
#include "3rd/nlohmann/json.hpp"
#include <sstream>

using namespace yaksha;

codegen_json::codegen_json() = default;
codegen_json::~codegen_json() = default;

comp_result codegen_json::emit(codefiles *cf, gc_pool<token> *token_pool,
                               errors::error_printer *ep) {
  nlohmann::json multi_file_json;

  auto process_file = [](file_info* fi) {
    nlohmann::json j;
    j["file_path"] = fi->filepath_.string();
    j["description"] = "Yaksha code export";
    j["version"] = "1.0";
    j["mangle_prefix"] = fi->prefix_;
    j["ast"] = nlohmann::json::array();
    auto statements = fi->data_->parser_->stmts_;
    for (auto stmt : statements) {
      if (stmt) {
        j["ast"].push_back(stmt->to_json());
      }
    }
    return j;
  };

  multi_file_json["main_file"] = process_file(cf->main_file_info_);
  multi_file_json["files"] = nlohmann::json::array();

  for (file_info *fi : cf->files_) {
    if (fi == cf->main_file_info_) { continue; }
    multi_file_json["files"].push_back(process_file(fi));
  }

  return {false, multi_file_json.dump(2)};
}