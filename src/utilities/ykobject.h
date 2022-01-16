// ykobject.h
#ifndef YKOBJECT_H
#define YKOBJECT_H
#include "tokenizer/string_utils.h"
#include "tokenizer/token.h"
#include <string>
namespace yaksha {
  struct ykfunction;
  enum class control_flow_change { BREAK, RETURN, CONTINUE, NO_CHANGE, ERROR };
  enum class object_type {
    INTEGER,
    DOUBLE, // TODO Create different integer types and float types
    STRING,
    NONE_OBJ,
    BOOL,
    FUNCTION,
    RUNTIME_ERROR
  };
  struct ykobject {
    explicit ykobject(int i);
    explicit ykobject(bool b);
    explicit ykobject(std::string str);
    explicit ykobject(const std::string &str, token *bad_token);
    explicit ykobject(double dbl);
    explicit ykobject(ykfunction *fun);
    explicit ykobject(control_flow_change flow_change);
    explicit ykobject();
    int integer_val_{0};
    std::string string_val_{};
    double double_val_{};
    bool bool_val_{};
    control_flow_change flow_ = control_flow_change::NO_CHANGE;
    object_type object_type_{object_type::NONE_OBJ};
    ykfunction *fn_val_{};
    // TODO convert errors to our friendly parsing errors for syntax errors
    // TODO Keep string errors for runtime errors?
    // TODO change error data type later on after we introduce maybe an actual,
    //  err type.
    /**
     * Write ykobject representation
     * @param out output stream to write to
     * @param s object
     * @return output stream
     */
    inline friend std::ostream &operator<<(std::ostream &out,
                                           const ykobject &s) {
      if (s.object_type_ == object_type::STRING) {
        out << string_utils::repr_string(s.string_val_);
      } else if (s.object_type_ == object_type::DOUBLE) {
        out << s.double_val_;
      } else if (s.object_type_ == object_type::INTEGER) {
        out << s.integer_val_;
      } else if (s.object_type_ == object_type::NONE_OBJ) {
        out << "None";
      } else if (s.object_type_ == object_type::BOOL) {
        out << (s.bool_val_ ? "True" : "False");
      } else {
        out << "[Error]::" << s.string_val_;
      }
      return out;
    }
    std::ostream &stringify(std::ostream &out) const {
      if (object_type_ == object_type::STRING) {
        out << string_val_;
      } else if (object_type_ == object_type::DOUBLE) {
        out << double_val_;
      } else if (object_type_ == object_type::INTEGER) {
        out << integer_val_;
      } else if (object_type_ == object_type::NONE_OBJ) {
        out << "None";
      } else if (object_type_ == object_type::BOOL) {
        out << (bool_val_ ? "True" : "False");
      } else {
        out << "[Error]::" << string_val_;
      }
      return out;
    }
  };
}// namespace yaksha
#endif
