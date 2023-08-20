// ==============================================================================================
// ╦  ┬┌─┐┌─┐┌┐┌┌─┐┌─┐    Yaksha Programming Language
// ║  ││  ├┤ │││└─┐├┤     is Licensed with GPLv3 + exta terms. Please see below.
// ╩═╝┴└─┘└─┘┘└┘└─┘└─┘
// Note: libs - MIT license, runtime/3rd - various
// ==============================================================================================
// GPLv3:
//
// Yaksha - Programming Language.
// Copyright (C) 2020 - 2023 Bhathiya Perera
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
// ast_vis.h
#ifndef AST_VIS_H
#define AST_VIS_H
#include "ast/ast.h"
#include <sstream>
#include <string>
namespace yaksha {
  /**
   * Print Abstract Syntax Tree as HTML
   */
  struct ast_vis : stmt_visitor, expr_visitor {
    explicit ast_vis();
    ~ast_vis() override = default;
    /**
     * Print given vector of statement as HTML
     * @param statements vector of statements
     */
    void print(const std::vector<stmt *> &statements);
    void field(const std::string &name, expr *expr);
    void field(const std::string &name, stmt *stmt);
    void field(const std::string &name, const std::string &literal_obj);
    void field(const std::string &name, const std::string &literal_obj,
               ykdatatype *dt);
    void begin_block(const std::string &name);
    void end_block();
    void visit_expression_stmt(expression_stmt *obj) override;
    void visit_let_stmt(let_stmt *obj) override;
    void visit_block_stmt(block_stmt *obj) override;
    void visit_if_stmt(if_stmt *obj) override;
    void visit_pass_stmt(pass_stmt *obj) override;
    void visit_variable_expr(variable_expr *obj) override;
    void visit_assign_expr(assign_expr *obj) override;
    void visit_logical_expr(logical_expr *obj) override;
    void visit_while_stmt(while_stmt *obj) override;
    void visit_break_stmt(break_stmt *obj) override;
    void visit_continue_stmt(continue_stmt *obj) override;
    void visit_fncall_expr(fncall_expr *obj) override;
    void visit_def_stmt(def_stmt *obj) override;
    void visit_defer_stmt(defer_stmt *obj) override;
    void visit_del_stmt(del_stmt *obj) override;
    void visit_get_expr(get_expr *obj) override;
    void visit_set_expr(set_expr *obj) override;
    void visit_assign_member_expr(assign_member_expr *obj) override;
    void
    visit_square_bracket_access_expr(square_bracket_access_expr *obj) override;
    void visit_square_bracket_set_expr(square_bracket_set_expr *obj) override;
    void visit_assign_arr_expr(assign_arr_expr *obj) override;
    void visit_ccode_stmt(ccode_stmt *obj) override;
    void visit_class_stmt(class_stmt *obj) override;
    void visit_binary_expr(binary_expr *obj) override;
    void visit_grouping_expr(grouping_expr *obj) override;
    void visit_literal_expr(literal_expr *obj) override;
    void visit_unary_expr(unary_expr *obj) override;
    void visit_return_stmt(return_stmt *obj) override;
    void visit_import_stmt(import_stmt *obj) override;
    void visit_const_stmt(const_stmt *obj) override;
    void visit_runtimefeature_stmt(runtimefeature_stmt *obj) override;
    void visit_nativeconst_stmt(nativeconst_stmt *obj) override;
    void visit_foreach_stmt(foreach_stmt *obj) override;
    void visit_forendless_stmt(forendless_stmt *obj) override;
    void visit_compins_stmt(compins_stmt *obj) override;
    void visit_curly_call_expr(curly_call_expr *obj) override;
    void visit_macro_call_expr(macro_call_expr *obj) override;
    void visit_cfor_stmt(cfor_stmt *obj) override;
    void visit_enum_stmt(enum_stmt *obj) override;
    void visit_union_stmt(union_stmt *obj) override;

private:
    std::stringstream text_{};
  };
}// namespace yaksha
#endif
