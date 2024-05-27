// ==============================================================================================
// ╦  ┬┌─┐┌─┐┌┐┌┌─┐┌─┐    Yaksha Programming Language
// ║  ││  ├┤ │││└─┐├┤     is Licensed with GPLv3 + extra terms. Please see below.
// ╩═╝┴└─┘└─┘┘└┘└─┘└─┘
// Note: libs - MIT license, runtime/3rd - various
// ==============================================================================================
// GPLv3:
//
// Yaksha - Programming Language.
// Copyright (C) 2020 - 2024 Bhathiya Perera
//
// This program is free software: you can redistribute it and/or modify it under the terms
// of the GNU General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with this program.
// If not, see https://www.gnu.org/licenses/.
//
// ==============================================================================================
// Additional Terms:
//
// Please note that any commercial use of the programming language's compiler source code
// (everything except compiler/runtime, compiler/libs and compiler/3rd) require a written agreement
// with author of the language (Bhathiya Perera).
//
// If you are using it for an open source project, please give credits.
// Your own project must use GPLv3 license with these additional terms.
//
// You may use programs written in Yaksha/YakshaLisp for any legal purpose
// (commercial, open-source, closed-source, etc) as long as it agrees
// to the licenses of linked runtime libraries (see compiler/runtime/README.md).
//
// ==============================================================================================
// parser.h
#ifndef PARSER_H
#define PARSER_H
#include "ast/ast.h"
#include "tokenizer/string_utils.h"
#include "tokenizer/token.h"
#include "utilities/gc_pool.h"
#include "utilities/ykdt_pool.h"
#include "yaksha_lisp/macro_processor.h"
#include <sstream>
#include <unordered_map>
#include <vector>
namespace yaksha {
  struct parser {
    explicit parser(std::string filepath_, std::vector<token *> &tokens,
                    ykdt_pool *pool);
    ~parser();
    // stepwise preprocess dsl macros
    void step_1_parse_token_soup();
    void step_3_execute_macros(macro_processor *mp);
    void step_4_expand_macros(macro_processor *mp, gc_pool<token> *token_pool);
    // facade for preprocess dsl macros (all above steps are done here, for tests)
    void preprocess(macro_processor *mp, gc_pool<token> *token_pool);
    /**
    * parse and return a vector of statements
    * @return empty if cannot parse, if so check errors
    */
    std::vector<stmt *> parse();
    /**
     * Errors vector
     */
    std::vector<parsing_error> errors_;
    std::vector<import_stmt *> pre_parse_import_stmts_;
    std::unordered_map<std::string, import_stmt *>
        pre_parse_import_stmts_alias_{};
    std::vector<import_stmt *> import_stmts_;
    std::unordered_map<std::string, import_stmt *> import_stmts_alias_{};
    std::vector<stmt *> stmts_{};
    std::string filepath_{};
    // parsing data types
    ykdatatype *parse_datatype();
    void rescan_datatypes();

private:
    std::vector<token *> macro_expand(macro_processor *mp,
                                      dsl_macro_stmt *dsl_macro,
                                      gc_pool<token> *token_pool);
    void parse_token_soup(std::vector<stmt *> &stmts,
                          std::vector<token *> &tokens_buffer);
    void parse_dsl_soup(std::vector<stmt *> &stmts,
                        std::vector<token *> &tokens_buffer);
    // expressions
    expr *assignment();
    expr *expression();
    expr *equality();
    expr *comparison();
    expr *bit_or();
    expr *bit_xor();
    expr *bit_and();
    expr *bit_shifts();
    expr *term();
    expr *factor();
    expr *unary();
    expr *fncall();
    expr *match_rest_of_fncall(expr *name);
    expr *match_array_access(expr *name);
    expr *match_rest_of_curly_call(expr *name);
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
    stmt *for_statement();
    stmt *block_statement();
    stmt *pass_statement();
    stmt *ccode_statement();
    stmt *continue_statement();
    stmt *break_statement();
    stmt *return_statement();
    stmt *attempt_parse_def_or_class();
    stmt *def_statement(annotations ants);
    stmt *class_statement(annotations ants);
    stmt *enum_statement(annotations ants);
    stmt *import_statement();
    stmt *runtimefeature_statement();
    std::vector<parameter> parse_class_members(token *name);
    stmt *expression_statement();
    stmt *declaration_statement();
    // parsing annotations
    annotation parse_annotation();
    // utilities
    bool match(std::initializer_list<token_type> types);
    bool check(token_type t);
    bool is_at_end();
    bool is_at_end_of_stream();
    token *advance();
    token *recede();
    token *peek();
    token *previous();
    token *consume(token_type t, const std::string &message);
    token *consume_or_eof(token_type t, const std::string &message);
    parsing_error error(token *tok, const std::string &message);
    void handle_error(const parsing_error &err);
    void synchronize_parser();
    void verify_statements(token *t, std::vector<stmt *> &statements);
    void verify_only_single_line_statements(token *token,
                                            std::vector<stmt *> &statements);
    // state
    std::size_t current_;
    ast_pool pool_;
    ykdt_pool *dt_pool_;
    std::vector<token *> &original_tokens_;
    std::vector<token *> tokens_{};
    std::vector<ykdatatype *> datatypes_from_modules_{};
    std::vector<stmt *> soup_statements_{};
    // Increase when we allow control, flow.
    // Decrease after parsing.
    // If this is <= zero do not allow `continue` or `break`
    int control_flow_;
    token *magic_return_token_;
    token *sugar_else_;
    stmt *parse_named_let_statement();
    stmt *directive_statement();
    token *consume_any_of(std::initializer_list<token_type> types,
                          const std::string &message);
    std::vector<parameter> parse_enum_members(token *name_token);
  };
}// namespace yaksha
#endif
