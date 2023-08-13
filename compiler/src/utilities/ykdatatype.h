// ykdatatype.h
#ifndef YKDATATYPE_H
#define YKDATATYPE_H
#include "tokenizer/token.h"
#include <sstream>
#include <vector>
namespace yaksha {
  enum class ykprimitive {
    // Numeric > 0 && < 1000
    BOOL = 1,
    HIDDEN_I4 [[maybe_unused]] = 2,// reserved
    HIDDEN_U4 [[maybe_unused]] = 3,// reserved
    I8 = 4,
    U8 = 5,
    I16 = 6,
    U16 = 7,
    I32 = 8,
    U32 = 9,
    I64 = 10,
    U64 = 11,
    HIDDEN_F8 [[maybe_unused]] = 12, // reserved
    HIDDEN_F16 [[maybe_unused]] = 13,// reserved
    F32 = 14,
    F64 = 15,
    // String >= 1000
    HIDDEN_STRING_LIT = 1000,// internal use only
    SR = 2000,
    STR = 3000,
    // None == 0
    NONE = 0,
    // Invalid < 0
    NOT_A_PRIMITIVE = -9999,// internal use only
  };
  enum class ykbuiltin {
    ARRAY,
    SM_ENTRY,
    M_ENTRY,
    NOT_A_BUILTIN,
    CONSTANT,
    POINTER,
    ANY_PTR,
    ANY_PTR_TO_CONST,
    TUPLE,
    // Function[In[str],Out]
    FUNCTION,
    F_IN,
    F_OUT,
  };
  struct ykdt_pool;
  struct ykdatatype {
    explicit ykdatatype(token *primitive_dt);
    explicit ykdatatype(std::string primitive_dt);
    explicit ykdatatype(std::string primitive_dt, std::string module);
    ~ykdatatype();
    // Quick Checks for Primitive Data Types
    [[nodiscard]] ykdatatype *const_unwrap();
    [[nodiscard]] ykdatatype *auto_cast(ykdatatype *rhs, bool lhs_mutates,
                                        ykdt_pool *pool);
    [[nodiscard]] bool is_int() const;
    [[nodiscard]] bool is_str() const;
    [[nodiscard]] bool is_sr() const;
    [[nodiscard]] bool is_string_literal() const;
    [[nodiscard]] bool is_float() const;
    [[nodiscard]] bool is_bool() const;
    [[nodiscard]] bool is_const_bool() const;
    [[nodiscard]] bool is_bool_or_const_bool() const;
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
    [[nodiscard]] bool is_builtin_or_primitive() const;
    [[nodiscard]] bool is_a_number() const;
    [[nodiscard]] bool is_a_number_or_const_number() const;
    [[nodiscard]] bool is_an_integer() const;
    [[nodiscard]] bool is_a_const_integer() const;
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
    [[nodiscard]] bool is_any_ptr_to_const() const;
    [[nodiscard]] bool is_tuple() const;
    [[nodiscard]] bool is_a_string() const;
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
    return primitive_equals(lhs, rhs);
  }
  inline bool operator!=(const ykdatatype &lhs, const ykdatatype &rhs) {
    return !(lhs == rhs);
  }
}// namespace yaksha
#endif
