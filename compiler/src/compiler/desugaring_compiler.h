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
// desugaring_compiler.h
#ifndef DESUGARING_COMPILER_H
#define DESUGARING_COMPILER_H
#include "ast/ast.h"
#include "utilities/ykdt_pool.h"
#include <algorithm>
#include <map>
#include <sstream>
#include <string>
#include <vector>
namespace yaksha {
  struct to_c_compiler;
  /**
   * Desugaring compiler
   *    - Desugaring also happens at parser
   *    - However, this is for additional desugaring needs
   *    - Ex: for loops, etc that needs rewriting for block's continue statements
   * compile AST -> AST desugared
   */
  struct desugaring_compiler : private stmt_visitor {
    explicit desugaring_compiler(ast_pool *ast_pool_obj,
                                 ykdt_pool *dt_pool_obj);
    std::vector<stmt *> desugar(const std::vector<stmt *> &statements,
                                to_c_compiler *compiler_obj);
    ~desugaring_compiler() override;

private:
    std::vector<std::vector<stmt *> *> statement_stack_;
    std::vector<stmt *> global_statements_;
    std::vector<stmt *> pre_continue_stack_;
    std::vector<token *> internal_token_pool_;
    ast_pool *ast_pool_;
    ykdt_pool *dt_pool_;

    token *true_token_;
    token *while_token_;
    token *break_token_;
    token *if_token_;
    token *not_token_;
    token *paren_token_;
    token *ccode_token_;
    token *less_token_;
    token *plus_eq_token_;
    to_c_compiler *compiler_obj_;
    token *create_name(const std::string &name);
    token *create_int_literal(const std::string &lit);
    token *create_str_literal(const std::string &string_literal_content);
    stmt *desugar(stmt *obj);
    // Implement stmt_visitor only
    // WHY:
    // We only support statement level desugar at the moment
    // If we do support expression level we can introduce those later
    void visit_block_stmt(block_stmt *obj) override;
    void visit_break_stmt(break_stmt *obj) override;
    void visit_ccode_stmt(ccode_stmt *obj) override;
    void visit_class_stmt(class_stmt *obj) override;
    void visit_compins_stmt(compins_stmt *obj) override;
    void visit_const_stmt(const_stmt *obj) override;
    void visit_continue_stmt(continue_stmt *obj) override;
    void visit_def_stmt(def_stmt *obj) override;
    void visit_defer_stmt(defer_stmt *obj) override;
    void visit_del_stmt(del_stmt *obj) override;
    void visit_expression_stmt(expression_stmt *obj) override;
    void visit_foreach_stmt(foreach_stmt *obj) override;
    void visit_forendless_stmt(forendless_stmt *obj) override;
    void visit_if_stmt(if_stmt *obj) override;
    void visit_import_stmt(import_stmt *obj) override;
    void visit_let_stmt(let_stmt *obj) override;
    void visit_nativeconst_stmt(nativeconst_stmt *obj) override;
    void visit_pass_stmt(pass_stmt *obj) override;
    void visit_return_stmt(return_stmt *obj) override;
    void visit_runtimefeature_stmt(runtimefeature_stmt *obj) override;
    void visit_while_stmt(while_stmt *obj) override;
    void visit_cfor_stmt(cfor_stmt *obj) override;
    void visit_enum_stmt(enum_stmt *obj) override;
    void visit_union_stmt(union_stmt *obj) override;
    void desugar_fixed_arr_foreach(foreach_stmt *obj);
    void desugar_arr_foreach(foreach_stmt *obj);
  };
}// namespace yaksha
#endif
