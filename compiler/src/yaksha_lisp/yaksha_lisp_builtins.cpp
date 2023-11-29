// ==============================================================================================
// ╦  ┬┌─┐┌─┐┌┐┌┌─┐┌─┐    Yaksha Programming Language
// ║  ││  ├┤ │││└─┐├┤     is Licensed with GPLv3 + exta terms. Please see below.
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
// yaksha_lisp_builtins.cpp
#include "yaksha_lisp_builtins.h"
#include "yaksha_lisp.h"
#include <fstream>
#include <iostream>
#include <unordered_set>
using namespace yaksha;
// TODO make the code here nicer, too much copy pasta
static bool yaksha_macro_print_allowed = false;
static yaksha_lisp_value *
eq_operator(yaksha_envmap *env,
            const std::vector<yaksha_lisp_value *> &e_args) {
  auto left_side_val = e_args[0];
  auto result = env->create_number(0);
  if (left_side_val->type_ != e_args[1]->type_) {
    throw parsing_error{"==/!= type mismatch", "", 0, 0};
  }
  if (left_side_val->type_ == yaksha_lisp_value_type::NUMBER &&
      e_args[1]->type_ == yaksha_lisp_value_type::NUMBER) {
    result->num_ = left_side_val->num_ == e_args[1]->num_;
  } else if (left_side_val->type_ == yaksha_lisp_value_type::STRING &&
             e_args[1]->type_ == yaksha_lisp_value_type::STRING) {
    result->num_ = left_side_val->str_ == e_args[1]->str_;
  } else if (left_side_val->type_ == yaksha_lisp_value_type::LIST &&
             e_args[1]->type_ == yaksha_lisp_value_type::LIST) {
    result->num_ = left_side_val->list_.size() == e_args[1]->list_.size();
    if (result->num_) {
      for (auto i = 0; i < left_side_val->list_.size(); ++i) {
        auto args = std::vector<yaksha_lisp_value *>{left_side_val->list_[i],
                                                     e_args[1]->list_[i]};
        result->num_ = eq_operator(env, args)->num_;
        if (!result->num_) { break; }
      }
    }
  } else if (left_side_val->type_ == yaksha_lisp_value_type::BUILTIN &&
             e_args[1]->type_ == yaksha_lisp_value_type::BUILTIN) {
    result->num_ = left_side_val->builtin_ == e_args[1]->builtin_;
  } else if ((left_side_val->type_ == yaksha_lisp_value_type::LAMBDA &&
              e_args[1]->type_ == yaksha_lisp_value_type::LAMBDA) ||
             (left_side_val->type_ == yaksha_lisp_value_type::METAMACRO &&
              e_args[1]->type_ == yaksha_lisp_value_type::METAMACRO)) {
    result->num_ = left_side_val == e_args[1];
  } else {
    // fall back to << string comparison
    std::stringstream left_side{};
    std::stringstream right_side{};
    left_side << left_side_val;
    right_side << e_args[1];
    result->num_ = left_side.str() == right_side.str();
  }
  return result;
}
yaksha_lisp_value *
yaksha_lisp_builtins::add_(const std::vector<yaksha_lisp_value *> &args,
                           yaksha_envmap *env) {
  if (args.size() < 2) {
    throw parsing_error{"+ takes at least 2 arguments", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto r = yaksha_lisp_builtins::copy_val(env, e_args[0]);
  for (auto i = 1; i < e_args.size(); ++i) {
    if (r->type_ != e_args[i]->type_) {
      throw parsing_error{"+ type mismatch", "", 0, 0};
    }
    if (r->type_ == yaksha_lisp_value_type::NUMBER &&
        e_args[i]->type_ == yaksha_lisp_value_type::NUMBER) {
      r->num_ += e_args[i]->num_;
    } else if (r->type_ == yaksha_lisp_value_type::STRING &&
               e_args[i]->type_ == yaksha_lisp_value_type::STRING) {
      r->str_ += e_args[i]->str_;
    } else if (r->type_ == yaksha_lisp_value_type::LIST &&
               e_args[i]->type_ == yaksha_lisp_value_type::LIST) {
      r->list_.insert(r->list_.end(), e_args[i]->list_.begin(),
                      e_args[i]->list_.end());
    } else {
      throw parsing_error{"+ takes only numbers, strings or lists", "", 0, 0};
    }
  }
  return r;
}
yaksha_lisp_value *
yaksha_lisp_builtins::sub_(const std::vector<yaksha_lisp_value *> &args,
                           yaksha_envmap *env) {
  if (args.size() != 2) {
    throw parsing_error{"- takes 2 arguments", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto r = yaksha_lisp_builtins::copy_val(env, e_args[0]);
  if (r->type_ != e_args[1]->type_) {
    throw parsing_error{"- type mismatch", "", 0, 0};
  }
  if (r->type_ == yaksha_lisp_value_type::NUMBER &&
      e_args[1]->type_ == yaksha_lisp_value_type::NUMBER) {
    r->num_ -= e_args[1]->num_;
  } else {
    throw parsing_error{"- takes only numbers", "", 0, 0};
  }
  return r;
}
yaksha_lisp_value *
yaksha_lisp_builtins::mul_(const std::vector<yaksha_lisp_value *> &args,
                           yaksha_envmap *env) {
  if (args.size() < 2) {
    throw parsing_error{"* takes at least 2 arguments", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto r = yaksha_lisp_builtins::copy_val(env, e_args[0]);
  for (auto i = 1; i < e_args.size(); ++i) {
    if (r->type_ != e_args[i]->type_) {
      throw parsing_error{"* type mismatch", "", 0, 0};
    }
    if (r->type_ == yaksha_lisp_value_type::NUMBER &&
        e_args[i]->type_ == yaksha_lisp_value_type::NUMBER) {
      r->num_ *= e_args[i]->num_;
    } else {
      throw parsing_error{"* takes only numbers", "", 0, 0};
    }
  }
  return r;
}
yaksha_lisp_value *
yaksha_lisp_builtins::div_(const std::vector<yaksha_lisp_value *> &args,
                           yaksha_envmap *env) {
  if (args.size() != 2) {
    throw parsing_error{"/ takes 2 arguments", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto r = yaksha_lisp_builtins::copy_val(env, e_args[0]);
  if (r->type_ != e_args[1]->type_) {
    throw parsing_error{"/ type mismatch", "", 0, 0};
  }
  if (r->type_ == yaksha_lisp_value_type::NUMBER &&
      e_args[1]->type_ == yaksha_lisp_value_type::NUMBER) {
    if (e_args[1]->num_ == 0) {
      throw parsing_error{"/ division by zero", "", 0, 0};
    }
    r->num_ /= e_args[1]->num_;
  } else {
    throw parsing_error{"/ takes only numbers", "", 0, 0};
  }
  return r;
}
yaksha_lisp_value *
yaksha_lisp_builtins::mod_(const std::vector<yaksha_lisp_value *> &args,
                           yaksha_envmap *env) {
  if (args.size() != 2) {
    throw parsing_error{"modulo takes 2 arguments", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto r = yaksha_lisp_builtins::copy_val(env, e_args[0]);
  if (r->type_ != e_args[1]->type_) {
    throw parsing_error{"modulo type mismatch", "", 0, 0};
  }
  if (r->type_ == yaksha_lisp_value_type::NUMBER &&
      e_args[1]->type_ == yaksha_lisp_value_type::NUMBER) {
    r->num_ = r->num_ % e_args[1]->num_;
  } else {
    throw parsing_error{"modulo takes only numbers", "", 0, 0};
  }
  return r;
}
yaksha_lisp_value *
yaksha_lisp_builtins::eq_(const std::vector<yaksha_lisp_value *> &args,
                          yaksha_envmap *env) {
  if (args.size() != 2) {
    throw parsing_error{"== takes 2 arguments", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  yaksha_lisp_value *r = eq_operator(env, e_args);
  r->type_ = yaksha_lisp_value_type::NUMBER;
  return r;
}
yaksha_lisp_value *
yaksha_lisp_builtins::neq_(const std::vector<yaksha_lisp_value *> &args,
                           yaksha_envmap *env) {
  if (args.size() != 2) {
    throw parsing_error{"!= takes 2 arguments", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  yaksha_lisp_value *r = eq_operator(env, e_args);
  r->type_ = yaksha_lisp_value_type::NUMBER;
  r->num_ = !r->num_;
  return r;
}
yaksha_lisp_value *
yaksha_lisp_builtins::gt_(const std::vector<yaksha_lisp_value *> &args,
                          yaksha_envmap *env) {
  if (args.size() != 2) {
    throw parsing_error{"> takes 2 arguments", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto r = yaksha_lisp_builtins::copy_val(env, e_args[0]);
  if (r->type_ != e_args[1]->type_) {
    throw parsing_error{"> type mismatch", "", 0, 0};
  }
  if (r->type_ == yaksha_lisp_value_type::NUMBER &&
      e_args[1]->type_ == yaksha_lisp_value_type::NUMBER) {
    r->num_ = r->num_ > e_args[1]->num_;
  } else if (r->type_ == yaksha_lisp_value_type::STRING &&
             e_args[1]->type_ == yaksha_lisp_value_type::STRING) {
    r->num_ = r->str_ > e_args[1]->str_;
  } else {
    throw parsing_error{"> takes only numbers or strings", "", 0, 0};
  }
  r->type_ = yaksha_lisp_value_type::NUMBER;
  return r;
}
yaksha_lisp_value *
yaksha_lisp_builtins::lt_(const std::vector<yaksha_lisp_value *> &args,
                          yaksha_envmap *env) {
  if (args.size() != 2) {
    throw parsing_error{"< takes 2 arguments", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto r = yaksha_lisp_builtins::copy_val(env, e_args[0]);
  if (r->type_ != e_args[1]->type_) {
    throw parsing_error{"< type mismatch", "", 0, 0};
  }
  if (r->type_ == yaksha_lisp_value_type::NUMBER &&
      e_args[1]->type_ == yaksha_lisp_value_type::NUMBER) {
    r->num_ = r->num_ < e_args[1]->num_;
  } else if (r->type_ == yaksha_lisp_value_type::STRING &&
             e_args[1]->type_ == yaksha_lisp_value_type::STRING) {
    r->num_ = r->str_ < e_args[1]->str_;
  } else {
    throw parsing_error{"< takes only numbers or strings", "", 0, 0};
  }
  r->type_ = yaksha_lisp_value_type::NUMBER;
  return r;
}
yaksha_lisp_value *
yaksha_lisp_builtins::gte_(const std::vector<yaksha_lisp_value *> &args,
                           yaksha_envmap *env) {
  if (args.size() != 2) {
    throw parsing_error{">= takes 2 arguments", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto r = yaksha_lisp_builtins::copy_val(env, e_args[0]);
  if (r->type_ != e_args[1]->type_) {
    throw parsing_error{">= type mismatch", "", 0, 0};
  }
  if (r->type_ == yaksha_lisp_value_type::NUMBER &&
      e_args[1]->type_ == yaksha_lisp_value_type::NUMBER) {
    r->num_ = r->num_ >= e_args[1]->num_;
  } else if (r->type_ == yaksha_lisp_value_type::STRING &&
             e_args[1]->type_ == yaksha_lisp_value_type::STRING) {
    r->num_ = r->str_ >= e_args[1]->str_;
  } else {
    throw parsing_error{">= takes only numbers or strings", "", 0, 0};
  }
  r->type_ = yaksha_lisp_value_type::NUMBER;
  return r;
}
yaksha_lisp_value *
yaksha_lisp_builtins::lte_(const std::vector<yaksha_lisp_value *> &args,
                           yaksha_envmap *env) {
  if (args.size() != 2) {
    throw parsing_error{"<= takes 2 arguments", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto r = yaksha_lisp_builtins::copy_val(env, e_args[0]);
  if (r->type_ != e_args[1]->type_) {
    throw parsing_error{"<= type mismatch", "", 0, 0};
  }
  if (r->type_ == yaksha_lisp_value_type::NUMBER &&
      e_args[1]->type_ == yaksha_lisp_value_type::NUMBER) {
    r->num_ = r->num_ <= e_args[1]->num_;
  } else if (r->type_ == yaksha_lisp_value_type::STRING &&
             e_args[1]->type_ == yaksha_lisp_value_type::STRING) {
    r->num_ = r->str_ <= e_args[1]->str_;
  } else {
    throw parsing_error{"<= takes only numbers or strings", "", 0, 0};
  }
  r->type_ = yaksha_lisp_value_type::NUMBER;
  return r;
}
yaksha_lisp_value *
yaksha_lisp_builtins::and_(const std::vector<yaksha_lisp_value *> &args,
                           yaksha_envmap *env) {
  if (args.size() != 2) {
    throw parsing_error{"and takes 2 arguments", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto r = yaksha_lisp_builtins::copy_val(env, e_args[0]);
  if (r->type_ != yaksha_lisp_value_type::NUMBER ||
      e_args[1]->type_ != yaksha_lisp_value_type::NUMBER) {
    throw parsing_error{"and takes only numbers", "", 0, 0};
  }
  r->num_ = r->num_ && e_args[1]->num_;
  r->type_ = yaksha_lisp_value_type::NUMBER;
  return r;
}
yaksha_lisp_value *
yaksha_lisp_builtins::or_(const std::vector<yaksha_lisp_value *> &args,
                          yaksha_envmap *env) {
  if (args.size() != 2) {
    throw parsing_error{"or takes 2 arguments", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto r = yaksha_lisp_builtins::copy_val(env, e_args[0]);
  if (r->type_ != yaksha_lisp_value_type::NUMBER ||
      e_args[1]->type_ != yaksha_lisp_value_type::NUMBER) {
    throw parsing_error{"or takes only numbers", "", 0, 0};
  }
  r->num_ = r->num_ || e_args[1]->num_;
  r->type_ = yaksha_lisp_value_type::NUMBER;
  return r;
}
yaksha_lisp_value *
yaksha_lisp_builtins::not_(const std::vector<yaksha_lisp_value *> &args,
                           yaksha_envmap *env) {
  if (args.size() != 1) {
    throw parsing_error{"not takes 1 argument", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto r = yaksha_lisp_builtins::copy_val(env, e_args[0]);
  if (r->type_ != yaksha_lisp_value_type::NUMBER) {
    throw parsing_error{"not takes only numbers", "", 0, 0};
  }
  r->num_ = !r->num_;
  r->type_ = yaksha_lisp_value_type::NUMBER;
  return r;
}
yaksha_lisp_value *
yaksha_lisp_builtins::if_(const std::vector<yaksha_lisp_value *> &args,
                          yaksha_envmap *env) {
  // if is a special form, so we don't evaluate the arguments
  if (args.size() != 2 && args.size() != 3) {
    throw parsing_error("if takes 2 or 3 arguments", "", 0, 0);
  }
  auto cond = args[0];
  auto true_val = args[1];
  auto false_val = args.size() == 3 ? args[2] : env->create_nil();
  auto condition_result = env->eval(cond);
  if (env->is_truthy(condition_result)) {
    return env->eval(true_val);
  } else {
    return env->eval(false_val);
  }
}
yaksha_lisp_value *
yaksha_lisp_builtins::print_(const std::vector<yaksha_lisp_value *> &args,
                             yaksha_envmap *env) {
  if (args.size() != 1) {
    throw parsing_error{"print/println takes 1 argument", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto r = yaksha_lisp_builtins::copy_val(env, e_args[0]);
  if (r->type_ == yaksha_lisp_value_type::NUMBER) {
    if (yaksha_macro_print_allowed) { std::cout << r->num_; }
  } else if (r->type_ == yaksha_lisp_value_type::STRING) {
    if (yaksha_macro_print_allowed) { std::cout << r->str_; }
  } else {
    throw parsing_error{"print/println takes only numbers or strings", "", 0,
                        0};
  }
  return env->create_nil();
}
yaksha_lisp_value *
yaksha_lisp_builtins::println_(const std::vector<yaksha_lisp_value *> &args,
                               yaksha_envmap *env) {
  auto v = yaksha_lisp_builtins::print_(args, env);
  if (yaksha_macro_print_allowed) { std::cout << std::endl; }
  return v;
}
yaksha_lisp_value *
yaksha_lisp_builtins::defun_(const std::vector<yaksha_lisp_value *> &args,
                             yaksha_envmap *env) {
  if (args.size() < 3) {
    throw parsing_error{"defun takes at least 3 arguments", "", 0, 0};
  }
  auto name = args[0];
  auto params = args[1];
  auto body = env->create_val();
  body->type_ = yaksha_lisp_value_type::LIST;
  for (size_t i = 2; i < args.size(); i++) { body->list_.push_back(args[i]); }
  if (!(name->type_ == yaksha_lisp_value_type::EXPR &&
        name->expr_->token_->type_ == yaksha_lisp_token_type::SYMBOL)) {
    throw parsing_error{"defun takes a symbol as first argument", "", 0, 0};
  }
  if (!(params->type_ == yaksha_lisp_value_type::EXPR &&
        params->expr_->token_->type_ == yaksha_lisp_token_type::PAREN_OPEN)) {
    throw parsing_error{"defun takes a s-expr as second argument", "", 0, 0};
  }
  std::unordered_set<std::string> param_names;
  for (auto &p : params->expr_->list_) {
    if (!(p->type_ == yaksha_lisp_expr_type::TERMINAL &&
          p->token_->type_ == yaksha_lisp_token_type::SYMBOL)) {
      throw parsing_error{"defun takes a s-expr of symbols as second argument",
                          "", 0, 0};
    }
    if (param_names.find(p->token_->token_) != param_names.end()) {
      throw parsing_error{"defun takes a s-expr of unique symbols as second "
                          "argument",
                          "", 0, 0};
    }
    param_names.insert(p->token_->token_);
  }
  auto callable = env->create_val();
  callable->type_ = yaksha_lisp_value_type::LAMBDA;
  callable->list_ = std::vector<yaksha_lisp_value *>{params, body};
  callable->str_ = name->expr_->token_->token_;
  callable->closure_ = env;
  env->set(name->expr_->token_->token_, callable);
  return env->create_nil();
}
yaksha_lisp_value *
yaksha_lisp_builtins::lambda_(const std::vector<yaksha_lisp_value *> &args,
                              yaksha_envmap *env) {
  if (args.size() != 2) {
    throw parsing_error{"lambda takes 2 arguments", "", 0, 0};
  }
  auto params = args[0];
  auto body = env->create_val();
  body->type_ = yaksha_lisp_value_type::LIST;
  body->list_.push_back(args[1]);
  if (!(params->type_ == yaksha_lisp_value_type::EXPR &&
        params->expr_->token_->type_ == yaksha_lisp_token_type::PAREN_OPEN)) {
    throw parsing_error{"lambda takes a s-expr as second argument", "", 0, 0};
  }
  std::unordered_set<std::string> param_names;
  for (auto &p : params->expr_->list_) {
    if (!(p->type_ == yaksha_lisp_expr_type::TERMINAL &&
          p->token_->type_ == yaksha_lisp_token_type::SYMBOL)) {
      throw parsing_error{"lambda takes a s-expr of symbols as second argument",
                          "", 0, 0};
    }
    if (param_names.find(p->token_->token_) != param_names.end()) {
      throw parsing_error{"lambda takes a s-expr of unique symbols as second "
                          "argument",
                          "", 0, 0};
    }
    param_names.insert(p->token_->token_);
  }
  auto callable = env->create_val();
  callable->type_ = yaksha_lisp_value_type::LAMBDA;
  callable->list_ = std::vector<yaksha_lisp_value *>{params, body};
  callable->str_ = "";
  callable->closure_ = env;
  return callable;
}
yaksha_lisp_value *
yaksha_lisp_builtins::def_(const std::vector<yaksha_lisp_value *> &args,
                           yaksha_envmap *env) {
  if (args.size() != 2) {
    throw parsing_error{"def takes 2 arguments", "", 0, 0};
  }
  auto name = args[0];
  if (!(name->type_ == yaksha_lisp_value_type::EXPR &&
        name->expr_->token_->type_ == yaksha_lisp_token_type::SYMBOL)) {
    throw parsing_error{"def takes a symbol as first argument", "", 0, 0};
  }
  auto val = env->eval(args[1]);
  env->set(name->expr_->token_->token_, val);
  return val;
}
yaksha_lisp_value *
yaksha_lisp_builtins::raise_error_(const std::vector<yaksha_lisp_value *> &args,
                                   yaksha_envmap *env) {
  if (args.size() != 1) {
    throw parsing_error{"raise-error takes 1 argument", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto r = yaksha_lisp_builtins::copy_val(env, e_args[0]);
  if (r->type_ != yaksha_lisp_value_type::STRING) {
    throw parsing_error{"raise-error takes only strings", "", 0, 0};
  }
  throw parsing_error{r->str_, "", 0, 0};
}
yaksha_lisp_value *
yaksha_lisp_builtins::setq_(const std::vector<yaksha_lisp_value *> &args,
                            yaksha_envmap *env) {
  if (args.size() != 2) {
    throw parsing_error{"setq takes 2 arguments", "", 0, 0};
  }
  auto name = args[0];
  if (!(name->type_ == yaksha_lisp_value_type::EXPR &&
        name->expr_->token_->type_ == yaksha_lisp_token_type::SYMBOL)) {
    throw parsing_error{"setq takes a symbol as first argument", "", 0, 0};
  }
  auto val = env->eval(args[1]);
  env->set(name->expr_->token_->token_, val, false);
  return val;
}
yaksha_lisp_value *
yaksha_lisp_builtins::do_(const std::vector<yaksha_lisp_value *> &args,
                          yaksha_envmap *env) {
  if (args.empty()) {
    throw parsing_error{"do takes at least 1 argument", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto last = e_args[e_args.size() - 1];
  return last;
}
yaksha_lisp_value *
yaksha_lisp_builtins::scope_(const std::vector<yaksha_lisp_value *> &args,
                             yaksha_envmap *env) {
  if (args.empty()) {
    throw parsing_error{"scope takes at least 1 argument", "", 0, 0};
  }
  auto e_args = eval_args(args, env->spawn());
  auto last = e_args[e_args.size() - 1];
  return last;
}
yaksha_lisp_value *
yaksha_lisp_builtins::quote_(const std::vector<yaksha_lisp_value *> &args,
                             yaksha_envmap *env) {
  auto value = env->create_val();
  value->type_ = yaksha_lisp_value_type::LIST;
  value->list_ = args;
  return value;
}
yaksha_lisp_value *
yaksha_lisp_builtins::for_(const std::vector<yaksha_lisp_value *> &args,
                           yaksha_envmap *env) {
  if (args.size() < 3) {
    throw parsing_error{"for takes at least 3 arguments", "", 0, 0};
  }
  auto symbol = args[0];
  if (!(symbol->type_ == yaksha_lisp_value_type::EXPR &&
        symbol->expr_->token_->type_ == yaksha_lisp_token_type::SYMBOL)) {
    throw parsing_error{"for takes a symbol as first argument", "", 0, 0};
  }
  auto list = env->eval(args[1]);
  if (list->type_ != yaksha_lisp_value_type::LIST) {
    throw parsing_error{"for takes a list as second argument", "", 0, 0};
  }
  auto body = std::vector<yaksha_lisp_value *>{args.begin() + 2, args.end()};
  yaksha_lisp_value *last = nullptr;
  for (auto &x : list->list_) {
    env->set(symbol->expr_->token_->token_, x);
    auto e_args = eval_args(body, env);
    last = e_args[e_args.size() - 1];
  }
  if (last == nullptr) { last = env->create_nil(); }
  return last;
}
yaksha_lisp_value *
yaksha_lisp_builtins::range_(const std::vector<yaksha_lisp_value *> &args,
                             yaksha_envmap *env) {
  if (args.size() != 2) {
    throw parsing_error{"range takes 2 arguments", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto start = e_args[0];
  auto end = e_args[1];
  if (start->type_ != yaksha_lisp_value_type::NUMBER ||
      end->type_ != yaksha_lisp_value_type::NUMBER) {
    throw parsing_error{"range takes only integers", "", 0, 0};
  }
  auto start_i = start->num_;
  auto end_i = end->num_;
  auto list = std::vector<yaksha_lisp_value *>{};
  for (auto i = start_i; i < end_i; i++) {
    auto v = env->create_number(i);
    list.emplace_back(v);
  }
  auto r = env->create_val();
  r->list_ = list;
  r->type_ = yaksha_lisp_value_type::LIST;
  return r;
}
yaksha_lisp_value *
yaksha_lisp_builtins::while_(const std::vector<yaksha_lisp_value *> &args,
                             yaksha_envmap *env) {
  if (args.size() < 2) {
    throw parsing_error{"while takes at least 2 arguments", "", 0, 0};
  }
  auto cond = args[0];
  // assign rest to body
  auto body = std::vector<yaksha_lisp_value *>{args.begin() + 1, args.end()};
  while (env->is_truthy(env->eval(cond))) {
    for (auto body_part : body) { env->eval(body_part); }
  }
  return env->create_nil();
}
yaksha_lisp_value *
yaksha_lisp_builtins::eval_(const std::vector<yaksha_lisp_value *> &args,
                            yaksha_envmap *env) {
  if (args.size() != 1) {
    throw parsing_error{"eval takes 1 argument", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto arg = e_args[0];
  if (arg->type_ == yaksha_lisp_value_type::LIST) {
    auto r = env->create_nil();
    for (auto &x : arg->list_) { r = env->eval(x); }
    return r;
  } else if (arg->type_ == yaksha_lisp_value_type::EXPR) {
    return env->eval(arg);
  } else {
    return arg;
  }
}
yaksha_lisp_value *
yaksha_lisp_builtins::list_(const std::vector<yaksha_lisp_value *> &args,
                            yaksha_envmap *env) {
  if (args.empty()) {
    throw parsing_error{"list takes at least 1 argument", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto list = std::vector<yaksha_lisp_value *>{};
  for (auto arg : e_args) { list.emplace_back(arg); }
  auto r = env->create_val();
  r->list_ = list;
  r->type_ = yaksha_lisp_value_type::LIST;
  return r;
}
yaksha_lisp_value *
yaksha_lisp_builtins::head_(const std::vector<yaksha_lisp_value *> &args,
                            yaksha_envmap *env) {
  if (args.size() != 1) {
    throw parsing_error{"head takes 1 argument", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto arg = e_args[0];
  if (arg->type_ != yaksha_lisp_value_type::LIST) {
    throw parsing_error{"head takes a list as argument", "", 0, 0};
  }
  if (arg->list_.empty()) { return env->create_nil(); }
  return arg->list_[0];
}
yaksha_lisp_value *
yaksha_lisp_builtins::tail_(const std::vector<yaksha_lisp_value *> &args,
                            yaksha_envmap *env) {
  if (args.size() != 1) {
    throw parsing_error{"tail takes 1 argument", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto arg = e_args[0];
  if (arg->type_ != yaksha_lisp_value_type::LIST) {
    throw parsing_error{"tail takes a list as argument", "", 0, 0};
  }
  if (arg->list_.empty()) { return env->create_nil(); }
  auto list = std::vector<yaksha_lisp_value *>{arg->list_.begin() + 1,
                                               arg->list_.end()};
  auto r = env->create_val();
  r->list_ = list;
  r->type_ = yaksha_lisp_value_type::LIST;
  return r;
}
yaksha_lisp_value *
yaksha_lisp_builtins::cons_(const std::vector<yaksha_lisp_value *> &args,
                            yaksha_envmap *env) {
  if (args.size() != 2) {
    throw parsing_error{"cons takes 2 arguments", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto arg = e_args[0];
  auto list = e_args[1];
  if (list->type_ != yaksha_lisp_value_type::LIST) {
    throw parsing_error{"cons takes a list as second argument", "", 0, 0};
  }
  auto r = env->create_val();
  r->list_ = list->list_;
  r->list_.insert(r->list_.begin(), arg);
  r->type_ = yaksha_lisp_value_type::LIST;
  return r;
}
yaksha_lisp_value *
yaksha_lisp_builtins::len_(const std::vector<yaksha_lisp_value *> &args,
                           yaksha_envmap *env) {
  if (args.size() != 1) {
    throw parsing_error{"len takes 1 argument", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto arg = e_args[0];
  if (arg->type_ == yaksha_lisp_value_type::LIST) {
    return env->create_number((int64_t) arg->list_.size());
  }
  if (arg->type_ == yaksha_lisp_value_type::STRING) {
    return env->create_number((int64_t) arg->str_.size());
  }
  throw parsing_error{"len takes a list or string as argument", "", 0, 0};
}
yaksha_lisp_value *
yaksha_lisp_builtins::push_(const std::vector<yaksha_lisp_value *> &args,
                            yaksha_envmap *env) {
  if (args.size() != 2) {
    throw parsing_error{"push takes 2 arguments", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto arg = e_args[0];
  auto list = e_args[1];
  if (list->type_ != yaksha_lisp_value_type::LIST) {
    throw parsing_error{"push takes a list as second argument", "", 0, 0};
  }
  list->list_.emplace_back(arg);
  return list;
}
yaksha_lisp_value *
yaksha_lisp_builtins::pop_(const std::vector<yaksha_lisp_value *> &args,
                           yaksha_envmap *env) {
  if (args.size() != 1) {
    throw parsing_error{"pop takes 1 argument", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto list = e_args[0];
  if (list->type_ != yaksha_lisp_value_type::LIST) {
    throw parsing_error{"pop takes a list as argument", "", 0, 0};
  }
  if (list->list_.empty()) {
    throw parsing_error{"pop takes a non-empty list as argument", "", 0, 0};
  }
  auto r = list->list_.back();
  list->list_.pop_back();
  return r;
}
yaksha_lisp_value *
yaksha_lisp_builtins::try_(const std::vector<yaksha_lisp_value *> &args,
                           yaksha_envmap *env) {
  if (args.size() != 1) {
    throw parsing_error{"try takes 1 argument", "", 0, 0};
  }
  auto exp = args[0];
  if (exp->type_ != yaksha_lisp_value_type::EXPR) {
    throw parsing_error{"try takes an s-expr as argument", "", 0, 0};
  }
  try {
    return env->eval(exp->expr_);
  } catch (const parsing_error &e) { return env->create_nil(); }
}
yaksha_lisp_value *
yaksha_lisp_builtins::try_catch_(const std::vector<yaksha_lisp_value *> &args,
                                 yaksha_envmap *env) {
  if (args.size() != 3) {
    throw parsing_error{"try_catch takes 3 arguments", "", 0, 0};
  }
  auto name = args[0];
  auto exp = args[1];
  auto catch_exp = args[2];
  if (!(name->type_ == yaksha_lisp_value_type::EXPR &&
        name->expr_->token_->type_ == yaksha_lisp_token_type::SYMBOL)) {
    throw parsing_error{"try_catch takes a symbol as first argument", "", 0, 0};
  }
  if (exp->type_ != yaksha_lisp_value_type::EXPR) {
    throw parsing_error{"try_catch takes an s-expr as second argument", "", 0,
                        0};
  }
  if (catch_exp->type_ != yaksha_lisp_value_type::EXPR) {
    throw parsing_error{"try_catch takes an s-expr as third argument", "", 0,
                        0};
  }
  try {
    return env->eval(exp->expr_);
  } catch (const parsing_error &e) {
    auto scope = env->spawn();
    scope->set(name->expr_->token_->token_, scope->create_string(e.message_));
    return scope->eval(catch_exp->expr_);
  }
}
yaksha_lisp_value *
yaksha_lisp_builtins::is_list_(const std::vector<yaksha_lisp_value *> &args,
                               yaksha_envmap *env) {
  if (args.size() != 1) {
    throw parsing_error{"is_list takes 1 argument", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto arg = e_args[0];
  return env->create_number(arg->type_ == yaksha_lisp_value_type::LIST);
}
yaksha_lisp_value *
yaksha_lisp_builtins::is_string_(const std::vector<yaksha_lisp_value *> &args,
                                 yaksha_envmap *env) {
  if (args.size() != 1) {
    throw parsing_error{"is_string takes 1 argument", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto arg = e_args[0];
  return env->create_number(arg->type_ == yaksha_lisp_value_type::STRING);
}
yaksha_lisp_value *
yaksha_lisp_builtins::is_int_(const std::vector<yaksha_lisp_value *> &args,
                              yaksha_envmap *env) {
  if (args.size() != 1) {
    throw parsing_error{"is_int takes 1 argument", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto arg = e_args[0];
  return env->create_number(arg->type_ == yaksha_lisp_value_type::NUMBER);
}
yaksha_lisp_value *
yaksha_lisp_builtins::is_truthy_(const std::vector<yaksha_lisp_value *> &args,
                                 yaksha_envmap *env) {
  if (args.size() != 1) {
    throw parsing_error{"is_truthy takes 1 argument", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto arg = e_args[0];
  return env->create_number(yaksha::yaksha_envmap::is_truthy(arg));
}
yaksha_lisp_value *
yaksha_lisp_builtins::is_callable_(const std::vector<yaksha_lisp_value *> &args,
                                   yaksha_envmap *env) {
  if (args.size() != 1) {
    throw parsing_error{"is_callable takes 1 argument", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto arg = e_args[0];
  return env->create_number(arg->type_ == yaksha_lisp_value_type::LAMBDA ||
                            arg->type_ == yaksha_lisp_value_type::BUILTIN);
}
yaksha_lisp_value *
yaksha_lisp_builtins::is_nil_(const std::vector<yaksha_lisp_value *> &args,
                              yaksha_envmap *env) {
  if (args.size() != 1) {
    throw parsing_error{"is_nil takes 1 argument", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto arg = e_args[0];
  return env->create_number(arg->type_ == yaksha_lisp_value_type::LIST &&
                            arg->list_.empty());
}
yaksha_lisp_value *
yaksha_lisp_builtins::filter_(const std::vector<yaksha_lisp_value *> &args,
                              yaksha_envmap *env) {
  if (args.size() != 2) {
    throw parsing_error{"filter takes 2 arguments", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto callable = e_args[0];
  auto list_ = e_args[1];
  if (callable->type_ != yaksha_lisp_value_type::LAMBDA &&
      callable->type_ != yaksha_lisp_value_type::BUILTIN) {
    throw parsing_error{"filter takes a callable as first argument", "", 0, 0};
  }
  if (list_->type_ != yaksha_lisp_value_type::LIST) {
    throw parsing_error{"filter takes a list as second argument", "", 0, 0};
  }
  auto result = env->create_val();
  result->type_ = yaksha_lisp_value_type::LIST;
  for (auto item : list_->list_) {
    auto res = env->eval_call(callable, {item});
    if (yaksha::yaksha_envmap::is_truthy(res)) {
      result->list_.push_back(item);
    }
  }
  return result;
}
yaksha_lisp_value *
yaksha_lisp_builtins::map_(const std::vector<yaksha_lisp_value *> &args,
                           yaksha_envmap *env) {
  if (args.size() != 2) {
    throw parsing_error{"map takes 2 arguments", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto callable = e_args[0];
  auto list_ = e_args[1];
  if (callable->type_ != yaksha_lisp_value_type::LAMBDA &&
      callable->type_ != yaksha_lisp_value_type::BUILTIN) {
    throw parsing_error{"map takes a callable as first argument", "", 0, 0};
  }
  if (list_->type_ != yaksha_lisp_value_type::LIST) {
    throw parsing_error{"map takes a list as second argument", "", 0, 0};
  }
  auto result = env->create_val();
  result->type_ = yaksha_lisp_value_type::LIST;
  for (auto item : list_->list_) {
    auto res = env->eval_call(callable, {item});
    result->list_.push_back(res);
  }
  return result;
}
yaksha_lisp_value *
yaksha_lisp_builtins::reduce_(const std::vector<yaksha_lisp_value *> &args,
                              yaksha_envmap *env) {
  if (args.size() != 2) {
    throw parsing_error{"reduce takes 2 arguments", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto callable = e_args[0];
  auto list_ = e_args[1];
  if (callable->type_ != yaksha_lisp_value_type::LAMBDA &&
      callable->type_ != yaksha_lisp_value_type::BUILTIN) {
    throw parsing_error{"reduce takes a callable as first argument", "", 0, 0};
  }
  if (list_->type_ != yaksha_lisp_value_type::LIST) {
    throw parsing_error{"reduce takes a list as second argument", "", 0, 0};
  }
  if (list_->list_.empty()) { return env->create_nil(); }
  auto item = list_->list_[0];
  yaksha_lisp_value *first = copy_val(env, item);
  for (size_t i = 1; i < list_->list_.size(); i++) {
    first = env->eval_call(callable, {first, list_->list_[i]});
  }
  return first;
}
yaksha_lisp_value *yaksha_lisp_builtins::copy_val(yaksha_envmap *env,
                                                  yaksha_lisp_value *item) {
  auto first = env->create_val();
  first->type_ = item->type_;
  first->num_ = item->num_;
  first->str_ = item->str_;
  first->list_ = item->list_;
  first->expr_ = item->expr_;
  first->builtin_ = item->builtin_;
  first->closure_ = item->closure_;
  return first;
}
yaksha_lisp_value *
yaksha_lisp_builtins::to_string_(const std::vector<yaksha_lisp_value *> &args,
                                 yaksha_envmap *env) {
  if (args.size() != 1) {
    throw parsing_error{"to_string takes 1 argument", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto arg = e_args[0];
  if (arg->type_ == yaksha_lisp_value_type::STRING) { return arg; }
  if (arg->type_ == yaksha_lisp_value_type::NUMBER) {
    auto result = env->create_val();
    result->type_ = yaksha_lisp_value_type::STRING;
    result->str_ = std::to_string(arg->num_);
    return result;
  }
  throw parsing_error{"to_string takes a number or string as argument", "", 0,
                      0};
}
yaksha_lisp_value *
yaksha_lisp_builtins::to_int_(const std::vector<yaksha_lisp_value *> &args,
                              yaksha_envmap *env) {
  if (args.size() != 1) {
    throw parsing_error{"to_int takes 1 argument", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto arg = e_args[0];
  if (arg->type_ == yaksha_lisp_value_type::NUMBER) { return arg; }
  if (arg->type_ == yaksha_lisp_value_type::STRING) {
    auto result = env->create_val();
    result->type_ = yaksha_lisp_value_type::NUMBER;
    result->num_ = std::stoll(arg->str_);
    return result;
  }
  throw parsing_error{"to_int takes a number or string as argument", "", 0, 0};
}
yaksha_lisp_value *
yaksha_lisp_builtins::read_file_(const std::vector<yaksha_lisp_value *> &args,
                                 yaksha_envmap *env) {
  if (args.size() != 1) {
    throw parsing_error{"read_file takes 1 argument", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto arg = e_args[0];
  if (arg->type_ != yaksha_lisp_value_type::STRING) {
    throw parsing_error{"read_file takes a string as argument", "", 0, 0};
  }
  try {
    std::ifstream t(arg->str_);
    std::string str((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());
    auto result = env->create_val();
    result->type_ = yaksha_lisp_value_type::STRING;
    result->str_ = str;
    return result;
  } catch (std::exception &ex) {
    throw parsing_error{"read_file failed", "", 0, 0};
  }
}
yaksha_lisp_value *
yaksha_lisp_builtins::write_file_(const std::vector<yaksha_lisp_value *> &args,
                                  yaksha_envmap *env) {
  if (args.size() != 2) {
    throw parsing_error{"write_file takes 2 arguments", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto filename = e_args[0];
  auto data_str = e_args[1];
  if (filename->type_ != yaksha_lisp_value_type::STRING) {
    throw parsing_error{"write_file takes a string as first argument", "", 0,
                        0};
  }
  if (data_str->type_ != yaksha_lisp_value_type::STRING) {
    throw parsing_error{"write_file takes a string as second argument", "", 0,
                        0};
  }
  try {
    std::ofstream t(filename->str_);
    t << data_str->str_;
    t.close();
    return env->create_val();
  } catch (std::exception &ex) {
    throw parsing_error{"write_file failed", "", 0, 0};
  }
}
yaksha_lisp_value *
yaksha_lisp_builtins::input_(const std::vector<yaksha_lisp_value *> &args,
                             yaksha_envmap *env) {
  if (args.size() != 1) {
    throw parsing_error{"input takes 1 argument", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto arg = e_args[0];
  if (arg->type_ != yaksha_lisp_value_type::STRING) {
    throw parsing_error{"input takes a string as argument", "", 0, 0};
  }
  std::cout << arg->str_;
  std::string input;
  std::getline(std::cin, input);
  auto result = env->create_string(input);
  return result;
}
yaksha_lisp_value *
yaksha_lisp_builtins::random_(const std::vector<yaksha_lisp_value *> &args,
                              yaksha_envmap *env) {
  if (args.size() != 2) {
    throw parsing_error{"random takes 2 arguments", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto arg1 = e_args[0];
  auto arg2 = e_args[1];
  if (arg1->type_ != yaksha_lisp_value_type::NUMBER ||
      arg2->type_ != yaksha_lisp_value_type::NUMBER) {
    throw parsing_error{"random takes 2 numbers as arguments", "", 0, 0};
  }
  auto result = env->create_val();
  result->type_ = yaksha_lisp_value_type::NUMBER;
  result->num_ = std::rand() % (arg2->num_ - arg1->num_) + arg1->num_;
  return result;
}
yaksha_lisp_value *
yaksha_lisp_builtins::time_(const std::vector<yaksha_lisp_value *> &args,
                            yaksha_envmap *env) {
  if (!args.empty()) {
    throw parsing_error{"time takes no arguments", "", 0, 0};
  }
  auto result = env->create_val();
  result->type_ = yaksha_lisp_value_type::NUMBER;
  result->num_ = std::time(nullptr);
  return result;
}
yaksha_lisp_value *
yaksha_lisp_builtins::insert_(const std::vector<yaksha_lisp_value *> &args,
                              yaksha_envmap *env) {
  if (args.size() != 3) {
    throw parsing_error{"insert takes 3 arguments", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto list = e_args[0];
  auto pos = e_args[1];
  auto elem = e_args[2];
  if (list->type_ != yaksha_lisp_value_type::LIST) {
    throw parsing_error{"insert takes a list as first argument", "", 0, 0};
  }
  if (pos->type_ != yaksha_lisp_value_type::NUMBER) {
    throw parsing_error{"insert takes a number as second argument", "", 0, 0};
  }
  if (pos->num_ < 0 || pos->num_ > list->list_.size()) {
    throw parsing_error{"insert position out of range", "", 0, 0};
  }
  list->list_.insert(list->list_.begin() + pos->num_, elem);
  return list;
}
yaksha_lisp_value *
yaksha_lisp_builtins::remove_(const std::vector<yaksha_lisp_value *> &args,
                              yaksha_envmap *env) {
  if (args.size() != 2) {
    throw parsing_error{"remove takes 2 arguments", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto list = e_args[0];
  auto pos = e_args[1];
  if (list->type_ != yaksha_lisp_value_type::LIST) {
    throw parsing_error{"remove takes a list as first argument", "", 0, 0};
  }
  if (pos->type_ != yaksha_lisp_value_type::NUMBER) {
    throw parsing_error{"remove takes a number as second argument", "", 0, 0};
  }
  if (pos->num_ < 0 || pos->num_ >= list->list_.size()) {
    throw parsing_error{"remove position out of range", "", 0, 0};
  }
  list->list_.erase(list->list_.begin() + pos->num_);
  return list;
}
yaksha_lisp_value *
yaksha_lisp_builtins::parse_(const std::vector<yaksha_lisp_value *> &args,
                             yaksha_envmap *env) {
  if (args.size() != 1) {
    throw parsing_error{"parse takes 1 argument", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto arg = e_args[0];
  if (arg->type_ != yaksha_lisp_value_type::STRING) {
    throw parsing_error{"parse takes a string as argument", "", 0, 0};
  }
  auto tokenizer = env->get_memory_manager()->create_tokenizer();
  tokenizer->tokenize("parse", arg->str_,
                      env->get_memory_manager()->get_yk_token_pool());
  if (!tokenizer->errors_.empty()) {
    parsing_error error = tokenizer->errors_.front();
    throw parsing_error{error.message_, "", 0, 0};
  }
  auto parser = env->get_memory_manager()->create_parser(tokenizer);
  parser->parse();
  if (!parser->errors_.empty()) {
    parsing_error error = parser->errors_.front();
    throw parsing_error{error.message_, "", 0, 0};
  }
  if (parser->exprs_.size() == 1) {
    auto result = env->create_val();
    result->type_ = yaksha_lisp_value_type::EXPR;
    result->expr_ = parser->exprs_.front();
    return result;
  }
  auto result = env->create_val();
  result->type_ = yaksha_lisp_value_type::LIST;
  for (auto expr : parser->exprs_) {
    auto val = env->create_val();
    val->type_ = yaksha_lisp_value_type::EXPR;
    val->expr_ = expr;
    result->list_.push_back(val);
  }
  return result;
}
yaksha_lisp_value *
yaksha_lisp_builtins::bitwise_and_(const std::vector<yaksha_lisp_value *> &args,
                                   yaksha_envmap *env) {
  if (args.size() != 2) {
    throw parsing_error{"bitwise_and takes 2 arguments", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto arg1 = e_args[0];
  auto arg2 = e_args[1];
  if (arg1->type_ != yaksha_lisp_value_type::NUMBER ||
      arg2->type_ != yaksha_lisp_value_type::NUMBER) {
    throw parsing_error{"bitwise_and takes 2 numbers as arguments", "", 0, 0};
  }
  auto result = env->create_val();
  result->type_ = yaksha_lisp_value_type::NUMBER;
  result->num_ = arg1->num_ & arg2->num_;
  return result;
}
yaksha_lisp_value *
yaksha_lisp_builtins::bitwise_or_(const std::vector<yaksha_lisp_value *> &args,
                                  yaksha_envmap *env) {
  if (args.size() != 2) {
    throw parsing_error{"bitwise_or takes 2 arguments", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto arg1 = e_args[0];
  auto arg2 = e_args[1];
  if (arg1->type_ != yaksha_lisp_value_type::NUMBER ||
      arg2->type_ != yaksha_lisp_value_type::NUMBER) {
    throw parsing_error{"bitwise_or takes 2 numbers as arguments", "", 0, 0};
  }
  auto result = env->create_val();
  result->type_ = yaksha_lisp_value_type::NUMBER;
  result->num_ = arg1->num_ | arg2->num_;
  return result;
}
yaksha_lisp_value *
yaksha_lisp_builtins::bitwise_xor_(const std::vector<yaksha_lisp_value *> &args,
                                   yaksha_envmap *env) {
  if (args.size() != 2) {
    throw parsing_error{"bitwise_xor takes 2 arguments", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto arg1 = e_args[0];
  auto arg2 = e_args[1];
  if (arg1->type_ != yaksha_lisp_value_type::NUMBER ||
      arg2->type_ != yaksha_lisp_value_type::NUMBER) {
    throw parsing_error{"bitwise_xor takes 2 numbers as arguments", "", 0, 0};
  }
  auto result = env->create_val();
  result->type_ = yaksha_lisp_value_type::NUMBER;
  result->num_ = arg1->num_ ^ arg2->num_;
  return result;
}
yaksha_lisp_value *
yaksha_lisp_builtins::bitwise_not_(const std::vector<yaksha_lisp_value *> &args,
                                   yaksha_envmap *env) {
  if (args.size() != 1) {
    throw parsing_error{"bitwise_not takes 1 argument", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto arg1 = e_args[0];
  if (arg1->type_ != yaksha_lisp_value_type::NUMBER) {
    throw parsing_error{"bitwise_not takes a number as argument", "", 0, 0};
  }
  auto result = env->create_val();
  result->type_ = yaksha_lisp_value_type::NUMBER;
  result->num_ = ~arg1->num_;
  return result;
}
yaksha_lisp_value *yaksha_lisp_builtins::bitwise_left_shift_(
    const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env) {
  if (args.size() != 2) {
    throw parsing_error{"bitwise_left_shift takes 2 arguments", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto arg1 = e_args[0];
  auto arg2 = e_args[1];
  if (arg1->type_ != yaksha_lisp_value_type::NUMBER ||
      arg2->type_ != yaksha_lisp_value_type::NUMBER) {
    throw parsing_error{"bitwise_left_shift takes 2 numbers as arguments", "",
                        0, 0};
  }
  auto result = env->create_val();
  result->type_ = yaksha_lisp_value_type::NUMBER;
  result->num_ = arg1->num_ << arg2->num_;
  return result;
}
yaksha_lisp_value *yaksha_lisp_builtins::bitwise_right_shift_(
    const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env) {
  if (args.size() != 2) {
    throw parsing_error{"bitwise_right_shift takes 2 arguments", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto arg1 = e_args[0];
  auto arg2 = e_args[1];
  if (arg1->type_ != yaksha_lisp_value_type::NUMBER ||
      arg2->type_ != yaksha_lisp_value_type::NUMBER) {
    throw parsing_error{"bitwise_right_shift takes 2 numbers as arguments", "",
                        0, 0};
  }
  auto result = env->create_val();
  result->type_ = yaksha_lisp_value_type::NUMBER;
  result->num_ = arg1->num_ >> arg2->num_;
  return result;
}
yaksha_lisp_value *
yaksha_lisp_builtins::setdef_(const std::vector<yaksha_lisp_value *> &args,
                              yaksha_envmap *env) {
  if (args.size() != 2) {
    throw parsing_error{"= takes 2 arguments", "", 0, 0};
  }
  auto name = args[0];
  if (!(name->type_ == yaksha_lisp_value_type::EXPR &&
        name->expr_->token_->type_ == yaksha_lisp_token_type::SYMBOL)) {
    throw parsing_error{"= takes a symbol as first argument", "", 0, 0};
  }
  auto val = env->eval(args[1]);
  LOG_COMP("trying to define");
  try {
    env->set(name->expr_->token_->token_, val, false);
    LOG_COMP("trying to define success");
    return val;
  } catch (const parsing_error &ignored) {}
  LOG_COMP("trying to set");
  try {
    env->set(name->expr_->token_->token_, val, true);
    LOG_COMP("trying to set success");
    return val;
  } catch (const parsing_error &ignored) {}
  throw parsing_error{"= failed to set or define value", "", 0, 0};
}
yaksha_lisp_value *
yaksha_lisp_builtins::index_(const std::vector<yaksha_lisp_value *> &args,
                             yaksha_envmap *env) {
  if (args.size() != 2) {
    throw parsing_error{"index takes 2 arguments", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto item = e_args[0];
  auto idx = e_args[1];
  if (item->type_ == yaksha_lisp_value_type::STRING &&
      idx->type_ == yaksha_lisp_value_type::NUMBER) {
    auto result = env->create_val();
    result->type_ = yaksha_lisp_value_type::STRING;
    if (idx->num_ < 0 || idx->num_ >= item->str_.size()) {
      throw parsing_error{"index out of bounds", "", 0, 0};
    }
    result->str_ = item->str_.substr(idx->num_, 1);
    return result;
  }
  if (item->type_ == yaksha_lisp_value_type::LIST &&
      idx->type_ == yaksha_lisp_value_type::NUMBER) {
    if (idx->num_ < 0 || idx->num_ >= item->list_.size()) {
      throw parsing_error{"index out of bounds", "", 0, 0};
    }
    return copy_val(env, item->list_[idx->num_]);
  }
  throw parsing_error{"index takes a string/list and a number as arguments", "",
                      0, 0};
}
yaksha_lisp_value *
yaksha_lisp_builtins::map_get_(const std::vector<yaksha_lisp_value *> &args,
                               yaksha_envmap *env) {
  if (args.size() != 2 && args.size() != 3) {
    throw parsing_error{"map_get takes 2 or 3 arguments", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto map_item = e_args[0];
  auto key_item = e_args[1];
  yaksha_lisp_value *default_val = nullptr;
  if (args.size() == 3) { default_val = e_args[2]; }
  yaksha_lisp_value *result = map_get_internal(map_item, key_item, default_val);
  return result;
}
yaksha_lisp_value *
yaksha_lisp_builtins::map_get_internal(yaksha_lisp_value *map_item,
                                       yaksha_lisp_value *key_item,
                                       yaksha_lisp_value *default_val) {
  if (map_item->type_ != yaksha_lisp_value_type::MAP) {
    throw parsing_error{"map_get takes a map as the first argument", "", 0, 0};
  }
  auto result = map_item->closure_->get_map(key_item, default_val);
  if (result == nullptr) {
    throw parsing_error{"map_get key not found", "", 0, 0};
  }
  return result;
}
yaksha_lisp_value *
yaksha_lisp_builtins::map_set_(const std::vector<yaksha_lisp_value *> &args,
                               yaksha_envmap *env) {
  if (args.size() != 3) {
    throw parsing_error{"map_set takes 3 arguments", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto map_item = e_args[0];
  auto key_item = e_args[1];
  auto val_item = e_args[2];
  if (map_item->type_ != yaksha_lisp_value_type::MAP) {
    throw parsing_error{"map_set takes a map as the first argument", "", 0, 0};
  }
  map_item->closure_->set_map(key_item, val_item);
  return env->create_nil();
}
yaksha_lisp_value *
yaksha_lisp_builtins::map_remove_(const std::vector<yaksha_lisp_value *> &args,
                                  yaksha_envmap *env) {
  if (args.size() != 2) {
    throw parsing_error{"map_remove takes 2 arguments", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto map_item = e_args[0];
  auto key_item = e_args[1];
  if (map_item->type_ != yaksha_lisp_value_type::MAP) {
    throw parsing_error{"map_remove takes a map as the first argument", "", 0,
                        0};
  }
  map_item->closure_->remove_map(key_item);
  return env->create_nil();
}
yaksha_lisp_value *
yaksha_lisp_builtins::map_keys_(const std::vector<yaksha_lisp_value *> &args,
                                yaksha_envmap *env) {
  if (args.size() != 1) {
    throw parsing_error{"map_keys takes 1 argument", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto map_item = e_args[0];
  if (map_item->type_ != yaksha_lisp_value_type::MAP) {
    throw parsing_error{"map_keys takes a map as the first argument", "", 0, 0};
  }
  return map_item->closure_->keys_map(env);
}
yaksha_lisp_value *
yaksha_lisp_builtins::map_values_(const std::vector<yaksha_lisp_value *> &args,
                                  yaksha_envmap *env) {
  if (args.size() != 1) {
    throw parsing_error{"map_values takes 1 argument", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto map_item = e_args[0];
  if (map_item->type_ != yaksha_lisp_value_type::MAP) {
    throw parsing_error{"map_values takes a map as the first argument", "", 0,
                        0};
  }
  return map_item->closure_->values_map(env);
}
yaksha_lisp_value *
yaksha_lisp_builtins::map_has_(const std::vector<yaksha_lisp_value *> &args,
                               yaksha_envmap *env) {
  if (args.size() != 2) {
    throw parsing_error{"map_has takes 2 arguments", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto map_item = e_args[0];
  auto key_item = e_args[1];
  if (map_item->type_ != yaksha_lisp_value_type::MAP) {
    throw parsing_error{"map_has takes a map as the first argument", "", 0, 0};
  }
  auto has = map_item->closure_->has_map(key_item);
  return env->create_number(has ? 1 : 0);
}
yaksha_lisp_value *
yaksha_lisp_builtins::this_(const std::vector<yaksha_lisp_value *> &args,
                            yaksha_envmap *env) {
  if (!args.empty()) {
    throw parsing_error{"this takes no arguments", "", 0, 0};
  }
  auto result = env->create_val();
  result->type_ = yaksha_lisp_value_type::MAP;
  result->closure_ = env;
  return result;
}
yaksha_lisp_value *
yaksha_lisp_builtins::parent_(const std::vector<yaksha_lisp_value *> &args,
                              yaksha_envmap *env) {
  if (!args.empty()) {
    throw parsing_error{"parent takes no arguments", "", 0, 0};
  }
  if (env->parent_ == nullptr) { return env->create_nil(); }
  auto result = env->create_val();
  result->type_ = yaksha_lisp_value_type::MAP;
  result->closure_ = env->parent_;
  return result;
}
yaksha_lisp_value *
yaksha_lisp_builtins::repr_(const std::vector<yaksha_lisp_value *> &args,
                            yaksha_envmap *env) {
  if (args.size() != 1) {
    throw parsing_error{"repr takes 1 argument", "", 0, 0};
  }
  std::stringstream ss{};
  auto e_args = eval_args(args, env);
  auto arg = e_args[0];
  ss << arg;
  auto result = env->create_val();
  result->type_ = yaksha_lisp_value_type::STRING;
  result->str_ = ss.str();
  return result;
}
yaksha_lisp_value *
yaksha_lisp_builtins::cond_(const std::vector<yaksha_lisp_value *> &args,
                            yaksha_envmap *env) {
  for (auto arg : args) {
    if (arg->type_ != yaksha_lisp_value_type::EXPR ||
        arg->expr_->list_.size() != 2) {
      throw parsing_error{
          "cond takes a list of s-exprs of 2 elements - (condition expr)", "",
          0, 0};
    }
    auto cond = env->eval(arg->expr_->list_[0]);
    auto expr = arg->expr_->list_[1];
    if (yaksha::yaksha_envmap::is_truthy(cond)) { return env->eval(expr); }
  }
  return env->create_nil();
}
yaksha_lisp_value *
yaksha_lisp_builtins::ghost_(const std::vector<yaksha_lisp_value *> &args,
                             yaksha_envmap *env) {
  if (args.size() != 1) {
    throw parsing_error{"ghost takes 1 argument", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto arg = e_args[0];
  return arg;
}
yaksha_lisp_value *
yaksha_lisp_builtins::metamacro_(const std::vector<yaksha_lisp_value *> &args,
                                 yaksha_envmap *env) {
  // TODO refactor with defun, almost same, duplicate
  if (args.size() < 3) {
    throw parsing_error{"metamacro takes at least 3 arguments", "", 0, 0};
  }
  auto name = args[0];
  auto params = args[1];
  auto body = env->create_val();
  body->type_ = yaksha_lisp_value_type::LIST;
  for (size_t i = 2; i < args.size(); i++) { body->list_.push_back(args[i]); }
  if (!(name->type_ == yaksha_lisp_value_type::EXPR &&
        name->expr_->token_->type_ == yaksha_lisp_token_type::SYMBOL)) {
    throw parsing_error{"metamacro takes a symbol as first argument", "", 0, 0};
  }
  if (!(params->type_ == yaksha_lisp_value_type::EXPR &&
        params->expr_->token_->type_ == yaksha_lisp_token_type::PAREN_OPEN)) {
    throw parsing_error{"metamacro takes a s-expr as second argument", "", 0,
                        0};
  }
  std::unordered_set<std::string> param_names;
  for (auto &p : params->expr_->list_) {
    if (!(p->type_ == yaksha_lisp_expr_type::TERMINAL &&
          p->token_->type_ == yaksha_lisp_token_type::SYMBOL)) {
      throw parsing_error{
          "metamacro takes a s-expr of symbols as second argument", "", 0, 0};
    }
    if (param_names.find(p->token_->token_) != param_names.end()) {
      throw parsing_error{
          "metamacro takes a s-expr of unique symbols as second "
          "argument",
          "", 0, 0};
    }
    param_names.insert(p->token_->token_);
  }
  auto callable = env->create_val();
  callable->type_ = yaksha_lisp_value_type::METAMACRO;
  callable->list_ = std::vector<yaksha_lisp_value *>{params, body};
  callable->str_ = name->expr_->token_->token_;
  callable->closure_ = env;
  env->set(name->expr_->token_->token_, callable);
  return env->create_nil();
}
yaksha_lisp_value *yaksha_lisp_builtins::is_metamacro_(
    const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env) {
  if (args.size() != 1) {
    throw parsing_error{"is_metamacro takes 1 argument", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto arg = e_args[0];
  return env->create_number(
      arg->type_ == yaksha_lisp_value_type::METAMACRO ? 1 : 0);
}
yaksha_lisp_value *
yaksha_lisp_builtins::is_module_(const std::vector<yaksha_lisp_value *> &args,
                                 yaksha_envmap *env) {
  if (args.size() != 1) {
    throw parsing_error{"is_module takes 1 argument", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto arg = e_args[0];
  return env->create_number(arg->type_ == yaksha_lisp_value_type::MODULE ? 1
                                                                         : 0);
}
yaksha_lisp_value *yaksha_lisp_builtins::access_module_(
    const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env) {
  if (args.size() != 2) {
    throw parsing_error{"access_module takes 2 argument", "", 0, 0};
  }
  auto module_ = env->eval(args[0]);
  auto attribute_ = args[1];
  return access_module_internal(env, module_, attribute_);
}
yaksha_lisp_value *yaksha_lisp_builtins::access_module_internal(
    yaksha_envmap *env, const yaksha_lisp_value *module_,
    const yaksha_lisp_value *attribute_) {
  if (module_->type_ != yaksha_lisp_value_type::MODULE) {
    throw parsing_error{"access_module takes a module as first argument", "", 0,
                        0};
  }
  if (!(attribute_->type_ == yaksha_lisp_value_type::EXPR &&
        attribute_->expr_->token_->type_ == yaksha_lisp_token_type::SYMBOL)) {
    throw parsing_error{"access_module takes a symbol as second argument", "",
                        0, 0};
  }
  auto module_env = env->ir_->validate_and_get_environment_root(module_->str_);
  auto name = attribute_->expr_->token_->token_;
  if (!module_env->has_map(name)) {
    throw parsing_error{
        "cannot find symbol " + name + " in module:" + module_->str_, "", 0, 0};
  }
  auto module_value = module_env->get_map(name, nullptr);
  // Do not allow importing a module import?!
  if (module_value == nullptr ||
      module_value->type_ == yaksha_lisp_value_type::MODULE ||
      module_value->type_ == yaksha_lisp_value_type::BUILTIN) {
    throw parsing_error{
        "cannot find symbol " + name + " in module:" + module_->str_, "", 0, 0};
  }
  if (module_value->type_ == yaksha_lisp_value_type::LAMBDA ||
      module_value->type_ == yaksha_lisp_value_type::METAMACRO) {
    module_value->foreign_ = true;
    module_value->foreign_env_ = module_env;
  }
  return module_value;// mutable?
}
yaksha_lisp_value *
yaksha_lisp_builtins::magic_dot_(const std::vector<yaksha_lisp_value *> &args,
                                 yaksha_envmap *env) {
  if (args.size() != 2) {
    throw parsing_error{"magic_dot takes 2 argument", "", 0, 0};
  }
  auto mod_map_ = env->eval(args[0]);
  auto attribute_ = args[1];
  if (mod_map_->type_ == yaksha_lisp_value_type::MODULE) {
    return access_module_internal(env, mod_map_, attribute_);
  } else if (mod_map_->type_ == yaksha_lisp_value_type::MAP) {
    yaksha_lisp_value *map_attribute = nullptr;
    if (attribute_->type_ == yaksha_lisp_value_type::EXPR &&
        attribute_->expr_->token_->type_ == yaksha_lisp_token_type::SYMBOL) {
      map_attribute = env->create_string(attribute_->expr_->token_->token_);
    } else {
      map_attribute = env->eval(attribute_);
    }
    return map_get_internal(mod_map_, map_attribute, nullptr);
  }
  throw parsing_error{"magic_dot takes a module or map as first argument", "",
                      0, 0};
}
yaksha_lisp_value *yaksha_lisp_builtins::system_lock_root_scope_(
    const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env) {
  if (!args.empty()) {
    throw parsing_error{"system_lock_root_scope takes no arguments", "", 0, 0};
  }
  env->lockdown_root();
  return env->create_nil();
}
yaksha_lisp_value *yaksha_lisp_builtins::system_unlock_root_scope_(
    const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env) {
  if (!args.empty()) {
    throw parsing_error{"system_unlock_root_scope takes no arguments", "", 0,
                        0};
  }
  env->unlock_root();
  return env->create_nil();
}
yaksha_lisp_value *yaksha_lisp_builtins::system_enable_gc_(
    const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env) {
  if (!args.empty()) {
    throw parsing_error{"system_enable_gc takes no arguments", "", 0, 0};
  }
  env->gc_enable();
  return env->create_nil();
}
yaksha_lisp_value *yaksha_lisp_builtins::system_disable_gc_(
    const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env) {
  if (!args.empty()) {
    throw parsing_error{"system_disable_gc takes no arguments", "", 0, 0};
  }
  env->gc_disable();
  return env->create_nil();
}
yaksha_lisp_value *yaksha_lisp_builtins::system_enable_print_(
    const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env) {
  if (!args.empty()) {
    throw parsing_error{"system_enable_print takes no arguments", "", 0, 0};
  }
  yaksha_macro_print_allowed = true;
  return env->create_nil();
}
yaksha_lisp_value *yaksha_lisp_builtins::system_disable_print_(
    const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env) {
  if (!args.empty()) {
    throw parsing_error{"system_disable_print takes no arguments", "", 0, 0};
  }
  yaksha_macro_print_allowed = false;
  return env->create_nil();
}
yaksha_lisp_value *
yaksha_lisp_builtins::sorted_(const std::vector<yaksha_lisp_value *> &args,
                              yaksha_envmap *env) {
  if (args.size() != 1) {
    throw parsing_error{"sorted takes 1 argument", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto list_ = e_args[0];
  if (list_->type_ != yaksha_lisp_value_type::LIST) {
    throw parsing_error{"sorted takes a list as first argument", "", 0, 0};
  }
  if (list_->list_.empty()) { return env->create_nil(); }
  if (list_->list_[0]->type_ != yaksha_lisp_value_type::STRING &&
      list_->list_[1]->type_ != yaksha_lisp_value_type::NUMBER) {
    throw parsing_error{
        "sorted - only string lists or number lists are supported", "", 0, 0};
  }
  auto data_type = list_->list_[0]->type_;
  for (auto item : list_->list_) {
    if (item->type_ != data_type) {
      throw parsing_error{"sorted - only string lists or number lists are "
                          "supported, mixed types are not supported",
                          "", 0, 0};
    }
  }
  auto v = copy_val(env, list_);
  if (data_type == yaksha_lisp_value_type::STRING) {
    std::sort(v->list_.begin(), v->list_.end(),
              [](yaksha_lisp_value *const &a, yaksha_lisp_value *const &b) {
                return a->str_ < b->str_;
              });
  } else {
    std::sort(v->list_.begin(), v->list_.end(),
              [](yaksha_lisp_value *const &a, yaksha_lisp_value *const &b) {
                return a->num_ < b->num_;
              });
  }
  return v;
}
yaksha_lisp_value *
yaksha_lisp_builtins::reversed_(const std::vector<yaksha_lisp_value *> &args,
                                yaksha_envmap *env) {
  if (args.size() != 1) {
    throw parsing_error{"sorted takes 1 argument", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  auto list_ = e_args[0];
  if (list_->type_ != yaksha_lisp_value_type::LIST) {
    throw parsing_error{"sorted takes a list as first argument", "", 0, 0};
  }
  if (list_->list_.empty()) { return env->create_nil(); }
  auto v = copy_val(env, list_);
  std::reverse(v->list_.begin(), v->list_.end());
  return v;
}
yaksha_lisp_value *
yaksha_lisp_builtins::os_exec_(const std::vector<yaksha_lisp_value *> &args,
                               yaksha_envmap *env) {
  if (args.empty()) {
    throw parsing_error{"os_exec takes at least 1 argument", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  std::vector<std::string> cmd_args;
  for (auto & e_arg : e_args) {
    if (e_arg->type_ != yaksha_lisp_value_type::STRING) {
      throw parsing_error{"os_exec takes only string arguments", "", 0, 0};
    }
    cmd_args.push_back(e_arg->str_);
  }
  auto result = exec(cmd_args);
  return env->create_number(result);
}
yaksha_lisp_value *
yaksha_lisp_builtins::os_shell_(const std::vector<yaksha_lisp_value *> &args,
                                yaksha_envmap *env) {
  if (args.size() != 1) {
    throw parsing_error{"os_shell takes 1 argument", "", 0, 0};
  }
  auto e_args = eval_args(args, env);
  std::vector<std::string> cmd_args;
#if defined(YAKSHA_OS_WINDOWS)
  cmd_args.emplace_back("cmd");
  cmd_args.emplace_back("/C");
#else
  cmd_args.emplace_back("sh");
  cmd_args.emplace_back("-c");
#endif
  cmd_args.push_back(e_args[0]->str_);
  auto result = exec(cmd_args);
  return env->create_number(result);
}
