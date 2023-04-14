// desugaring_compiler.h
#ifndef DESUGARING_COMPILER_H
#define DESUGARING_COMPILER_H
#include "ast/ast.h"
#include "utilities/ykdt_pool.h"
#include <algorithm>
#include <map>
#include <sstream>
#include <string>
#include <vector>
namespace yaksha {
  struct compiler;
  /**
   * Desugaring compiler
   *    - Desugaring also happens at parser
   *    - However, this is for additional desugaring needs
   *    - Ex: for loops, etc that needs rewriting for block's continue statements
   * compile AST -> AST desugared
   */
  struct desugaring_compiler : private stmt_visitor {
    explicit desugaring_compiler(ast_pool *ast_pool_obj,
                                 ykdt_pool *dt_pool_obj);
    std::vector<stmt *> desugar(const std::vector<stmt *> &statements,
                                compiler *compiler_obj);
    ~desugaring_compiler() override;

private:
    std::vector<std::vector<stmt *> *> statement_stack_;
    std::vector<stmt *> global_statements_;
    std::vector<stmt *> pre_continue_stack_;
    ast_pool *ast_pool_;
    ykdt_pool *dt_pool_;
    token *true_token_;
    token *while_token_;
    token *break_token_;
    token *if_token_;
    token *not_token_;
    token *paren_token_;
    token *ccode_token_;
    token *less_token_;
    token *plus_eq_token_;
    compiler *compiler_obj_;
    std::vector<token *> internal_token_pool_;
    token *create_name(const std::string &name);
    token *create_int_literal(const std::string &lit);
    token *create_str_literal(const std::string &string_literal_content);
    stmt *desugar(stmt *obj);
    // Implement stmt_visitor only
    // WHY:
    // We only support statement level desugar at the moment
    // If we do support expression level we can introduce those later
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
  };
}// namespace yaksha
#endif
