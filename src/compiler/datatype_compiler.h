// datatype_compiler.h
#ifndef DATATYPE_COMPILER_H
#define DATATYPE_COMPILER_H
#include "utilities/ykdatatype.h"
namespace yaksha {
  struct datatype_compiler {
    virtual std::string convert_dt(ykdatatype *entry_dt) = 0;
    virtual ~datatype_compiler() = default;
private:
  };
}// namespace yaksha

#endif
