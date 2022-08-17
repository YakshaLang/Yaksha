// entry_struct_compiler.cpp
#include "entry_struct_compiler.h"
using namespace yaksha;
entry_struct_compiler::entry_struct_compiler(ykdt_pool *pool)
    : pool_(pool), counter_(0), autogen_structs_list_(), code_() {}
std::string entry_struct_compiler::compile(ykdatatype *entry_dt,
                                           datatype_compiler *dtc) {
  entry_data d{};
  d.incremented_id_ = counter_++;
  if (entry_dt->is_sm_entry()) {
    d.key_dt_ = pool_->create("str");
    d.val_dt_ = entry_dt->args_[0];
  } else if (entry_dt->is_m_entry()) {
    d.key_dt_ = entry_dt->args_[0];
    d.key_dt_ = entry_dt->args_[1];
  } else {
    // Must not happen
    return "<><>";
  }
  code_ << "struct ykentry" << d.incremented_id_ << " { "
        << dtc->convert_dt(d.key_dt_) << " key; " << dtc->convert_dt(d.val_dt_)
        << " value; };\n";
  autogen_structs_list_.emplace_back(d);
  return "struct ykentry" + std::to_string(d.incremented_id_);
}
void entry_struct_compiler::compile_forward_declarations(
    std::stringstream &target) {
  for (auto &e : autogen_structs_list_) {
    // Pre declarations
    target << "struct ykentry" << e.incremented_id_ << ";\n";
  }
}
void entry_struct_compiler::compile_structures(std::stringstream &target) {
  target << code_.str();
}
bool entry_struct_compiler::has() { return !autogen_structs_list_.empty(); }
entry_struct_compiler::~entry_struct_compiler() = default;
