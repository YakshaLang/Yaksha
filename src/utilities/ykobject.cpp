// ykobject.cpp
#include "utilities/ykobject.h"
#include "utilities/error_printer.h"
#include <sstream>
#include <utility>
using namespace yaksha;
ykobject::ykobject(ykdt_pool *pool)
    : object_type_(object_type::PRIMITIVE_OR_OBJ) {
  datatype_ = pool->create("None");
}
ykobject::ykobject(int i, ykdt_pool *pool)
    : object_type_(object_type::PRIMITIVE_OR_OBJ), integer_val_{i} {
  datatype_ = pool->create("i32");
}
ykobject::ykobject(std::string str, ykdt_pool *pool)
    : string_val_{std::move(str)}, object_type_(object_type::PRIMITIVE_OR_OBJ) {
  datatype_ = pool->create("str");
}
ykobject::ykobject(double dbl, ykdt_pool *pool)
    : double_val_{dbl}, object_type_{object_type::PRIMITIVE_OR_OBJ} {
  datatype_ = pool->create("f64");
}
ykobject::ykobject(float float_val, ykdt_pool *pool)
    : double_val_{float_val}, object_type_{object_type::PRIMITIVE_OR_OBJ} {
  datatype_ = pool->create("f32");
}
ykobject::ykobject(bool i, ykdt_pool *pool)
    : object_type_(object_type::PRIMITIVE_OR_OBJ), bool_val_(i) {
  datatype_ = pool->create("bool");
}
ykobject::ykobject(const std::string &str, token *bad_token)
    : flow_(control_flow_change::ERROR) {
  std::stringstream error_message{};
  error_message << "\n";
  errors::print_token(error_message, *bad_token);
  error_message << " --> " << str;
  string_val_ = error_message.str();
  object_type_ = object_type::RUNTIME_ERROR;
}
ykobject::ykobject(control_flow_change flow_change)
    : object_type_{object_type::RUNTIME_ERROR}, flow_{flow_change},
      string_val_("break/continue") {}
bool ykobject::is_primitive_or_obj() const {
  return object_type_ == object_type::PRIMITIVE_OR_OBJ;
}
bool ykobject::is_a_function() const {
  return object_type_ == object_type::FUNCTION ||
         object_type_ == object_type::MODULE_FUNCTION;
}
bool ykobject::is_same_datatype(ykobject &other) const {
  if (is_primitive_or_obj() && other.is_primitive_or_obj()) {
    return *datatype_ == *other.datatype_;
  }
  return object_type_ == other.object_type_;
}
ykobject::ykobject(ykdatatype *dt) {
  datatype_ = dt;
  object_type_ = object_type::PRIMITIVE_OR_OBJ;
}
ykobject::ykobject() : object_type_(object_type::UNKNOWN_OBJECT) {}
