// codegen_json.h
#ifndef CODEGEN_JSON_H
#define CODEGEN_JSON_H
#include "codegen.h"
namespace yaksha {
    struct codegen_json: codegen {
        codegen_json();
        ~codegen_json() override;
        comp_result emit(codefiles *cf, gc_pool<token> *token_pool) override;

    private:
    };
}
#endif
