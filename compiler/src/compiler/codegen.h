// codegen.h
#ifndef CODEGEN_H
#define CODEGEN_H
#include "utilities/gc_pool.h"
namespace yaksha {
  struct comp_result;
  struct codefiles;
  struct token;
  struct codegen {
    virtual ~codegen() = default;
    virtual comp_result emit(codefiles *cf, gc_pool<token> *token_pool) = 0;

private:
  };
}// namespace yaksha
#endif
