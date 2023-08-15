// usage_analyser.h
#ifndef USAGE_ANALYSER_H
#define USAGE_ANALYSER_H
#include "ast/ast.h"
#include "tokenizer/token.h"
#include "utilities/ykobject.h"
namespace yaksha {
    struct usage_analyser: expr_visitor, stmt_visitor {
        explicit usage_analyser(file_info *main_file_info);
        void analyse();
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
        void
        visit_square_bracket_set_expr(square_bracket_set_expr *obj) override;
        void visit_unary_expr(unary_expr *obj) override;
        void visit_variable_expr(variable_expr *obj) override;
        void visit_block_stmt(block_stmt *obj) override;
        void visit_break_stmt(break_stmt *obj) override;
        void visit_ccode_stmt(ccode_stmt *obj) override;
        void visit_class_stmt(class_stmt *obj) override;
        void visit_compins_stmt(compins_stmt *obj) override;
        void visit_const_stmt(const_stmt *obj) override;
        void visit_continue_stmt(continue_stmt *obj) override;
        void visit_def_stmt(def_stmt *obj) override;
        void visit_defer_stmt(defer_stmt *obj) override;
        void visit_del_stmt(del_stmt *obj) override;
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
        void visit_while_stmt(while_stmt *obj) override;
        ~usage_analyser() override;
        std::vector<parsing_error> errors_{};
    private:
        file_info* main_;
        std::vector<file_info*> import_stack_{};
        std::vector<ykobject> object_stack_{};
        void visit_data_type(ykdatatype *dt, token *token_for_err);
        void error(token* t, std::string message);
        std::pair<import_stmt *, bool> find_import(std::string &filepath,
                            std::vector<import_stmt *> &import_statements);
        file_info *peek_file_info();
        ykobject pop_object();
        void push_object(const ykobject &lhs);
        void push_import(const import_stmt *import_st);
        void pop_import();
    };
}
#endif
