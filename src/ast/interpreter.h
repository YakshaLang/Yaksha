// interpreter.h
#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "ast/ast.h"
#include "ast/environment_stack.h"
#include "utilities/ykfunction.h"
#include "utilities/ykobject.h"
namespace yaksha {
  /**
   * AST navigating Interpreter, uses a stack for returns & errors
   */
  struct interpreter : expr_visitor, stmt_visitor {
    explicit interpreter(ykdt_pool *pool);
    ~interpreter() override;
    /**
     * Interpret given statements return last object in stack
     * @param statements statements to execute
     * @return last object in stack, can be an error
     */
    void calculate(const std::vector<stmt *> &statements);
    void visit_class_stmt(class_stmt *obj) override;
    const ykobject *result();
    void visit_binary_expr(binary_expr *obj) override;
    void visit_grouping_expr(grouping_expr *obj) override;
    void visit_literal_expr(literal_expr *obj) override;
    void visit_unary_expr(unary_expr *obj) override;
    void visit_return_stmt(return_stmt *obj) override;
    void visit_expression_stmt(expression_stmt *obj) override;
    void visit_print_stmt(print_stmt *obj) override;
    void visit_variable_expr(variable_expr *obj) override;
    void visit_let_stmt(let_stmt *obj) override;
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
    void debug_print_stack();
    void visit_defer_stmt(defer_stmt *obj) override;
    void visit_del_stmt(del_stmt *obj) override;

private:
    environment_stack globals_;
    std::vector<ykobject> object_stack_{};
    std::vector<ykfunction *> func_pool_{};
    ykdt_pool *dt_pool_;
    bool has_error();
    const ykobject &peek();
    void push(ykobject obj);
    const ykobject &evaluate(expr *exp);
    ykobject pop();
  };
}// namespace yaksha
#endif
