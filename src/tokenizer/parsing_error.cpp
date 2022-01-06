#include <utility>
#include "tokenizer/token.h"
using namespace yaksha;
parsing_error::parsing_error(std::string message, token *at)
    : message_(std::move(message)), tok_(*at), token_set_{true} {}
parsing_error::parsing_error(std::string message, std::string file, int line,
                             int pos)
    : message_(std::move(message)), tok_{} {
  tok_.file_ = std::move(file);
  tok_.line_ = line;
  tok_.pos_ = pos;
}