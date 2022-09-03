// parser.h
#ifndef PARSER_H
#define PARSER_H
#include "ast/ast.h"
#include "tokenizer/string_utils.h"
#include "tokenizer/token.h"
#include "utilities/ykdt_pool.h"
#include <sstream>
#include <unordered_map>
#include <vector>
namespace yaksha {
  struct parser {
    explicit parser(std::string filepath_, std::vector<token> &tokens,
                    ykdt_pool *pool);
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
    std::vector<import_stmt *> import_stmts_;
    std::unordered_map<std::string, import_stmt *> import_stmts_alias_{};
    std::vector<stmt *> stmts_{};
    std::string filepath_{};
    // parsing data types
    ykdatatype *parse_datatype();
    void rescan_datatypes();

private:
    // expressions
    expr *assignment();
    expr *expression();
    expr *equality();
    expr *comparison();
    expr *term();
    expr *factor();
    expr *unary();
    expr *fncall();
    expr *match_rest_of_fncall(expr *name);
    expr *match_array_access(expr *name);
    expr *primary();
    expr *or_op();
    expr *and_op();
    // statements
    stmt *statement();
    stmt *defer_statement();
    stmt *del_statement();
    stmt *del_statement_base();
    stmt *if_statement();
    stmt *while_statement();
    stmt *block_statement();
    stmt *pass_statement();
    stmt *ccode_statement();
    stmt *continue_statement();
    stmt *break_statement();
    stmt *return_statement();
    stmt *attempt_parse_def_or_class();
    stmt *def_statement(annotations ants);
    stmt *class_statement(annotations ants);
    stmt *import_statement();
    std::vector<parameter> parse_class_members(token *name);
    stmt *expression_statement();
    stmt *declaration_statement();
    // parsing annotations
    annotation parse_annotation();
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
    ykdt_pool *dt_pool_;
    std::vector<token> &tokens_;
    std::vector<ykdatatype *> datatypes_from_modules_{};
    // Increase when we allow control, flow.
    // Decrease after parsing.
    // If this is <= zero do not allow `continue` or `break`
    int control_flow_;
    token *magic_return_token_;
    token *sugar_else_;
  };
}// namespace yaksha
#endif
