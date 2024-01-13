// codegen_json.h
#ifndef CODEGEN_JSON_H
#define CODEGEN_JSON_H
#include "ast/ast.h"
#include "codegen.h"
namespace yaksha {
    struct codegen_json: codegen {
        codegen_json();
        ~codegen_json() override;
        comp_result emit(codefiles *cf, gc_pool<token> *token_pool) override;

    private:
    };

    struct to_json_compiler : expr_visitor, stmt_visitor {
      std::string compile(file_info *fi);
      // -------------- expr_visitor --------------
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
      void visit_square_bracket_access_expr(
          square_bracket_access_expr *obj) override;
      void visit_square_bracket_set_expr(square_bracket_set_expr *obj) override;
      void visit_unary_expr(unary_expr *obj) override;
      void visit_variable_expr(variable_expr *obj) override;
      // -------------- stmt_visitor --------------
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
  private:
      std::stringstream json_{};
    };
}
#endif
