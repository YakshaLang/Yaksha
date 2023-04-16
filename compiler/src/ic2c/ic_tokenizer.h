// ic_tokenizer.h
#ifndef IC_TOKENIZER_H
#define IC_TOKENIZER_H
#include <string>
#include <vector>
#include "ic_token.h"
namespace yaksha {
  struct ic_token;
  struct ic_parsing_error;
  struct ic_tokenizer {
    ic_tokenizer(std::string file, std::string data);
    ~ic_tokenizer();
    void tokenize();
    std::vector<ic_token> tokens_;
    std::vector<ic_parsing_error> errors_;

private:
    void tokenize_internal();
    std::string file_;
    std::string data_;
    int line_;
    int pos_;
    int prev_line_;
    int prev_pos_;
  };
}// namespace yaksha
#endif
