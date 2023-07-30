// compiler_utils.cpp
#include "compiler_utils.h"
#include <cstdint>
#include <unordered_map>
// TODO note that this is not thread safe,
//   and we should fix this if we ever start using multi threaded compilation
static std::unordered_map<std::string, std::string> GENSYMS{};
static std::int64_t GENSYM_COUNTER = -1;
std::string yaksha::prefix(const std::string &input,
                           const std::string &prefix_val) {
  if (input.rfind('$') == 0) {
    // This is a gensym, so we should generate a new symbol for this usecase
    // But you cannot already have yk__, yy__ or YK__ in the name if so
    std::string key = prefix_val + input;
    if (GENSYMS.find(key) == GENSYMS.end()) {
      GENSYM_COUNTER++;
      // since prefix_val is unique to files, this make gensym unique
      // `$a = 1 + 2` now this $a << this will be converted to a g_[prefix]_counter
      //  $a --> g_yk__1 for example
      GENSYMS[key] = "g_" + prefix_val + std::to_string(GENSYM_COUNTER);
    }
    return GENSYMS[key];
  }
  if ((input.rfind("yk__", 0) == 0) || input.rfind("YK__", 0) == 0 ||
      input.rfind("yy__", 0) == 0) {
    return input;
  }
  return prefix_val + input;
}
void yaksha::write_indent(std::stringstream &where_to, int level) {
  for (auto i = 0; i < level; i++) { where_to << "    "; }
}
