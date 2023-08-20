# ==============================================================================================
# ╦  ┬┌─┐┌─┐┌┐┌┌─┐┌─┐    Yaksha Programming Language
# ║  ││  ├┤ │││└─┐├┤     is Licensed with GPLv3 + exta terms. Please see below.
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
This code generates Abstract Syntax Tree (AST) classes
WHY? There's a lot of boilerplate code in that, easier to generate.
I am not modifying the generated code, so it is better.
Never modify generated code, as that defeats the purpose of code gen.
This script updates ast.h and ast.cpp
"""
import os

# Different kind of expressions
# expression type name is followed by content of the class
EXPRS = sorted([
    # Assign to a variable
    # We can promote an assignment to a let statement, if so promoted is set to true
    ("assign", (("token*", "name"), ("token*", "opr"), ("expr*", "right"), ("bool", "promoted"),
                ("ykdatatype*", "promoted_data_type"))),
    # Assign to a member
    ("assign_member", (("expr*", "set_oper"), ("token*", "opr"), ("expr*", "right"))),
    # Assign to array object
    # a[1] = 2 or a[2 + 3] = c
    ("assign_arr", (("expr*", "assign_oper"), ("token*", "opr"), ("expr*", "right"))),
    # Binary operator (+, -, /, etc)
    ("binary", (("expr*", "left"), ("token*", "opr"), ("expr*", "right"))),
    # Logical operator (and, or)
    ("logical", (("expr*", "left"), ("token*", "opr"), ("expr*", "right"))),
    # Parens
    ("grouping", (("expr*", "expression"),)),
    # strings, numbers
    ("literal", (("token*", "literal_token"),)),
    # -x
    ("unary", (("token*", "opr"), ("expr*", "right"))),
    # Reference a variable
    ("variable", (("token*", "name"),)),
    # Function call
    # Can be abc(), abc(1), abc(1, 2, 3), etc
    #        name->`abc` args->`1, 2, 3` paren_token->`)`
    ("fncall", (("expr*", "name"), ("token*", "paren_token"), ("std::vector<expr*>", "args"))),
    ("curly_call", (("expr*", "dt_expr"),
                    ("token*", "curly_open"),
                    ("std::vector<name_val>", "values"),
                    ("token*", "curly_close"))),
    # Simple macro call (function or procedure macro)
    # examples
    #   eval!("(+ 1 2 3)") --> 6
    ("macro_call", (("token*", "path"), ("token*", "name"), ("token*", "not_symbol_tok"), ("token*", "paren_token"),
                    ("std::vector<expr*>", "args"), ("token*", "close_paren_token"))),
    # Can be a[1], a[b[1]], etc
    ("square_bracket_access", (("expr*", "name"), ("token*", "sqb_token"), ("expr*", "index_expr"))),
    ("square_bracket_set", (("expr*", "name"), ("token*", "sqb_token"), ("expr*", "index_expr"))),
    # Dot operator is used as both set and get operations
    ("set", (("expr*", "lhs"), ("token*", "dot"), ("token*", "item"))),
    ("get", (("expr*", "lhs"), ("token*", "dot"), ("token*", "item"))),
], key=lambda x: x[0])
# Do not add visitor methods for this stmt type
IGNORE_VISITS_STMT = {"elif", "macros", "token_soup", "dsl_macro"}
# Different kinds of statements
STMTS = sorted([
    # Define macros in current file.
    # Parser should check that for a single invoke of parse(), there must be only one, macros section.
    # -- macros code will be validated and parsed same way.
    # macros! {
    #     (println "Hello from macro processor")
    # }
    ("macros", (("token*", "macros_token"), ("token*", "not_symbol_tok"), ("token*", "curly_open"),
                ("std::vector<token*>", "lisp_code"), ("token*", "curly_close"))),
    # Execute a DSL macro
    # format: name[. name2]!{ internal_soup }
    ("dsl_macro", (("token*", "name"), ("token*", "name2"), ("token*", "not_symbol_tok"), ("token*", "curly_open"),
                   ("std::vector<token*>", "internal_soup"), ("token*", "curly_close"))),
    # Why?
    # this allows us to store arbitrary tokens in order in statement list
    ("token_soup", (("std::vector<token*>", "soup"),)),
    ("return", (("token*", "return_keyword"), ("expr*", "expression"), ("ykdatatype*", "result_type"))),
    # defer statement works just like how we use string, deletions.
    ("defer", (("token*", "defer_keyword"), ("expr*", "expression"), ("stmt*", "del_statement"))),
    # del statement
    ("del", (("token*", "del_keyword"), ("expr*", "expression"))),
    ("expression", (("expr*", "expression"),)),
    # ccode statement
    ("ccode", (("token*", "ccode_keyword"), ("token*", "code_str"))),
    # If statement contain if, elif*, else?
    ("if", (("token*", "if_keyword"), ("expr*", "expression"), ("stmt*", "if_branch"),
            ("token*", "else_keyword"), ("stmt*", "else_branch"))),
    # Note that the elif statement is actually used only as a temp data structure
    # if-elif-else is converted to nested if structures
    ("elif", (("token*", "elif_keyword"), ("expr*", "expression"), ("stmt*", "elif_branch"))),
    # While loop just got a condition and a body
    ("while", (("token*", "while_keyword"), ("expr*", "expression"), ("stmt*", "while_body"),)),
    # For loop
    # for x: int in expr:
    #     println(x)
    # ## or
    # for x in expr:
    #     println(x)
    ("foreach", (("token*", "for_keyword"), ("token*", "name"), ("ykdatatype*", "data_type"),
                 ("token*", "in_keyword"), ("expr*", "expression"), ("stmt*", "for_body"),)),
    # For loop - endless loop
    # for:
    #     println("endless")
    ("forendless", (("token*", "for_keyword"), ("stmt*", "for_body"),)),
    # C-like for loop
    # for (x = 0; x < 5; x += 1):
    #     println(x)
    ("cfor", (("token*", "for_keyword"), ("token*", "open_paren"),
              ("expr*", "init_expr"),
              ("token*", "semi1"),
              ("expr*", "comparison"),
              ("token*", "semi2"),
              ("expr*", "operation"),
              ("token*", "close_paren"),
              ("stmt*", "for_body"),)),
    # Block -> COLON, NEW_LINE, STATEMENTS+
    ("block", (("std::vector<stmt*>", "statements"),)),
    # Pass statement is needed to allow for empty blocks
    ("pass", (("token*", "pass_token"),)),
    # Control flow change -> break and continue support for while loops
    ("continue", (("token*", "continue_token"),)),
    ("break", (("token*", "break_token"),)),
    # Let statements
    ("let", (("token*", "name"), ("ykdatatype*", "data_type"), ("expr*", "expression"))),
    ("const", (("token*", "name"), ("ykdatatype*", "data_type"), ("expr*", "expression"))),
    # Native constant statement
    # `ITEM: Const[int] = ccode """1 + 1"""`
    ("nativeconst", (("token*", "name"), ("ykdatatype*", "data_type"),
                     ("token*", "ccode_keyword"), ("token*", "code_str"))),
    # Function declarations
    # Make sure we always say the return type
    # `def abc(a: int) -> None:`
    ("def", (("token*", "name"), ("std::vector<parameter>", "params"),
             ("stmt*", "function_body"), ("ykdatatype*", "return_type"), ("annotations", "annotations"))),
    ("class", (("token*", "name"), ("std::vector<parameter>", "members"), ("annotations", "annotations"))),
    ("enum", (("token*", "name"), ("std::vector<parameter>", "members"), ("annotations", "annotations"))),
    ("union", (("token*", "name"), ("std::vector<parameter>", "members"), ("annotations", "annotations"))),
    # import io [as io]
    ("import", (("token*", "import_token"), ("std::vector<token*>", "import_names"),
                ("token*", "name"), ("file_info*", "data"))),
    # --------------------- Special instructions in code -----------------
    # runtimefeature statement
    ("runtimefeature", (("token*", "runtimefeature_token"), ("token*", "feature"))),
    # ------------ Hidden special instructions for compiler --------------
    ("compins", (
        ("token*", "name"), ("ykdatatype*", "data_type"), ("token*", "meta1"), ("ykdatatype*", "meta2"),
        ("void*", "meta3"))
     )
], key=lambda x: x[0])

# EXPR CODE GEN
H_EXPR_SINGLE_FORWARD_DECLARE = "struct $R$_expr;"
H_EXPR_VISITOR_SINGLE = "  virtual void visit_$R$_expr($R$_expr *obj) = 0;"
H_EXPR_VISITOR = """
struct expr_visitor {
$VISIT_METHODS$
  virtual ~expr_visitor() = default;
};
""".strip()
H_EXPR_STRUCT = """
struct $R$_expr : expr {
  $EXPLICIT$$R$_expr($PARAMS$);
  void accept(expr_visitor *v) override;
  ast_type get_type() override;
$STATE$
};
""".strip()
# STMT CODE GEN
H_STMT_SINGLE_FORWARD_DECLARE = H_EXPR_SINGLE_FORWARD_DECLARE.replace("expr", "stmt")
H_STMT_VISITOR_SINGLE = H_EXPR_VISITOR_SINGLE.replace("expr", "stmt")
H_STMT_VISITOR = H_EXPR_VISITOR.replace("expr", "stmt")
H_STMT_STRUCT = H_EXPR_STRUCT.replace("expr", "stmt")
H_CREATE_AST_POOL_EXPR = "  expr *c_$R$_expr($PARAMS$);"
H_CREATE_AST_POOL_STMT = H_CREATE_AST_POOL_EXPR.replace("expr", "stmt")
CPP_EXPR = """
$R$_expr::$R$_expr($PARAMS$)
    : $FILL_STATE_PARAMS$ {}
