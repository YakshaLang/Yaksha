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
// builtin.h
#ifndef BUILTIN_H
#define BUILTIN_H
#include "compiler/datatype_compiler.h"
#include "compiler/datatype_parser.h"
#include "compiler/entry_struct_func_compiler.h"
#include "compiler/function_datatype_extractor.h"
#include "compiler/slot_matcher.h"
#include "compiler/statement_writer.h"
#include "utilities/ykobject.h"
#include <string>
#include <unordered_map>
#include <vector>
namespace yaksha {
  struct builtin {
    virtual ~builtin() = default;
    virtual bool require_stdlib() = 0;
    virtual ykobject
    verify(const std::vector<ykobject> &args,
           const std::vector<expr *> &arg_expressions,
           datatype_parser *dt_parser, ykdt_pool *dt_pool,
           const std::unordered_map<std::string, import_stmt *> &import_aliases,
           const std::string &filepath, slot_matcher *dt_slot_matcher) = 0;
    virtual std::pair<std::string, ykobject> compile(
        const std::vector<std::pair<std::string, ykobject>> &args,
        const std::vector<expr *> &arg_expressions,
        datatype_compiler *dt_compiler, datatype_parser *dt_parser,
        ykdt_pool *dt_pool,
        const std::unordered_map<std::string, import_stmt *> &import_aliases,
        const std::string &filepath, statement_writer *st_writer,
        function_datatype_extractor *fnc_dt_extractor,
        entry_struct_func_compiler *esc) = 0;
  };
}// namespace yaksha
#endif
