// samplefn.h
#ifndef SAMPLEFN_H
#define SAMPLEFN_H
#include "ykfunction.h"
namespace yaksha {
  /**
   * Dummy function object that just return 1 no matter
   *    what one give it as arguments
   */
  struct samplefn : ykfunction {
    samplefn();
    ~samplefn() override;
    std::pair<func_control_flow, ykobject>
    call(const std::vector<ykobject> &args) override;

private:
  };
}// namespace yaksha
#endif
