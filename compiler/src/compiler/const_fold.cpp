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
// const_fold.cpp
#include "const_fold.h"
#include "literal_utils.h"
#include "utilities/ykdt_pool.h"
#include <utility>
using namespace yaksha;
const_fold::const_fold(ast_pool *ast_pool, yk_datatype_pool *dt_pool)
    : statement_stack_(), global_statements_(), ast_pool_(ast_pool),
      dt_pool_(dt_pool), context_pool_(), internal_token_pool_(), errors_(),
      env_stack_(dt_pool) {
  statement_stack_.emplace_back(&global_statements_);
};
const_fold::~const_fold() {
  for (auto &it : context_pool_) { delete it; }
  context_pool_.clear();
  for (auto &it : internal_token_pool_) { delete it; }
  internal_token_pool_.clear();
}
// ----------------------------------------------------
//  _______       ___    ___  ________   ________
// |\  ___ \     |\  \  /  /||\   __  \ |\   __  \-
// \ \   __/|    \ \  \/  / /\ \  \|\  \\ \  \|\  \-
//  \ \  \_|/__   \ \    / /  \ \   ____\\ \   _  _\-
//   \ \  \_|\ \   /     \/    \ \  \___| \ \  \\  \|-
//    \ \_______\ /  /\   \     \ \__\     \ \__\\ _\-
//     \|_______|/__/ /\ __\     \|__|      \|__|\|__|-
//               |__|/ \|__|
// ----------------------------------------------------
void const_fold::visit_assign_expr(assign_expr *obj) {
  // assign to a variable: a = `expr`
  if (obj->right_ == nullptr) {
    error("Expected an expression", nullptr);
    store_expression(obj);
    return;
  }
  obj->right_->accept(this);
  auto val = pop_last_expr_or_null();
  if (val == nullptr) {
    error("Failed to evaluate expression", obj->locate());
    store_expression(obj);
    return;
  }
  auto folded = ast_pool_->c_assign_expr(
      obj->name_, obj->opr_, val, obj->promoted_, obj->promoted_data_type_);
  store_expression(folded);
}
void const_fold::visit_assign_arr_expr(assign_arr_expr *obj) {
  // assign to an array member arr[`expr`] = `expr`
  // simplify rhs and store ✅
  if (obj->right_ == nullptr) {// TODO see if this is unnecessary
    error("Expected an expression", nullptr);
    store_expression(obj);
    return;
  }
  obj->right_->accept(this);
  auto val = pop_last_expr_or_null();
  if (val == nullptr) {
    error("Failed to evaluate expression", obj->locate());
    store_expression(obj);
    return;
  }
  auto folded = ast_pool_->c_assign_arr_expr(obj->assign_oper_, obj->opr_, val);
  store_expression(folded);
}
void const_fold::visit_assign_member_expr(assign_member_expr *obj) {
  // assign to a member obj.member = `expr`
  // simplify rhs and store ✅
  if (obj->right_ == nullptr) {// TODO see if this is unnecessary
    error("Expected an expression", nullptr);
    store_expression(obj);
    return;
  }
  obj->right_->accept(this);
  auto val = pop_last_expr_or_null();
  if (val == nullptr) {
    error("Failed to evaluate expression", obj->locate());
    store_expression(obj);
    return;
  }
  auto folded = ast_pool_->c_assign_member_expr(obj->set_oper_, obj->opr_, val);
  store_expression(folded);
}
void const_fold::visit_binary_expr(binary_expr *obj) {
  if (obj->right_ == nullptr || obj->left_ == nullptr) {
    error("Expected an expression", nullptr);
    store_expression(obj);
    return;
  }
  obj->left_->accept(this);
  auto left = pop_last_or_null();
  if (left == nullptr) {
    error("Failed to evaluate expression", obj->left_->locate());
    store_expression(obj);
    return;
  }
  obj->right_->accept(this);
  auto right = pop_last_or_null();
  if (right == nullptr) {
    error("Failed to evaluate expression", obj->right_->locate());
    store_expression(obj);
    return;
  }
  auto both_values =
      (left->context_type_ == const_fold_context_type::CFT_VALUE &&
       right->context_type_ == const_fold_context_type::CFT_VALUE);
  auto both_same_datatype = (left->fold_type_ == right->fold_type_);
  if (both_values && both_same_datatype) {
    // calculate
  } else {
    // keep as is
    store_expression(obj);
  }
}
void const_fold::visit_curly_call_expr(curly_call_expr *obj) {
  // here we are creating a new struct on stack or heap
  // but individual members can be evaluated here
  // vector<params> = new vector()
  // for each param in curly_call_expr:
  //   param->accept(this)
  //   vector<params>.push_back(pop_last())
  // push -> repack(vector<params>)
  store_expression(obj);
}
void const_fold::visit_fncall_expr(fncall_expr *obj) {
  // if all arguments are literals then we can evaluate the expression
  // otherwise we can let the rest of the system handle it
  // vector<params> = new vector()
  // for each param in fncall_expr:
  //   param->accept(this)
  //   vector<params>.push_back(pop_last())
  // push -> repack(vector<params>)
  store_expression(obj);
}
void const_fold::visit_get_expr(get_expr *obj) {
  // keep as is
  store_expression(obj);
}
void const_fold::visit_grouping_expr(grouping_expr *obj) {
  store_expression(obj->expression_);
}
void const_fold::visit_literal_expr(literal_expr *obj) {
  auto token_type = obj->literal_token_->type_;
  // will do nothing for string literals
  if (token_type == token_type::STRING ||
      token_type == token_type::THREE_QUOTE_STRING) {
    store_expression(obj);
    return;
  }
  if (token_type == token_type::KEYWORD_NONE) {
    auto con = new_context();
    con->context_type_ = const_fold_context_type::CFT_VALUE;
    con->fold_type_ = const_fold_type::CFT_NONE;
    con->expr_or_stmt_.expr_val_ = obj;
    // con->token_ = ... // TODO
    store(con);
    return;
  }
  // TODO True / False / None?
  auto converted = convert_literal(token_type, obj->literal_token_);
  if (!converted.error_.empty()) {
    error(converted.error_, obj->literal_token_);
    store_expression(obj);
    return;
  }
  // first convert token type to ykdatatype (u8, i8, etc)
  // convert to fold type
  // context --> CFT_VALUE
  // add it to a value holder union // TOD
}
void const_fold::visit_logical_expr(logical_expr *obj) {
  // same as binary_expr
}
void const_fold::visit_macro_call_expr(macro_call_expr *obj) {
  // ignored (this is handled prior to const folding)
  store_expression(obj);
}
void const_fold::visit_set_expr(set_expr *obj) {
  // keep as is
  store_expression(obj);
}
void const_fold::visit_square_bracket_access_expr(
    square_bracket_access_expr *obj) {
  // keep as is
  store_expression(obj);
}
void const_fold::visit_square_bracket_set_expr(square_bracket_set_expr *obj) {
  store_expression(obj);
}
void const_fold::visit_unary_expr(unary_expr *obj) {
  // if right side is a literal then we can evaluate the expression
  store_expression(obj);
}
void const_fold::visit_variable_expr(variable_expr *obj) {
  // if this is a global variable or a const variable then we can evaluate the expression
  store_expression(obj);
}
// ----------------------------------------------------
//  ________   _________   _____ ______    _________
// |\   ____\ |\___   ___\|\   _ \  _   \ |\___   ___\-
// \ \  \___|_\|___ \  \_|\ \  \\\__\ \  \\|___ \  \_|
//  \ \_____  \    \ \  \  \ \  \\|__| \  \    \ \  \-
//   \|____|\  \    \ \  \  \ \  \    \ \  \    \ \  \-
//     ____\_\  \    \ \__\  \ \__\    \ \__\    \ \__\-
//    |\_________\    \|__|   \|__|     \|__|     \|__|-
//    \|_________|
// ----------------------------------------------------
void const_fold::visit_block_stmt(block_stmt *obj) {
  // If we visit a block statement that means we need to ensure tha the all sub statements are captured
  std::vector<const_fold_context *> block_statements{};
  statement_stack_.emplace_back(&block_statements);
  for (stmt *st : obj->statements_) { st->accept(this); }
  statement_stack_.pop_back();
  statement_stack_.back()->emplace_back(
      wrap(ast_pool_->c_block_stmt(unwrap_vector_stmt(block_statements))));
}
void const_fold::visit_break_stmt(break_stmt *obj) { store_statement(obj); }
void const_fold::visit_ccode_stmt(ccode_stmt *obj) { store_statement(obj); }
void const_fold::visit_cfor_stmt(cfor_stmt *obj) {
  statement_stack_.back()->emplace_back(wrap(obj));
}
void const_fold::visit_class_stmt(class_stmt *obj) { store_statement(obj); }
void const_fold::visit_compins_stmt(compins_stmt *obj) { store_statement(obj); }
void const_fold::visit_const_stmt(const_stmt *obj) {
  // a: Const[int] = 1     // ok - literal
  // b: Const[int] = a + 2 // ok - evaluate to literal
  // c: Const[int] = a + b // ok - evaluate to literal
  // d: Const[int] = user_input() // error - not a literal
  // TODO -- const statements in local scopes, RHS does not need to be a literal
  // TODO -- const statements in global scope, RHS must be a literal or evaluate to a literal
  if (obj->data_type_ == nullptr) {
    error("Expected a data type", obj->name_);
    store_statement(obj);
    return;
  }
  if (obj->expression_ == nullptr) {
    error("Expected an expression", obj->name_);
    store_statement(obj);
    return;
  }
  // TODO if this is already a literal then we can just store it
  // see if we can evaluate the expression and simplify it to a literal
  //  if not then we can let the rest of the system handle it as an error
  obj->expression_->accept(this);
  const_fold_context *val = peek_last_or_null();
  if (val == nullptr) {
    error("Failed to evaluate expression", obj->name_);
    store_statement(obj);
    return;
  }
  // TODO convert the result to a literal, if it is a literal
  //   else we can let the rest of the system handle it as an error
  statement_stack_.back()->emplace_back(wrap(obj));
}
void const_fold::visit_continue_stmt(continue_stmt *obj) {
  store_statement(obj);
}
void const_fold::visit_def_stmt(def_stmt *obj) {
  statement_stack_.back()->emplace_back(wrap(obj));
}
void const_fold::visit_defer_stmt(defer_stmt *obj) { store_statement(obj); }
void const_fold::visit_del_stmt(del_stmt *obj) { store_statement(obj); }
void const_fold::visit_enum_stmt(enum_stmt *obj) { store_statement(obj); }
void const_fold::visit_expression_stmt(expression_stmt *obj) {
  if (obj->expression_ == nullptr) {
    error("Expected an expression", obj->locate());
    store_statement(obj);
    return;
  }
  obj->expression_->accept(this);
  auto val = peek_last_or_null();
  if (val == nullptr) {
    error("Failed to evaluate expression", obj->expression_->locate());
    store_statement(obj);
    return;
  }
  // TODO recreate the expression statement
  statement_stack_.back()->emplace_back(wrap(obj));
}
void const_fold::visit_foreach_stmt(foreach_stmt *obj) {
  statement_stack_.back()->emplace_back(wrap(obj));
}
void const_fold::visit_forendless_stmt(forendless_stmt *obj) {
  statement_stack_.back()->emplace_back(wrap(obj));
}
void const_fold::visit_if_stmt(if_stmt *obj) {
  // TODO try and simplify the conditions
  statement_stack_.back()->emplace_back(wrap(obj));
}
void const_fold::visit_import_stmt(import_stmt *obj) { store_statement(obj); }
void const_fold::visit_let_stmt(let_stmt *obj) {
  // eval rhs
  // TODO keep it in scope if the RHS is a literal
  statement_stack_.back()->emplace_back(wrap(obj));
}
void const_fold::visit_nativeconst_stmt(nativeconst_stmt *obj) {
  store_statement(obj);
}
void const_fold::visit_pass_stmt(pass_stmt *obj) { store_statement(obj); }
void const_fold::visit_return_stmt(return_stmt *obj) {
  // If we have an expression here, then we need to evaluate it
  statement_stack_.back()->emplace_back(wrap(obj));
}
void const_fold::visit_runtimefeature_stmt(runtimefeature_stmt *obj) {
  store_statement(obj);
}
void const_fold::visit_while_stmt(while_stmt *obj) {
  statement_stack_.back()->emplace_back(wrap(obj));
}
const_fold_context *const_fold::wrap(stmt *statement) {
  auto con = new_context();
  con->context_type_ = const_fold_context_type::CFT_STMT;
  con->expr_or_stmt_.stmt_val_ = statement;
  return con;
}
const_fold_context *const_fold::wrap(expr *expression) {
  auto con = new_context();
  con->context_type_ = const_fold_context_type::CFT_EXPR;
  con->expr_or_stmt_.expr_val_ = expression;
  return con;
}
const_fold_context *const_fold::new_context() {
  auto con = new const_fold_context();
  con->fold_type_ = const_fold_type::CFT_UNKNOWN;
  context_pool_.emplace_back(con);
  return con;
}
void const_fold::error(const std::string &message, token *token) {
  if (token == nullptr) {
    errors_.emplace_back(message, "-", 0, 0);
    return;
  }
  errors_.emplace_back(message, token);
}
void const_fold::store(const_fold_context *obj) {
  statement_stack_.back()->emplace_back(obj);
}
void const_fold::store_statement(stmt *obj) {
  statement_stack_.back()->emplace_back(wrap(obj));
}
void const_fold::store_expression(expr *obj) {
  statement_stack_.back()->emplace_back(wrap(obj));
}
std::vector<stmt *> const_fold::unwrap_vector_stmt(
    const std::vector<const_fold_context *> &to_unwrap) {
  std::vector<stmt *> unwrapped{};
  for (auto &it : to_unwrap) {
    if (it->context_type_ == const_fold_context_type::CFT_STMT) {
      unwrapped.emplace_back(it->expr_or_stmt_.stmt_val_);
    } else {
      error("Expected a statement", nullptr);
    }
  }
  return unwrapped;
}
const_fold_context *const_fold::peek_last_or_null() {
  if (statement_stack_.empty() || statement_stack_.back()->empty()) {
    return nullptr;
  }
  return statement_stack_.back()->back();
}
const_fold_context *const_fold::pop_last_or_null() {
  if (statement_stack_.empty() || statement_stack_.back()->empty()) {
    return nullptr;
  }
  auto val = statement_stack_.back()->back();
  statement_stack_.back()->pop_back();
  return val;
}
expr *const_fold::pop_last_expr_or_null() {
  auto val = pop_last_or_null();
  if (val == nullptr) { return nullptr; }
  if (val->context_type_ == const_fold_context_type::CFT_EXPR ||
      val->context_type_ == const_fold_context_type::CFT_GARBAGE_VALUE) {
    return val->expr_or_stmt_.expr_val_;
  }
  return to_expr_or_null(val);
}
expr *const_fold::to_expr_or_null(const_fold_context *val) {
  if (val->context_type_ == const_fold_context_type::CFT_VALUE) {
    switch (val->fold_type_) {
      case const_fold_type::CFT_INT8:
        return this->ast_pool_->c_literal_expr(
            this->new_token(val->token_, token_type::INTEGER_DECIMAL_8,
                            std::to_string(val->value_.int_val_)));
      case const_fold_type::CFT_INT16:
        return this->ast_pool_->c_literal_expr(
            this->new_token(val->token_, token_type::INTEGER_DECIMAL_16,
                            std::to_string(val->value_.int_val_)));
      case const_fold_type::CFT_INT32:
        return this->ast_pool_->c_literal_expr(
            this->new_token(val->token_, token_type::INTEGER_DECIMAL,
                            std::to_string(val->value_.int_val_)));
      case const_fold_type::CFT_INT64:
        return this->ast_pool_->c_literal_expr(
            this->new_token(val->token_, token_type::INTEGER_DECIMAL_64,
                            std::to_string(val->value_.int_val_)));
      case const_fold_type::CFT_UINT8:
        return this->ast_pool_->c_literal_expr(
            this->new_token(val->token_, token_type::UINTEGER_DECIMAL_8,
                            std::to_string(val->value_.uint_val_)));
      case const_fold_type::CFT_UINT16:
        return this->ast_pool_->c_literal_expr(
            this->new_token(val->token_, token_type::UINTEGER_DECIMAL_16,
                            std::to_string(val->value_.uint_val_)));
      case const_fold_type::CFT_UINT32:
        return this->ast_pool_->c_literal_expr(
            this->new_token(val->token_, token_type::UINTEGER_DECIMAL,
                            std::to_string(val->value_.uint_val_)));
      case const_fold_type::CFT_UINT64:
        return this->ast_pool_->c_literal_expr(
            this->new_token(val->token_, token_type::UINTEGER_DECIMAL_64,
                            std::to_string(val->value_.uint_val_)));
      case const_fold_type::CFT_FLOAT:
        return this->ast_pool_->c_literal_expr(
            this->new_token(val->token_, token_type::FLOAT_NUMBER,
                            std::to_string(val->value_.float_val_)));
      case const_fold_type::CFT_DOUBLE:
        return this->ast_pool_->c_literal_expr(
            this->new_token(val->token_, token_type::DOUBLE_NUMBER,
                            std::to_string(val->value_.double_val_)));
      case const_fold_type::CFT_BOOL:
        return this->ast_pool_->c_literal_expr(
            this->new_token(val->token_,
                            val->value_.bool_val_ ? token_type::KEYWORD_TRUE
                                                  : token_type::KEYWORD_FALSE,
                            val->value_.bool_val_ ? "True" : "False"));
      case const_fold_type::CFT_NONE:
        return this->ast_pool_->c_literal_expr(
            this->new_token(val->token_, token_type::KEYWORD_NONE, "None"));
      default:
        return nullptr;
    }
  }
  return nullptr;
}
token *const_fold::new_token(token *location_token, token_type token_type,
                             std::string token_str) {
  auto tok = new token();
  tok->token_ = std::move(token_str);
  tok->type_ = token_type;
  tok->file_ = location_token->file_;
  tok->line_ = location_token->line_;
  internal_token_pool_.emplace_back(tok);
  return tok;
}
cf_evaluator::cf_evaluator(std::vector<const_fold_context *> *context_pool)
    : context_pool_(context_pool) {}
