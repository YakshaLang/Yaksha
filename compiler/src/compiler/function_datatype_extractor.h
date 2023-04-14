// function_datatype_extractor.h
#ifndef FUNCTION_DATATYPE_EXTRACTOR_H
#define FUNCTION_DATATYPE_EXTRACTOR_H
#include "utilities/ykobject.h"
namespace yaksha {
  /**
   * Extract data type of a given function
   */
  struct function_datatype_extractor {
    virtual ~function_datatype_extractor() = default;
    /**
     * Get a datatype object for a function
     * @param arg argument
     * @return nullptr if failed, else a valid datatype
     */
    virtual ykdatatype *function_to_datatype(const ykobject &arg) = 0;
  };
}// namespace yaksha
#endif