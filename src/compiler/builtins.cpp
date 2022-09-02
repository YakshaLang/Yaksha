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
  if (name == "charat") { return true; }
  if (name == "getref") { return true; }
  if (name == "unref") { return true; }
  if (name == "shnew") { return true; }
  if (name == "shput") { return true; }
  if (name == "shget") { return true; }
  if (name == "shgeti") { return true; }
  return false;
}
ykobject builtins::verify(const std::string &name,
                          const std::vector<ykobject> &args) {
  auto o = ykobject(dt_pool_);
  if (name == "arrput" && args.size() == 2 &&
      args[0].datatype_->is_an_array() &&
      *(args[0].datatype_->args_[0]) == *args[1].datatype_) {
    // verify arrput(Array[T], T)
    return o;
  } else if ((name == "print" || name == "println") && args.size() == 1 &&
             args[0].is_primitive_or_obj() &&
             args[0].datatype_->is_primitive()) {
    return o;
  } else if (name == "len" && args.size() == 1 &&
             (args[0].datatype_->is_an_array() ||
              args[0].datatype_->is_str())) {
    // verify len(Array[?])
    return ykobject(dt_pool_->create("int"));
  } else if (name == "arrpop" && args.size() == 1 &&
             args[0].datatype_->is_an_array()) {
    // arrpop(Array[T]) -> returns T
    return ykobject(args[0].datatype_->args_[0]);
  } else if (name == "charat" && args.size() == 2 &&
             args[0].datatype_->is_str() &&
             args[1].datatype_->is_an_integer()) {
    return ykobject(dt_pool_->create("int"));
  } else if (name == "getref" && args.size() == 1) {
    ykdatatype *dt = dt_pool_->create("Ptr");
    dt->args_.emplace_back(args[0].datatype_);
    return ykobject(dt);
  } else if (name == "unref" && args.size() == 1 &&
             args[0].datatype_->is_a_pointer()) {
    // Ptr[x] << access this x
    return ykobject(args[0].datatype_->args_[0]);
  } else if (name == "shnew" && args.size() == 1 &&
             args[0].datatype_->is_an_array() &&
             args[0].datatype_->args_[0]->is_sm_entry()) {
    // shnew(Array[SMEntry[T]])
    // Create a new string hash
    return o;// None returned
  } else if (name == "shget" && args.size() == 2 &&
             args[0].datatype_->is_an_array() &&
             args[0].datatype_->args_[0]->is_sm_entry() &&
             args[1].datatype_->is_str()) {
    // shget(Array[SMEntry[T]], str) -> T
    return ykobject(args[0].datatype_->args_[0]->args_[0]);
  } else if (name == "shgeti" && args.size() == 2 &&
             args[0].datatype_->is_an_array() &&
             args[0].datatype_->args_[0]->is_sm_entry() &&
             args[1].datatype_->is_str()) {
    // shgeti(Array[SMEntry[T]], str) -> int
    return ykobject(dt_pool_->create("int"));
  } else if (name == "shput" && args.size() == 3 &&
             args[0].datatype_->is_an_array() &&
             args[0].datatype_->args_[0]->is_sm_entry() &&
             args[1].datatype_->is_str() &&
             (*args[2].datatype_ == *args[0].datatype_->args_[0]->args_[0])) {
    // shput(Array[SMEntry[T]], str, T) -> None
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
  if (name == "arrput") {
    if (args[1].second.datatype_->is_str()) {
      code << "yk__arrput(" << args[0].first << ", yk__sdsdup(" << args[1].first
           << "))";
    } else {
      code << "yk__arrput(" << args[0].first << ", " << args[1].first << ")";
    }
  } else if (name == "print") {
    auto rhs = args[0];
    if (rhs.second.datatype_->is_a_signed_integer()) {
      code << "yk__printint(((intmax_t)" << rhs.first << "))";
    } else if (rhs.second.datatype_->is_an_unsigned_integer()) {
      code << "yk__printuint(((uintmax_t)" << rhs.first << "))";
    } else if (rhs.second.datatype_->is_str()) {
      code << "yk__printstr((" << rhs.first << "))";
    } else if (rhs.second.datatype_->is_a_float()) {
      code << "yk__printdbl((" << rhs.first << "))";
    }
  } else if (name == "println") {
    auto rhs = args[0];
    if (rhs.second.datatype_->is_a_signed_integer()) {
      code << "yk__printlnint(((intmax_t)" << rhs.first << "))";
    } else if (rhs.second.datatype_->is_an_unsigned_integer()) {
      code << "yk__printlnuint(((uintmax_t)" << rhs.first << "))";
    } else if (rhs.second.datatype_->is_str()) {
      code << "yk__printlnstr((" << rhs.first << "))";
    } else if (rhs.second.datatype_->is_a_float()) {
      code << "yk__printlndbl((" << rhs.first << "))";
    }
  } else if (name == "len") {
    if (args[0].second.datatype_->is_str()) {
      code << "yk__sdslen(" << args[0].first << ")";
    } else if (args[0].second.datatype_->is_an_array() &&
               args[0].second.datatype_->args_[0]->is_sm_entry()) {
      // Array[SMEntry[?]]
      code << "yk__shlen(" << args[0].first << ")";
    } else {
      code << "yk__arrlen(" << args[0].first << ")";
    }
    o = ykobject(dt_pool_->create("int"));
  } else if (name == "arrpop") {
    o = ykobject(args[0].second.datatype_->args_[0]);
    code << "yk__arrpop(" << args[0].first << ")";
  } else if (name == "charat") {
    code << "(" << args[0].first << "[" << args[1].first << "])";
    o = ykobject(dt_pool_->create("int"));
  } else if (name == "getref") {
    code << "(&(" << args[0].first << "))";
    ykdatatype *dt = dt_pool_->create("Ptr");
    dt->args_.emplace_back(args[0].second.datatype_);
    o = ykobject(dt);
  } else if (name == "unref") {
    code << "(*(" << args[0].first << "))";
    o = ykobject(args[0].second.datatype_->args_[0]);
  } else if (name == "shnew") {
    code << "yk__sh_new_strdup(" << args[0].first << ")";
  } else if (name == "shget") {
    code << "yk__shget(" << args[0].first << ", " << args[1].first << ")";
    o = ykobject(args[0].second.datatype_->args_[0]->args_[0]);
  } else if (name == "shgeti") {
    code << "yk__shgeti(" << args[0].first << ", " << args[1].first << ")";
    o = ykobject(dt_pool_->create("int"));
  } else if (name == "shput") {
    code << "yk__shput(" << args[0].first << ", " << args[1].first << ", "
         << args[2].first << ")";
  }
  return {code.str(), o};
}