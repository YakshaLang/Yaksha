// def_class_visitor.h
#ifndef DEF_VISITOR_H
#define DEF_VISITOR_H
#include "../ast/ast.h"
#include <unordered_map>
namespace yaksha {
  /**
   * Visits def-s and class-es and find out type information
   *
   * This phase need to happen before type_checker
   * Once we know what kind of arguments functions take then
   * we can match the function and args in type_checker
   *
   * We also extract classes in this phase
   */
  struct def_class_visitor : expr_visitor, stmt_visitor {
    def_class_visitor();
    ~def_class_visitor() override;
    void extract(const std::vector<stmt *> &statements);
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
    void visit_assign_arr_expr(assign_arr_expr *obj) override;
    void visit_square_bracket_set_expr(square_bracket_set_expr *obj) override;
    void visit_ccode_stmt(ccode_stmt *obj) override;
    bool has_function(const std::string &prefixed_name);
    def_stmt *get_function(const std::string &prefixed_name);
    bool has_class(const std::string &prefixed_name);
    class_stmt *get_class(const std::string &prefixed_name);
    void visit_import_stmt(import_stmt *obj) override;
    std::vector<std::string> function_names_{};
    std::vector<std::string> class_names_{};
    std::vector<parsing_error> errors_{};

private:
    std::unordered_map<std::string, def_stmt *> functions_{};
    std::unordered_map<std::string, class_stmt *> classes_{};
    void error(token *tok, const std::string &message);
  };
}// namespace yaksha
#endif
