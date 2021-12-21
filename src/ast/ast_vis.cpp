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
void ast_vis::visit_return_stmt(return_stmt *obj) {}
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
void ast_vis::print(expr *st) {
  st->accept(this);
  text_ << "</body>\n"
           "</html>";
  std::cout << text_.str() << "\n";
}
void ast_vis::visit_expression_stmt(expression_stmt *obj) {
  begin_block("expr-statement");
  obj->expression_->accept(this);
  end_block();
}
void ast_vis::visit_print_stmt(print_stmt *obj) {
  begin_block("print-statement");
  field("expression", obj->expression_);
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
  begin_block("let-statement");
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
  begin_block("block-statement");
  for (auto st : obj->statements_) {
    st->accept(this);
    text_ << "\n<br />";
  }
  end_block();
}
void ast_vis::visit_if_stmt(if_stmt *obj) {
  begin_block("if-statement");
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
  begin_block("while-statement");
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
