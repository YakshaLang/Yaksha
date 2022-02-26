// builtins.cpp
#include "compiler/builtins.h"
#include <sstream>
using namespace yaksha;
builtins::builtins(ykdt_pool *dt_pool) : dt_pool_(dt_pool) {}
builtins::~builtins() = default;
bool builtins::has_builtin(const std::string &name) {
  if (name == "arrput") { return true; }
  if (name == "arrpop") { return true; }
  if (name == "print") { return true; }
  if (name == "println") { return true; }
  if (name == "len") { return true; }
  return false;
}
ykobject builtins::verify(const std::string &name,
                          const std::vector<ykobject> &args) {
  auto o = ykobject(dt_pool_);
  if (name == "arrput" && args.size() == 2 &&
      args[0].datatype_->is_an_array() &&
      *(args[0].datatype_->args_[0]) == *args[1].datatype_) {
    return o;
  } else if ((name == "print" || name == "println") && args.size() == 1 &&
             args[0].is_primitive_or_obj() &&
             args[0].datatype_->is_primitive()) {
    return o;
  } else if (name == "len" && args.size() == 1 &&
             (args[0].datatype_->is_an_array() ||
              args[0].datatype_->is_str())) {
    return ykobject(dt_pool_->create("int"));
  } else if (name == "arrpop" && args.size() == 1 &&
             args[0].datatype_->is_an_array()) {
    return ykobject(args[0].datatype_->args_[0]);// Array[x] << access this x
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
  if (name == "arrput") {
    code << "yk__arrput(" << args[0].first << ", " << args[1].first << ")";
  } else if (name == "print") {
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
  } else if (name == "println") {
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
  } else if (name == "len") {
    if (args[0].second.datatype_->is_str()) {
      code << "yk__sdslen(" << args[0].first << ")";
    } else {
      code << "yk__arrlen(" << args[0].first << ")";
    }
    o = ykobject(dt_pool_->create("int"));
  } else if (name == "arrpop") {
    o = ykobject(args[0].second.datatype_->args_[0]);
    code << "yk__arrpop(" << args[0].first << ")";
  }
  return {code.str(), o};
}