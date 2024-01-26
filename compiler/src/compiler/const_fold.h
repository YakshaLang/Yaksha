// const_fold.h
#ifndef CONST_FOLD_H
#define CONST_FOLD_H
#include "ast/ast.h"
#include "utilities/ykobject.h"
#include "ast/environment_stack.h"
namespace yaksha {
  struct cf_evaluator {
    // TODO numeric value casting? think what we can do about it?
    //   can I use same i64/u64 for all? this might mean how overflow happen in a number might be different isn't it?
    //   but, we kind of can do it, since we are basically optimizing the code.
    //   but we should not mix uint / int
    //   uint -> int, ok? but int -> uint? no, we can't do that
    //   uint/int -> float -> double ok
    //   bool -> int/uint/float/double ok
    explicit cf_evaluator(std::vector<const_fold_context *> *context_pool);
    ~cf_evaluator() = default;
    const_fold_context * add(const_fold_context *lhs, const_fold_context *rhs);
    const_fold_context * sub(const_fold_context *lhs, const_fold_context *rhs);
    const_fold_context * mul(const_fold_context *lhs, const_fold_context *rhs);
    const_fold_context * div(const_fold_context *lhs, const_fold_context *rhs);
    const_fold_context * mod(const_fold_context *lhs, const_fold_context *rhs);
    const_fold_context * pow(const_fold_context *lhs, const_fold_context *rhs);
    const_fold_context * bit_and(const_fold_context *lhs, const_fold_context *rhs);
    const_fold_context * bit_or(const_fold_context *lhs, const_fold_context *rhs);
    const_fold_context * bit_xor(const_fold_context *lhs, const_fold_context *rhs);
    const_fold_context * bit_not(const_fold_context *lhs);
    const_fold_context * bit_lshift(const_fold_context *lhs, const_fold_context *rhs);
    const_fold_context * bit_rshift(const_fold_context *lhs, const_fold_context *rhs);
    const_fold_context * logical_and(const_fold_context *lhs, const_fold_context *rhs);
    const_fold_context * logical_or(const_fold_context *lhs, const_fold_context *rhs);
    const_fold_context * logical_not(const_fold_context *lhs);
    const_fold_context * unary_minus(const_fold_context *lhs);
    private:
      std::vector<const_fold_context *> *context_pool_;
  };
  /**
   * Partially evaluates expressions that can be evaluated at compile time
   *  this is basically a mini interpreter that runs on AST evaluating to AST
   */
  struct const_fold : stmt_visitor, expr_visitor {
    const_fold(ast_pool *ast_pool, ykdt_pool *dt_pool);
    ~const_fold() override;
    // ---------------------------------------------------------------------------------------------
    void visit_assign_expr(assign_expr *obj) override;
    void visit_assign_arr_expr(assign_arr_expr *obj) override;
    void visit_assign_member_expr(assign_member_expr *obj) override;
    void visit_binary_expr(binary_expr *obj) override;
    void visit_curly_call_expr(curly_call_expr *obj) override;
    void visit_fncall_expr(fncall_expr *obj) override;
    void visit_get_expr(get_expr *obj) override;
    void visit_grouping_expr(grouping_expr *obj) override;
    void visit_literal_expr(literal_expr *obj) override;
    void visit_logical_expr(logical_expr *obj) override;
    void visit_macro_call_expr(macro_call_expr *obj) override;
    void visit_set_expr(set_expr *obj) override;
    void
    visit_square_bracket_access_expr(square_bracket_access_expr *obj) override;
    void visit_square_bracket_set_expr(square_bracket_set_expr *obj) override;
    void visit_unary_expr(unary_expr *obj) override;
    void visit_variable_expr(variable_expr *obj) override;
    // ---------------------------------------------------------------------------------------------
    void visit_block_stmt(block_stmt *obj) override;
    void visit_break_stmt(break_stmt *obj) override;
    void visit_ccode_stmt(ccode_stmt *obj) override;
    void visit_cfor_stmt(cfor_stmt *obj) override;
    void visit_class_stmt(class_stmt *obj) override;
    void visit_compins_stmt(compins_stmt *obj) override;
    void visit_const_stmt(const_stmt *obj) override;
    void visit_continue_stmt(continue_stmt *obj) override;
    void visit_def_stmt(def_stmt *obj) override;
    void visit_defer_stmt(defer_stmt *obj) override;
    void visit_del_stmt(del_stmt *obj) override;
    void visit_enum_stmt(enum_stmt *obj) override;
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
    void visit_union_stmt(union_stmt *obj) override;
    void visit_while_stmt(while_stmt *obj) override;
    std::vector<parsing_error> errors_;

private:
    environment_stack env_stack_;
    // Why inner is a pointer:
    //  at the start I push global_statements_ to statement_stack_ and it should be the last one remaining
    std::vector<std::vector<const_fold_context *> *> statement_stack_;
    std::vector<const_fold_context *> global_statements_;
    std::vector<const_fold_context *> pre_continue_stack_;
    // pools
    std::vector<const_fold_context *> context_pool_;// to delete
    std::vector<token *> internal_token_pool_;      // to delete
    ast_pool
        *ast_pool_;// this is a passed in pointer and will not need to delete
    ykdt_pool
        *dt_pool_;// this is a passed in pointer and will not need to delete
    const_fold_context *wrap(stmt *statement);
    const_fold_context *wrap(expr *expression);
    const_fold_context *new_context();
    std::vector<stmt *>
    unwrap_vector_stmt(const std::vector<const_fold_context *> &to_unwrap);
    void error(const std::string &message, token *token);
    void store_statement(stmt *obj);
    const_fold_context *peek_last_or_null();
    void store_expression(expr *obj);
    void store(const_fold_context *obj);
    const_fold_context *pop_last_or_null();
    expr *pop_last_expr_or_null();
    token *new_token(token *location_token, token_type token_type,
                     std::string token_str);
    expr *to_expr_or_null(const_fold_context *val);
  };
}// namespace yaksha
#endif
