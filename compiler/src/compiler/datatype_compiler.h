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
// datatype_compiler.h
#ifndef DATATYPE_COMPILER_H
#define DATATYPE_COMPILER_H
#include "utilities/ykdatatype.h"
#include "utilities/ykobject.h"
#include <string>
namespace yaksha {
  enum class datatype_location { STRUCT, VARIABLE, PARAMETER, CAST, SIZEOF_ };
  struct datatype_compiler {
    virtual std::string convert_dt(ykdatatype *entry_dt,
                                   datatype_location dt_location,
                                   std::string extra_data_1,
                                   std::string extra_data_2) = 0;
    virtual void
    compile_string_assign(token *t, std::stringstream &code,
                          const std::pair<std::string, ykobject> &rhs,
                          const ykdatatype *rhs_datatype,
                          const ykdatatype *lhs_datatype) = 0;
    [[nodiscard]] virtual std::string
    wrap_in_paren(const std::string &code) const = 0;
    virtual ~datatype_compiler() = default;

private:
  };
}// namespace yaksha
#endif
