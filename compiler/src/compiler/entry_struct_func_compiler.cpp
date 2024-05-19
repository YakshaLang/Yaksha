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
#include "compiler/compiler_utils.h"
#include <iomanip>
#include <iostream>
const std::vector<std::pair<std::string, std::string>> REPLACEMENTS = {
    {"function", "fn"},
    {"m_entry", "pair"},
    {"_s_pair_", "_pair_str_"},
    {"fixed_arr", "arr"}};
using namespace yaksha;
entry_struct_func_compiler::entry_struct_func_compiler(ykdt_pool *pool)
    : pool_(pool), counter_(0), counter_bin_data_(0), autogen_bin_data_(),
      bin_data_(), name_improvements_(), errors_(), structure_pool_(),
      structures_(), reverse_name_improvements_() {}
std::string entry_struct_func_compiler::compile(ykdatatype *entry_dt,
                                                datatype_compiler *dtc) {
  std::string repr = entry_dt->as_string();
  std::string simple_repr = entry_dt->as_string_simplified();
  if (structures_.find(repr) != structures_.end()) {
    return structures_[repr]->prefixed_full_name_;
  }
  auto d = new structure_definition{};
  d->id_ = counter_++;
  d->dt_ = entry_dt;
  if (entry_dt->is_m_entry()) {
    d->a_ = entry_dt->args_[0];
    d->b_ = entry_dt->args_[1];
  } else if (entry_dt->is_sm_entry()) {
    d->a_ = pool_->create("str");
    d->b_ = entry_dt->args_[0];
  } else {
    errors_.emplace_back(
        "Invalid entry datatype: " + entry_dt->as_string_simplified(), nullptr);
    return "<><>";
  }
  std::stringstream code{};
  std::string name =
      improve_name(repr, simple_repr, "ykentry" + std::to_string(d->id_));
  code << "struct " << name << " { "
       << dtc->convert_dt(d->a_, datatype_location::STRUCT, "", "") << " key; "
       << dtc->convert_dt(d->b_, datatype_location::STRUCT, "", "")
       << " value; };\n";
  d->prefixed_name_ = name;
  d->prefixed_full_name_ = "struct " + name;
  d->code_ = code.str();
  d->meta_type_ = structure_type::PAIR;
  structures_[repr] = d;
  structure_pool_.push_back(d);
  return d->prefixed_full_name_;
}
void entry_struct_func_compiler::compile_structures(std::stringstream &target) {
  // Alphabetically sort structures first
  std::vector<structure_definition *> alpha_sorted_types{};
  std::vector<structure_definition *> alpha_sorted_classes{};
  std::vector<structure_definition *> sorted{};
  for (auto &it : structures_) {
    if (it.second->meta_type_ == structure_type::CLASS) {
      alpha_sorted_classes.push_back(it.second);
      it.second->permanent_mark_ = true; /* Consider sorted */
    } else {
      alpha_sorted_types.push_back(it.second);
    }
    if (it.second->meta_type_ == structure_type::CLASS ||
        it.second->meta_type_ == structure_type::STRUCT) {
      sorted.push_back(it.second);
    }
  }
  std::sort(alpha_sorted_types.begin(), alpha_sorted_types.end(),
            [](structure_definition *a, structure_definition *b) {
              return a->prefixed_name_ < b->prefixed_name_;
            });
  std::sort(alpha_sorted_classes.begin(), alpha_sorted_classes.end(),
            [](structure_definition *a, structure_definition *b) {
              return a->prefixed_name_ < b->prefixed_name_;
            });
  std::sort(sorted.begin(), sorted.end(),
            [](structure_definition *a, structure_definition *b) {
              return a->prefixed_name_ < b->prefixed_name_;
            });
  // Topological sort
  std::vector<structure_definition *> topo_sorted_types{};
  for (structure_definition *it : alpha_sorted_types) {
    if (!it->permanent_mark_) {
      bool cycle = this->visit(it, topo_sorted_types);
      if (cycle) {
        errors_.emplace_back("Cycle detected in structure: " +
                                 it->dt_->as_string_simplified(),
                             nullptr);
        return;
      }
    }
  }
  // Forward declarations of classes
  for (auto *it : sorted) { target << it->prefixed_full_name_ << ";\n"; }
  // Topologically sorted structures
  for (auto *it : topo_sorted_types) { target << it->code_; }
  // Classes
  for (auto *it : alpha_sorted_classes) { target << it->code_; }
}
#define CONSIDER_CYCLE(x)                                                      \
  if (x) { return true; }
