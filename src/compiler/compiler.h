// compiler.h
#ifndef COMPILER_H
#define COMPILER_H
#include "ast/ast.h"
#include "ast/environment_stack.h"
#include "compiler/compiler_utils.h"
#include "compiler/delete_stack_stack.h"
#include "def_class_visitor.h"
#include "utilities/defer_stack_stack.h"
#include <sstream>
namespace yaksha {
  struct compiler : expr_visitor, stmt_visitor {
    compiler(def_class_visitor &defs_classes, ykdt_pool *pool);
    ~compiler() override;
    std::string compile(const std::vector<stmt *> &statements);
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
    void visit_print_stmt(print_stmt *obj) override;
    void visit_return_stmt(return_stmt *obj) override;
    void visit_while_stmt(while_stmt *obj) override;
    void visit_defer_stmt(defer_stmt *obj) override;
    void visit_class_stmt(class_stmt *obj) override;

private:
    /**
     * @return unique temp variable name
     */
    std::string temp();
    /**
     * Convert Yaksha data type to appropriate C data type.
     * TODO: This should support complex data types in future.
     *  For now just int, str.
     * @param basic_dt data type as a token.
     * @return converted data type.
     */
    std::string convert_dt(token *basic_dt);
    void push_scope_type(ast_type scope_type);
    ast_type peek_scope_type();
    void pop_scope_type();
    void write_indent(std::stringstream &where) const;
    void write_prev_indent(std::stringstream &where) const;
    static void write_end_statement(std::stringstream &where);
    void indent();
    void dedent();
    void push(const std::string &expr, const ykobject &data_type);
    std::pair<std::string, ykobject> pop();
    // Indentation to generate
    int indent_{0};
    // Counter for temp variables.
    long temp_{0};
    /**
     * Function declarations, etc
     */
    std::stringstream forward_declarations_{};
    /**
     * Function bodies, etc
     */
    std::stringstream body_{};
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
    ykdt_pool *dt_pool;
  };
}// namespace yaksha
#endif
