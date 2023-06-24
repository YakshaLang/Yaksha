// ic_tokens_file.h
#ifndef IC_TOKENS_FILE_H
#define IC_TOKENS_FILE_H
#include "ic2c/ic_tokenizer.h"
namespace yaksha {
  std::vector<ic_token> ic_load_token_dump(const std::string &file);
  [[maybe_unused]] bool ic_save_token_dump(const std::string &file,
                                           const std::vector<ic_token> &tokens);
  void ic_write_token_dump(std::ostream &output,
                           const std::vector<ic_token> &tokens);
}// namespace yaksha
#endif
