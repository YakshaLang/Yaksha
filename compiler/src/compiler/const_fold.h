// const_fold.h
#ifndef CONST_FOLD_H
#define CONST_FOLD_H
#include "ast/ast.h"
namespace yaksha {
  enum class const_fold_type {
    CFT_INT8,
    CFT_INT16,
    CFT_INT32,
    CFT_INT64,
    CFT_UINT8,
    CFT_UINT16,
    CFT_UINT32,
    CFT_UINT64,
    CFT_FLOAT,
    CFT_DOUBLE,
    CFT_BOOL,
    CFT_STRING, /* str, sr, string literal --> will not support strings (some optimizations are done at later stage) */
    CFT_NONE,
    CFT_NON_PRIMITIVE, /* array, map, tuple, fixed-array -> will not support */
    CFT_UNKNOWN,
    CFT_ERROR_OCCURRED
  };
  enum class const_fold_context_type {
    CFT_EXPR, /* this is an expression that cannot be folded */
    CFT_STMT,
    CFT_ERROR_OCCURRED,
    CFT_VALUE, /* this is a folded value */
    CFT_GARBAGE_VALUE /* this is a garbage value, also an expression that cannot be folded */
  };
  union const_fold_value_holder {
    int8_t int8_val_;
    int16_t int16_val_;
    int32_t int32_val_;
    int64_t int64_val_;
    uint8_t uint8_val_;
    uint16_t uint16_val_;
    uint32_t uint32_val_;
    uint64_t uint64_val_;
    float float_val_;
    double double_val_;
    bool bool_val_;
  };
  union expr_or_stmt {
    expr *expr_val_;
    stmt *stmt_val_;
  };
  struct const_fold_context {
    ykdatatype *type_ = nullptr;
    const_fold_type fold_type_ = const_fold_type::CFT_UNKNOWN;
    const_fold_context_type context_type_ = const_fold_context_type::CFT_VALUE;
    bool is_const_ = false;
    std::string error_msg_{};
    // values
    const_fold_value_holder value_ = {.int8_val_ = 0};
    expr_or_stmt expr_or_stmt_ = {.expr_val_ = nullptr};
    token *token_ = nullptr;
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
  };
}// namespace yaksha
#endif
