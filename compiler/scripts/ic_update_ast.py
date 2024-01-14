# ==============================================================================================
# ╦  ┬┌─┐┌─┐┌┐┌┌─┐┌─┐    Yaksha Programming Language
# ║  ││  ├┤ │││└─┐├┤     is Licensed with GPLv3 + extra terms. Please see below.
# ╩═╝┴└─┘└─┘┘└┘└─┘└─┘
# Note: libs - MIT license, runtime/3rd - various
# ==============================================================================================
# GPLv3:
# 
# Yaksha - Programming Language.
# Copyright (C) 2020 - 2023 Bhathiya Perera
# 
# This program is free software: you can redistribute it and/or modify it under the terms
# of the GNU General Public License as published by the Free Software Foundation,
# either version 3 of the License, or (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
# or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License along with this program.
# If not, see https://www.gnu.org/licenses/.
# 
# ==============================================================================================
# Additional Terms:
# 
# Please note that any commercial use of the programming language's compiler source code
# (everything except compiler/runtime, compiler/libs and compiler/3rd) require a written agreement
# with author of the language (Bhathiya Perera).
# 
# If you are using it for an open source project, please give credits.
# Your own project must use GPLv3 license with these additional terms.
# 
# You may use programs written in Yaksha/YakshaLisp for any legal purpose
# (commercial, open-source, closed-source, etc) as long as it agrees
# to the licenses of linked runtime libraries (see compiler/runtime/README.md).
# 
# ==============================================================================================
# !/usr/bin/env python
"""
This code generates Abstract Syntax Tree (AST) classes for intermediate C
"""
import os


def _token(name): return "ic_token*", "t_" + name


def _tokens(*names): return tuple([_token(x) for x in names])


EXPRS = sorted([
    ("assign", (("ic_token*", "name"), ("ic_token*", "opr"), ("ic_expr*", "right"))),
], key=lambda x: x[0])
# Do not add visitor methods for this stmt type
IGNORE_VISITS_STMT = {"pp_if_line", "pp_ifdef_line", "pp_ifndef_line",
                      "pp_elif_line", "pp_else_line", "pp_endif_line"}
STMTS = sorted([
    ("pp_define_normal", (*_tokens("hash", "define", "identifier"), ("std::vector<ic_token*>", "token_string"))),
    ("pp_define_function",
     (*_tokens("hash", "define", "identifier", "paren_open"), ("std::vector<ic_token*>", "params"),
      _token("paren_close"), ("std::vector<ic_token*>", "token_string"))),
    ("pp_include", (*_tokens("hash", "include", "path_spec"),)),
    ("pp_line", (*_tokens("hash", "line", "line_number", "path_spec"),)),
    ("pp_undef", (*_tokens("hash", "undef", "identifier"),)),
    ("pp_error", (*_tokens("hash", "error"), ("std::vector<ic_token*>", "token_string"),)),
    ("pp_warning", (*_tokens("hash", "warning"), ("std::vector<ic_token*>", "token_string"),)),
    ("pp_pragma", (*_tokens("hash", "pragma"), ("std::vector<ic_token*>", "token_string"),)),
    # Line of C code
    ("pp_code_line", (("std::vector<ic_token*>", "token_string"), _token("newline"),)),
    ("pp_block", (("std::vector<ic_stmt*>", "statements"),)),
    ("pp_if_line", (*_tokens("hash", "if_t"), ("std::vector<ic_token*>", "if_expression"),
                    ("ic_stmt*", "block"),)),
    ("pp_ifdef_line", (*_tokens("hash", "ifdef_t", "identifier"), ("ic_stmt*", "block"),)),
    ("pp_ifndef_line", (*_tokens("hash", "ifndef_t", "identifier"), ("ic_stmt*", "block"),)),
    ("pp_elif_line", (*_tokens("hash", "elif_t"), ("std::vector<ic_token*>", "if_expression"),
                      ("ic_stmt*", "block"),)),
    ("pp_else_line", (*_tokens("hash", "else_t"), ("ic_stmt*", "block"),)),
    ("pp_endif_line", (*_tokens("hash", "elif_t"),)),
    ("pp_if", (("ic_stmt*", "if_t"), ("std::vector<ic_stmt*>", "elifs"), ("ic_stmt*", "else_t"),
               ("ic_stmt*", "endif_t")))
], key=lambda x: x[0])

