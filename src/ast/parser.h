// parser.h
#ifndef PARSER_H
#define PARSER_H
#include "ast/ast.h"
#include "tokenizer/string_utils.h"
#include "tokenizer/token.h"
#include <sstream>
#include <vector>
namespace yaksha {
  struct parser {
    explicit parser(std::vector<token> &tokens);
    ~parser();
    /**
   * parse and return a vector of statements
   * @return empty if cannot parse, if so check errors
   */
    std::vector<stmt *> parse();
    /**
     * Errors vector
     */
    std::vector<parsing_error> errors_;

private:
    // expressions
    expr *assignment();
    expr *expression();
    expr *equality();
    expr *comparison();
    expr *term();
    expr *factor();
    expr *unary();
    expr *primary();
    expr *or_op();
    expr *and_op();
    // statements
    stmt *statement();
    stmt *print_statement();
    stmt *if_statement();
    stmt *while_statement();
    stmt *block_statement();
    stmt *expression_statement();
    stmt *declaration_statement();
    // utilities
    bool match(std::initializer_list<token_type> types);
    bool check(token_type t);
    bool is_at_end();
    token *advance();
    token *recede();
    token *peek();
    token *previous();
    token *consume(token_type t, const std::string &message);
    token *consume_or_eof(token_type t, const std::string &message);
    parsing_error error(token *tok, const std::string &message);
    void handle_error(const parsing_error &err);
    void synchronize_parser();
    // state
    std::size_t current_;
    ast_pool pool_;
    std::vector<token> &tokens_;
    stmt *pass_statement();
  };
}// namespace yaksha
#endif
