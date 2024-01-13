// codegen_json.cpp
#include "codegen_json.h"
#include "ast/codefiles.h"
#include "compiler/comp_result.h"
using namespace yaksha;
codegen_json::codegen_json() = default;
codegen_json::~codegen_json() = default;
comp_result codegen_json::emit(codefiles *cf, gc_pool<token> *token_pool) { return comp_result(); }
