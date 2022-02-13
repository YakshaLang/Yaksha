// ykobject.h
#ifndef YKOBJECT_H
#define YKOBJECT_H
#include "tokenizer/string_utils.h"
#include "tokenizer/token.h"
#include "ykdatatype.h"
#include "ykdt_pool.h"
#include <string>
namespace yaksha {
  struct ykfunction;
  enum class control_flow_change { BREAK, RETURN, CONTINUE, NO_CHANGE, ERROR };
  enum class object_type {
    PRIMITIVE_OR_OBJ,
    FUNCTION,
    RUNTIME_ERROR,
    UNKNOWN_OBJECT,
    CLASS_ITSELF,
    BUILTIN_FUNCTION
  };
  struct ykobject {
    ykobject();
    explicit ykobject(ykdatatype *dt);
    explicit ykobject(int i, ykdt_pool *pool);
    explicit ykobject(bool b, ykdt_pool *pool);
    explicit ykobject(std::string str, ykdt_pool *pool);
    explicit ykobject(const std::string &str, token *bad_token);
    explicit ykobject(double dbl, ykdt_pool *pool);
    explicit ykobject(ykfunction *fun);
    explicit ykobject(control_flow_change flow_change);
    explicit ykobject(ykdt_pool *pool);
    [[nodiscard]] bool is_primitive_or_obj() const;
    bool is_same_datatype(ykobject &other) const;
    int integer_val_{0};
    std::string string_val_{};
    double double_val_{};
    bool bool_val_{};
    control_flow_change flow_ = control_flow_change::NO_CHANGE;
    object_type object_type_{object_type::PRIMITIVE_OR_OBJ};
    ykdatatype *datatype_{nullptr};
    ykfunction *fn_val_{};
    /**
     * Write ykobject representation
     * @param out output stream to write to
     * @param s object
     * @return output stream
     */
    inline friend std::ostream &operator<<(std::ostream &out,
                                           const ykobject &s) {
      if (s.object_type_ == object_type::RUNTIME_ERROR) {
        out << "[Error]::" << s.string_val_;
      } else if (s.object_type_ == object_type::PRIMITIVE_OR_OBJ) {
        if (s.datatype_->is_str()) {
          out << string_utils::repr_string(s.string_val_);
        } else if (s.datatype_->is_f64()) {
          out << s.double_val_;
        } else if (s.datatype_->is_i32()) {
          out << s.integer_val_;
        } else if (s.datatype_->is_none()) {
          out << "None";
        } else if (s.datatype_->is_bool()) {
          out << (s.bool_val_ ? "True" : "False");
        }
      }
      return out;
    }
    std::ostream &stringify(std::ostream &out) const { return out << *this; }
  };
}// namespace yaksha
#endif
