// samplefn.cpp
#include "samplefn.h"
using namespace yaksha;
samplefn::samplefn() = default;
samplefn::~samplefn() = default;
ykobject samplefn::call(const std::vector<ykobject> &args) {
  return ykobject(1);
}