void $R$_expr::accept(expr_visitor *v) {
  v->visit_$R$_expr(this);
}
ast_type $R$_expr::get_type() {
  return ast_type::EXPR_$RU$;
}
expr *ast_pool::c_$R$_expr($PARAMS$) {
  auto o = new $R$_expr($PARAMS_NO_TYPES$);
  cleanup_expr_.push_back(o);
  return o;
}
""".strip()
CPP_EXPR_NO_ACCEPT = """
$R$_expr::$R$_expr($PARAMS$)
    : $FILL_STATE_PARAMS$ {}
ast_type $R$_expr::get_type() {
  return ast_type::EXPR_$RU$;
}
void $R$_expr::accept(expr_visitor *v) {
}
expr *ast_pool::c_$R$_expr($PARAMS$) {
  auto o = new $R$_expr($PARAMS_NO_TYPES$);
  cleanup_expr_.push_back(o);
  return o;
}
""".strip()
CPP_STMT = CPP_EXPR.replace("expr", "stmt").replace("EXPR", "STMT")
CPP_STMT_NO_ACCEPT = CPP_EXPR_NO_ACCEPT.replace("expr", "stmt").replace("EXPR", "STMT")
H_AST_POOL = """
struct ast_pool {
  ast_pool();
  ~ast_pool();
$CREATE_EXPR$
$CREATE_STMT$

private:
  std::vector<expr *> cleanup_expr_;
  std::vector<stmt *> cleanup_stmt_;
};
""".strip()
H_AST_TYPES = """
enum class ast_type {
$EXPR_TYPES$,
$STMT_TYPES$
};
""".strip()
HEADER = """
// ast.h
// generated by update_ast.py
#ifndef AST_H
#define AST_H
#include "tokenizer/token.h"
#include "utilities/ykdatatype.h"
#include "utilities/annotations.h"
#include <vector>
namespace yaksha {
// ------ forward declarations ------
struct expr;
struct stmt;
struct parameter;
struct name_val;
$FORWARD_DECLS$
// Types of expressions and statements
$AST_TYPES$
// ------ expression visitor ------
$EXPR_VISITOR$
// ------ statement visitor ------
$STATEMENT_VISITOR$
// ------ expression base class ------
struct expr {
  virtual ~expr() = default;
  virtual void accept(expr_visitor *v) = 0;
  virtual ast_type get_type() = 0;
  size_t hits_{0};
};
// ------- statement base class ------
struct stmt {
  virtual ~stmt() = default;
  virtual void accept(stmt_visitor *v) = 0;
  virtual ast_type get_type() = 0;
  size_t hits_{0};
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
struct parameter {
    token* name_;
    ykdatatype* data_type_;
    token* enum_val_override_;
};
/**
* Name + value item
*/
struct name_val {
    token* name_;
    expr* value_;
};
} // namespace yaksha
#endif
""".strip()
CPP_FILE = """
// ast.cpp
// generated by update_ast.py
#include "ast/ast.h"
using namespace yaksha;
// ------- expressions -----
$EXPRESSIONS_IMPL$
// ------- statements -----
$STATEMENTS_IMPL$
// ------- utils ------
ast_pool::~ast_pool() {
  for (auto e : cleanup_expr_) {
    delete e;
  }
  for (auto e : cleanup_stmt_) {
    delete e;
  }
  cleanup_expr_.clear();
  cleanup_stmt_.clear();
}
ast_pool::ast_pool() {
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
    with open(os.path.join(".", "src", "ast", "ast.h"), "w+") as header_h:
        header_h.write(header_file_data)
    with open(os.path.join(".", "src", "ast", "ast.cpp"), "w+") as header_h:
        header_h.write(cpp_file_data)


if __name__ == "__main__":
    os.chdir(os.path.dirname(os.path.dirname(__file__)))
    main()
