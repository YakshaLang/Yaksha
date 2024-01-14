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
// delete_stack_stack.h
#ifndef DELETE_STACK_STACK_H
#define DELETE_STACK_STACK_H
#include "delete_stack.h"
namespace yaksha {
  struct delete_stack_stack : delete_stack {
    delete_stack_stack();
    void push(const std::string &name, const std::string &free_code) override;
    void push_delete_stack(ast_type stack_type);
    void pop_delete_stack();
    void remove(const std::string &name) override;
    void write(std::stringstream &target, int indent_level) override;
    void write(std::stringstream &target, int indent_level,
               const std::string &return_name) override;
    void write_one(std::stringstream &target, int indent_level);
    void write_one(std::stringstream &target, int indent_level,
                   const std::string &return_name);
    void write_upto_loop(std::stringstream &target, int indent_level);
    void write_upto_loop(std::stringstream &target, int indent_level,
                         const std::string &return_name);
    ~delete_stack_stack() override;

private:
    std::vector<delete_stack> delete_levels_{};
  };
}// namespace yaksha
#endif
