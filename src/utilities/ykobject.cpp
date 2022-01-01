// ykobject.cpp
#include "utilities/ykobject.h"
#include "utilities/error_printer.h"
#include <sstream>
#include <utility>
using namespace yaksha;
ykobject::ykobject() : object_type_(object_type::NONE_OBJ) {}
ykobject::ykobject(int i)
    : object_type_(object_type::INTEGER), integer_val_{i} {}
ykobject::ykobject(std::string str)
    : string_val_{std::move(str)}, object_type_(object_type::STRING) {}
ykobject::ykobject(double dbl)
    : double_val_{dbl}, object_type_{object_type::DOUBLE} {}
ykobject::ykobject(bool i) : object_type_(object_type::BOOL), bool_val_(i) {}
ykobject::ykobject(ykfunction *fun)
    : object_type_(object_type::FUNCTION), fn_val_(fun) {}
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
