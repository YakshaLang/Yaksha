// yaksha_lisp.h
#ifndef YAKSHA_LISP_H
#define YAKSHA_LISP_H
#include "ast/ast.h"
#include "macro_processor.h"
#include "tokenizer/token.h"
#include "utilities/gc_pool.h"
#include <cstdint>
#include <functional>
#include <map>
#include <string>
#include <unordered_map>
/**
 * <h3>YakshaLisp is a lisp like language (dialect) that is interpreted
 * Yaksha language uses YakshaLisp to define macros and mutate AST.</h3>
 *
 * YakshaLisp is inspired by build your own lisp book's (BYOL) lisp dialect
 *   Wisp and lispy(by Norvig)
 *
 * Wisp - https://github.com/adam-mcdaniel/wisp/tree/main
 * Build your own lisp book - https://buildyourownlisp.com/
 * Lispy - https://norvig.com/lispy.html
 *
 * Unlike Yaksha, YakshaLisp only has expressions and no statements.
 * YakshaLisp has 2 types of expressions - S-Expressions and Q-Expressions.
 * Q-Expressions are kept as is and not evaluated. {a b c} is same as '(a b c).
 * Unlike BYOL, YakshaLisp does support special forms.
 * Example special forms are - if, do, scope, defun, def and lambda.
 *
 */
