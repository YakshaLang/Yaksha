// ast_printer.h
#ifndef AST_PRINTER_H
#define AST_PRINTER_H
#include "ast/ast.h"
#include <sstream>
#include <string>
namespace yaksha {
  /**
   * Prints Abstract Syntax Tree data structures in Lisp like syntax
   */
  struct ast_printer : stmt_visitor, expr_visitor {
    explicit ast_printer() = default;
    ~ast_printer() override = default;
    /**
     * Print given vector of statements
     * @param statements vector of statements
     */
    void print(const std::vector<stmt *> &statements);
    std::string print_to_str(const std::vector<stmt*> &statements);
    void visit_expression_stmt(expression_stmt *obj) override;
    void visit_print_stmt(print_stmt *obj) override;
    void visit_variable_expr(variable_expr *obj) override;
    void visit_let_stmt(let_stmt *obj) override;
    void visit_binary_expr(binary_expr *obj) override;
    void visit_grouping_expr(grouping_expr *obj) override;
    void visit_literal_expr(literal_expr *obj) override;
    void visit_unary_expr(unary_expr *obj) override;
    void visit_return_stmt(return_stmt *obj) override;
    void parenthesize(const std::string &name,
                      std::initializer_list<expr *> exprs);
    void visit_assign_expr(assign_expr *obj) override;
    void visit_block_stmt(block_stmt *obj) override;
    void visit_if_stmt(if_stmt *obj) override;
    void visit_pass_stmt(pass_stmt *obj) override;
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

private:
    std::stringstream text_{};
  };
}// namespace yaksha
#endif
