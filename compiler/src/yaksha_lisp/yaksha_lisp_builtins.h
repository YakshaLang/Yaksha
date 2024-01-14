// ==============================================================================================
// ╦  ┬┌─┐┌─┐┌┐┌┌─┐┌─┐    Yaksha Programming Language
// ║  ││  ├┤ │││└─┐├┤     is Licensed with GPLv3 + extra terms. Please see below.
// ╩═╝┴└─┘└─┘┘└┘└─┘└─┘
// Note: libs - MIT license, runtime/3rd - various
// ==============================================================================================
// GPLv3:
//
// Yaksha - Programming Language.
// Copyright (C) 2020 - 2023 Bhathiya Perera
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
// yaksha_lisp_builtins.h
#ifndef YAKSHA_LISP_BUILTINS_H
#define YAKSHA_LISP_BUILTINS_H
#include <vector>
namespace yaksha {
  struct yaksha_envmap;
  struct yaksha_lisp_value;
  struct yaksha_lisp_builtins {
    static yaksha_lisp_value *add_(const std::vector<yaksha_lisp_value *> &args,
                                   yaksha_envmap *env);
    static yaksha_lisp_value *sub_(const std::vector<yaksha_lisp_value *> &args,
                                   yaksha_envmap *env);
    static yaksha_lisp_value *mul_(const std::vector<yaksha_lisp_value *> &args,
                                   yaksha_envmap *env);
    static yaksha_lisp_value *div_(const std::vector<yaksha_lisp_value *> &args,
                                   yaksha_envmap *env);
    static yaksha_lisp_value *mod_(const std::vector<yaksha_lisp_value *> &args,
                                   yaksha_envmap *env);
    static yaksha_lisp_value *eq_(const std::vector<yaksha_lisp_value *> &args,
                                  yaksha_envmap *env);
    static yaksha_lisp_value *neq_(const std::vector<yaksha_lisp_value *> &args,
                                   yaksha_envmap *env);
    static yaksha_lisp_value *gt_(const std::vector<yaksha_lisp_value *> &args,
                                  yaksha_envmap *env);
    static yaksha_lisp_value *lt_(const std::vector<yaksha_lisp_value *> &args,
                                  yaksha_envmap *env);
    static yaksha_lisp_value *gte_(const std::vector<yaksha_lisp_value *> &args,
                                   yaksha_envmap *env);
    static yaksha_lisp_value *lte_(const std::vector<yaksha_lisp_value *> &args,
                                   yaksha_envmap *env);
    static yaksha_lisp_value *and_(const std::vector<yaksha_lisp_value *> &args,
                                   yaksha_envmap *env);
    static yaksha_lisp_value *or_(const std::vector<yaksha_lisp_value *> &args,
                                  yaksha_envmap *env);
    static yaksha_lisp_value *not_(const std::vector<yaksha_lisp_value *> &args,
                                   yaksha_envmap *env);
    static yaksha_lisp_value *if_(const std::vector<yaksha_lisp_value *> &args,
                                  yaksha_envmap *env);
    static yaksha_lisp_value *
    print_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    static yaksha_lisp_value *
    println_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    static yaksha_lisp_value *
    defun_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    static yaksha_lisp_value *def_(const std::vector<yaksha_lisp_value *> &args,
                                   yaksha_envmap *env);
    // only if it is defined in the current scope or a parent scope(s)
    // changes the value
    static yaksha_lisp_value *
    setq_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    // sets the value in the current scope if it is defined there
    // otherwise defines it in the current scope
    static yaksha_lisp_value *
    setdef_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    // (lambda (args) body)
    static yaksha_lisp_value *
    lambda_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    // (do expr...)
    // evaluates exprs in order and returns the result of the last one
    static yaksha_lisp_value *do_(const std::vector<yaksha_lisp_value *> &args,
                                  yaksha_envmap *env);
    // (scope expr...)
    // evaluates exprs in order in a new scope and returns the result of the last one
    static yaksha_lisp_value *
    scope_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    // (quote expr)
    // returns expr as a list without evaluating it
    static yaksha_lisp_value *
    quote_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    // (for (var) list body)
    // for each item in list, set var to item and evaluate body
    static yaksha_lisp_value *for_(const std::vector<yaksha_lisp_value *> &args,
                                   yaksha_envmap *env);
    // (range start end)
    // returns list of numbers from start to end
    static yaksha_lisp_value *
    range_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    // (while condition body)
    // while condition is truthy, evaluate body
    static yaksha_lisp_value *
    while_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    // evaluates a list as code, returns result
    static yaksha_lisp_value *
    eval_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    // returns new list
    static yaksha_lisp_value *
    list_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    // returns first value
    static yaksha_lisp_value *
    head_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    // new list without first value
    static yaksha_lisp_value *
    tail_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    // prepend first value to list
    static yaksha_lisp_value *
    cons_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    // returns length of list/string, or 0 if not a list
    static yaksha_lisp_value *len_(const std::vector<yaksha_lisp_value *> &args,
                                   yaksha_envmap *env);
    // add value to end of list, returns list
    static yaksha_lisp_value *
    push_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    // remove last value from list, returns value
    static yaksha_lisp_value *pop_(const std::vector<yaksha_lisp_value *> &args,
                                   yaksha_envmap *env);
    static yaksha_lisp_value *
    raise_error_(const std::vector<yaksha_lisp_value *> &args,
                 yaksha_envmap *env);
    static yaksha_lisp_value *try_(const std::vector<yaksha_lisp_value *> &args,
                                   yaksha_envmap *env);
    static yaksha_lisp_value *
    try_catch_(const std::vector<yaksha_lisp_value *> &args,
               yaksha_envmap *env);
    static yaksha_lisp_value *
    is_list_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    static yaksha_lisp_value *
    is_string_(const std::vector<yaksha_lisp_value *> &args,
               yaksha_envmap *env);
    static yaksha_lisp_value *
    is_int_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    static yaksha_lisp_value *
    is_truthy_(const std::vector<yaksha_lisp_value *> &args,
               yaksha_envmap *env);
    static yaksha_lisp_value *
    is_callable_(const std::vector<yaksha_lisp_value *> &args,
                 yaksha_envmap *env);
    static yaksha_lisp_value *
    is_nil_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    static yaksha_lisp_value *
    filter_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    static yaksha_lisp_value *map_(const std::vector<yaksha_lisp_value *> &args,
                                   yaksha_envmap *env);
    static yaksha_lisp_value *
    reduce_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    static yaksha_lisp_value *
    to_string_(const std::vector<yaksha_lisp_value *> &args,
               yaksha_envmap *env);
    static yaksha_lisp_value *
    to_int_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    static yaksha_lisp_value *
    read_file_(const std::vector<yaksha_lisp_value *> &args,
               yaksha_envmap *env);
    static yaksha_lisp_value *
    write_file_(const std::vector<yaksha_lisp_value *> &args,
                yaksha_envmap *env);
    static yaksha_lisp_value *
    input_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    static yaksha_lisp_value *
    random_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    static yaksha_lisp_value *
    time_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    static yaksha_lisp_value *
    insert_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    static yaksha_lisp_value *
    index_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    static yaksha_lisp_value *
    remove_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    static yaksha_lisp_value *
    parse_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    static yaksha_lisp_value *
    bitwise_and_(const std::vector<yaksha_lisp_value *> &args,
                 yaksha_envmap *env);
    static yaksha_lisp_value *
    bitwise_or_(const std::vector<yaksha_lisp_value *> &args,
                yaksha_envmap *env);
    static yaksha_lisp_value *
    bitwise_xor_(const std::vector<yaksha_lisp_value *> &args,
                 yaksha_envmap *env);
    static yaksha_lisp_value *
    bitwise_not_(const std::vector<yaksha_lisp_value *> &args,
                 yaksha_envmap *env);
    static yaksha_lisp_value *
    bitwise_left_shift_(const std::vector<yaksha_lisp_value *> &args,
                        yaksha_envmap *env);
    static yaksha_lisp_value *
    bitwise_right_shift_(const std::vector<yaksha_lisp_value *> &args,
                         yaksha_envmap *env);
    // Map functionality
    static yaksha_lisp_value *
    map_get_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    static yaksha_lisp_value *
    map_set_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    static yaksha_lisp_value *
    map_remove_(const std::vector<yaksha_lisp_value *> &args,
                yaksha_envmap *env);
    static yaksha_lisp_value *
    map_keys_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    static yaksha_lisp_value *
    map_values_(const std::vector<yaksha_lisp_value *> &args,
                yaksha_envmap *env);
    static yaksha_lisp_value *
    map_has_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    // Get current scope as a MAP
    static yaksha_lisp_value *
    this_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    // Get parent scope as a MAP, or nil if no parent
    static yaksha_lisp_value *
    parent_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    // Get string representation of given value
    static yaksha_lisp_value *
    repr_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    // 'cond' -> this has the format (cond (test1 expr1) (test2 expr2) ...)
    // returns the result of the first expr that has a truthy test or nil
    static yaksha_lisp_value *
    cond_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    // 'ghost' -> (ghost whatever) -> whatever
    static yaksha_lisp_value *
    ghost_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    static yaksha_lisp_value *
    metamacro_(const std::vector<yaksha_lisp_value *> &args,
               yaksha_envmap *env);
    static yaksha_lisp_value *
    is_metamacro_(const std::vector<yaksha_lisp_value *> &args,
                  yaksha_envmap *env);
    static yaksha_lisp_value *
    is_module_(const std::vector<yaksha_lisp_value *> &args,
               yaksha_envmap *env);
    static yaksha_lisp_value *
    access_module_(const std::vector<yaksha_lisp_value *> &args,
                   yaksha_envmap *env);
    static yaksha_lisp_value *
    magic_dot_(const std::vector<yaksha_lisp_value *> &args,
               yaksha_envmap *env);
    static yaksha_lisp_value *
    sorted_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    static yaksha_lisp_value *
    reversed_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    static yaksha_lisp_value *
    os_exec_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    static yaksha_lisp_value *
    os_shell_(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
    // --
    static yaksha_lisp_value *
    system_lock_root_scope_(const std::vector<yaksha_lisp_value *> &args,
                            yaksha_envmap *env);
    static yaksha_lisp_value *
    system_unlock_root_scope_(const std::vector<yaksha_lisp_value *> &args,
                              yaksha_envmap *env);
    static yaksha_lisp_value *
    system_enable_gc_(const std::vector<yaksha_lisp_value *> &args,
                      yaksha_envmap *env);
    static yaksha_lisp_value *
    system_disable_gc_(const std::vector<yaksha_lisp_value *> &args,
                       yaksha_envmap *env);
    static yaksha_lisp_value *
    system_enable_print_(const std::vector<yaksha_lisp_value *> &args,
                         yaksha_envmap *env);
    static yaksha_lisp_value *
    system_disable_print_(const std::vector<yaksha_lisp_value *> &args,
                          yaksha_envmap *env);
    // ----------------------------------------------------------------- //
    static yaksha_lisp_value *copy_val(yaksha_envmap *env,
                                       yaksha_lisp_value *item);
    static yaksha_lisp_value *
    access_module_internal(yaksha_envmap *env, const yaksha_lisp_value *module_,
                           const yaksha_lisp_value *attribute_);
    static yaksha_lisp_value *map_get_internal(yaksha_lisp_value *map_item,
                                               yaksha_lisp_value *key_item,
                                               yaksha_lisp_value *default_val);
  };
}// namespace yaksha
#endif
