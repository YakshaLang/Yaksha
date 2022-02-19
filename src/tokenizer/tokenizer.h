// tokenizer.h
#ifndef TOKENIZER_H
#define TOKENIZER_H
// TODO Stop using a vector and provide an iterator for tokens
// TODO on error skip to next line and continue tokenizing, display all possible
// errors
#include "tokenizer/string_utils.h"
#include "tokenizer/token.h"
#include <fstream>
#include <functional>
#include <iostream>
#include <unordered_set>
#include <utf8.h>
#include <vector>
namespace yaksha {
  /**
 * Consume a triple quoted string
 * @tparam octet_iterator iterator data type
 * @param buf buffer to write the string to
 * @param begin current position in iterator
 * @param end last position in iterator
 * @return <matched size, last character, line_count>
 */
  template<typename octet_iterator>
  std::tuple<int, utf8::uint32_t, int> consume_triple_str(std::string &buf,
                                                          octet_iterator &begin,
                                                          octet_iterator end);
  /**
 * Consume a number (decimal integer or a float)
 * Hex, Oct, Bin is handled separately
 * @tparam octet_iterator iterator data type
 * @param buf buffer to write the string to
 * @param begin current position in iterator
 * @param end last position in iterator
 * @return <matched size, last character,
 *      token_type::INTEGER_DECIMAL or token_type::FLOAT_NUMBER>
 */
  template<typename octet_iterator>
  std::tuple<int, utf8::uint32_t, token_type>
  consume_number(std::string &buf, octet_iterator &begin, octet_iterator end);
  /**
 * Tokenize a string to vector of tokens
 */
  struct tokenizer {
    explicit tokenizer(std::string file, std::string data);
    std::vector<token> tokens_;
    std::vector<parsing_error> errors_;
    /**
   * Parse given string to a list of tokens accessible in tokens_
   * parsing errors will be present in errors_ field.
   */
    void tokenize();

private:
    std::string file_;
    std::string data_;
    void handle_error(const parsing_error &err);
  };
}// namespace yaksha
#endif
