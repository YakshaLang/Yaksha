// ykobject.h
#ifndef YKOBJECT_H
#define YKOBJECT_H
#include "tokenizer/string_utils.h"
#include "tokenizer/token.h"
#include "ykdatatype.h"
#include "ykdt_pool.h"
#include <string>
namespace yaksha {
  enum class object_type {
    PRIMITIVE_OR_OBJ,
    FUNCTION,
    ERROR_DETECTED,
    UNKNOWN_OBJECT,
    CLASS_ITSELF,
    BUILTIN_FUNCTION,
    MODULE,
    MODULE_CLASS,
    MODULE_FUNCTION,
  };
  struct ykobject {
    ykobject();
    explicit ykobject(ykdatatype *dt);
    explicit ykobject(int i, ykdt_pool *pool);
    explicit ykobject(bool b, ykdt_pool *pool);
    explicit ykobject(std::string str, ykdt_pool *pool);
    explicit ykobject(double dbl, ykdt_pool *pool);
    explicit ykobject(float dbl, ykdt_pool *pool);
    explicit ykobject(ykdt_pool *pool);
    [[nodiscard]] bool is_primitive_or_obj() const;
    [[nodiscard]] bool is_a_function() const;
    int integer_val_{0};
    std::string string_val_{};
    std::string module_file_{};
    std::string module_name_{};
    bool desugar_rewrite_needed_{false};
    std::string desugar_rewrite_{};
    double double_val_{};
    bool bool_val_{};
    object_type object_type_{object_type::PRIMITIVE_OR_OBJ};
    ykdatatype *datatype_{nullptr};
  };
}// namespace yaksha
#endif
