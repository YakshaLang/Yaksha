// ykobject.cpp
#include "utilities/ykobject.h"
#include "utilities/error_printer.h"
#include <sstream>
#include <utility>
using namespace yaksha;
ykobject::ykobject() : object_type_(object_type::PRIMITIVE) {
  datatype_ = new ykdatatype("None");
}
ykobject::ykobject(int i)
    : object_type_(object_type::PRIMITIVE), integer_val_{i} {
  datatype_ = new ykdatatype("i32");
}
ykobject::ykobject(std::string str)
    : string_val_{std::move(str)}, object_type_(object_type::PRIMITIVE) {
  datatype_ = new ykdatatype("str");
}
ykobject::ykobject(double dbl)
    : double_val_{dbl}, object_type_{object_type::PRIMITIVE} {
  datatype_ = new ykdatatype("f64");
}
ykobject::ykobject(bool i)
    : object_type_(object_type::PRIMITIVE), bool_val_(i) {
  datatype_ = new ykdatatype("bool");
}
ykobject::ykobject(ykfunction *fun)
    : object_type_(object_type::FUNCTION), fn_val_(fun), datatype_(nullptr) {}
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
bool ykobject::is_primitive() const {
  return object_type_ == object_type::PRIMITIVE;
}
bool ykobject::is_same_datatype(ykobject &other) const {
  if (is_primitive() && other.is_primitive()) {
    return *datatype_ == *other.datatype_;
  }
  return object_type_ == other.object_type_;
}
ykobject::ykobject(ykdatatype *dt) {
  datatype_ = dt;
  object_type_ = object_type::PRIMITIVE;
}