bool entry_struct_func_compiler::visit(
    ykdatatype *data, std::vector<structure_definition *> &sorted) {
  if (data == nullptr) { return false; }
  // These are builtins, no need to visit these
  if (data->is_primitive() || data->is_any_ptr() ||
      data->is_any_ptr_to_const()) {
    return false;
  }
  if (!data->args_.empty()) {
    for (auto dt : data->args_) { CONSIDER_CYCLE(visit(dt, sorted)); }
  }
  auto repr = data->as_string();
  // Cannot find structure, must be a builtin!
  if (structures_.find(repr) == structures_.end()) { return false; }
  // Found structure, visit it
  auto definition = structures_[repr];
  return visit(definition, sorted);
}
bool entry_struct_func_compiler::visit(
    structure_definition *n, std::vector<structure_definition *> &sorted) {
  if (n == nullptr) { return false; }
  if (n->permanent_mark_) { return false; }
  if (n->temporary_mark_) { return true; }
  n->temporary_mark_ = true;
  if (n->meta_type_ == structure_type::PAIR ||
      n->meta_type_ == structure_type::FUNCTION_TYPEDEF) {
    CONSIDER_CYCLE(visit(n->a_, sorted));
    CONSIDER_CYCLE(visit(n->b_, sorted));
  } else if (n->meta_type_ == structure_type::TUPLE) {
    for (auto dt : n->dt_->args_) { CONSIDER_CYCLE(visit(dt, sorted)); }
  } else if (n->meta_type_ == structure_type::FIXED_ARRAY) {
    CONSIDER_CYCLE(visit(n->a_, sorted));
  } else if (n->meta_type_ == structure_type::STRUCT) {
    for (auto &member : n->class_stmt_or_null_->members_) {
      CONSIDER_CYCLE(visit(member.data_type_, sorted));
    }
  } else {
    return false;
  }
  n->temporary_mark_ = false;
  n->permanent_mark_ = true;
  sorted.push_back(n);
  return false;
}
std::string
entry_struct_func_compiler::compile_function_dt(ykdatatype *function_dt,
                                                datatype_compiler *dtc) {
  std::string repr = function_dt->as_string();
  std::string simple_repr = function_dt->as_string_simplified();
  if (structures_.find(repr) != structures_.end()) {
    return structures_[repr]->prefixed_full_name_;
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
  auto d = new structure_definition{};
  d->id_ = counter_++;
  d->dt_ = function_dt;
  std::stringstream code{};
  d->a_ = function_dt->args_[0];
  d->b_ = function_dt->args_[1];
  code << "typedef ";
  if (d->b_->args_.empty()) {
    code << "void ";
  } else if (d->b_->args_.size() == 1) {
    code << dtc->convert_dt(d->b_->args_[0], datatype_location::STRUCT, "", "")
         << " ";
  } else {
    errors_.emplace_back("Invalid function output datatype: " +
                             d->b_->as_string_simplified(),
                         nullptr);
    code << "<><>";
  }
  std::string name =
      improve_name(repr, simple_repr, "ykfncptr" + std::to_string(d->id_));
  code << "(*" << name << ")(";
  if (d->a_->args_.empty()) {
    code << "void";
  } else {
    bool first = true;
    for (auto dt : d->a_->args_) {
      if (first) {
        first = false;
      } else {
        code << ", ";
      }
      code << dtc->convert_dt(dt, datatype_location::STRUCT, "", "");
    }
  }
  code << ");\n";
  d->code_ = code.str();
  d->meta_type_ = structure_type::FUNCTION_TYPEDEF;
  d->prefixed_name_ = name;
  d->prefixed_full_name_ = name;
  structures_[repr] = d;
  structure_pool_.push_back(d);
  return name;
}
std::string entry_struct_func_compiler::compile_tuple(ykdatatype *tuple_dt,
                                                      datatype_compiler *dtc) {
  std::string repr = tuple_dt->as_string();
  std::string simple_repr = tuple_dt->as_string_simplified();
  if (structures_.find(repr) != structures_.end()) {
    return structures_[repr]->prefixed_full_name_;
  }
  auto d = new structure_definition{};
  d->id_ = counter_++;
  d->dt_ = tuple_dt;
  d->a_ = nullptr;
  d->b_ = nullptr;
  std::stringstream code{};
  std::string name =
      improve_name(repr, simple_repr, "yktuple" + std::to_string(d->id_));
  code << "struct " << name << " {";
  size_t i = 1;
  for (ykdatatype *dt_arg : d->dt_->args_) {
    code << " " << dtc->convert_dt(dt_arg, datatype_location::STRUCT, "", "")
         << " e" << i << ";";
    i++;
  }
  code << " };\n";
  d->prefixed_name_ = name;
  d->prefixed_full_name_ = "struct " + name;
  d->code_ = code.str();
  d->meta_type_ = structure_type::TUPLE;
  structures_[repr] = d;
  structure_pool_.push_back(d);
  return d->prefixed_full_name_;
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
  std::string repr = fixed_array_dt->as_string();
  std::string simple_repr = fixed_array_dt->as_string_simplified();
  if (structures_.find(repr) != structures_.end()) {
    return structures_[repr]->prefixed_full_name_;
  }
  // Check assumption that must not happen
  if (!fixed_array_dt->is_fixed_size_array() ||
      fixed_array_dt->args_.size() != 2 ||
      fixed_array_dt->args_[0]->is_sm_entry() ||
      fixed_array_dt->args_[1]->is_m_entry()) {
    errors_.emplace_back("Invalid fixed array datatype: " +
                             fixed_array_dt->as_string_simplified(),
                         nullptr);
    return "<><>";
  }
  // -- convert
  // typedef ARG0 ykfxa##num[ARG1];
  auto d = new structure_definition{};
  d->id_ = counter_++;
  d->dt_ = fixed_array_dt;
  std::stringstream code{};
  d->a_ = fixed_array_dt->args_[0]; /* target */
  d->b_ = fixed_array_dt->args_[1]; /* size */
  code << "typedef ";
  code << dtc->convert_dt(d->a_, datatype_location::STRUCT, "", "") << " ";
  std::string name =
      improve_name(repr, simple_repr, "ykfxa" + std::to_string(d->id_));
  code << name << "[";
  code << d->b_->token_->token_; /* size */
  code << "];\n";
  // write the finalized code here
  d->code_ = code.str();
  d->meta_type_ = structure_type::FIXED_ARRAY;
  d->prefixed_name_ = name;
  d->prefixed_full_name_ = name;
  structures_[repr] = d;
  structure_pool_.push_back(d);
  return name;
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
void entry_struct_func_compiler::register_structure(
    const std::string &prefixed_name, ykdatatype *class_dt,
    class_stmt *class_statement, datatype_compiler *dtc,
    const std::string &member_prefix) {
  std::string repr = class_dt->as_string();
  if (structures_.find(repr) != structures_.end()) { return; }
  auto d = new structure_definition{};
  d->id_ = counter_++;
  d->dt_ = class_dt;
  d->a_ = nullptr;
  d->b_ = nullptr;
  std::stringstream code{};
  code << "struct " << prefixed_name << " {\n";
  for (auto &member : class_statement->members_) {
    code << "    ";
    code << dtc->convert_dt(member.data_type_, datatype_location::STRUCT, "",
                            "");
    code << " " << ::prefix(member.name_->token_, member_prefix) << ";\n";
  }
  code << "};\n";
  d->prefixed_name_ = prefixed_name;
  d->prefixed_full_name_ = "struct " + prefixed_name;
  d->code_ = code.str();
  d->class_stmt_or_null_ = class_statement;
  // struct or class based on the @onstack annotation or struct keyword usage
  if (class_statement->annotations_.on_stack_) {
    d->meta_type_ = structure_type::STRUCT;
  } else {
    d->meta_type_ = structure_type::CLASS;
  }
  structures_[repr] = d;
  structure_pool_.push_back(d);
}
entry_struct_func_compiler::~entry_struct_func_compiler() {
  for (auto *it : structure_pool_) { delete it; }
  structure_pool_.clear();
}
