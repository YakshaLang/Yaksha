// udfunction.h
#ifndef UDFUNCTION_H
#define UDFUNCTION_H
#include "ast/ast.h"
#include "ast/environment.h"
#include "ast/interpreter.h"
#include "ykfunction.h"
namespace yaksha {
  /**
   * User defined function object that can be called by interpreter
   */
  struct udfunction : ykfunction {
    /**
     * Create a new user defined function
     * @param scope Pointer to the environment stack/scope
     *  that this function will read variables from
     * @param statement_visitor Pointer to current running interpreter?
     * @param code code to execute (this is a block)
     * @param parameters List of parameters in function definition
     * @param token token to chuck errors
     */
    explicit udfunction(environment *scope, stmt_visitor *statement_visitor,
                        stmt *code, std::vector<parameter> *parameters,
                        token *token);
    ~udfunction() override;
    ykobject verify(const std::vector<ykobject> &args, ykdt_pool* pool) override;
    std::pair<func_control_flow, ykobject>
    call(const std::vector<ykobject> &args, ykdt_pool* pool) override;

private:
    environment *scope_;
    stmt_visitor *statement_visitor_;
    stmt *code_;
    std::vector<parameter> *parameters_;
    token *token_;
  };
}// namespace yaksha
#endif
