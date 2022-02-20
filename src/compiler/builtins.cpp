// builtins.cpp
#include "compiler/builtins.h"
#include <sstream>
using namespace yaksha;
builtins::builtins(ykdt_pool *dt_pool) : dt_pool_(dt_pool) {}
builtins::~builtins() = default;
bool builtins::has_builtin(const std::string &name) {
  if (name == "yy__arrput") { return true; }
  if (name == "yy__print") { return true; }
  if (name == "yy__println") { return true; }
  return false;
}
ykobject builtins::verify(const std::string &name,
                          const std::vector<ykobject> &args) {
  auto o = ykobject(dt_pool_);
  if (name == "yy__arrput" && args.size() == 2 &&
      args[0].datatype_->is_an_array() &&
      *(args[0].datatype_->args_[0]) == *args[1].datatype_) {
    return o;
  } else if ((name == "yy__print" || name == "yy__println") &&
             args.size() == 1 && args[0].is_primitive_or_obj() &&
             args[0].datatype_->is_primitive()) {
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
  } else if (name == "yy__print") {
    auto rhs = args[0];
    if (rhs.second.datatype_->is_a_signed_integer()) {
      code << "printf(\"%jd\", ((intmax_t)" << rhs.first << "))";
    } else if (rhs.second.datatype_->is_an_unsigned_integer()) {
      code << "printf(\"%ju\", ((uintmax_t)" << rhs.first << "))";
    } else if (rhs.second.datatype_->is_str()) {
      // TODO do not assume it's all ascii, and works fine :p
      code << "printf(\"%s\", (" << rhs.first << "))";
    } else if (rhs.second.datatype_->is_a_float()) {
      code << "printf(\"%f\", (" << rhs.first << "))";
    }
  } else if (name == "yy__println") {
    auto rhs = args[0];
    if (rhs.second.datatype_->is_a_signed_integer()) {
      code << R"(printf("%jd\n", ((intmax_t))" << rhs.first << "))";
    } else if (rhs.second.datatype_->is_an_unsigned_integer()) {
      code << R"(printf("%ju\n", ((uintmax_t))" << rhs.first << "))";
    } else if (rhs.second.datatype_->is_str()) {
      // TODO do not assume it's all ascii, and works fine :p
      code << R"(printf("%s\n", ()" << rhs.first << "))";
    } else if (rhs.second.datatype_->is_a_float()) {
      code << R"(printf("%f\n", ()" << rhs.first << "))";
    }
  }
  return {code.str(), o};
}