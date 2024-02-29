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
// codegen_json.cpp
#include "codegen_json.h"
#include "ast/codefiles.h"
#include "ast/parser.h"
#include "compiler/comp_result.h"
using namespace yaksha;
codegen_json::codegen_json() = default;
codegen_json::~codegen_json() = default;
comp_result codegen_json::emit(codefiles *cf, gc_pool<token> *token_pool) {
  //  return {false, to_json.compile(cf->main_file_info_)};
  std::stringstream multi_file_json{};
  multi_file_json << "{\n";
  multi_file_json << "\"main_file\": ";
  to_json_compiler js{};
  multi_file_json << js.compile(cf->main_file_info_);
  multi_file_json << ",\n";
  multi_file_json << "\"files\": [\n";
  for (file_info *fi : cf->files_) {
    if (fi == cf->main_file_info_) { continue; }
    to_json_compiler to_json{};
    multi_file_json << to_json.compile(fi);
    if (fi != cf->files_.back()) { multi_file_json << ","; }
  }
  multi_file_json << "]\n";
  multi_file_json << "}\n";
  return {false, multi_file_json.str()};
}
std::string to_json_compiler::compile(file_info *fi) {
  // Compile the main file to a JSON
  json_ << "{\n";
  json_ << "\"file_path\": \"" << string_utils::escape_json(fi->filepath_.string())
        << "\",\n";
  json_ << "\"description\": \"Yaksha code export\",\n";
  json_ << "\"version\": \"1.0\",\n";
  json_ << "\"mangle_prefix\": \"" << fi->prefix_ << "\",\n";
  json_ << "\"ast\": [\n";
  auto statements = fi->data_->parser_->stmts_;
  for (auto stmt : statements) {
    stmt->accept(this);
    if (stmt != statements.back()) { json_ << ","; }
  }
  json_ << "]\n";
  json_ << "}\n";
  return json_.str();
}
void to_json_compiler::write_annotations(const annotations &anns) {
  int w = 0;
  json_ << "\"annotations\": [\n";
  if (anns.native_) {
    json_ << "{\"type\": \"native\", ";
    json_ << "\"value\": \"" << string_utils::escape_json(anns.native_arg_) << "\"}";
    w++;
  }
  if (anns.native_define_) {
    if (w > 0) { json_ << ", "; }
    json_ << "{\"type\": \"native_define\", ";
    json_ << "\"value\": \"" << string_utils::escape_json(anns.native_define_arg_)
          << "\"}";
    w++;
  }
  if (anns.native_macro_) {
    if (w > 0) { json_ << ", "; }
    json_ << "{\"type\": \"native_macro\", ";
    json_ << "\"value\": \"" << string_utils::escape_json(anns.native_macro_arg_)
          << "\"}";
  }
  json_ << "],\n"; // NEEDS comma here
}
void to_json_compiler::write_location(expr *obj) {
  auto loc = obj->locate();
  if (loc != nullptr) {
    json_ << "\"location\": {\n";
    json_ << "\"line\": " << loc->line_ << ",\n";
    json_ << "\"column\": " << loc->pos_ << "\n";
    json_ << "},\n";// COMMA is needed here
  }
}
void to_json_compiler::write_location(stmt *obj) {
  auto loc = obj->locate();
  if (loc != nullptr) {
    json_ << "\"location\": {\n";
    json_ << "\"line\": " << loc->line_ << ",\n";
    json_ << "\"column\": " << loc->pos_ << "\n";
    json_ << "},\n";// COMMA is needed here
  }
}
void to_json_compiler::visit_assign_expr(assign_expr *obj) {
  if (!obj->promoted_) {
    json_ << "{\n";
    json_ << "\"type\": \"assign\",\n";
    json_ << "\"name\": \"" << obj->name_->token_ << "\",\n";
    write_location(obj);
    json_ << "\"value\": ";
    obj->right_->accept(this);
    json_ << "\n}\n";
  } else {
    json_ << "{\n";
    json_ << "\"type\": \"let\",\n";
    json_ << "\"promoted\": true,\n";
    json_ << "\"name\": \"" << obj->name_->token_ << "\",\n";
    write_location(obj);
    json_ << "\"datatype\": \"" << string_utils::escape_json(obj->promoted_data_type_->as_string())
          << "\",\n";
    json_ << "\"value\": ";
    obj->right_->accept(this);
    json_ << "\n}\n";
  }
}
void to_json_compiler::visit_assign_arr_expr(assign_arr_expr *obj) {
  json_ << "{\n";
  json_ << "\"type\": \"assign\",\n";
  json_ << "\"name\": ";
  obj->assign_oper_->accept(this);
  json_ << ",\n";
  write_location(obj);
  json_ << "\"value\": ";
  obj->right_->accept(this);
  json_ << "\n}\n";
}
void to_json_compiler::visit_assign_member_expr(assign_member_expr *obj) {
  json_ << "{\n";
  json_ << "\"type\": \"assign\",\n";
  json_ << "\"name\": ";
  obj->set_oper_->accept(this);
  json_ << ",\n";
  write_location(obj);
  json_ << "\"value\": ";
  obj->right_->accept(this);
  json_ << "\n}\n";
}
void to_json_compiler::visit_binary_expr(binary_expr *obj) {
  json_ << "{\n";
  json_ << "\"type\": \"binary\",\n";
  write_location(obj);
  json_ << "\"left\": ";
  obj->left_->accept(this);
  json_ << ",\n";
  json_ << "\"op\": \"" << obj->opr_->token_ << "\",\n";
  json_ << "\"right\": ";
  obj->right_->accept(this);
  json_ << "\n}\n";
}
void to_json_compiler::visit_curly_call_expr(curly_call_expr *obj) {
  json_ << "{\n";
  json_ << "\"type\": \"construct\",\n";
  write_location(obj);
  json_ << "\"datatype\": ";
  obj->dt_expr_->accept(this);
  json_ << ",\n";
  json_ << "\"args\": [\n";
  for (auto &param : obj->values_) {
    json_ << "{\n";
    json_ << "\"name\": \"" << param.name_->token_ << "\",\n";
    json_ << "\"value\": ";
    param.value_->accept(this);
    json_ << "\n";
    json_ << "}\n";
    if (&param != &obj->values_.back()) { json_ << ","; }
  }
  json_ << "]\n";
  json_ << "}\n";
}
void to_json_compiler::visit_fncall_expr(fncall_expr *obj) {
  json_ << "{\n";
  json_ << "\"type\": \"call\",\n";
  write_location(obj);
  json_ << "\"name\": ";
  obj->name_->accept(this);
  json_ << ",\n";
  json_ << "\"args\": [\n";
  for (auto &arg : obj->args_) {
    json_ << "{\n";
    json_ << "\"value\": ";
    arg->accept(this);
    json_ << "\n";
    json_ << "}\n";
    if (&arg != &obj->args_.back()) { json_ << ","; }
  }
  json_ << "]\n";
  json_ << "}\n";
}
void to_json_compiler::visit_get_expr(get_expr *obj) {
  json_ << "{\n";
  json_ << "\"type\": \"get\",\n";
  write_location(obj);
  json_ << "\"name\": ";
  obj->lhs_->accept(this);
  json_ << ",\n";
  json_ << "\"attribute\": \"" << obj->item_->token_;
  json_ << "\"\n}\n";
}
void to_json_compiler::visit_grouping_expr(grouping_expr *obj) {
  obj->expression_->accept(this);
}
void to_json_compiler::visit_literal_expr(literal_expr *obj) {
  json_ << "{\n";
  json_ << "\"type\": \"literal\",\n";
  write_location(obj);
  json_ << "\"token\": \"" << token_to_str(obj->literal_token_->type_)
        << "\",\n";
  json_ << "\"value\": \"" << string_utils::escape_json(obj->literal_token_->token_)
        << "\"\n";
  json_ << "}\n";
}
void to_json_compiler::visit_logical_expr(logical_expr *obj) {
  json_ << "{\n";
  json_ << "\"type\": \"logical\",\n";
  write_location(obj);
  json_ << "\"left\": ";
  obj->left_->accept(this);
  json_ << ",\n";
  json_ << "\"op\": \"" << obj->opr_->token_ << "\",\n";
  json_ << "\"right\": ";
  obj->right_->accept(this);
  json_ << "\n}\n";
}
void to_json_compiler::visit_macro_call_expr(macro_call_expr *obj) {
  // This should be replaced with generated code
}
void to_json_compiler::visit_set_expr(set_expr *obj) {
  json_ << "{\n";
  json_ << "\"type\": \"set\",\n";
  write_location(obj);
  json_ << "\"name\": ";
  obj->lhs_->accept(this);
  json_ << ",\n";
  json_ << "\"attribute\": \"" << obj->item_->token_;
  json_ << "\"\n}\n";
}
void to_json_compiler::visit_square_bracket_access_expr(
    square_bracket_access_expr *obj) {
  json_ << "{\n";
  json_ << "\"type\": \"get[]\",\n";
  write_location(obj);
  json_ << "\"name\": ";
  obj->name_->accept(this);
  json_ << ",\n";
  json_ << "\"index\": ";
  obj->index_expr_->accept(this);
  json_ << "\n}\n";
}
void to_json_compiler::visit_square_bracket_set_expr(
    square_bracket_set_expr *obj) {
  json_ << "{\n";
  json_ << "\"type\": \"set[]\",\n";
  write_location(obj);
  json_ << "\"name\": ";
  obj->name_->accept(this);
  json_ << ",\n";
  json_ << "\"index\": ";
  obj->index_expr_->accept(this);
  json_ << "\n}\n";
}
void to_json_compiler::visit_unary_expr(unary_expr *obj) {
  json_ << "{\n";
  json_ << "\"type\": \"unary\",\n";
  write_location(obj);
  json_ << "\"op\": \"" << obj->opr_->token_ << "\",\n";
  json_ << "\"right\": ";
  obj->right_->accept(this);
  json_ << "\n}\n";
}
void to_json_compiler::visit_variable_expr(variable_expr *obj) {
  json_ << "{\n";
  json_ << "\"type\": \"variable\",\n";
  write_location(obj);
  json_ << "\"name\": \"" << obj->name_->token_ << "\"\n";
  json_ << "}\n";
}
void to_json_compiler::visit_block_stmt(block_stmt *obj) {
  // Note this is already inside an []
  for (stmt *s : obj->statements_) {
    s->accept(this);
    if (s != obj->statements_.back()) { json_ << ","; }
  }
}
void to_json_compiler::visit_break_stmt(break_stmt *obj) {
  json_ << "{\n";
  write_location(obj);
  json_ << "\"type\": \"break\"\n";
  json_ << "}\n";
}
void to_json_compiler::visit_ccode_stmt(ccode_stmt *obj) {
  json_ << "{\n";
  write_location(obj);
  json_ << "\"type\": \"ccode\",\n";
  json_ << "\"code\": \"" << string_utils::escape_json(obj->code_str_->token_)
        << "\"\n";
  json_ << "}\n";
}
void to_json_compiler::visit_cfor_stmt(cfor_stmt *obj) {
  json_ << "{\n";
  write_location(obj);
  json_ << "\"type\": \"cfor\",\n";
  json_ << "\"init\": ";
  obj->init_expr_->accept(this);
  json_ << ",\n";
  json_ << "\"condition\": ";
  obj->comparison_->accept(this);
  json_ << ",\n";
  json_ << "\"increment\": ";
  obj->operation_->accept(this);
  json_ << ",\n";
  json_ << "\"body\": [";
  obj->for_body_->accept(this);
  json_ << "]\n";
  json_ << "}\n";
}
void to_json_compiler::visit_class_stmt(class_stmt *obj) {
  json_ << "{\n";
  write_location(obj);
  if (obj->annotations_.on_stack_) {
    json_ << "\"type\": \"struct\",\n";
  } else {
    json_ << "\"type\": \"class\",\n";
  }
  json_ << "\"name\": \"" << obj->name_->token_ << "\",\n";
  write_annotations(obj->annotations_);
  json_ << "\"fields\": [\n";
  for (auto &field : obj->members_) {
    json_ << "{\n";
    json_ << "\"name\": \"" << field.name_->token_ << "\",\n";
    json_ << "\"datatype\": \"" << string_utils::escape_json(field.data_type_->as_string()) << "\"\n";
    json_ << "}\n";
    if (&field != &obj->members_.back()) { json_ << ","; }
  }
  json_ << "]\n";
  json_ << "}\n";
}
void to_json_compiler::visit_compins_stmt(compins_stmt *obj) {
  // This is a special to_c_compiler instruction, no need to be implemented here
}
void to_json_compiler::visit_const_stmt(const_stmt *obj) {
  json_ << "{\n";
  write_location(obj);
  json_ << "\"type\": \"const\",\n";
  json_ << "\"ccode\": false,\n";
  json_ << "\"name\": \"" << obj->name_->token_ << "\",\n";
  json_ << "\"datatype\": \"" << string_utils::escape_json(obj->data_type_->as_string()) << "\",\n";
  json_ << "\"value\": ";
  obj->expression_->accept(this);
  json_ << "\n}\n";
}
void to_json_compiler::visit_continue_stmt(continue_stmt *obj) {
  json_ << "{\n";
  write_location(obj);
  json_ << "\"type\": \"continue\"\n";
  json_ << "}\n";
}
void to_json_compiler::visit_def_stmt(def_stmt *obj) {
  auto name = obj->name_->token_;
  json_ << "{\n";
  write_location(obj);
  json_ << "\"type\": \"def\",\n";
  write_annotations(obj->annotations_);
  json_ << "\"name\": \"" << name << "\",\n";
  json_ << "\"params\": [\n";
  for (auto &param : obj->params_) {
    json_ << "{\n";
    json_ << "\"name\": \"" << param.name_->token_ << "\",\n";
    json_ << "\"type\": \"" << string_utils::escape_json(param.data_type_->as_string()) << "\"\n";
    json_ << "}\n";
    if (&param != &obj->params_.back()) { json_ << ","; }
  }
  json_ << "],\n";
  json_ << "\"return_type\": \"" << string_utils::escape_json(obj->return_type_->as_string()) << "\",\n";
  json_ << "\"body\": [\n";
  obj->function_body_->accept(this);// visit block_stmt
  json_ << "]\n";
  json_ << "}\n";
}
void to_json_compiler::visit_defer_stmt(defer_stmt *obj) {
  if (obj->expression_ == nullptr) {
    json_ << "{\n";
    write_location(obj);
    json_ << "\"type\": \"defer\",\n";
    json_ << "\"expression\": \n";
    obj->del_statement_->accept(this);// visit block_stmt
    json_ << "\n";
    json_ << "}\n";
  } else {
    json_ << "{\n";
    json_ << "\"type\": \"defer\",\n";
    json_ << "\"expression\": \n";
    obj->expression_->accept(this);// visit block_stmt
    json_ << "\n";
    json_ << "}\n";
  }
}
void to_json_compiler::visit_del_stmt(del_stmt *obj) {
  json_ << "{\n";
  write_location(obj);
  json_ << "\"type\": \"del\",\n";
  json_ << "\"element\": ";
  obj->expression_->accept(this);
  json_ << "\n";
  json_ << "}\n";
}
void to_json_compiler::visit_enum_stmt(enum_stmt *obj) {
  // Placeholder statement - this is not parsed
}
void to_json_compiler::visit_expression_stmt(expression_stmt *obj) {
  obj->expression_->accept(this);
}
void to_json_compiler::visit_foreach_stmt(foreach_stmt *obj) {
  json_ << "{\n";
  write_location(obj);
  json_ << "\"type\": \"foreach\",\n";
  json_ << "\"name\": \"" << obj->name_->token_ << "\",\n";
  json_ << "\"datatype\": \"" << string_utils::escape_json(obj->data_type_->as_string()) << "\",\n";
  json_ << "\"expression\": ";
  obj->expression_->accept(this);
  json_ << ",\n";
  json_ << "\"body\": [";
  obj->for_body_->accept(this);
  json_ << "]\n";
  json_ << "}\n";
}
void to_json_compiler::visit_forendless_stmt(forendless_stmt *obj) {
  json_ << "{\n";
  write_location(obj);
  json_ << "\"type\": \"loop\",\n";
  json_ << "\"body\": [";
  obj->for_body_->accept(this);
  json_ << "]\n";
  json_ << "}\n";
}
void to_json_compiler::visit_if_stmt(if_stmt *obj) {
  if (obj->else_branch_ == nullptr) {
    json_ << "{\n";
    write_location(obj);
    json_ << "\"type\": \"if\",\n";
    json_ << "\"condition\": ";
    obj->expression_->accept(this);
    json_ << ",\n";
    json_ << "\"if_body\": [";
    obj->if_branch_->accept(this);
    json_ << "]\n";
    json_ << "}\n";
  } else {
    json_ << "{\n";
    write_location(obj);
    json_ << "\"type\": \"if\",\n";
    json_ << "\"condition\": ";
    obj->expression_->accept(this);
    json_ << ",\n";
    json_ << "\"if_body\": [";
    obj->if_branch_->accept(this);
    json_ << "],\n";
    json_ << "\"else\": [";
    obj->else_branch_->accept(this);
    json_ << "]\n";
    json_ << "}\n";
  }
}
void to_json_compiler::visit_import_stmt(import_stmt *obj) {
  json_ << "{\n";
  write_location(obj);
  json_ << "\"type\": \"import\",\n";
  json_ << "\"import_path\": [";
  for (token *p : obj->import_names_) {
    json_ << "\"" << p->token_ << "\"";
    if (p != obj->import_names_.back()) { json_ << ", "; }
  }
  json_ << "],\n";
  json_ << "\"file_path\": \""
        << string_utils::escape_json(obj->data_->filepath_.string()) << "\",\n";
  json_ << "\"mangle_prefix\": \"" << obj->data_->prefix_ << "\",\n";
  json_ << "\"name\": \"" << obj->name_->token_ << "\"\n";
  json_ << "}\n";
}
void to_json_compiler::visit_let_stmt(let_stmt *obj) {
  json_ << "{\n";
  write_location(obj);
  json_ << "\"type\": \"let\",\n";
  json_ << "\"name\": \"" << obj->name_->token_ << "\",",
      json_ << "\"datatype\": \"" << string_utils::escape_json(obj->data_type_->as_string()) << "\"\n";
  if (obj->expression_ != nullptr) {
    json_ << ",\"value\": ";
    obj->expression_->accept(this);
  }
  json_ << "\n}";
}
void to_json_compiler::visit_nativeconst_stmt(nativeconst_stmt *obj) {
  json_ << "{\n";
  write_location(obj);
  json_ << "\"type\": \"const\",\n";
  json_ << "\"ccode\": true,\n";
  json_ << "\"name\": \"" << obj->name_->token_ << "\",\n";
  json_ << "\"datatype\": \"" << string_utils::escape_json(obj->data_type_->as_string()) << "\",\n";
  json_ << "\"value\": \"";
  json_ << string_utils::escape_json(obj->code_str_->token_);
  json_ << "\"\n}\n";
}
void to_json_compiler::visit_pass_stmt(pass_stmt *obj) {
  json_ << "{\n";
  write_location(obj);
  json_ << "\"type\": \"pass\"\n";
  json_ << "}\n";
}
void to_json_compiler::visit_return_stmt(return_stmt *obj) {
  if (obj->expression_ == nullptr) {
    json_ << "{\n";
    write_location(obj);
    json_ << "\"type\": \"return\"\n";
    json_ << "}\n";
  } else {
    json_ << "{\n";
    write_location(obj);
    json_ << "\"type\": \"return\",\n";
    json_ << "\"value\": ";
    obj->expression_->accept(this);
    json_ << "\n}\n";
  }
}
void to_json_compiler::visit_runtimefeature_stmt(runtimefeature_stmt *obj) {
  json_ << "{\n";
  write_location(obj);
  json_ << "\"type\": \"runtimefeature\",\n";
  json_ << "\"feature\": \"" << obj->feature_->token_ << "\"\n";
  json_ << "}\n";
}
void to_json_compiler::visit_union_stmt(union_stmt *obj) {
  // Placeholder statement - this is not parsed
}
void to_json_compiler::visit_while_stmt(while_stmt *obj) {
  json_ << "{\n";
  write_location(obj);
  json_ << "\"type\": \"while\",\n";
  json_ << "\"condition\": ";
  obj->expression_->accept(this);
  json_ << ",\n";
  json_ << "\"body\": [";
  obj->while_body_->accept(this);
  json_ << "]\n";
  json_ << "}\n";
}
