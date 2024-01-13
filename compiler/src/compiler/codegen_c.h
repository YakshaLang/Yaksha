// codegen_c.h
#ifndef CODEGEN_C_H
#define CODEGEN_C_H
#include "codegen.h"
namespace yaksha {
    struct codegen_c: codegen {
        codegen_c();
        ~codegen_c() override;
        comp_result emit(codefiles *cf, gc_pool<token> *token_pool) override;
    private:
    };
}
#endif
