// return_checker.h
#ifndef RETURN_CHECKER_H
#define RETURN_CHECKER_H
#include "ast/ast.h"
#include "def_visitor.h"
namespace yaksha {
    struct return_checker: expr_visitor, stmt_visitor {
        return_checker();
        ~return_checker() override;
        void check(def_visitor& functions);
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
        void visit_defer_stmt(defer_stmt *obj) override;
        void visit_expression_stmt(expression_stmt *obj) override;
        void visit_if_stmt(if_stmt *obj) override;
        void visit_let_stmt(let_stmt *obj) override;
        void visit_pass_stmt(pass_stmt *obj) override;
        void visit_print_stmt(print_stmt *obj) override;
        void visit_return_stmt(return_stmt *obj) override;
        void visit_while_stmt(while_stmt *obj) override;
        std::vector<parsing_error> errors_{};
    private:
        void error(token *tok, const std::string &message);
        void error(const std::string &message);
        void push_return_found();
        bool peek_return_found();
        void pop_return_found();
        std::vector<bool> return_found_{};
    };
}
#endif
