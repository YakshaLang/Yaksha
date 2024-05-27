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
// entry_struct_func_compiler.h
#ifndef ENTRY_STRUCT_COMPILER_H
#define ENTRY_STRUCT_COMPILER_H
#include "datatype_compiler.h"
#include "utilities/ykdt_pool.h"
#include <unordered_map>
namespace yaksha {
  enum class structure_type {
    PAIR,
    TUPLE,
    FUNCTION_TYPEDEF,
    FIXED_ARRAY,
    STRUCT,
    CLASS
  };
  struct structure_definition {
    /** The datatype of the structure */
    [[maybe_unused]] yk_datatype *dt_{nullptr};
    [[maybe_unused]] yk_datatype *a_{nullptr};
    [[maybe_unused]] yk_datatype *b_{nullptr};
    /** If this is a structure (struct/class), this will be set */
    [[maybe_unused]] class_stmt *class_stmt_or_null_{nullptr};
    /** Prefixed name or nice name for the structure: yt_arr_1*/
    [[maybe_unused]] std::string prefixed_name_{};
    /** Prefixed full name: struct yt_pair_1 **/
    [[maybe_unused]] std::string prefixed_full_name_{};
    /**
     * Definition of the structure:
     *
     * struct yt_pair_1 { key: yt_int_1; value: yt_int_1; }
     */
    [[maybe_unused]] std::string code_{};
    /** What kind of type is this? */
    [[maybe_unused]] structure_type meta_type_;
    /** Increment ID **/
    [[maybe_unused]] int id_;
    /** Topological sorting **/
    [[maybe_unused]] bool temporary_mark_{false};
    [[maybe_unused]] bool permanent_mark_{false};
  };
  struct entry_struct_func_compiler {
    explicit entry_struct_func_compiler(yk_datatype_pool *pool);
    std::string compile(yk_datatype *entry_dt, datatype_compiler *dtc);
    std::string compile_tuple(yk_datatype *tuple_dt, datatype_compiler *dtc);
    std::string compile_function_dt(yk_datatype *function_dt,
                                    datatype_compiler *dtc);
    std::string compile_binary_data(const std::string &data);
    std::string compile_fixed_array(yk_datatype *fixed_array_dt,
                                    datatype_compiler *dtc);
    void register_structure(const std::string &prefixed_name,
                            yk_datatype *class_dt, class_stmt *class_statement,
                            datatype_compiler *dtc,
                            const std::string &member_prefix);
    void compile_binary_data_to(std::stringstream &target);
    bool has_bin_data();
    void compile_structures(std::stringstream &target);
    ~entry_struct_func_compiler();
    std::vector<parsing_error> errors_;

private:
    // Nice names for structures and such
    std::string improve_name(const std::string &yaksha_datatype_string,
                             const std::string &simple_name,
                             const std::string &numbered_name);
    std::unordered_map<std::string /* fully qualified data type */,
                       std::string /* Nice name */>
        name_improvements_;
    std::unordered_map<std::string, std::string> reverse_name_improvements_;
    // ------------------------------------------------
    yk_datatype_pool *pool_;
    int counter_;
    std::unordered_map<std::string /* fully qualified data type */,
                       structure_definition *>
        structures_;
    std::vector<structure_definition *> structure_pool_;
    // Autogenerated Binary Data
    unsigned int counter_bin_data_;
    std::unordered_map<std::string, unsigned int> autogen_bin_data_;
    std::stringstream bin_data_;
    bool visit(structure_definition *n,
               std::vector<structure_definition *> &sorted);
    bool visit(yk_datatype *data, std::vector<structure_definition *> &sorted);
  };
}// namespace yaksha
#endif
