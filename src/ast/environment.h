// environment.h
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include "utilities/ykobject.h"
#include <string>
namespace yaksha {
  /**
   * A collection of variables in current scope
   */
  struct environment {
    /**
     * See if this variable is defined
     * @param name name of the variable
     * @return true if defined
     */
    virtual bool is_defined(const std::string &name);
    /**
     * Define a variable for the first time
     * @param name name of the variable
     * @param data object
     */
    virtual void define(const std::string &name, ykobject data);
    /**
     * Assign a value to a variable (only if it's declared)
     * @param name name of the variable
     * @param data object
     */
    virtual void assign(const std::string &name, ykobject data);
    /**
     * Get mutable data for a variable
     * @param name name of the variable
     * @return mutable object
     */
    virtual ykobject &get(const std::string &name);
    environment();
    virtual ~environment();

private:
    std::unordered_map<std::string, ykobject> variables_;
  };
}// namespace yaksha
#endif
