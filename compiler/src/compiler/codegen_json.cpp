// codegen_json.cpp
#include "codegen_json.h"
#include "ast/codefiles.h"
#include "ast/parser.h"
#include "compiler/comp_result.h"
using namespace yaksha;
codegen_json::codegen_json() = default;
codegen_json::~codegen_json() = default;
comp_result codegen_json::emit(codefiles *cf, gc_pool<token> *token_pool) {
  to_json_compiler to_json{};
  return {false, to_json.compile(cf->main_file_info_)};
}
std::string to_json_compiler::compile(file_info *fi) {
  // Compile the main file to a JSON
  json_ << "{\n";
  json_ << "\"file\": \"" << fi->filepath_.string() << "\",\n";
  json_ << "\"ast\": [\n";
  auto statements = fi->data_->parser_->stmts_;
  for (auto stmt : statements) { stmt->accept(this); }
  json_ << "]\n";
  json_ << "}\n";
  return json_.str();
}
void to_json_compiler::visit_assign_expr(assign_expr *obj) {}
void to_json_compiler::visit_assign_arr_expr(assign_arr_expr *obj) {}
void to_json_compiler::visit_assign_member_expr(assign_member_expr *obj) {}
void to_json_compiler::visit_binary_expr(binary_expr *obj) {}
void to_json_compiler::visit_curly_call_expr(curly_call_expr *obj) {}
void to_json_compiler::visit_fncall_expr(fncall_expr *obj) {}
void to_json_compiler::visit_get_expr(get_expr *obj) {}
void to_json_compiler::visit_grouping_expr(grouping_expr *obj) {}
void to_json_compiler::visit_literal_expr(literal_expr *obj) {}
void to_json_compiler::visit_logical_expr(logical_expr *obj) {}
void to_json_compiler::visit_macro_call_expr(macro_call_expr *obj) {}
void to_json_compiler::visit_set_expr(set_expr *obj) {}
void to_json_compiler::visit_square_bracket_access_expr(
    square_bracket_access_expr *obj) {}
void to_json_compiler::visit_square_bracket_set_expr(
    square_bracket_set_expr *obj) {}
void to_json_compiler::visit_unary_expr(unary_expr *obj) {}
void to_json_compiler::visit_variable_expr(variable_expr *obj) {}
void to_json_compiler::visit_block_stmt(block_stmt *obj) {
  // Code blocks?
}
void to_json_compiler::visit_break_stmt(break_stmt *obj) {}
void to_json_compiler::visit_ccode_stmt(ccode_stmt *obj) {}
void to_json_compiler::visit_cfor_stmt(cfor_stmt *obj) {}
void to_json_compiler::visit_class_stmt(class_stmt *obj) {
  // Both classes and structs are treated the same way
}
void to_json_compiler::visit_compins_stmt(compins_stmt *obj) {
  // This is a special to_c_compiler instruction, no need to be implemented here
}
void to_json_compiler::visit_const_stmt(const_stmt *obj) {}
void to_json_compiler::visit_continue_stmt(continue_stmt *obj) {}
void to_json_compiler::visit_def_stmt(def_stmt *obj) {
  auto name = obj->name_->token_;
  json_ << "{\n";
  json_ << "\"type\": \"def\",\n";
  json_ << "\"name\": \"" << name << "\",\n";
  json_ << "\"params\": [\n";
  for (auto &param : obj->params_) {
    json_ << "{\n";
    json_ << "\"name\": \"" << param.name_->token_ << "\",\n";
    json_ << "\"type\": \"" << param.data_type_->as_string() << "\"\n";
    json_ << "},\n";
  }
  json_ << "],\n";
  json_ << "\"return_type\": \"" << obj->return_type_->as_string() << "\",\n";
  json_ << "\"body\": [\n";
  obj->function_body_->accept(this);// visit block_stmt
  json_ << "]\n";
  json_ << "},\n";
}
void to_json_compiler::visit_defer_stmt(defer_stmt *obj) {}
void to_json_compiler::visit_del_stmt(del_stmt *obj) {}
void to_json_compiler::visit_enum_stmt(enum_stmt *obj) {}
void to_json_compiler::visit_expression_stmt(expression_stmt *obj) {}
void to_json_compiler::visit_foreach_stmt(foreach_stmt *obj) {}
void to_json_compiler::visit_forendless_stmt(forendless_stmt *obj) {}
void to_json_compiler::visit_if_stmt(if_stmt *obj) {}
void to_json_compiler::visit_import_stmt(import_stmt *obj) {}
void to_json_compiler::visit_let_stmt(let_stmt *obj) {}
void to_json_compiler::visit_nativeconst_stmt(nativeconst_stmt *obj) {}
void to_json_compiler::visit_pass_stmt(pass_stmt *obj) {}
void to_json_compiler::visit_return_stmt(return_stmt *obj) {}
void to_json_compiler::visit_runtimefeature_stmt(runtimefeature_stmt *obj) {}
void to_json_compiler::visit_union_stmt(union_stmt *obj) {
  // Placeholder statement - this is not parsed
}
void to_json_compiler::visit_while_stmt(while_stmt *obj) {
  // Placeholder statement - this is not parsed
}
