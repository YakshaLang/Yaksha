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
// ast_vis.cpp
#include "ast_vis.h"
#include <iostream>
#include <tokenizer/string_utils.h>
using namespace yaksha;
ast_vis::ast_vis() {
  text_ << "<!DOCTYPE html>\n"
           "<html lang=\"en\">\n"
           "<head>\n"
           "    <meta charset=\"UTF-8\">\n"
           "    <title>Yaksha - AST Visualizer</title>\n"
           "    <style>\n"
           "        html, body {\n"
           "            background-color: #444444;\n"
           "            color: #eeeeee;\n"
           "        }\n"
           "        * {\n"
           "            font-family: monospace;\n"
           "        }\n"
           "\n"
           "        .block {\n"
           "            display: inline-block;\n"
           "            border: 1px solid black;\n"
           "            padding: 1px;\n"
           "            margin: 1px;\n"
           "        }\n"
           "\n"
           "        .block_title {\n"
           "            display: block;\n"
           "            border: none;\n"
           "            background-color: #1F3C1F;\n"
           "            padding-left: 1px;\n"
           "            padding-right: 1px;\n"
           "            margin-bottom: 1px;\n"
           "        }\n"
           "\n"
           "        .field {\n"
           "            display: inline-block;\n"
           "            border: 1px dashed black;\n"
           "            padding: 1px;\n"
           "            margin: 1px;\n"
           "        }\n"
           "\n"
           "        .field_title {\n"
           "            display: block;\n"
           "            border: none;\n"
           "            background-color: #417070;\n"
           "            padding-left: 1px;\n"
           "            padding-right: 1px;\n"
           "            margin-bottom: 1px;\n"
           "        }\n"
           "        code {\n"
           "            background: #1F3C1F;\n"
           "            color: #29ff29;\n"
           "            padding: 0 3px;\n"
           "        }\n"
           "        .cyan-code {\n"
           "            background: #03363d;\n"
           "            color: #00e1ff;\n"
           "            padding: 0 3px;\n"
           "        }\n"
           "    </style>\n"
           "</head>\n"
           "<body>";
}
void ast_vis::visit_binary_expr(binary_expr *obj) {
  begin_block("binary");
  field("left", obj->left_);
  field("opr", obj->opr_->token_);
  field("right", obj->right_);
  end_block();
}
void ast_vis::visit_grouping_expr(grouping_expr *obj) {
  begin_block("grouping");
  field("expression", obj->expression_);
  end_block();
}
void ast_vis::visit_literal_expr(literal_expr *obj) {
  text_ << ::string_utils::html_escape(obj->literal_token_->token_);
}
void ast_vis::visit_unary_expr(unary_expr *obj) {
  begin_block("unary");
  field("opr", obj->opr_->token_);
  field("right", obj->right_);
  end_block();
}
void ast_vis::visit_return_stmt(return_stmt *obj) {
  begin_block("return");
  if (obj->expression_ != nullptr) { field("value", obj->expression_); }
  end_block();
}
void ast_vis::field(const std::string &name, expr *expr) {
  text_ << R"(<div class="field"><div class="field_title">)"
        << ::string_utils::html_escape(name) << "</div>";
  expr->accept(this);
  text_ << "</div>";
}
void ast_vis::field(const std::string &name, stmt *stmt) {
  text_ << R"(<div class="field"><div class="field_title">)"
        << ::string_utils::html_escape(name) << "</div>";
  stmt->accept(this);
  text_ << "</div>";
}
void ast_vis::field(const std::string &name, const std::string &literal_obj) {
  text_ << R"(<div class="field"><div class="field_title">)"
        << ::string_utils::html_escape(name) << "</div>";
  text_ << ::string_utils::html_escape(literal_obj);
  text_ << "</div>";
}
void ast_vis::begin_block(const std::string &name) {
  text_ << R"(<div class="block"><div class="block_title">)"
        << ::string_utils::html_escape(name) << "</div>";
}
void ast_vis::end_block() { text_ << "</div>"; }
void ast_vis::visit_expression_stmt(expression_stmt *obj) {
  begin_block("expr");
  obj->expression_->accept(this);
  end_block();
}
void ast_vis::print(const std::vector<stmt *> &statements) {
  for (auto statement : statements) {
    statement->accept(this);
    text_ << "\n<hr />";
  }
  text_ << "</body>\n"
           "</html>";
  std::cout << text_.str() << "\n";
}
void ast_vis::visit_variable_expr(variable_expr *obj) {
  text_ << ::string_utils::html_escape(obj->name_->token_);
}
void ast_vis::visit_let_stmt(let_stmt *obj) {
  begin_block("let");
  field("name", obj->name_->token_);
  if (obj->expression_ != nullptr) { field("value", obj->expression_); }
  end_block();
}
void ast_vis::visit_assign_expr(assign_expr *obj) {
  begin_block("assign");
  field("name", obj->name_->token_);
  field("value", obj->right_);
  end_block();
}
void ast_vis::visit_block_stmt(block_stmt *obj) {
  begin_block("block");
  for (auto st : obj->statements_) {
    st->accept(this);
    text_ << "\n<br />";
  }
  end_block();
}
void ast_vis::visit_if_stmt(if_stmt *obj) {
  begin_block("if");
  field("condition", obj->expression_);
  text_ << "\n<br />";
  field("if-branch", obj->if_branch_);
  if (obj->else_branch_ != nullptr) { field("else-branch", obj->else_branch_); }
  end_block();
}
void ast_vis::visit_pass_stmt(pass_stmt *obj) {
  begin_block("nop");
  end_block();
}
void ast_vis::visit_logical_expr(logical_expr *obj) {
  begin_block("logical");
  field("left", obj->left_);
  field("opr", obj->opr_->token_);
  field("right", obj->right_);
  end_block();
}
void ast_vis::visit_while_stmt(while_stmt *obj) {
  begin_block("while");
  field("condition", obj->expression_);
  text_ << "\n<br />";
  field("body", obj->while_body_);
  end_block();
}
void ast_vis::visit_break_stmt(break_stmt *obj) {
  begin_block("break");
  end_block();
}
void ast_vis::visit_continue_stmt(continue_stmt *obj) {
  begin_block("continue");
  end_block();
}
void ast_vis::visit_fncall_expr(fncall_expr *obj) {
  begin_block("call");
  field("name", obj->name_);
  for (auto st : obj->args_) { field("arg", st); }
  end_block();
}
void ast_vis::visit_def_stmt(def_stmt *obj) {
  begin_block("def");
  if (obj->annotations_.native_macro_) {
    field("@nativemacro", obj->annotations_.native_macro_arg_);
  } else if (obj->annotations_.native_) {
    field("@native", obj->annotations_.native_arg_);
  }
  field("name", obj->name_->token_);
  for (auto st : obj->params_) {
    field("param", st.name_->token_, st.data_type_);
  }
  text_ << "\n<br />";
  field("body", obj->function_body_);
  end_block();
}
void ast_vis::visit_defer_stmt(defer_stmt *obj) {
  begin_block("defer");
  if (obj->expression_ != nullptr) {
    field("expression", obj->expression_);
  } else {
    obj->del_statement_->accept(this);
  }
  end_block();
}
void ast_vis::visit_class_stmt(class_stmt *obj) {
  begin_block("class");
  field("name", obj->name_->token_);
  for (auto st : obj->members_) {
    field("member", st.name_->token_, st.data_type_);
  }
  text_ << "\n<br />";
  end_block();
}
void ast_vis::field(const std::string &name, const std::string &literal_obj,
                    ykdatatype *dt) {
  text_ << R"(<div class="field"><div class="field_title">)"
        << ::string_utils::html_escape(name) << "</div>";
  text_ << ::string_utils::html_escape(literal_obj) << ": <code>";
  text_ << ::string_utils::html_escape(dt->as_string());
  text_ << "</code></div>";
}
void ast_vis::visit_del_stmt(del_stmt *obj) {
  begin_block("del");
  field("expression", obj->expression_);
  end_block();
}
void ast_vis::visit_get_expr(get_expr *obj) {
  begin_block("get");
  field("lhs", obj->lhs_);
  field("item", obj->item_->token_);
  end_block();
}
void ast_vis::visit_set_expr(set_expr *obj) {
  begin_block("set");
  field("lhs", obj->lhs_);
  field("item", obj->item_->token_);
  end_block();
}
void ast_vis::visit_assign_member_expr(assign_member_expr *obj) {
  begin_block("assign.");
  field("name", obj->set_oper_);
  field("value", obj->right_);
  end_block();
}
void ast_vis::visit_square_bracket_access_expr(
    square_bracket_access_expr *obj) {
  begin_block("get[]");
  field("array", obj->name_);
  field("index", obj->index_expr_);
  end_block();
}
void ast_vis::visit_square_bracket_set_expr(square_bracket_set_expr *obj) {
  begin_block("set[]");
  field("array", obj->name_);
  field("index", obj->index_expr_);
  end_block();
}
void ast_vis::visit_assign_arr_expr(assign_arr_expr *obj) {
  begin_block("assign[]");
  field("name", obj->assign_oper_);
  field("value", obj->right_);
  end_block();
}
void ast_vis::visit_ccode_stmt(ccode_stmt *obj) {
  begin_block("c");
  text_ << "<pre class=\"cyan-code\">"
        << ::string_utils::html_escape(
               string_utils::unescape(obj->code_str_->token_))
        << "</pre>" << "<br />";
  end_block();
}
void ast_vis::visit_import_stmt(import_stmt *obj) {
  begin_block("import");
  std::stringstream name;
  bool first = true;
  for (auto tok : obj->import_names_) {
    if (first) {
      first = false;
    } else {
      name << ".";
    }
    name << tok->token_;
  }
  field("path", name.str());
  end_block();
}
void ast_vis::visit_const_stmt(const_stmt *obj) {
  begin_block("const");
  field("name", obj->name_->token_);
  if (obj->expression_ != nullptr) { field("value", obj->expression_); }
  end_block();
}
void ast_vis::visit_nativeconst_stmt(nativeconst_stmt *obj) {
  begin_block("nativeconst");
  field("name", obj->name_->token_);
  if (obj->code_str_ != nullptr) {
    begin_block("c");
    text_ << "<pre class=\"cyan-code\">"
          << ::string_utils::html_escape(
                 string_utils::unescape(obj->code_str_->token_))
          << "</pre>" << "<br />";
    end_block();
  }
  end_block();
}
void ast_vis::visit_runtimefeature_stmt(runtimefeature_stmt *obj) {
  begin_block("feature");
  text_ << "<pre class=\"cyan-code\">"
        << ::string_utils::html_escape(
               string_utils::unescape(obj->feature_->token_))
        << "</pre>" << "<br />";
  end_block();
}
void ast_vis::visit_foreach_stmt(foreach_stmt *obj) {
  begin_block("for");
  field("let", obj->name_->token_);
  field("condition", obj->expression_);
  text_ << "\n<br />";
  field("body", obj->for_body_);
  end_block();
}
void ast_vis::visit_forendless_stmt(forendless_stmt *obj) {
  begin_block("for");
  text_ << "\n<br />";
  field("body", obj->for_body_);
  end_block();
}
void ast_vis::visit_compins_stmt(compins_stmt *obj) {
  // Does not occur in AST
}
void ast_vis::visit_curly_call_expr(curly_call_expr *obj) {
  begin_block("struct");
  field("datatype", obj->dt_expr_);
  for (auto st : obj->values_) { field("." + st.name_->token_, st.value_); }
  text_ << "\n<br />";
  end_block();
}
void ast_vis::visit_macro_call_expr(macro_call_expr *obj) {
  begin_block("macro");
  field("name", obj->name_->token_);
  if (obj->paren_token_->type_ == token_type::CURLY_BRACKET_OPEN) {
    field("type", "dsl");
  }
  for (auto st : obj->args_) { field("arg", st); }
  text_ << "\n<br />";
  end_block();
}
void ast_vis::visit_cfor_stmt(cfor_stmt *obj) {}
void ast_vis::visit_enum_stmt(enum_stmt *obj) {}
void ast_vis::visit_directive_stmt(directive_stmt *obj) {}
