// compiler.h
#ifndef COMPILER_H
#define COMPILER_H
#include "ast/ast.h"
#include "ast/codefiles.h"
#include "ast/environment_stack.h"
#include "builtins.h"
#include "compiler/compiler_utils.h"
#include "compiler/delete_stack_stack.h"
#include "def_class_visitor.h"
#include "tokenizer/token.h"
#include "utilities/defer_stack_stack.h"
#include <sstream>
namespace yaksha {
  struct compiler_output {
    std::string struct_forward_declarations_{};
    std::string function_forward_declarations_{};
    std::string classes_{};
    std::string body_{};
    std::string global_constants_{};
  };
  struct compiler : expr_visitor, stmt_visitor {
    compiler(def_class_visitor &defs_classes, ykdt_pool *pool);
    ~compiler() override;
    compiler_output compile(codefiles *cf, file_info *fi);
    compiler_output compile(const std::vector<stmt *> &statements);
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
    void visit_square_bracket_set_expr(square_bracket_set_expr *obj) override;
    void visit_assign_arr_expr(assign_arr_expr *obj) override;
    void visit_ccode_stmt(ccode_stmt *obj) override;
    void visit_import_stmt(import_stmt *obj) override;
    void visit_const_stmt(const_stmt *obj) override;

private:
    /**
     * @return unique temp variable name
     */
    std::string temp();
    /**
     * Convert Yaksha data type to appropriate C data type.
     * @param basic_dt data type as a token.
     * @return converted data type.
     */
    std::string convert_dt(ykdatatype *basic_dt);
    void push_scope_type(ast_type scope_type);
    ast_type peek_scope_type();
    void pop_scope_type();
    void write_indent(std::stringstream &where) const;
    void write_prev_indent(std::stringstream &where) const;
    static void write_end_statement(std::stringstream &where);
    void indent();
    void dedent();
    void push(const std::string &expr, const ykobject &data_type);
    std::string prefix_val_{};
    codefiles *cf_{nullptr};
    std::pair<std::string, ykobject> pop();
    // Indentation to generate
    int indent_{0};
    // Counter for temp variables.
    long temp_{0};
    builtins builtins_;
    /**
     * Function declarations, etc
     */
    std::stringstream struct_forward_declarations_{};
    std::stringstream function_forward_declarations_{};
    std::stringstream classes_{};
    std::stringstream body_{};
    std::stringstream global_constants_{};
    // Scope
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
    // Data type pool
    ykdt_pool *dt_pool;
    // AST pool
    ast_pool *ast_pool_;
    void compile_function_call(fncall_expr *obj, const std::string &name,
                               std::stringstream &code,
                               ykdatatype *return_type);
    void compile_obj_creation(const std::string &name, std::stringstream &code,
                              ykdatatype *return_type);
  };
}// namespace yaksha
#endif
