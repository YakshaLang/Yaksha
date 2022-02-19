// builtins.h
#ifndef BUILTINS_H
#define BUILTINS_H
#include "utilities/ykobject.h"
#include <string>
#include <vector>
namespace yaksha {
  /**
   * Handle verifying and checking built in types
   */
  struct builtins {
    explicit builtins(ykdt_pool *dt_pool);
    ~builtins();
    /**
     * Is this name a valid builtin
     * @param name name of the builtin
     * @return if this is a valid builtin
     */
    static bool has_builtin(const std::string &name);
    /**
     * Type check call to builtin
     * @param name name of the function
     * @param args argument ykobjects
     * @return return type, if this is a runtime error something is wrong
     */
    ykobject verify(const std::string &name, const std::vector<ykobject> &args);
    /**
     * Compile a builtin function call.
     * This assumes verify and has builtin is called.
     * @param name name of the function
     * @param args compiled arguments to pass to function
     * @return compiled code + return type
     */
    std::pair<std::string, ykobject>
    compile(const std::string &name,
            const std::vector<std::pair<std::string, ykobject>> &args);

private:
    ykdt_pool *dt_pool_;
  };
}// namespace yaksha
#endif