# EXPR CODE GEN
H_EXPR_SINGLE_FORWARD_DECLARE = "struct ic_$R$_expr;"
H_EXPR_VISITOR_SINGLE = "  virtual void visit_ic_$R$_expr(ic_$R$_expr *obj) = 0;"
H_EXPR_VISITOR = """
struct ic_expr_visitor {
$VISIT_METHODS$
  virtual ~ic_expr_visitor() = default;
};
""".strip()
H_EXPR_STRUCT = """
struct ic_$R$_expr : ic_expr {
  $EXPLICIT$ic_$R$_expr($PARAMS$);
  void accept(ic_expr_visitor *v) override;
  ic_ast_type get_type() override;
$STATE$
};
""".strip()
# STMT CODE GEN
H_STMT_SINGLE_FORWARD_DECLARE = H_EXPR_SINGLE_FORWARD_DECLARE.replace("expr", "stmt")
H_STMT_VISITOR_SINGLE = H_EXPR_VISITOR_SINGLE.replace("expr", "stmt")
H_STMT_VISITOR = H_EXPR_VISITOR.replace("expr", "stmt")
H_STMT_STRUCT = H_EXPR_STRUCT.replace("expr", "stmt")
H_CREATE_AST_POOL_EXPR = "  ic_expr *ic_c_$R$_expr($PARAMS$);"
H_CREATE_AST_POOL_STMT = H_CREATE_AST_POOL_EXPR.replace("expr", "stmt")
CPP_EXPR = """
ic_$R$_expr::ic_$R$_expr($PARAMS$)
    : $FILL_STATE_PARAMS$ {}
void ic_$R$_expr::accept(ic_expr_visitor *v) {
  v->visit_ic_$R$_expr(this);
}
ic_ast_type ic_$R$_expr::get_type() {
  return ic_ast_type::EXPR_$RU$;
}
ic_expr *ic_ast_pool::ic_c_$R$_expr($PARAMS$) {
  auto o = new ic_$R$_expr($PARAMS_NO_TYPES$);
  cleanup_expr_.push_back(o);
  return o;
}
""".strip()
CPP_EXPR_NO_ACCEPT = """
ic_$R$_expr::ic_$R$_expr($PARAMS$)
    : $FILL_STATE_PARAMS$ {}
ic_ast_type ic_$R$_expr::get_type() {
  return ic_ast_type::EXPR_$RU$;
}
void ic_$R$_expr::accept(ic_expr_visitor *v) {
}
ic_expr *ic_ast_pool::ic_c_$R$_expr($PARAMS$) {
  auto o = new ic_$R$_expr($PARAMS_NO_TYPES$);
  cleanup_expr_.push_back(o);
  return o;
}
""".strip()
CPP_STMT = CPP_EXPR.replace("expr", "stmt").replace("EXPR", "STMT")
CPP_STMT_NO_ACCEPT = CPP_EXPR_NO_ACCEPT.replace("expr", "stmt").replace("EXPR", "STMT")
H_AST_POOL = """
struct ic_ast_pool {
  ic_ast_pool();
  ~ic_ast_pool();
$CREATE_EXPR$
$CREATE_STMT$

private:
  std::vector<ic_expr *> cleanup_expr_;
  std::vector<ic_stmt *> cleanup_stmt_;
};
""".strip()
H_AST_TYPES = """
enum class ic_ast_type {
$EXPR_TYPES$,
$STMT_TYPES$
};
""".strip()
HEADER = """
// ic_ast.h
// generated by ic_update_ast.py
#ifndef IC_AST_H
#define IC_AST_H
#include "ic_token.h"
#include <vector>
namespace yaksha {
// ------ forward declarations ------
struct ic_expr;
struct ic_stmt;
struct ic_parameter;
$FORWARD_DECLS$
// Types of expressions and statements
$AST_TYPES$
// ------ expression visitor ------
$EXPR_VISITOR$
// ------ statement visitor ------
$STATEMENT_VISITOR$
// ------ expression base class ------
struct ic_expr {
  virtual ~ic_expr() = default;
  virtual void accept(ic_expr_visitor *v) = 0;
  virtual ic_ast_type get_type() = 0;
};
// ------- statement base class ------
struct ic_stmt {
  virtual ~ic_stmt() = default;
  virtual void accept(ic_stmt_visitor *v) = 0;
  virtual ic_ast_type get_type() = 0;
};
// ------- expressions ------
$EXPRESSIONS$
// ------- statements ------
$STATEMENTS$
// ------- utils ------
$AST_POOL$
/**
* Parameter for a user defined function declaration
*/
struct ic_parameter {
    ic_token* name_;
    std::vector<ic_token*> data_type_;
};
} // namespace yaksha
#endif
""".strip()
CPP_FILE = """
// ic_ast.cpp
// generated by ic_update_ast.py
#include "ic_ast.h"
using namespace yaksha;
// ------- expressions -----
$EXPRESSIONS_IMPL$
// ------- statements -----
$STATEMENTS_IMPL$
// ------- utils ------
ic_ast_pool::~ic_ast_pool() {
  for (auto e : cleanup_expr_) {
    delete e;
  }
  for (auto e : cleanup_stmt_) {
    delete e;
  }
  cleanup_expr_.clear();
  cleanup_stmt_.clear();
}
ic_ast_pool::ic_ast_pool() {
  cleanup_expr_.reserve(1000);
  cleanup_stmt_.reserve(1000);
}
""".strip()


def c_params(x) -> str:
    return ", ".join([y[0] + " " + y[1] for y in x[1]])


def c_state(x) -> str:
    return "\n".join(["  " + y[0] + " " + y[1] + "_;" for y in x[1]])


