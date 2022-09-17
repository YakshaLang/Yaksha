// ykdatatype.h
#ifndef YKDATATYPE_H
#define YKDATATYPE_H
#include "tokenizer/token.h"
#include <sstream>
#include <vector>
namespace yaksha {
  enum class ykprimitive {
    I8,
    I16,
    I32,
    I64,
    F32,
    F64,
    U8,
    U16,
    U32,
    U64,
    STR,
    BOOL,
    NONE,
    NOT_A_PRIMITIVE,
  };
  enum class ykbuiltin {
    ARRAY,
    SM_ENTRY,
    M_ENTRY,
    NOT_A_BUILTIN,
    CONSTANT,
    POINTER,
    // Function[In[str],Out]
    FUNCTION,
    F_IN,
    F_OUT,
    ANY_PTR
  };
  struct ykdatatype {
    explicit ykdatatype(token *primitive_dt);
    explicit ykdatatype(std::string primitive_dt);
    explicit ykdatatype(std::string primitive_dt, std::string module);
    ~ykdatatype();
    // Quick Checks for Primitive Data Types
    [[nodiscard]] bool is_int() const;
    [[nodiscard]] bool is_str() const;
    [[nodiscard]] bool is_float() const;
    [[nodiscard]] bool is_bool() const;
    [[nodiscard]] std::string as_string() const;
    [[nodiscard]] bool is_primitive() const;
    [[nodiscard]] bool is_i8() const;
    [[nodiscard]] bool is_i16() const;
    [[nodiscard]] bool is_i32() const;
    [[nodiscard]] bool is_i64() const;
    [[nodiscard]] bool is_u8() const;
    [[nodiscard]] bool is_u16() const;
    [[nodiscard]] bool is_u32() const;
    [[nodiscard]] bool is_u64() const;
    [[nodiscard]] bool is_f32() const;
    [[nodiscard]] bool is_f64() const;
    [[nodiscard]] bool is_none() const;
    [[nodiscard]] bool support_plus() const;
    [[nodiscard]] bool is_builtin_or_primitive() const;
    [[nodiscard]] bool is_a_number() const;
    [[nodiscard]] bool is_an_integer() const;
    [[nodiscard]] bool is_a_signed_integer() const;
    [[nodiscard]] bool is_an_unsigned_integer() const;
    [[nodiscard]] bool is_a_float() const;
    [[nodiscard]] bool is_an_array() const;
    [[nodiscard]] bool is_a_pointer() const;
    [[nodiscard]] bool is_const() const;
    [[nodiscard]] bool is_m_entry() const;
    [[nodiscard]] bool is_sm_entry() const;
    [[nodiscard]] bool is_function() const;
    [[nodiscard]] bool is_function_input() const;
    [[nodiscard]] bool is_function_output() const;
    [[nodiscard]] bool is_any_ptr() const;
    [[nodiscard]] bool matches(const ykdatatype &template_) const;
    token *token_{};
    std::string type_{};
    std::string module_{};
    std::vector<ykdatatype *> args_;
    ykprimitive primitive_type_{ykprimitive::NOT_A_PRIMITIVE};
    ykbuiltin builtin_type_{ykbuiltin::NOT_A_BUILTIN};

private:
    void write_to_str(std::stringstream &s) const;
    void find_builtin_or_primitive();
  };
  inline bool primitive_equals(const ykdatatype &lhs, const ykdatatype &rhs) {
    if (lhs.is_primitive() && rhs.is_primitive()) {
      return lhs.primitive_type_ == rhs.primitive_type_;
    }
    return lhs.as_string() == rhs.as_string();
  }
  inline bool operator==(const yaksha::ykdatatype &lhs,
                         const yaksha::ykdatatype &rhs) {
    // TODO rethink this, this is clearly wrong?
    if (lhs.is_const() || rhs.is_const()) {
      const yaksha::ykdatatype *unwrapped_lhs;
      const yaksha::ykdatatype *unwrapped_rhs;
      if (lhs.is_const()) {
        unwrapped_lhs = lhs.args_[0];
      } else {
        unwrapped_lhs = &lhs;
      }
      if (rhs.is_const()) {
        unwrapped_rhs = rhs.args_[0];
      } else {
        unwrapped_rhs = &rhs;
      }
      return primitive_equals(*unwrapped_lhs, *unwrapped_rhs);
    }
    return primitive_equals(lhs, rhs);
  }
  inline bool operator!=(const ykdatatype &lhs, const ykdatatype &rhs) {
    return !(lhs == rhs);
  }
}// namespace yaksha
#endif
