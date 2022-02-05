// type_checker.h
#ifndef TYPE_CHECKER_H
#define TYPE_CHECKER_H
#include "ast/ast.h"
#include "ast/environment_stack.h"
#include "compiler/def_visitor.h"
#include "utilities/ykobject.h"
namespace yaksha {
  struct type_checker : expr_visitor, stmt_visitor {
    explicit type_checker(ykdt_pool *pool);
    void visit_class_stmt(class_stmt *obj) override;
    ~type_checker() override;
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
    void visit_expression_stmt(expression_stmt *obj) override;
    void visit_if_stmt(if_stmt *obj) override;
    void visit_let_stmt(let_stmt *obj) override;
    void visit_pass_stmt(pass_stmt *obj) override;
    void visit_print_stmt(print_stmt *obj) override;
    void visit_return_stmt(return_stmt *obj) override;
    void visit_while_stmt(while_stmt *obj) override;
    void visit_defer_stmt(defer_stmt *obj) override;
    /**
     * Errors vector, type checker will try and identify as much errors as possible
     * but after first error, everything else is best guess
     */
    std::vector<parsing_error> errors_;
    /**
     * Get function information
     */
    def_visitor functions_{};

private:
    ykobject pop();
    void push(const ykobject &data_type);
    void error(token *tok, const std::string &message);
    void error(const std::string &message);
    void push_scope_type(ast_type scope_type);
    ast_type peek_scope_type();
    void pop_scope_type();
    void push_function(const std::string &prefixed_name);
    std::string peek_function();
    void pop_function();
    environment_stack scope_;
    ykdt_pool *dt_pool_;
    std::vector<ykobject> object_stack_{};
    // Different types of scopes stack, -> are we in function body, if or while
    std::vector<ast_type> scope_type_stack_{};
    // Function stack
    std::vector<std::string> function_name_stack_{};
  };
}// namespace yaksha
#endif
