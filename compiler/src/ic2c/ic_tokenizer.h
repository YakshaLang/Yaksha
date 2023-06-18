// ic_tokenizer.h
#ifndef IC_TOKENIZER_H
#define IC_TOKENIZER_H
#include <string>
#include <vector>
#include "ic_token.h"
#include "ic_trigraph_translater.h"
#include "ic_peek_ahead_iter.h"
#include "ic_line_splicer.h"
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
    int prev_line_;
    int prev_pos_;
    ic_trigraph_translater iter_tt_;
    ic_line_splicer iter_ls_;
    ic_peek_ahead_iter character_iterator_;
  };
}// namespace yaksha
#endif
