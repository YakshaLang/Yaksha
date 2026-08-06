#ifndef CODEGEN_JSON_H
#define CODEGEN_JSON_H
#include "ast/ast.h"
#include "codegen.h"
namespace yaksha {
  struct codegen_json : codegen {
    codegen_json();
    ~codegen_json() override;
    comp_result emit(codefiles *cf, gc_pool<token> *token_pool,
                     errors::error_printer *ep) override;
  };
} // namespace yaksha
#endif
