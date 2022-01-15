// environment_stack.h
#ifndef ENVIRONMENT_STACK_H
#define ENVIRONMENT_STACK_H
#include "ast/environment.h"
namespace yaksha {
  /**
   * Wrapper around scope stack
   *    - Call push when a function is called.
   *    - Call pop afterwards
   */
  struct environment_stack : environment {
    environment_stack();
    ~environment_stack() override;
    /**
     * See if this variable is defined
     * You are not allowed to create a variable
     *  with same name as that's in global
     * @param name name of the variable
     * @return true if defined
     */
    bool is_defined(const std::string &name) override;
    /**
     * Define a variable for the first time
     * @param name name of the variable
     * @param data object
     */
    void define(const std::string &name, ykobject data) override;
    void define_global(const std::string &name, ykobject data);
    /**
     * Assign a value to a variable (only if it's declared)
     * @param name name of the variable
     * @param data object
     */
    void assign(const std::string &name, ykobject data) override;
    /**
     * Get mutable data for a variable
     * @param name name of the variable
     * @return mutable object
     */
    ykobject get(const std::string &name) override;
    /**
     * Go to a deeper level of scope
     */
    void push();
    /**
     * Get out of the scopes
     */
    void pop();

private:
    bool has_inner_scope();
    environment &peek();
    std::vector<environment> scope_stack_{};
  };
}// namespace yaksha
#endif
