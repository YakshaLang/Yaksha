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
// builtins.h
#ifndef BUILTINS_H
#define BUILTINS_H
#include "ast/ast.h"
#include "builtins/builtin.h"
#include "compiler/datatype_compiler.h"
#include "compiler/datatype_parser.h"
#include "compiler/entry_struct_func_compiler.h"
#include "compiler/function_datatype_extractor.h"
#include "compiler/slot_matcher.h"
#include "compiler/statement_writer.h"
#include "utilities/gc_pool.h"
#include "utilities/ykobject.h"
#include <string>
#include <vector>
namespace yaksha {
  /**
   * Handle verifying and checking built in types
   */
  struct builtins : datatype_parser {
    explicit builtins(ykdt_pool *dt_pool, gc_pool<token> *token_pool);
    ~builtins() override;
    /**
     * Is this name a valid builtin
     * @param name name of the builtin
     * @return if this is a valid builtin
     */
    bool has_builtin(const std::string &name);
    /**
     * Type check call to builtin
     * @param name name of the function
     * @param args argument ykobjects
     * @param arg expressions to verify
     * @param import_aliases import aliases in current file
     * @return return type, if this is a runtime error something is wrong
     */
    ykobject
    verify(const std::string &name, const std::vector<ykobject> &args,
           const std::vector<expr *> &arg_expressions,
           const std::unordered_map<std::string, import_stmt *> &import_aliases,
           const std::string &filepath, slot_matcher *dt_slot_matcher);
    /**
     * Compile a builtin function call.
     * This assumes verify and has builtin is called.
     * @param name name of the function
     * @param args compiled arguments to pass to function
     * @param arg expressions
     * @param dt_compiler data type compiler parameter
     * @param import_aliases import aliases in current file
     * @return compiled code + return type
     */
    std::pair<std::string, ykobject> compile(
        const std::string &name,
        const std::vector<std::pair<std::string, ykobject>> &args,
        const std::vector<expr *> &arg_expressions,
        datatype_compiler *dt_compiler,
        const std::unordered_map<std::string, import_stmt *> &import_aliases,
        const std::string &filepath, statement_writer *st_writer,
        function_datatype_extractor *fnc_dt_extractor,
        entry_struct_func_compiler *esc);
    /**
     * Data type parser converts given data type string to a ykdatatype*
     * @param data_type_str string containing data type -> Array[str] for example
     * @param import_aliases what does c means in c.CInt
     * @param filepath filepath to current file this builtin call located in
     * @return nullptr if failed, else ykdatatype*
     */
    ykdatatype *
    parse(std::string data_type_str,
          const std::unordered_map<std::string, import_stmt *> &import_aliases,
          const std::string &filepath) override;

private:
    ykdt_pool *dt_pool_;
    std::unordered_map<std::string, builtin *> builtins_;
    gc_pool<token> *token_pool_;
  };
}// namespace yaksha
#endif
