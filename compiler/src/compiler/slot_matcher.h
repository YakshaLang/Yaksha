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
// slot_matcher.h
#ifndef SLOT_MATCHER_H
#define SLOT_MATCHER_H
#include "compiler/function_datatype_extractor.h"
#include "utilities/ykobject.h"
namespace yaksha {
  struct type_match_result {
    std::string error_{};
    bool matched_{false};
    bool auto_casted_{false};
  };
  /**
   * Facade for typechecking and auto-casting needs
   */
  struct slot_matcher : function_datatype_extractor {
    ~slot_matcher() override = default;
    virtual type_match_result
    slot_match_with_result(ykdatatype *datatype,
                           const ykobject &provided_arg) = 0;
    virtual type_match_result rvalue_match(const ykobject &left_side,
                                           const ykobject &right_side) = 0;
    /**
     * Match given two data types, taking auto-casting into account
     * @param required_datatype datatype that we require (LHS)
     * @param provided_datatype datatype provided by the user (RHS)
     * @param primitive_or_obj true if provided data is a primitive/object, false otherwise
     * @return type_match_result struct
     */
    virtual type_match_result type_match(ykdatatype *required_datatype,
                                         ykdatatype *provided_datatype,
                                         bool primitive_or_obj) = 0;
    virtual bool is_identical_type(ykdatatype *required_datatype,
                                   ykdatatype *provided_datatype) = 0;
    virtual bool is_not_identical_type(ykdatatype *required_datatype,
                                       ykdatatype *provided_datatype) = 0;
  };
}// namespace yaksha
#endif