const_fold_context *cf_evaluator::add(const_fold_context *lhs,
                                      const_fold_context *rhs) {
  return nullptr;
}
const_fold_context *cf_evaluator::sub(const_fold_context *lhs,
                                      const_fold_context *rhs) {
  return nullptr;
}
const_fold_context *cf_evaluator::mul(const_fold_context *lhs,
                                      const_fold_context *rhs) {
  return nullptr;
}
const_fold_context *cf_evaluator::div(const_fold_context *lhs,
                                      const_fold_context *rhs) {
  return nullptr;
}
const_fold_context *cf_evaluator::mod(const_fold_context *lhs,
                                      const_fold_context *rhs) {
  return nullptr;
}
const_fold_context *cf_evaluator::pow(const_fold_context *lhs,
                                      const_fold_context *rhs) {
  return nullptr;
}
const_fold_context *cf_evaluator::bit_and(const_fold_context *lhs,
                                          const_fold_context *rhs) {
  return nullptr;
}
const_fold_context *cf_evaluator::bit_or(const_fold_context *lhs,
                                         const_fold_context *rhs) {
  return nullptr;
}
const_fold_context *cf_evaluator::bit_xor(const_fold_context *lhs,
                                          const_fold_context *rhs) {
  return nullptr;
}
const_fold_context *cf_evaluator::bit_not(const_fold_context *lhs) {
  return nullptr;
}
const_fold_context *cf_evaluator::bit_lshift(const_fold_context *lhs,
                                             const_fold_context *rhs) {
  return nullptr;
}
const_fold_context *cf_evaluator::bit_rshift(const_fold_context *lhs,
                                             const_fold_context *rhs) {
  return nullptr;
}
const_fold_context *cf_evaluator::logical_and(const_fold_context *lhs,
                                              const_fold_context *rhs) {
  return nullptr;
}
const_fold_context *cf_evaluator::logical_or(const_fold_context *lhs,
                                             const_fold_context *rhs) {
  return nullptr;
}
const_fold_context *cf_evaluator::logical_not(const_fold_context *lhs) {
  return nullptr;
}
const_fold_context *cf_evaluator::unary_minus(const_fold_context *lhs) {
  return nullptr;
}
