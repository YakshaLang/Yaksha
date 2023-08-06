// macro_processor.h
#ifndef MACRO_PROCESSOR_H
#define MACRO_PROCESSOR_H
#include "ast/ast.h"
#include "tokenizer/token.h"
#include <string>
#include <unordered_map>
#include <vector>
namespace yaksha {
  struct macro_processor {
    virtual ~macro_processor() = default;
    virtual void
    init_env(std::string filepath,
             std::unordered_map<std::string, import_stmt *> &imports) = 0;
    /**
     * Execute a macros!{} block, and create
     * @param filepath current file path
     * @param lisp_code lisp code tokens
     * @param imports import map
     */
    virtual void
    execute(std::string &filepath, std::vector<token *> &lisp_code,
            std::unordered_map<std::string, import_stmt *> &imports) = 0;
    /**
     * After macros!{} are executed, it will define dsl macros
     *  Now we can then execute this dsl defun and expand given tokens
     * @param filepath current file path
     * @param imports import map
     * @param dsl_macro_name name of the DSL macro name such as magic!{}
     * @param dsl_macro_input tokens as input
     * @return resulting tokens
     */
    virtual std::vector<token *>
    expand_dsl(std::string &filepath,
               std::unordered_map<std::string, import_stmt *> &imports,
               std::string &dsl_macro_name,
               std::vector<token *> &dsl_macro_input,
               std::string imported_macro, token *macro_name) = 0;

private:
  };
}// namespace yaksha
#endif
