// ==============================================================================================
// ╦  ┬┌─┐┌─┐┌┐┌┌─┐┌─┐    Yaksha Programming Language
// ║  ││  ├┤ │││└─┐├┤     is Licensed with GPLv3 + extra terms. Please see below.
// ╩═╝┴└─┘└─┘┘└┘└─┘└─┘
// Note: libs - MIT license, runtime/3rd - various
// ==============================================================================================
// GPLv3:
//
// Yaksha - Programming Language.
// Copyright (C) 2020 - 2024 Bhathiya Perera
//
// This program is free software: you can redistribute it and/or modify it under the terms
// of the GNU General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with this program.
// If not, see https://www.gnu.org/licenses/.
//
// ==============================================================================================
// Additional Terms:
//
// Please note that any commercial use of the programming language's compiler source code
// (everything except compiler/runtime, compiler/libs and compiler/3rd) require a written agreement
// with author of the language (Bhathiya Perera).
//
// If you are using it for an open source project, please give credits.
// Your own project must use GPLv3 license with these additional terms.
//
// You may use programs written in Yaksha/YakshaLisp for any legal purpose
// (commercial, open-source, closed-source, etc) as long as it agrees
// to the licenses of linked runtime libraries (see compiler/runtime/README.md).
//
// ==============================================================================================
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
    explicit environment_stack(yk_datatype_pool *pool);
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
    void define(const std::string &name, yk_object data) override;
    void define_global(const std::string &name, yk_object data);
    /**
     * Assign a value to a variable (only if it's declared)
     * @param name name of the variable
     * @param data object
     */
    void assign(const std::string &name, yk_object data) override;
    /**
     * Get mutable data for a variable
     * @param name name of the variable
     * @return mutable object
     */
    yk_object get(const std::string &name) override;
    /**
     * Go to a deeper level of scope
     */
    void push();
    /**
     * Get out of the scopes
     */
    void pop();
    /**
     * @return true if we are declaring a global
     */
    bool is_global_level();

private:
    bool has_inner_scope();
    environment &peek();
    std::vector<environment> scope_stack_{};
    yk_datatype_pool *pool_;
  };
}// namespace yaksha
#endif
