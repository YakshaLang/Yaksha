// indent_analyzer.h
#ifndef INDENT_ANALYZER_H
#define INDENT_ANALYZER_H
#include "tokenizer/token.h"
#include <vector>
namespace yaksha {
  /**
   * Different types of indentations
   * UNKNOWN is pretty bad!
   */
  enum class indent_type { TWO_SPACES, FOUR_SPACES, TAB, UNKNOWN };
  /**
   * Convert given string to an indent type
   * @param indent_str string to examine
   * @return indent type
   */
  static inline indent_type str_to_indent_type(const std::string &indent_str) {
    if (indent_str == "  ") {
      return indent_type::TWO_SPACES;
    } else if (indent_str == "    ") {
      return indent_type::FOUR_SPACES;
    } else if (indent_str == "\t") {
      return indent_type::TAB;
    }
    return indent_type::UNKNOWN;
  }
  /**
   * Analyze indented blocks and replace INDENT tokens with
   * BA_INDENT & BA_DEDENT,
   * Additionally this cleans up extra new lines, indents & comments
   * // TODO Extract cleaning to a different class (Single Responsibility/SOLID)
   */
  struct block_analyzer {
    explicit block_analyzer(const std::vector<token> &tokens);
    void analyze();
    std::vector<parsing_error> errors_;
    std::vector<token> tokens_;

private:
    void handle_error(const parsing_error &err);
    void create_dedents(std::vector<std::size_t> &indents, const token &tok,
                        size_t prev_level, size_t current_level);
    const std::vector<token> &original_tokens_;
  };
}// namespace yaksha
#endif
