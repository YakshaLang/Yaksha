
// ==============================================================================================
// ╦  ┬┌─┐┌─┐┌┐┌┌─┐┌─┐    Yaksha Programming Language
// ║  ││  ├┤ │││└─┐├┤     is Licensed with GPLv3 + extra terms. Please see below.
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
// type_checker.h
#ifndef TYPE_CHECKER_H
#define TYPE_CHECKER_H
#include "ast/ast.h"
#include "ast/codefiles.h"
#include "ast/environment_stack.h"
#include "builtins/builtins.h"
#include "compiler/def_class_visitor.h"
#include "compiler/slot_matcher.h"
#include "return_checker.h"
#include "utilities/ykobject.h"
namespace yaksha {
  struct type_checker : expr_visitor, stmt_visitor, slot_matcher {
    explicit type_checker(std::string filepath, codefiles *cf,
                          def_class_visitor *dcv, ykdt_pool *pool,
                          gc_pool<token> *token_pool);
    ~type_checker() override;
    bool slot_match(const ykobject &arg, ykdatatype *datatype) override;
    ykdatatype *function_to_datatype(const ykobject &arg) override;
    void check(const std::vector<stmt *> &statements);
    void visit_assign_expr(assign_expr *obj) override;
    void visit_binary_expr(binary_expr *obj) override;
    void visit_fncall_expr(fncall_expr *obj) override;
    void visit_grouping_expr(grouping_expr *obj) override;
    void visit_literal_expr(literal_expr *obj) override;
    void visit_logical_expr(logical_expr *obj) override;
    void visit_unary_expr(unary_expr *obj) override;
    void visit_variable_expr(variable_expr *obj) override;
    void visit_block_stmt(block_stmt *obj) override;
    void visit_break_stmt(break_stmt *obj) override;
    void visit_continue_stmt(continue_stmt *obj) override;
    void visit_def_stmt(def_stmt *obj) override;
    void visit_class_stmt(class_stmt *obj) override;
    void visit_expression_stmt(expression_stmt *obj) override;
    void visit_if_stmt(if_stmt *obj) override;
    void visit_let_stmt(let_stmt *obj) override;
    void visit_pass_stmt(pass_stmt *obj) override;
    void visit_return_stmt(return_stmt *obj) override;
    void visit_while_stmt(while_stmt *obj) override;
    void visit_defer_stmt(defer_stmt *obj) override;
    void visit_del_stmt(del_stmt *obj) override;
    void visit_get_expr(get_expr *obj) override;
    void visit_set_expr(set_expr *obj) override;
    void visit_assign_member_expr(assign_member_expr *obj) override;
    void
    visit_square_bracket_access_expr(square_bracket_access_expr *obj) override;
    void visit_assign_arr_expr(assign_arr_expr *obj) override;
    void visit_square_bracket_set_expr(square_bracket_set_expr *obj) override;
    void visit_ccode_stmt(ccode_stmt *obj) override;
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
    /**
     * Errors vector, type checker will try and identify as much errors as possible
     * but after first error, everything else is best guess
     */
    std::vector<parsing_error> errors_;
    /**
     * Get function information
     */
    def_class_visitor *defs_classes_;
    // Scope
    environment_stack scope_;
    codefiles *cf_;
    std::string filepath_;

private:
    ykobject pop();
    // TODO why is this method not used?
    class_stmt *find_class(token *tok, ykdatatype *data_type);
    void push(const ykobject &data_type);
    void error(token *tok, const std::string &message);
    void error(const std::string &message);
    void push_scope_type(ast_type scope_type);
    ast_type peek_scope_type();
    void pop_scope_type();
    void push_function(const std::string &prefixed_name);
    std::string peek_function();
    void pop_function();
    void handle_dot_operator(expr *lhs_expr, token *dot, token *member_item);
    void handle_square_access(expr *index_expr, token *sqb_token,
                              expr *name_expr, bool mutate);
    void handle_assigns(token *oper, const ykobject &lhs, const ykobject &rhs);
    // Data type pool
    ykdt_pool *dt_pool_;
    std::vector<ykobject> object_stack_{};
    // Different types of scopes stack, -> are we in function body, if or while
    std::vector<ast_type> scope_type_stack_{};
    // Function stack
    std::vector<std::string> function_name_stack_{};
    // Builtin functions
    builtins builtins_;
    // Copy of internal stmt_alias to handle dt parsing in builtins
    std::unordered_map<std::string, import_stmt *> import_stmts_alias_{};
    // TODO why is this method not used?
    void validate_member(name_val &member, class_stmt *class_st);
    return_checker return_checker_{};
    ast_pool *ast_pool_;
    token *magic_return_token_;
  };
}// namespace yaksha
#endif
