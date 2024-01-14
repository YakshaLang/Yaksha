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
// entry_struct_func_compiler.cpp
#include "entry_struct_func_compiler.h"
#include <iomanip>
#include <iostream>
using namespace yaksha;
entry_struct_func_compiler::entry_struct_func_compiler(ykdt_pool *pool)
    : pool_(pool), counter_(0), autogen_structs_list_(), autogen_structs_(),
      autogen_func_typedefs_(), autogen_func_typedef_list_(),
      counter_functions_(0), code_(), code_fnc_(), counter_tuples_(0),
      autogen_tuple_list_(), autogen_tuples_(), code_tuples_(),
      counter_bin_data_(0), autogen_bin_data_(), bin_data_() {}
std::string entry_struct_func_compiler::compile(ykdatatype *entry_dt,
                                                datatype_compiler *dtc) {
  std::string repr = entry_dt->as_string();
  if (autogen_structs_.find(repr) != autogen_structs_.end()) {
    return "struct ykentry" + std::to_string(autogen_structs_[repr]);
  }
  entry_data d{};
  d.incremented_id_ = counter_++;
  if (entry_dt->is_sm_entry()) {
    d.key_dt_ = pool_->create("str");
    d.val_dt_ = entry_dt->args_[0];
  } else if (entry_dt->is_m_entry()) {
    d.key_dt_ = entry_dt->args_[0];
    d.val_dt_ = entry_dt->args_[1];
  } else {
    // Must not happen
    return "<><>";
  }
  std::stringstream code{};
  code << "struct ykentry" << d.incremented_id_ << " { "
       << dtc->convert_dt(d.key_dt_, datatype_location::STRUCT, "", "")
       << " key; "
       << dtc->convert_dt(d.val_dt_, datatype_location::STRUCT, "", "")
       << " value; };\n";
  code_ << code.str();
  autogen_structs_list_.emplace_back(d);
  autogen_structs_[repr] = d.incremented_id_;
  return "struct ykentry" + std::to_string(d.incremented_id_);
}
void entry_struct_func_compiler::compile_forward_declarations(
    std::stringstream &target) {
  for (auto &e : autogen_structs_list_) {
    target << "struct ykentry" << e.incremented_id_ << ";\n";
  }
  for (auto &e : autogen_tuple_list_) {
    target << "struct yktuple" << e.incremented_id_ << ";\n";
  }
}
void entry_struct_func_compiler::compile_structures(std::stringstream &target) {
  target << code_.str();
  target << code_tuples_.str();
}
bool entry_struct_func_compiler::has_structures() {
  return !autogen_structs_list_.empty() || !autogen_tuple_list_.empty();
}
std::string
entry_struct_func_compiler::compile_function_dt(ykdatatype *function_dt,
                                                datatype_compiler *dtc) {
  std::string fdt_str = function_dt->as_string();
  if (autogen_func_typedefs_.find(fdt_str) != autogen_func_typedefs_.end()) {
    return "ykfncptr" + std::to_string(autogen_func_typedefs_[fdt_str]);
  }
  // Check assumption that must not happen
  if (!function_dt->is_function() || function_dt->args_.size() != 2 ||
      !function_dt->args_[0]->is_function_input() ||
      !function_dt->args_[1]->is_function_output()) {
    // Must not happen
    return "<><>";
  }
  // -- convert
  // typedef F_OUT *(ykfncptr##num)(F_IN...)
  std::stringstream code{};
  ykdatatype *input = function_dt->args_[0];
  ykdatatype *output = function_dt->args_[1];
  code << "typedef ";
  if (output->args_.empty()) {
    code << "void ";
  } else if (output->args_.size() == 1) {
    code << dtc->convert_dt(output->args_[0], datatype_location::STRUCT, "", "")
         << " ";
  } else {
    // Must not happen
    code << "<><>";
  }
  unsigned int current_num = counter_functions_++;
  code << "(*ykfncptr" << current_num << ")(";
  if (input->args_.empty()) {
    code << "void";
  } else {
    bool first = true;
    for (auto dt : input->args_) {
      if (first) {
        first = false;
      } else {
        code << ", ";
      }
      code << dtc->convert_dt(dt, datatype_location::STRUCT, "", "");
    }
  }
  code << ");\n";
  // write the finalized code here
  code_fnc_ << code.str();
  func_data d{input, output, current_num};
  autogen_func_typedef_list_.emplace_back(d);
  autogen_func_typedefs_[fdt_str] = current_num;
  return "ykfncptr" + std::to_string(current_num);
}
void entry_struct_func_compiler::compile_function_defs(
    std::stringstream &target) {
  target << code_fnc_.str();
}
bool entry_struct_func_compiler::has_functions() {
  return !autogen_func_typedef_list_.empty();
}
std::string entry_struct_func_compiler::compile_tuple(ykdatatype *tuple_dt,
                                                      datatype_compiler *dtc) {
  std::string repr = tuple_dt->as_string();
  if (autogen_tuples_.find(repr) != autogen_tuples_.end()) {
    return "struct yktuple" + std::to_string(autogen_tuples_[repr]);
  }
  tuple_data d{};
  d.incremented_id_ = counter_tuples_++;
  d.tuple_dt_ = tuple_dt;
  std::stringstream code{};
  code << "struct yktuple" << d.incremented_id_ << " {";
  size_t i = 1;
  for (ykdatatype *dt_arg : d.tuple_dt_->args_) {
    code << " " << dtc->convert_dt(dt_arg, datatype_location::STRUCT, "", "")
         << " e" << i << ";";
    i++;
  }
  code << " };\n";
  code_ << code.str();
  autogen_tuple_list_.emplace_back(d);
  autogen_tuples_[repr] = d.incremented_id_;
  return "struct yktuple" + std::to_string(d.incremented_id_);
}
bool entry_struct_func_compiler::has_bin_data() {
  return !autogen_bin_data_.empty();
}
template<typename T>
std::string int_to_hex(T i) {
  std::stringstream stream;
  stream << std::setfill('0') << std::setw(2) << std::hex << (unsigned long) i;
  return stream.str();
}
std::string
entry_struct_func_compiler::compile_binary_data(const std::string &data) {
  if (autogen_bin_data_.find(data) != autogen_bin_data_.end()) {
    return "ykbindata" + std::to_string(autogen_bin_data_[data]);
  }
  unsigned int current = counter_bin_data_++;
  autogen_bin_data_.insert({data, current});
  bin_data_ << "uint8_t const ykbindata" << current << "[] = {";
  unsigned long int x = 0;
  for (const unsigned char current_char : data) {
    if (x == 0) {
      bin_data_ << "\n";
    } else if (x % 4 == 0) {
      bin_data_ << ",\n";
    } else {
      bin_data_ << ", ";
    }
    x++;
    bin_data_ << "UINT8_C(0x" << int_to_hex(current_char) << ")";
  }
  bin_data_ << "\n};\n";
  return "ykbindata" + std::to_string(current);
}
void entry_struct_func_compiler::compile_binary_data_to(
    std::stringstream &target) {
  target << bin_data_.str();
}
entry_struct_func_compiler::~entry_struct_func_compiler() = default;
