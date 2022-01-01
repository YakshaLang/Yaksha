// ykfunction.h
#ifndef YKFUNCTION_H
#define YKFUNCTION_H
#include "utilities/ykobject.h"
#include <vector>
namespace yaksha {
  struct ykfunction {
    ykfunction();
    virtual ~ykfunction() = default;
    /**
     * Verify the arity, data types, etc with given arguments?
     * NOTE: If this is not overridden, default behaviour is allow anything
     * @param args args to consider
     * @return ykobject, if this is NONE_OBJ no issues, else it's a runtime error
     */
    virtual ykobject verify(const std::vector<ykobject> &args);
    /**
     * Call a function with given arguments
     * @param args arguments that this function is called with
     * @return result
     */
    virtual ykobject call(const std::vector<ykobject> &args) = 0;

private:
  };
}// namespace yaksha
#endif
