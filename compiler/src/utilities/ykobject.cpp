// ykobject.cpp
#include "utilities/ykobject.h"
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
bool ykobject::is_primitive_or_obj() const {
  return object_type_ == object_type::PRIMITIVE_OR_OBJ;
}
bool ykobject::is_a_function() const {
  return object_type_ == object_type::FUNCTION ||
         object_type_ == object_type::MODULE_FUNCTION;
}
ykobject::ykobject(ykdatatype *dt) {
  datatype_ = dt;
  object_type_ = object_type::PRIMITIVE_OR_OBJ;
}
ykobject::ykobject() : object_type_(object_type::UNKNOWN_OBJECT) {}
