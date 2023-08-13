// datatype_compiler.h
#ifndef DATATYPE_COMPILER_H
#define DATATYPE_COMPILER_H
#include "utilities/ykdatatype.h"
#include "utilities/ykobject.h"
#include <string>
namespace yaksha {
  struct datatype_compiler {
    virtual std::string convert_dt(ykdatatype *entry_dt) = 0;
    virtual void
    compile_string_assign(token *t, std::stringstream &code,
                          const std::pair<std::string, ykobject> &rhs,
                          const ykdatatype *rhs_datatype,
                          const ykdatatype *lhs_datatype) = 0;
    [[nodiscard]] virtual std::string
    wrap_in_paren(const std::string &code) const = 0;
    virtual ~datatype_compiler() = default;

private:
  };
}// namespace yaksha
#endif
