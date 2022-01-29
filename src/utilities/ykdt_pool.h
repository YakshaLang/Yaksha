// ykdt_pool.h
#ifndef YKDT_POOL_H
#define YKDT_POOL_H
#include "utilities/ykdatatype.h"
#include <vector>
namespace yaksha {
  struct ykdt_pool {
    ykdt_pool();
    ~ykdt_pool();
    ykdatatype *create();

private:
    std::vector<ykdatatype *> pool_;
  };
}// namespace yaksha
#endif
