// pipeline.h
#ifndef PIPELINE_H
#define PIPELINE_H
#include "pipeline/pipe.h"
namespace yaksha {
  struct pipeline {
    pipeline();
    ~pipeline();

private:
    std::vector<tok_to_tok> token_transformers_;
    std::vector<ast_to_ast> ast_transformers_;
  };
}// namespace yaksha
#endif
