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
// ykdt_pool.cpp
#include "ykdt_pool.h"
#include <utility>
using namespace yaksha;
ykdt_pool::ykdt_pool() { pool_.reserve(1000); }
ykdt_pool::~ykdt_pool() {
  for (auto item : pool_) { delete (item); }
  pool_.clear();
}
ykdatatype *ykdt_pool::create(std::string tok) {
  auto dt = new ykdatatype(std::move(tok));
  pool_.emplace_back(dt);
  return dt;
}
ykdatatype *ykdt_pool::create(std::string tok, std::string module) {
  auto dt = new ykdatatype(std::move(tok), std::move(module));
  pool_.emplace_back(dt);
  return dt;
}
ykdatatype *ykdt_pool::create_dimension(token *tok, std::string fpath) {
  auto dt = new ykdatatype(tok);
  dt->dimension_ = std::stoi(tok->token_);
  dt->module_ = std::move(fpath);
  dt->builtin_type_ = ykbuiltin::DIMENSION;
  pool_.emplace_back(dt);
  return dt;
}
ykdatatype *ykdt_pool::create_dimension(int x) {
  auto dt = new ykdatatype(std::move(std::to_string(x)));
  dt->builtin_type_ = ykbuiltin::DIMENSION;
  dt->dimension_ = x;
  dt->module_ = "";
  pool_.emplace_back(dt);
  return dt;
}
