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
// ykobject.cpp
#include "utilities/ykobject.h"
#include <sstream>
#include <utility>
using namespace yaksha;
ykobject::ykobject(ykdt_pool *pool)
    : object_type_(object_type::PRIMITIVE_OR_OBJ) {
  datatype_ = pool->create("None");
}
ykobject::ykobject(int i, ykdt_pool *pool)
    : object_type_(object_type::PRIMITIVE_OR_OBJ), integer_val_{i} {
  datatype_ = pool->create("i32");
}
ykobject::ykobject(std::string str, ykdt_pool *pool)
    : string_val_{std::move(str)}, object_type_(object_type::PRIMITIVE_OR_OBJ) {
  datatype_ = pool->create(":s:");
}
ykobject::ykobject(double dbl, ykdt_pool *pool)
    : double_val_{dbl}, object_type_{object_type::PRIMITIVE_OR_OBJ} {
  datatype_ = pool->create("f64");
}
ykobject::ykobject(float float_val, ykdt_pool *pool)
    : double_val_{float_val}, object_type_{object_type::PRIMITIVE_OR_OBJ} {
  datatype_ = pool->create("f32");
}
ykobject::ykobject(bool i, ykdt_pool *pool)
    : object_type_(object_type::PRIMITIVE_OR_OBJ), bool_val_(i) {
  datatype_ = pool->create("bool");
}
bool ykobject::is_primitive_or_obj() const {
  return object_type_ == object_type::PRIMITIVE_OR_OBJ;
}
bool ykobject::is_a_function() const {
  return object_type_ == object_type::FUNCTION ||
         object_type_ == object_type::MODULE_FUNCTION;
}
ykobject::ykobject(ykdatatype *dt) {
  datatype_ = dt;
  object_type_ = object_type::PRIMITIVE_OR_OBJ;
}
ykobject::ykobject() : object_type_(object_type::UNKNOWN_OBJECT) {}
