// builtins.cpp
#include "compiler/builtins.h"
#include <sstream>
using namespace yaksha;
builtins::builtins(ykdt_pool *dt_pool) : dt_pool_(dt_pool) {}
builtins::~builtins() = default;
bool builtins::has_builtin(const std::string &name) {
  if (name == "yy__arrput") { return true; }
  return false;
}
ykobject builtins::verify(const std::string &name,
                          const std::vector<ykobject> &args) {
  auto o = ykobject(dt_pool_);
  if (name == "yy__arrput" && args.size() == 2 &&
      args[0].datatype_->is_an_array() &&
      *(args[0].datatype_->args_[0]) == *args[1].datatype_) {
    return o;
  }
  o.object_type_ = object_type::RUNTIME_ERROR;
  o.string_val_ = "Invalid arguments for builtin function";
  return o;
}
std::pair<std::string, ykobject>
builtins::compile(const std::string &name,
                  const std::vector<std::pair<std::string, ykobject>> &args) {
  std::stringstream code{};
  auto o = ykobject(dt_pool_);
  if (name == "yy__arrput") {
    code << "yk__arrput(" << args[0].first << ", " << args[1].first << ")";
    return {code.str(), o};
  }
  return {"", o};
}