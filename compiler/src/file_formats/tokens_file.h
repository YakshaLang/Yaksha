// tokens_file.h
#ifndef TOKENS_FILE_H
#define TOKENS_FILE_H
#include "tokenizer/tokenizer.h"
// Collection of tokens that can be used for snapshot testing of tokenizer
namespace yaksha {
  /**
 * Load vector of tokens from given file
 * @param file file with token data
 * @return list of tokens
 */
  std::vector<token *> load_token_dump(const std::string &file,
                                       gc_pool<token> *token_pool);
  /**
 * Save vector of tokens to given file
 * @param file file with token data
 * @param tokens list of tokens
 */
  [[maybe_unused]] bool save_token_dump(const std::string &file,
                                        const std::vector<token *> &tokens);
  void write_token_dump(std::ostream &output,
                        const std::vector<token *> &tokens);
}// namespace yaksha
#endif
