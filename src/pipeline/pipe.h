// pipe.h
#ifndef PIPE_H
#define PIPE_H
#include "ast/ast.h"
#include <vector>
namespace yaksha {
  struct ast_input {
    virtual void analyze(expr *expression) = 0;
    virtual ~ast_input() = default;
  };
  struct ast_output {
    virtual expr *program() = 0;
    virtual ~ast_output() = default;
  };
  struct token_input {
    virtual void analyze(std::vector<token> &tokens) = 0;
    virtual ~token_input() = default;
  };
  struct token_output {
    virtual const std::vector<parsing_error> &errors() = 0;
    virtual const std::vector<token> &tokens() = 0;
    virtual ~token_output() = default;

private:
  };
  struct ast_to_ast : ast_input, ast_output {
    ~ast_to_ast() override = default;
  };
  struct tok_to_tok : token_input, token_output {
    ~tok_to_tok() override = default;
  };
}// namespace yaksha
#endif
