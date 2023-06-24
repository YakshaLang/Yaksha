// ic_parser.h
#ifndef IC_PARSER_H
#define IC_PARSER_H
#include "ic_ast.h"
namespace yaksha {
  struct ic_parser {
    ic_parser(std::vector<ic_token> &tokens, ic_ast_pool *ast_pool);
    ~ic_parser();
    void parse();
    std::vector<ic_stmt *> statements_;
    std::vector<ic_parsing_error> errors_;

private:
    // ---------------------- Parsing ----------------------
    ic_stmt *preprocessor_statement();
    ic_stmt *define_st(ic_token *hash_t);
    ic_stmt *include_st(ic_token *hash_t);
    ic_stmt *line_st(ic_token *hash_t);
    ic_stmt *undef_st(ic_token *hash_t);
    ic_stmt *error_st(ic_token *hash_t);
    ic_stmt *warning_st(ic_token *hash_t);
    ic_stmt *pragma_st(ic_token *hash_t);
    ic_stmt *code_line();
    ic_stmt *block(ic_token *hash_t);
    ic_stmt *if_st(ic_token *hash_t);
    // ---------------------- State -------------------------
    ic_ast_pool *ast_pool_;
    std::vector<ic_token> &tokens_;
    std::size_t current_;
    // ----------------------- Utilities -------------------
    ic_token *advance();
    ic_token *recede();
    bool is_at_end();
    ic_token *peek();
    ic_token *previous();
    bool match(std::initializer_list<ic_token_type> types);
    bool check(ic_token_type t);
    ic_token *consume(ic_token_type t, const std::string &message);
    ic_token *consume_or_eof(ic_token_type t, const std::string &message);
    ic_parsing_error error(ic_token *tok, const std::string &message);
    std::vector<ic_token *> token_string();
  };
}// namespace yaksha
#endif