static const char *const KEY_IMPORT_REFERENCE = "yk_import_ref";
namespace yaksha {
  struct yk_memory_manager;
  enum class yaksha_lisp_token_type {
    NUMBER,
    STRING,
    SYMBOL,
    PAREN_OPEN,
    PAREN_CLOSE,
    CURLY_OPEN,
    CURLY_CLOSE,
    AT,
    COLON,
    DOUBLE_COLON,
    COMMA,
    YAKSHA_LISP_EOF,
    INVALID
  };
  enum class yaksha_lisp_expr_type { S_EXPR, Q_EXPR, MAP_LITERAL, TERMINAL };
  enum class yaksha_lisp_value_type {
    NUMBER,   // sets num_
    STRING,   // sets str_
    LIST,     // sets list_
    EXPR,     // sets expr_
    BUILTIN,  // sets builtin_, str_ (name)
    LAMBDA,   // sets list_, closure_ (env), str_ (name if present)
    METAMACRO,// sets list_, closure_ (env), str_ (name)
    MODULE,   // sets closure_ (module's env), str_ (name)
    MAP,      // sets closure_ (env)
  };
  // ┌┬┐┌─┐┬┌─┌─┐┌┐┌
  //  │ │ │├┴┐├┤ │││
  //  ┴ └─┘┴ ┴└─┘┘└┘
  struct yaksha_lisp_token {
    yaksha_lisp_token_type type_;
    std::string token_;
    std::string file_;
    int pos_;
    int line_;
    // for pool
    yaksha_lisp_token *next_{nullptr};
    yaksha_lisp_token *prev_{nullptr};
    std::uint8_t mark_{0};
    void clean_state();
  };
  // ┌─┐─┐ ┬┌─┐┬─┐┌─┐┌─┐┌─┐┬┌─┐┌┐┌
  // ├┤ ┌┴┬┘├─┘├┬┘├┤ └─┐└─┐││ ││││
  // └─┘┴ └─┴  ┴└─└─┘└─┘└─┘┴└─┘┘└┘
  struct yaksha_lisp_expr {
    yaksha_lisp_expr_type type_;
    std::vector<yaksha_lisp_expr *> list_;
    yaksha_lisp_token *token_;
    yaksha_lisp_token *close_token_;
    // for pool
    yaksha_lisp_expr *next_{nullptr};
    yaksha_lisp_expr *prev_{nullptr};
    std::uint8_t mark_{0};
    void clean_state();
    void gc_mark(yk_memory_manager *memory_manager);
  };
  // ┌┬┐┌─┐┬┌─┌─┐┌┐┌┬┌─┐┌─┐┬─┐
  //  │ │ │├┴┐├┤ ││││┌─┘├┤ ├┬┘
  //  ┴ └─┘┴ ┴└─┘┘└┘┴└─┘└─┘┴└─
  struct yaksha_lisp_tokenizer {
    yaksha_lisp_tokenizer();
    explicit yaksha_lisp_tokenizer(yk_memory_manager *mm);
    ~yaksha_lisp_tokenizer();
    void tokenize(std::string file, std::string code,
                  gc_pool<token> *token_pool);
    void tokenize(std::string file, std::vector<token *> &tokens);
    std::vector<yaksha_lisp_token *> tokens_;
    std::vector<parsing_error> errors_;
    std::string file_;
    yk_memory_manager *mm_;
    // for pool
    yaksha_lisp_tokenizer *next_{nullptr};
    yaksha_lisp_tokenizer *prev_{nullptr};
    std::uint8_t mark_{0};
    void clean_state();

private:
    yaksha_lisp_token_type identify_token_type(token &token,
                                               yaksha_lisp_token *dt);
    void handle_numbers(yaksha_lisp_token *dt);
    void process_yk_tokens(tokenizer &tok);
    bool consider_token(token *t);
    void inject_eof();
    void convert_tokens(std::vector<token *> &tokens);
  };
  // ┌─┐┌─┐┬─┐┌─┐┌─┐┬─┐
  // ├─┘├─┤├┬┘└─┐├┤ ├┬┘
  // ┴  ┴ ┴┴└─└─┘└─┘┴└─
  struct yaksha_lisp_parser {
    yaksha_lisp_parser();
    explicit yaksha_lisp_parser(yaksha_lisp_tokenizer *dt,
                                yk_memory_manager *mm);
    ~yaksha_lisp_parser();
    void parse();
    void print();
    std::vector<yaksha_lisp_expr *> exprs_;
    std::vector<parsing_error> errors_;
    std::string file_;
    int current_{0};
    yaksha_lisp_tokenizer *dt_;
    yk_memory_manager *mm_;
    // for pool
    yaksha_lisp_parser *next_{nullptr};
    yaksha_lisp_parser *prev_{nullptr};
    std::uint8_t mark_{0};
    void clean_state();

private:
    yaksha_lisp_expr *parse_s_expr();
    yaksha_lisp_expr *parse_q_expr();
    yaksha_lisp_expr *parse_expr();
    yaksha_lisp_expr *parse_map_literal();
    // utils
    bool is_at_end();
    yaksha_lisp_expr *create_expr();
    yaksha_lisp_token *advance();
    yaksha_lisp_token *recede();
    yaksha_lisp_token *peek();
    bool has_previous();
    yaksha_lisp_token *previous();
    bool has_prev_prev();
    yaksha_lisp_token *peek_prev_prev();
    bool has_next_next();
    yaksha_lisp_token *peek_next_next();
    bool has_next();
    yaksha_lisp_token *peek_next();
    bool match(std::initializer_list<yaksha_lisp_token_type> types);
    bool check(yaksha_lisp_token_type t);
    yaksha_lisp_token *consume(yaksha_lisp_token_type t,
                               const std::string &message);
    parsing_error error(yaksha_lisp_token *tok, const std::string &message);
    yaksha_lisp_token *consume_or_eof(yaksha_lisp_token_type t,
                                      const std::string &message);
    yaksha_lisp_expr *parse_terminal();
    static void print_exp(yaksha_lisp_expr *exp);
    yaksha_lisp_expr *create_terminal_expr_from_token(yaksha_lisp_token *token);
  };
  struct yaksha_lisp_value;
  struct yaksha_envmap;
  // ┌┬┐┌─┐┌┬┐  ┌┬┐┌─┐┌┐┌┌─┐┌─┐┌─┐┬─┐
  // │││├┤ │││  │││├─┤│││├─┤│ ┬├┤ ├┬┘
  // ┴ ┴└─┘┴ ┴  ┴ ┴┴ ┴┘└┘┴ ┴└─┘└─┘┴└─
  struct yk_memory_manager {
    virtual ~yk_memory_manager() = default;
    virtual yaksha_lisp_value *create_value() = 0;
    virtual yaksha_envmap *create_env() = 0;
    virtual yaksha_lisp_expr *create_expr() = 0;
    virtual yaksha_lisp_token *create_token() = 0;
    virtual yaksha_lisp_tokenizer *create_tokenizer() = 0;
    virtual yaksha_lisp_parser *create_parser(yaksha_lisp_tokenizer *dt) = 0;
    virtual void init_mark_sweep() = 0;
    virtual void mark(yaksha_lisp_value *value) = 0;
    virtual void mark(yaksha_envmap *env) = 0;
    virtual void mark(yaksha_lisp_expr *expr) = 0;
    virtual void mark(yaksha_lisp_token *token) = 0;
    virtual void mark(yaksha_lisp_tokenizer *tokenizer) = 0;
    virtual void mark(yaksha_lisp_parser *parser) = 0;
    virtual size_t sweep() = 0;
    virtual gc_pool<token> *get_yk_token_pool() = 0;
    virtual void gc_mark() = 0;
    virtual void enable_gc() = 0;
    virtual void disable_gc() = 0;
    virtual void root_lock() = 0;
    virtual void root_unlock() = 0;
  };
  // ┬┌┬┐┌─┐┌─┐┬─┐┌┬┐  ┬─┐┌─┐┌─┐┌─┐┬ ┬  ┬┌─┐┬─┐
  // ││││├─┘│ │├┬┘ │   ├┬┘├┤ └─┐│ ││ └┐┌┘├┤ ├┬┘
  // ┴┴ ┴┴  └─┘┴└─ ┴   ┴└─└─┘└─┘└─┘┴─┘└┘ └─┘┴└─
  struct yk_import_resolver {
    virtual ~yk_import_resolver() = default;
    virtual yaksha_envmap *
    validate_and_get_environment_root(const std::string &filepath) = 0;
  };
  // ┌─┐┌┐┌┬  ┬┬┬─┐┌─┐┌┐┌┌┬┐┌─┐┌┐┌┌┬┐
  // ├┤ │││└┐┌┘│├┬┘│ │││││││├┤ │││ │
  // └─┘┘└┘ └┘ ┴┴└─└─┘┘└┘┴ ┴└─┘┘└┘ ┴
  struct yaksha_envmap {
    yaksha_envmap(yaksha_envmap *parent, yk_memory_manager *pool);
    explicit yaksha_envmap(yk_memory_manager *pool);
    yaksha_envmap();
    ~yaksha_envmap();
    void setup_builtins();
    void setup_prelude();
    yaksha_lisp_value *
    eval(const std::vector<yaksha_lisp_expr *> &expressions_);
    yaksha_lisp_value *eval(yaksha_lisp_expr *exp);
    yaksha_lisp_value *eval(yaksha_lisp_value *val_);
    yaksha_lisp_value *eval_call(yaksha_lisp_value *symbol_value,
                                 const std::vector<yaksha_lisp_value *> &args);
    yaksha_lisp_value *get(const std::string &symbol);
    void set(const std::string &symbol, yaksha_lisp_value *value,
             bool defining);
    void set(const std::string &symbol, yaksha_lisp_value *value);
    bool has_map(yaksha_lisp_value *key);
    bool has_map(std::string key);
    void set_map(yaksha_lisp_value *key, yaksha_lisp_value *value);
    void set_map(std::string key, yaksha_lisp_value *value);
    yaksha_lisp_value *keys_map(yaksha_envmap *env);
    yaksha_lisp_value *values_map(yaksha_envmap *env);
    void remove_map(yaksha_lisp_value *key);
    void remove_map(std::string key);
    yaksha_lisp_value *get_map(yaksha_lisp_value *key,
                               yaksha_lisp_value *default_value);
    yaksha_lisp_value *get_map(std::string key,
                               yaksha_lisp_value *default_value);
    void push_closure(yaksha_envmap *env);
    void pop_closure();
    yaksha_envmap *peek_closure();
    yaksha_envmap *spawn();
    yaksha_envmap *get_parent() const;
    yk_memory_manager *get_memory_manager() const;
    const std::unordered_map<std::string, yaksha_lisp_value *> &
    get_symbols() const;
    yaksha_lisp_value *create_nil();
    yaksha_lisp_value *create_number(std::int64_t num);
    yaksha_lisp_value *create_string(const std::string &str);
    yaksha_lisp_value *create_expr_val(yaksha_lisp_expr *exp);
    yaksha_lisp_value *create_val();
    static bool is_truthy(yaksha_lisp_value *val);
    static std::string to_string(yaksha_lisp_value *value);
    void cleanup();
    void lockdown();
    void unlock();
    void gc_enable();
    void gc_disable();
    // for pool
    yaksha_envmap *next_{nullptr};
    yaksha_envmap *prev_{nullptr};
    std::uint8_t mark_{0};
    void clean_state();
    // --
    void gc_mark();
    // ----
    std::unordered_map<std::string, yaksha_lisp_value *> symbols_{};
    yk_memory_manager *mm_;
    yk_import_resolver *ir_;
    yaksha_envmap *parent_ = nullptr;
    std::string identifier_{};
    bool builtins_created_{false};
    bool prelude_evaluate_success_{false};
    void lockdown_root();
    void unlock_root();

private:
    std::vector<yaksha_envmap *> closures_{};
    std::string indent_{};
    yaksha_lisp_value *eval_internal(yaksha_lisp_expr *exp);
    yaksha_lisp_value *eval_internal(yaksha_lisp_value *val_);
    yaksha_lisp_value *
    eval_call_internal(yaksha_lisp_value *symbol_value,
                       const std::vector<yaksha_lisp_value *> &args);
    yaksha_lisp_value *get_internal(const std::string &symbol);
    void increase_indent();
    void decrease_indent();
    static std::string derive_key(yaksha_lisp_value *key);
    bool locked_down_env_{false};
    void define_internal(const std::string &symbol, yaksha_lisp_value *value);
    void setq_internal(const std::string &symbol, yaksha_lisp_value *value);
  };
  // ┌─┐┌─┐┬  ┬  ┌─┐┌┐ ┬  ┌─┐
  // │  ├─┤│  │  ├─┤├┴┐│  ├┤
  // └─┘┴ ┴┴─┘┴─┘┴ ┴└─┘┴─┘└─┘
  typedef yaksha_lisp_value *(*yaksha_lisp_builtin_callable)(
      const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
  // ┬  ┬┌─┐┬  ┬ ┬┌─┐
  // └┐┌┘├─┤│  │ │├┤
  //  └┘ ┴ ┴┴─┘└─┘└─┘
  struct yaksha_lisp_value {
    yaksha_lisp_value_type type_;
    std::string str_;
    std::int64_t num_;
    std::vector<yaksha_lisp_value *> list_;
    yaksha_lisp_expr *expr_;
    yaksha_lisp_builtin_callable builtin_{nullptr};
    yaksha_envmap *closure_{nullptr};
    bool foreign_{false};
    yaksha_envmap *foreign_env_{nullptr};
    // for pool
    yaksha_lisp_value *next_{nullptr};
    yaksha_lisp_value *prev_{nullptr};
    std::uint8_t mark_{0};
    void clean_state();
    void gc_mark(yk_memory_manager *memory_manager);
  };
  static std::vector<yaksha_lisp_value *>
  eval_args(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env);
  // ┌┬┐┌─┐┌─┐┬─┐┌─┐  ┌─┐┬─┐┌─┐┌─┐┌─┐┌─┐┌─┐┬┌┐┌┌─┐
  // │││├─┤│  ├┬┘│ │  ├─┘├┬┘│ ││  ├┤ └─┐└─┐│││││ ┬
  // ┴ ┴┴ ┴└─┘┴└─└─┘  ┴  ┴└─└─┘└─┘└─┘└─┘└─┘┴┘└┘└─┘
  struct yaksha_macros : public yk_memory_manager,
                         public macro_processor,
                         public yk_import_resolver {
    yaksha_macros();
    ~yaksha_macros() override;
    yaksha_lisp_expr *expand(yaksha_lisp_expr *expr, yaksha_envmap *env);
    yaksha_lisp_value *create_value() override;
    yaksha_envmap *create_env() override;
    yaksha_lisp_expr *create_expr() override;
    yaksha_lisp_token *create_token() override;
    yaksha_lisp_tokenizer *create_tokenizer() override;
    yaksha_lisp_parser *create_parser(yaksha_lisp_tokenizer *dt) override;
    void init_mark_sweep() override;
    void mark(yaksha_lisp_value *value) override;
    void mark(yaksha_envmap *env) override;
    void mark(yaksha_lisp_expr *expr) override;
    void mark(yaksha_lisp_token *token) override;
    void mark(yaksha_lisp_tokenizer *tokenizer) override;
    void mark(yaksha_lisp_parser *parser) override;
    size_t sweep() override;
    void
    execute(std::string &filepath, std::vector<token *> &lisp_code,
            std::unordered_map<std::string, import_stmt *> &imports) override;
    std::vector<token *>
    expand_dsl(std::string &filepath,
               std::unordered_map<std::string, import_stmt *> &imports,
               std::string &dsl_macro_name,
               std::vector<token *> &dsl_macro_input,
               std::string imported_macro, token *macro_name) override;
    gc_pool<token> *get_yk_token_pool() override;
    void
    init_env(std::string filepath,
             std::unordered_map<std::string, import_stmt *> &imports) override;
    yaksha_envmap *
    validate_and_get_environment_root(const std::string &filepath) override;
    void gc_mark() override;
    void enable_gc() override;
    void disable_gc() override;
    void root_lock() override;
    void root_unlock() override;

private:
    bool enable_gc_{false};
    gc_pool<yaksha_lisp_value> value_pool_{};
    gc_pool<yaksha_envmap> env_pool_{};
    gc_pool<yaksha_lisp_expr> expr_pool_{};
    gc_pool<yaksha_lisp_token> token_pool_{};
    gc_pool<yaksha_lisp_parser> parser_pool_{};
    gc_pool<yaksha_lisp_tokenizer> tokenizer_pool_{};
    gc_pool<token> yk_token_pool_{};
    yaksha_envmap *builtins_root_{nullptr};
    std::unordered_map<std::string, yaksha_envmap *> roots_{};
    std::vector<token *>
    create_yaksha_tokens_from_result(const std::string &dsl_macro_name,
                                     yaksha_lisp_value *result,
                                     token *macro_name);
    std::vector<yaksha_lisp_value *>
    create_token_maps_from_yaksha_tokens(std::vector<token *> &dsl_macro_input,
                                         yaksha_envmap *env);
  };
  // ┌─┐┬─┐┬┌┐┌┌┬┐┬┌┐┌┌─┐
  // ├─┘├┬┘││││ │ │││││ ┬
  // ┴  ┴└─┴┘└┘ ┴ ┴┘└┘└─┘
  std::ostream &operator<<(std::ostream &outs, yaksha_lisp_token_type p);
  std::ostream &operator<<(std::ostream &outs, yaksha_lisp_expr_type p);
  std::ostream &operator<<(std::ostream &outs, yaksha_lisp_token *p);
  std::ostream &operator<<(std::ostream &outs, yaksha_lisp_expr *p);
  std::ostream &operator<<(std::ostream &outs, yaksha_lisp_value *p);
  std::ostream &operator<<(std::ostream &outs,
                           const std::vector<yaksha_lisp_value *> &p);
  std::ostream &operator<<(std::ostream &outs,
                           const std::vector<yaksha_lisp_expr *> &p);
  std::ostream &operator<<(std::ostream &outs, yaksha_envmap *p);
  // -- additional utilities
  inline std::vector<yaksha_lisp_value *>
  eval_args(const std::vector<yaksha_lisp_value *> &args, yaksha_envmap *env) {
    auto length = args.size();
    auto r = std::vector<yaksha_lisp_value *>{length};
    for (auto i = 0; i < length; ++i) { r[i] = env->eval(args[i]); }
    return r;
  }
}// namespace yaksha
#endif
