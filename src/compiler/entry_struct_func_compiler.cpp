// entry_struct_func_compiler.cpp
#include "entry_struct_func_compiler.h"
using namespace yaksha;
entry_struct_func_compiler::entry_struct_func_compiler(ykdt_pool *pool)
    : pool_(pool), counter_(0), autogen_structs_list_(), autogen_structs_(),
      autogen_func_typedefs_(), autogen_func_typedef_list_(),
      counter_functions_(0), code_(), code_fnc_() {}
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
       << dtc->convert_dt(d.key_dt_) << " key; " << dtc->convert_dt(d.val_dt_)
       << " value; };\n";
  code_ << code.str();
  autogen_structs_list_.emplace_back(d);
  autogen_structs_[repr] = d.incremented_id_;
  return "struct ykentry" + std::to_string(d.incremented_id_);
}
void entry_struct_func_compiler::compile_forward_declarations(
    std::stringstream &target) {
  for (auto &e : autogen_structs_list_) {
    // Pre declarations
    target << "struct ykentry" << e.incremented_id_ << ";\n";
  }
}
void entry_struct_func_compiler::compile_structures(std::stringstream &target) {
  target << code_.str();
}
bool entry_struct_func_compiler::has_structures() {
  return !autogen_structs_list_.empty();
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
    code << dtc->convert_dt(output->args_[0]) << " ";
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
      code << dtc->convert_dt(dt);
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
entry_struct_func_compiler::~entry_struct_func_compiler() = default;
