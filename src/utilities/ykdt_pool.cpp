// ykdt_pool.cpp
#include "ykdt_pool.h"
#include <utility>
using namespace yaksha;
ykdt_pool::ykdt_pool() { pool_.reserve(1000); }
ykdt_pool::~ykdt_pool() {
  for (auto item : pool_) { delete (item); }
  pool_.clear();
}
ykdatatype *ykdt_pool::create(std::string tok) {
  auto dt = new ykdatatype(std::move(tok));
  pool_.emplace_back(dt);
  return dt;
}
ykdatatype *ykdt_pool::create(std::string tok, std::string module) {
  auto dt = new ykdatatype(std::move(tok), std::move(module));
  pool_.emplace_back(dt);
  return dt;
}