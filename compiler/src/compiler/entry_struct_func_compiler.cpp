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
// entry_struct_func_compiler.cpp
#include "entry_struct_func_compiler.h"
#include <iomanip>
#include <iostream>
const std::vector<std::pair<std::string, std::string>> REPLACEMENTS = {
    {"function", "fn"},
    {"m_entry", "pair"},
    {"_s_pair_", "_pair_str_"},
    {"fixed_arr", "arr"}};
using namespace yaksha;
entry_struct_func_compiler::entry_struct_func_compiler(ykdt_pool *pool)
    : pool_(pool), counter_(0), autogen_structs_list_(), autogen_structs_(),
      autogen_func_typedefs_(), autogen_func_typedef_list_(),
      counter_functions_(0), code_(), code_fnc_(), counter_tuples_(0),
      autogen_tuple_list_(), autogen_tuples_(), code_tuples_(),
      counter_bin_data_(0), autogen_bin_data_(), bin_data_(), counter_fxa_(0),
      forward_decls_(), name_improvements_() {}
std::string entry_struct_func_compiler::compile(ykdatatype *entry_dt,
                                                datatype_compiler *dtc) {
  std::string repr = entry_dt->as_string();
  std::string simple_repr = entry_dt->as_string_simplified();
  if (autogen_structs_.find(repr) != autogen_structs_.end()) {
    return "struct " +
           improve_name(repr, simple_repr,
                        "ykentry" + std::to_string(autogen_structs_[repr]));
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
  std::string name = improve_name(
      repr, simple_repr, "ykentry" + std::to_string(d.incremented_id_));
  code << "struct " << name << " { "
       << dtc->convert_dt(d.key_dt_, datatype_location::STRUCT, "", "")
       << " key; "
       << dtc->convert_dt(d.val_dt_, datatype_location::STRUCT, "", "")
       << " value; };\n";
  code_ << code.str();
  autogen_structs_list_.emplace_back(d);
  autogen_structs_[repr] = d.incremented_id_;
  forward_decls_ << "struct " << name << ";\n";
  return "struct " + improve_name(repr, simple_repr, name);
}
void entry_struct_func_compiler::compile_forward_declarations(
    std::stringstream &target) {
  target << forward_decls_.str();
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
  std::string simple_fdt_str = function_dt->as_string_simplified();
  if (autogen_func_typedefs_.find(fdt_str) != autogen_func_typedefs_.end()) {
    return improve_name(fdt_str, simple_fdt_str,
                        "ykfncptr" +
                            std::to_string(autogen_func_typedefs_[fdt_str]));
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
  std::string name = improve_name(fdt_str, simple_fdt_str,
                                  "ykfncptr" + std::to_string(current_num));
  code << "(*" << name << ")(";
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
  return name;
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
  std::string simple_repr = tuple_dt->as_string_simplified();
  if (autogen_tuples_.find(repr) != autogen_tuples_.end()) {
    std::string name = improve_name(
        repr, simple_repr, "yktuple" + std::to_string(autogen_tuples_[repr]));
    return "struct " + name;
  }
  tuple_data d{};
  d.incremented_id_ = counter_tuples_++;
  d.tuple_dt_ = tuple_dt;
  std::stringstream code{};
  std::string name = improve_name(
      repr, simple_repr, "yktuple" + std::to_string(d.incremented_id_));
  code << "struct " << name << " {";
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
  forward_decls_ << "struct " << name << ";\n";
  return "struct " + name;
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
std::string
entry_struct_func_compiler::compile_fixed_array(ykdatatype *fixed_array_dt,
                                                datatype_compiler *dtc) {
  std::string fxa_str = fixed_array_dt->as_string();
  std::string fxa_str_simple = fixed_array_dt->as_string_simplified();
  if (autogen_fxa_.find(fxa_str) != autogen_fxa_.end()) {
    return improve_name(fxa_str, fxa_str_simple,
                        "ykfxa" + std::to_string(autogen_fxa_[fxa_str]));
  }
  // Check assumption that must not happen
  if (!fixed_array_dt->is_fixed_size_array() ||
      fixed_array_dt->args_.size() != 2 ||
      fixed_array_dt->args_[0]->is_sm_entry() ||
      fixed_array_dt->args_[1]->is_m_entry()) {
    // Must not happen
    return "<><>";
  }
  // -- convert
  // typedef ARG0 ykfxa##num[ARG1];
  std::stringstream code{};
  ykdatatype *target_datatype = fixed_array_dt->args_[0];
  ykdatatype *size_specifier = fixed_array_dt->args_[1];
  code << "typedef ";
  code << dtc->convert_dt(target_datatype, datatype_location::STRUCT, "", "")
       << " ";
  unsigned int current_num = counter_fxa_++;
  std::string name = improve_name(fxa_str, fxa_str_simple,
                                  "ykfxa" + std::to_string(current_num));
  code << name << "[";
  code << size_specifier->token_->token_;
  code << "];\n";
  // write the finalized code here
  code_fxa_ << code.str();
  tuple_data d{fixed_array_dt, current_num};
  autogen_fxa_list_.emplace_back(d);
  autogen_fxa_[fxa_str] = current_num;
  return name;
}
void entry_struct_func_compiler::compiled_fixed_array_to(
    std::stringstream &target) {
  target << code_fxa_.str();
}
bool entry_struct_func_compiler::has_fixed_arrays() {
  return !autogen_fxa_.empty();
}
std::string sanitize_name(const std::string &input) {
  auto is_valid_char = [](char c) { return std::isalnum(c) || c == '_'; };
  std::string result;
  for (size_t i = 0; i < input.length(); ++i) {
    char c = input[i];
    if (is_valid_char(c)) {
      if (std::isupper(c)) {
        result += "_";
        result += static_cast<char>(std::tolower(c));
      } else {
        result += c;
      }
    } else {
      result += '_';
    }
  }
  // Remove double underscores
  std::size_t dunder = result.find("__");
  while (dunder != std::string::npos) {
    result.erase(dunder, 1);
    dunder = result.find("__");
  }
  // Remove leading and trailing underscores
  result.erase(result.begin(),
               std::find_if(result.begin(), result.end(),
                            [](unsigned char ch) { return ch != '_'; }));
  result.erase(std::find_if(result.rbegin(), result.rend(),
                            [](unsigned char ch) { return ch != '_'; })
                   .base(),
               result.end());
  result = "yt_" + result;
  // Replace
  for (const auto &replacement : REPLACEMENTS) {
    size_t pos;
    while ((pos = result.find(replacement.first)) != std::string::npos) {
      result.replace(pos, replacement.first.length(), replacement.second);
    }
  }
  return result;
}
std::string entry_struct_func_compiler::improve_name(
    const std::string &yaksha_datatype_string, const std::string &simple_name,
    const std::string &numbered_name) {
  if (name_improvements_.find(yaksha_datatype_string) !=
      name_improvements_.end()) {
    return name_improvements_[yaksha_datatype_string];
  }
  std::string improved = sanitize_name(simple_name);
  // too large use numbered name
  if (improved.size() > 60 || improved.empty()) { improved = numbered_name; }
  // conflict, so use numbered name
  if (reverse_name_improvements_.find(improved) !=
      reverse_name_improvements_.end()) {
    improved = numbered_name;
  }
  name_improvements_[yaksha_datatype_string] = improved;
  reverse_name_improvements_[improved] = yaksha_datatype_string;
  return improved;
}
entry_struct_func_compiler::~entry_struct_func_compiler() = default;
