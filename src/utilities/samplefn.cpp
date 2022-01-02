// samplefn.cpp
#include "samplefn.h"
using namespace yaksha;
samplefn::samplefn() = default;
samplefn::~samplefn() = default;
std::pair<func_control_flow, ykobject>
samplefn::call(const std::vector<ykobject> &args) {
  return std::make_pair(func_control_flow::NATIVE, ykobject(1));
}
