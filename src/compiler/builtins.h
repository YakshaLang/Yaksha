// builtins.h
#ifndef BUILTINS_H
#define BUILTINS_H
#include "ast/ast.h"
#include "compiler/datatype_compiler.h"
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
     * @param arg expressions to verify
     * @param import_aliases import aliases in current file
     * @return return type, if this is a runtime error something is wrong
     */
    ykobject verify(const std::string &name, const std::vector<ykobject> &args,
                    const std::vector<expr *> &arg_expressions,
                    const std::unordered_map<std::string, import_stmt *>& import_aliases,
                    const std::string& filepath);
    /**
     * Should we compile given argument + arg index
     * This is used to handle <code>cast("c.AnyPtr", state)</code>
     * @param name Built in name
     * @param arg_index argument to compile
     * @return Should we compile this argument?
     * (if false this needs to be consumed
     *      as a literal by the builtin compile function)
     */
    bool should_compile_argument(const std::string &name, int arg_index);
    /**
     * Compile a builtin function call.
     * This assumes verify and has builtin is called.
     * @param name name of the function
     * @param args compiled arguments to pass to function
     * @param arg expressions
     * @param dt_compiler data type compiler parameter
     * @param import_aliases import aliases in current file
     * @return compiled code + return type
     */
    std::pair<std::string, ykobject>
    compile(const std::string &name,
            const std::vector<std::pair<std::string, ykobject>> &args,
            const std::vector<expr *> &arg_expressions,
            datatype_compiler *dt_compiler,
            const std::unordered_map<std::string, import_stmt *>& import_aliases,
            const std::string& filepath);

private:
    ykdt_pool *dt_pool_;
    ykdatatype* parse(std::string basicString,
               const std::unordered_map<std::string, import_stmt *> &map, const std::string& filepath);
  };
}// namespace yaksha
#endif
