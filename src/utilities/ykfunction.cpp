// ykfunction.cpp
#include "ykfunction.h"
using namespace yaksha;
ykfunction::ykfunction() = default;
ykobject ykfunction::verify(const std::vector<ykobject> &args,
                            ykdt_pool *pool) {
  return ykobject(pool);
}
