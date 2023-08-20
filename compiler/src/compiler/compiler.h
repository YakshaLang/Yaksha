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
// compiler.h
#ifndef COMPILER_H
#define COMPILER_H
#include "ast/ast.h"
#include "ast/codefiles.h"
#include "ast/environment_stack.h"
#include "builtins/builtins.h"
#include "compiler/compiler_utils.h"
#include "compiler/delete_stack_stack.h"
#include "compiler/desugaring_compiler.h"
#include "compiler/function_datatype_extractor.h"
#include "compiler/statement_writer.h"
#include "datatype_compiler.h"
#include "def_class_visitor.h"
#include "entry_struct_func_compiler.h"
#include "tokenizer/token.h"
#include "utilities/cpp_util.h"
#include "utilities/defer_stack_stack.h"
#include <sstream>
namespace yaksha {
  struct compiler_output {
    std::string struct_forward_declarations_{};
    std::string function_forward_declarations_{};
    std::string classes_{};
    std::string body_{};
    std::string global_constants_{};
    std::vector<parsing_error> errors_{};
  };
  struct compiler : expr_visitor,
                    stmt_visitor,
                    datatype_compiler,
                    statement_writer,
                    function_datatype_extractor {
    compiler(def_class_visitor &defs_classes, ykdt_pool *pool,
             entry_struct_func_compiler *esc, gc_pool<token> *token_pool);
    ~compiler() override;
    compiler_output compile(codefiles *cf, file_info *fi);
    ykdatatype *function_to_datatype(const ykobject &arg) override;
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
    void visit_expression_stmt(expression_stmt *obj) override;
    void visit_if_stmt(if_stmt *obj) override;
    void visit_let_stmt(let_stmt *obj) override;
    void visit_pass_stmt(pass_stmt *obj) override;
    void visit_return_stmt(return_stmt *obj) override;
    void visit_while_stmt(while_stmt *obj) override;
    void visit_defer_stmt(defer_stmt *obj) override;
    void visit_class_stmt(class_stmt *obj) override;
    void visit_del_stmt(del_stmt *obj) override;
    void visit_get_expr(get_expr *obj) override;
    void visit_set_expr(set_expr *obj) override;
    void visit_assign_member_expr(assign_member_expr *obj) override;
    void
    visit_square_bracket_access_expr(square_bracket_access_expr *obj) override;
    void visit_square_bracket_set_expr(square_bracket_set_expr *obj) override;
    void visit_assign_arr_expr(assign_arr_expr *obj) override;
    void visit_ccode_stmt(ccode_stmt *obj) override;
    void visit_import_stmt(import_stmt *obj) override;
    void visit_const_stmt(const_stmt *obj) override;
    void visit_runtimefeature_stmt(runtimefeature_stmt *obj) override;
    void visit_nativeconst_stmt(nativeconst_stmt *obj) override;
    void visit_foreach_stmt(foreach_stmt *obj) override;
    void visit_forendless_stmt(forendless_stmt *obj) override;
    std::string prefix_token(token *p_token);
    void visit_compins_stmt(compins_stmt *obj) override;
    void visit_curly_call_expr(curly_call_expr *obj) override;
    /**
     * Convert Yaksha data type to appropriate C data type.
     * @param basic_dt data type as a token.
     * @return converted data type.
     */
    std::string convert_dt(ykdatatype *basic_dt) override;
    /**
     * @return unique temp variable name
     */
    std::string temp() override;
    std::string temp(const std::string &custom_prefix) override;
    /**
     * Write a statement to code body (in current function)
     */
    void write_statement(std::string code_line) override;
    /**
     * Write a statement to code body (in current function) without ';'
     */
    void write_statement_no_end(std::string code_line) override;
    void indent() override;
    void dedent() override;
    void visit_macro_call_expr(macro_call_expr *obj) override;
    void compile_string_assign(token *t, std::stringstream &code,
                               const std::pair<std::string, ykobject> &rhs,
                               const ykdatatype *rhs_datatype,
                               const ykdatatype *lhs_datatype) override;
    std::string wrap_in_paren(const std::string &code) const override;
    void visit_cfor_stmt(cfor_stmt *obj) override;
    void visit_enum_stmt(enum_stmt *obj) override;
    void visit_union_stmt(union_stmt *obj) override;

private:
    void push_scope_type(ast_type scope_type);
    ast_type peek_scope_type();
    void pop_scope_type();
    void write_indent(std::stringstream &where) const;
    void write_prev_indent(std::stringstream &where) const;
    void write_end_statement(std::stringstream &where);
    void push(const std::string &expr, const ykobject &data_type);
    void error(token *tok, const std::string &message);
    void error(const std::string &message);
    std::string conv_integer_literal(token_type token_type_val,
                                     token *literal_token);
    std::string prefix_val_{};
    codefiles *cf_{nullptr};
    std::pair<std::string, ykobject> pop();
    std::pair<std::string, ykobject> compile_expression(expr *ex);
    // Indentation to generate
    int indent_{0};
    // Counter for temp variables.
    long temp_{0};
    // inline
    bool inline_mode_{false};
    long statements_{0};
    builtins builtins_;
    /**
     * Function declarations, etc
     */
    std::stringstream struct_forward_declarations_{};
    std::stringstream function_forward_declarations_{};
    std::stringstream classes_{};
    std::stringstream body_{};
    std::stringstream global_constants_{};
    // Scope
    environment_stack scope_;
    // Expr + Type
    // This is to hold expressions.
    std::vector<std::string> expr_stack_{};
    // Note this does not check for types.
    // This is just to place current type.
    // type_checker round should do the type checking, before compiler.
    std::vector<ykobject> type_stack_{};
    // Delete stack for strings
    delete_stack_stack deletions_{};
    // Access functions and classes by name
    def_class_visitor &defs_classes_;
    // Different types of scopes stack, -> are we in function body, if or while
    std::vector<ast_type> scope_type_stack_{};
    // Defer stack
    defer_stack_stack defers_{};
    // Data type pool
    ykdt_pool *dt_pool_;
    // AST pool
    ast_pool *ast_pool_;
    // Desugaring compiler
    desugaring_compiler *desugar_;
    // Entry struct & function datatypes compiler
    entry_struct_func_compiler *esc_;
    // Copy of internal stmt_alias to handle dt parsing in builtins
    std::unordered_map<std::string, import_stmt *> import_stmts_alias_{};
    // Current file path
    std::string filepath_{};
    std::vector<parsing_error> errors_;
    void compile_function_call(fncall_expr *obj, const std::string &name,
                               std::stringstream &code, ykdatatype *return_type,
                               const std::vector<ykdatatype *> &parameters,
                               bool varargs_fnc);
    void compile_obj_creation(const std::string &name, std::stringstream &code,
                              ykdatatype *return_type);
    std::string
    prefix_function_arg(const std::pair<std::string, ykobject> &arg_val);
    void perform_assign(std::pair<std::string, ykobject> &lhs,
                        std::pair<std::string, ykobject> &rhs,
                        token *operator_token, bool assign_variable,
                        bool lhs_mutates);
    static void obj_calloc(const std::string &name, std::stringstream &code);
    static bool should_wrap_in_paren(const std::string &code);
    void compile_simple_bin_op(const binary_expr *obj,
                               const token_type &operator_type,
                               const std::pair<std::string, ykobject> &lhs,
                               const std::pair<std::string, ykobject> &rhs);
    void cast_numbers(const ykdatatype *castable,
                      std::pair<std::string, ykobject> &lhs,
                      std::pair<std::string, ykobject> &rhs);
    void write_casted_rhs(std::stringstream &stream,
                          std::pair<std::string, ykobject> &rhs,
                          ykdatatype *lhsu);
  };
}// namespace yaksha
#endif
