// ykdatatype.h
#ifndef YKDATATYPE_H
#define YKDATATYPE_H
#include "tokenizer/token.h"
#include <sstream>
#include <vector>
namespace yaksha {
  struct ykdatatype {
    ykdatatype();
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
    [[nodiscard]] bool matches(const ykdatatype &template_) const;
    token *name_{};
    std::vector<ykdatatype *> args_;

private:
    void write_to_str(std::stringstream &s) const;
  };
  inline bool operator==(const yaksha::ykdatatype &lhs,
                         const yaksha::ykdatatype &rhs) {
    return lhs.as_string() == rhs.as_string();
  }
  inline bool operator!=(const ykdatatype &lhs, const ykdatatype &rhs) {
    return !(lhs == rhs);
  }
}// namespace yaksha
#endif
