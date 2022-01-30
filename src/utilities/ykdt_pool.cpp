// ykdt_pool.cpp
#include "ykdt_pool.h"
using namespace yaksha;
ykdt_pool::ykdt_pool() { pool_.reserve(1000); }
ykdt_pool::~ykdt_pool() {
  for (auto item : pool_) { delete (item); }
  pool_.clear();
}
ykdatatype *ykdt_pool::create(token *tok) {
  auto dt = new ykdatatype(tok);
  pool_.emplace_back(dt);
  return dt;
}
