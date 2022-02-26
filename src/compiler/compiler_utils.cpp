// compiler_utils.cpp
#include "compiler_utils.h"
std::string yaksha::prefix(const std::string &input,
                           const std::string &prefix_val) {
  if ((input.rfind("yk__", 0) == 0) || input.rfind("YK__", 0) == 0 ||
      input.rfind("yy__", 0) == 0) {
    return input;
  }
  return prefix_val + input;
}
void yaksha::write_indent(std::stringstream &where_to, int level) {
  for (auto i = 0; i < level; i++) { where_to << "    "; }
}