def c_single_param(y):
    if y[0].startswith("std::"):
        return "std::move(" + y[1] + ")"
    return y[1]


def c_params_no_types(x) -> str:
    return ", ".join([c_single_param(y) for y in x[1]])


def c_fill_state_params(x) -> str:
    return ", ".join([y[1] + "_(" + c_single_param(y) + ")" for y in x[1]])


def c_r(x) -> str:
    return x[0]


def c_visitor(types, visitor_template: str, single_template: str) -> str:
    visit_methods = "\n".join([single_template.replace("$R$", c_r(x)) for x in types])
    return visitor_template.replace("$VISIT_METHODS$", visit_methods)


def c_forward_decls(types, single_type: str) -> str:
    return "\n".join([single_type.replace("$R$", c_r(x)) for x in types])


def c_structs(types, single_struct: str) -> str:
    return "\n".join([single_struct
                     .replace("$R$", c_r(x))
                     .replace("$PARAMS$", c_params(x))
                     .replace("$STATE$", c_state(x))
                     .replace("$EXPLICIT$", c_explicit(x)) for x in types])


def c_ast_pool(types_expr, types_stmt, expr_single, stmt_single, ast_pool_temp):
    create_expr = "\n".join([expr_single.replace("$R$", c_r(x))
                            .replace("$PARAMS$", c_params(x)) for x in types_expr])
    create_stmt = "\n".join([stmt_single.replace("$R$", c_r(x))
                            .replace("$PARAMS$", c_params(x)) for x in types_stmt])
    return ast_pool_temp.replace("$CREATE_EXPR$", create_expr).replace("$CREATE_STMT$", create_stmt)


def c_ast_types(types_expr, types_stmt, types_temp):
    create_expr = "\n".join(["  EXPR_" + c_r(x).upper() + "," for x in types_expr])[:-1]
    create_stmt = "\n".join(["  STMT_" + c_r(x).upper() + "," for x in types_stmt])[:-1]
    return types_temp.replace("$EXPR_TYPES$", create_expr) \
        .replace("$STMT_TYPES$", create_stmt)


def c_explicit(x):
    explicit = ""
    if (len(x[1])) == 1:
        explicit = "explicit "
    return explicit


def c_impl(types, impl_template: str) -> str:
    return "\n".join([impl_template
                     .replace("$R$", c_r(x))
                     .replace("$RU$", c_r(x).upper())
                     .replace("$PARAMS$", c_params(x))
                     .replace("$FILL_STATE_PARAMS$", c_fill_state_params(x))
                     .replace("$PARAMS_NO_TYPES$", c_params_no_types(x)) for x in types])


def c_cpp_file():
    impl_expr = c_impl(EXPRS, CPP_EXPR)
    impl_stmt = c_impl([x for x in STMTS if x[0] not in IGNORE_VISITS_STMT], CPP_STMT)
    impl_stmt += c_impl([x for x in STMTS if x[0] in IGNORE_VISITS_STMT], CPP_STMT_NO_ACCEPT)
    return CPP_FILE.replace("$EXPRESSIONS_IMPL$", impl_expr) \
        .replace("$STATEMENTS_IMPL$", impl_stmt)


def c_header_file():
    forward_decls = c_forward_decls(EXPRS, H_EXPR_SINGLE_FORWARD_DECLARE) \
                    + "\n" + c_forward_decls(STMTS, H_STMT_SINGLE_FORWARD_DECLARE)
    expr_visitor = c_visitor(EXPRS, H_EXPR_VISITOR, H_EXPR_VISITOR_SINGLE)
    stmt_visitor = c_visitor([x for x in STMTS if x[0] not in IGNORE_VISITS_STMT], H_STMT_VISITOR,
                             H_STMT_VISITOR_SINGLE)
    expressions = c_structs(EXPRS, H_EXPR_STRUCT)
    statements = c_structs(STMTS, H_STMT_STRUCT)
    ast_pool = c_ast_pool(EXPRS, STMTS, H_CREATE_AST_POOL_EXPR,
                          H_CREATE_AST_POOL_STMT, H_AST_POOL)
    ast_types = c_ast_types(EXPRS, STMTS, H_AST_TYPES)
    return HEADER.replace("$FORWARD_DECLS$", forward_decls) \
        .replace("$EXPR_VISITOR$", expr_visitor) \
        .replace("$STATEMENT_VISITOR$", stmt_visitor) \
        .replace("$EXPRESSIONS$", expressions) \
        .replace("$STATEMENTS$", statements) \
        .replace("$AST_POOL$", ast_pool) \
        .replace("$AST_TYPES$", ast_types)


def main():
    header_file_data = c_header_file()
    cpp_file_data = c_cpp_file()
    with open(os.path.join(".", "src", "ic2c", "ic_ast.h"), "w+") as header_h:
        header_h.write(header_file_data)
    with open(os.path.join(".", "src", "ic2c", "ic_ast.cpp"), "w+") as header_h:
        header_h.write(cpp_file_data)


if __name__ == "__main__":
    os.chdir(os.path.dirname(os.path.dirname(__file__)))
    main()
