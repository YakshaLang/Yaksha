// compiler_utils.h
#ifndef COMPILER_UTILS_H
#define COMPILER_UTILS_H
#include <sstream>
#include <string>
namespace yaksha {
  /**
   * Convert given name to prefixed name.
   * if name starts with `yk__` or `YK__` leave it as it is.
   * else prefix with `yy__` for all.
   * @param input name
   * @return prefixed name
   */
  std::string prefix(const std::string &input, const std::string &prefix_val);
  void write_indent(std::stringstream &where_to, int level);
}// namespace yaksha
#endif
