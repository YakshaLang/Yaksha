// yaksha_lisp.cpp
#include "yaksha_lisp.h"
#include "ast/ast.h"
#include "tokenizer/tokenizer.h"
#include "utilities/cpp_util.h"
#include "utilities/human_id.h"
#include "yaksha_lisp/prelude.h"
#include "yaksha_lisp/yaksha_lisp_builtins.h"
#include <cassert>
#include <queue>
#include <regex>
#include <utility>
#ifdef YAKSHA_DEBUG
#define YAKSHA_LISP_EVAL_DEBUG_IS_PRINTED
#endif
using namespace yaksha;
// ----------------------------------------
// YakshaLisp Tokenizer
// ----------------------------------------
yaksha_lisp_tokenizer::yaksha_lisp_tokenizer(yk_memory_manager *mm) : mm_(mm) {}
yaksha_lisp_tokenizer::~yaksha_lisp_tokenizer() = default;
void yaksha_lisp_tokenizer::tokenize(std::string file, std::string code,
                                     gc_pool<token> *token_pool) {
  file_ = file;
  auto tok = tokenizer{std::move(file), std::move(code), token_pool};
  tok.tokenize();
  if (!tok.errors_.empty()) {
    for (auto &e : tok.errors_) { errors_.emplace_back(e); }
    return;
  }
  process_yk_tokens(tok);
}
void yaksha_lisp_tokenizer::tokenize(std::string file,
                                     std::vector<token *> &tokens) {
  file_ = std::move(file);
  convert_tokens(tokens);
}
void yaksha_lisp_tokenizer::process_yk_tokens(tokenizer &tok) {
  convert_tokens(tok.tokens_);
}
void yaksha_lisp_tokenizer::convert_tokens(std::vector<token *> &tokens) {
  for (auto t : tokens) {
    if (!consider_token(t)) { break; }
  }
  inject_eof();
}
void yaksha_lisp_tokenizer::inject_eof() {
  if (tokens_.empty() ||
      tokens_.back()->type_ != yaksha_lisp_token_type::YAKSHA_LISP_EOF) {
    auto eof_token = mm_->create_token();
    eof_token->type_ = yaksha_lisp_token_type::YAKSHA_LISP_EOF;
    tokens_.emplace_back(eof_token);
  }
}
bool yaksha_lisp_tokenizer::consider_token(token *t) {
  // Discard whitespace, comments and newlines
  if (t->type_ == token_type::NEW_LINE || t->type_ == token_type::INDENT ||
      t->type_ == token_type::COMMENT || t->type_ == token_type::BA_INDENT ||
      t->type_ == token_type::BA_DEDENT) {
    return true;
  }
  auto dt = mm_->create_token();
  dt->file_ = t->file_;
  dt->line_ = t->line_;
  dt->pos_ = t->pos_;
  dt->token_ = t->token_;
  dt->type_ = identify_token_type(*t, dt);
  if (!errors_.empty()) { return false; }
  // Handle :: token
  if (!tokens_.empty() && dt->type_ == yaksha_lisp_token_type::COLON &&
      tokens_.back()->type_ == yaksha_lisp_token_type::COLON &&
      tokens_.back()->line_ == t->line_ &&
      tokens_.back()->pos_ + 1 == dt->pos_) {
    tokens_.back()->type_ = yaksha_lisp_token_type::DOUBLE_COLON;
    tokens_.back()->token_ = "::";
    return true;
  }
  handle_numbers(dt);
  tokens_.emplace_back(dt);
  return true;
}
void yaksha_lisp_tokenizer::handle_numbers(yaksha_lisp_token *dt) {
  if (dt->type_ == yaksha_lisp_token_type::NUMBER && !tokens_.empty()) {
    auto prev = tokens_.back();
    // Handle negative numbers  -1 << this is negative but - 1 is not
    if (prev->type_ == yaksha_lisp_token_type::SYMBOL && prev->token_ == "-") {
      if (prev->line_ == dt->line_ && prev->pos_ + 1 == dt->pos_) {
        dt->token_ = "-" + dt->token_;
        tokens_.pop_back();
      }
    }
  }
  if (dt->type_ == yaksha_lisp_token_type::NUMBER &&
      dt->token_.find("i32") != std::string::npos) {
    dt->token_ = dt->token_.substr(0, dt->token_.size() - 3);
  }
}
yaksha_lisp_token_type
yaksha_lisp_tokenizer::identify_token_type(token &token,
                                           yaksha_lisp_token *dt) {
  if (token.type_ == yaksha::token_type::PAREN_OPEN) {
    return yaksha_lisp_token_type::PAREN_OPEN;
  } else if (token.type_ == yaksha::token_type::PAREN_CLOSE) {
    return yaksha_lisp_token_type::PAREN_CLOSE;
  } else if (token.type_ == yaksha::token_type::CURLY_BRACKET_OPEN) {
    return yaksha_lisp_token_type::CURLY_OPEN;
  } else if (token.type_ == yaksha::token_type::CURLY_BRACKET_CLOSE) {
    return yaksha_lisp_token_type::CURLY_CLOSE;
  } else if (token.type_ == yaksha::token_type::AT) {
    return yaksha_lisp_token_type::AT;
  } else if (token.type_ == yaksha::token_type::COLON) {
    return yaksha_lisp_token_type::COLON;
  } else if (token.type_ == yaksha::token_type::COMMA) {
    return yaksha_lisp_token_type::COMMA;
  } else if (token.type_ == yaksha::token_type::INTEGER_DECIMAL) {
    return yaksha_lisp_token_type::NUMBER;
  } else if (token.type_ == yaksha::token_type::STRING ||
             token.type_ == yaksha::token_type::THREE_QUOTE_STRING) {
    return yaksha_lisp_token_type::STRING;
  } else if (token.type_ == yaksha::token_type::END_OF_FILE) {
    return yaksha_lisp_token_type::YAKSHA_LISP_EOF;
  } else if (token.type_ == yaksha::token_type::SQUARE_BRACKET_CLOSE ||
             token.type_ == yaksha::token_type::SQUARE_BRACKET_OPEN) {
    errors_.emplace_back(
        "'[', ']' tokens are reserved, and not supported at the moment.",
        dt->file_, dt->line_, dt->pos_);
  } else if (!is_number_token(token.type_)) {
    return yaksha_lisp_token_type::SYMBOL;
  } else {
    errors_.emplace_back("Invalid token", dt->file_, dt->line_, dt->pos_);
  }
  return yaksha_lisp_token_type::INVALID;
}
yaksha_lisp_tokenizer::yaksha_lisp_tokenizer() : mm_{nullptr} {}
void yaksha_lisp_tokenizer::clean_state() {
  this->mm_ = nullptr;
  this->tokens_.clear();
  this->errors_.clear();
  this->file_ = "";
}
// ----------------------------------------
// YakshaLisp Parser
// ----------------------------------------
yaksha_lisp_parser::yaksha_lisp_parser(yaksha_lisp_tokenizer *dt,
                                       yk_memory_manager *mm)
    : dt_(dt), mm_(mm) {}
yaksha_lisp_parser::~yaksha_lisp_parser() = default;
void yaksha_lisp_parser::parse() {
  while (!is_at_end()) {
    try {
      auto de = parse_expr();
      exprs_.emplace_back(de);
    } catch (parsing_error &e) {
      // Skip an element and see if we can parse as possible
      advance();
    }
  }
}
yaksha_lisp_expr *yaksha_lisp_parser::parse_s_expr() {
  auto paren = previous();
  auto de = create_expr();
  de->type_ = yaksha_lisp_expr_type::S_EXPR;
  de->token_ = paren;
  while (!check(yaksha_lisp_token_type::PAREN_CLOSE)) {
    auto e = parse_expr();
    de->list_.emplace_back(e);
  }
  auto close_paren =
      consume(yaksha_lisp_token_type::PAREN_CLOSE, "Expected ')'");
  de->close_token_ = close_paren;
  return de;
}
yaksha_lisp_expr *yaksha_lisp_parser::parse_q_expr() {
  auto curly = previous();
  auto de = create_expr();
  de->type_ = yaksha_lisp_expr_type::Q_EXPR;
  de->token_ = curly;
  while (!check(yaksha_lisp_token_type::CURLY_CLOSE)) {
    auto e = parse_expr();
    de->list_.emplace_back(e);
  }
  auto close_curly =
      consume(yaksha_lisp_token_type::CURLY_CLOSE, "Expected '}'");
  de->close_token_ = close_curly;
  return de;
}
yaksha_lisp_expr *yaksha_lisp_parser::parse_terminal() {
  auto token = peek();
  if (token->type_ != yaksha_lisp_token_type::NUMBER &&
      token->type_ != yaksha_lisp_token_type::STRING &&
      token->type_ != yaksha_lisp_token_type::SYMBOL) {
    throw error(token, "Expected a terminal");
  }
  // syntax sugar. symbol1::[symbol2|string] --> (. symbol1 symbol2|string)
  if (token->type_ == yaksha_lisp_token_type::SYMBOL && has_next() &&
      has_next_next()) {
    auto double_colon_token = peek_next();
    auto attr_token = peek_next_next();
    if (double_colon_token->type_ == yaksha_lisp_token_type::DOUBLE_COLON &&
        (attr_token->type_ == yaksha_lisp_token_type::SYMBOL ||
         attr_token->type_ == yaksha_lisp_token_type::STRING)) {
      // seems like symbol::[symbol|string]
      if (token->line_ == double_colon_token->line_ &&
          double_colon_token->line_ == attr_token->line_) {
        // elements are in same line
        if (token->pos_ + token->token_.size() == double_colon_token->pos_ &&
            double_colon_token->pos_ + 2 == attr_token->pos_) {
          // elements are in consecutive positions
          // ---------
          // create expression object, so we can create the s-expr
          auto dot_access_expr = create_expr();
          // create ( token
          dot_access_expr->token_ = mm_->create_token();
          dot_access_expr->token_->type_ = yaksha_lisp_token_type::PAREN_OPEN;
          dot_access_expr->token_->token_ = "(";
          dot_access_expr->token_->line_ = double_colon_token->line_;
          dot_access_expr->token_->pos_ = double_colon_token->pos_;
          dot_access_expr->token_->file_ = double_colon_token->file_;
          // create ) token
          dot_access_expr->close_token_ = mm_->create_token();
          dot_access_expr->close_token_->type_ =
              yaksha_lisp_token_type::PAREN_CLOSE;
          dot_access_expr->close_token_->line_ = double_colon_token->line_;
          dot_access_expr->close_token_->pos_ = double_colon_token->pos_;
          dot_access_expr->close_token_->token_ = ")";
          dot_access_expr->close_token_->file_ = double_colon_token->file_;
          // create . token
          auto dot_token = mm_->create_token();
          dot_token->type_ = yaksha_lisp_token_type::SYMBOL;
          dot_token->line_ = double_colon_token->line_;
          dot_token->pos_ = double_colon_token->pos_;
          dot_token->token_ = "magic_dot";
          dot_token->file_ = double_colon_token->file_;
          // create (. symbol1 symbol2|string)
          dot_access_expr->type_ = yaksha_lisp_expr_type::S_EXPR;
          dot_access_expr->list_.clear();
          dot_access_expr->list_.emplace_back(
              create_terminal_expr_from_token(dot_token));
          dot_access_expr->list_.emplace_back(
              create_terminal_expr_from_token(token));
          dot_access_expr->list_.emplace_back(
              create_terminal_expr_from_token(attr_token));
          // symbol1 :: [symbol2|string]
          advance();
          advance();
          advance();
          return dot_access_expr;
        }
      }
    }
  }
  advance();
  return create_terminal_expr_from_token(token);
}
yaksha_lisp_expr *
yaksha_lisp_parser::create_terminal_expr_from_token(yaksha_lisp_token *token) {
  auto de = create_expr();
  de->type_ = yaksha_lisp_expr_type::TERMINAL;
  de->token_ = token;
  if (token->type_ == yaksha_lisp_token_type::STRING) {
    de->token_->token_ = string_utils::unescape(token->token_);
  }
  de->close_token_ = de->token_;
  return de;
}
yaksha_lisp_expr *yaksha_lisp_parser::parse_expr() {
  if (match({yaksha_lisp_token_type::PAREN_OPEN})) { return parse_s_expr(); }
  if (match({yaksha_lisp_token_type::CURLY_OPEN})) { return parse_q_expr(); }
  // @{a: 1, b: 2, c} // <--- c will have a value of c (similar to ES6)
  // @{} is an empty map
  if (match({yaksha_lisp_token_type::AT})) { return parse_map_literal(); }
  return parse_terminal();
}
yaksha_lisp_expr *yaksha_lisp_parser::parse_map_literal() {
  auto at = previous();
  consume(yaksha_lisp_token_type::CURLY_OPEN, "Expected '{'");
  auto de = create_expr();
  de->type_ = yaksha_lisp_expr_type::MAP_LITERAL;
  de->token_ = at;
  if (!check(yaksha_lisp_token_type::CURLY_CLOSE)) {
    do {
      auto key = parse_terminal();
      yaksha_lisp_expr *value = nullptr;
      auto maybe_colon = peek();
      if (maybe_colon->type_ == yaksha_lisp_token_type::COMMA ||
          maybe_colon->type_ == yaksha_lisp_token_type::CURLY_CLOSE) {
        value = key;
      } else {
        consume(yaksha_lisp_token_type::COLON, "Expected ':'");
        value = parse_expr();
      }
      // add key, value to the list, so we can iterate over it later and create an environment
      de->list_.emplace_back(key);
      de->list_.emplace_back(value);
    } while (match({yaksha_lisp_token_type::COMMA}));
  }
  auto close_curly =
      consume(yaksha_lisp_token_type::CURLY_CLOSE, "Expected '}'");
  de->close_token_ = close_curly;
  return de;
}
yaksha_lisp_expr *yaksha_lisp_parser::create_expr() {
  return mm_->create_expr();
}
yaksha_lisp_token *yaksha_lisp_parser::advance() {
  if (!is_at_end()) { current_++; }
  return previous();
}
yaksha_lisp_token *yaksha_lisp_parser::recede() {
  if (current_ != 0) { current_--; }
  return peek();
}
bool yaksha_lisp_parser::is_at_end() {
  return current_ + 1 >= dt_->tokens_.size() ||
         peek()->type_ == yaksha_lisp_token_type::YAKSHA_LISP_EOF;
}
yaksha_lisp_token *yaksha_lisp_parser::peek() { return dt_->tokens_[current_]; }
yaksha_lisp_token *yaksha_lisp_parser::previous() {
  assert(current_ > 0);
  return dt_->tokens_[current_ - 1];
}
bool yaksha_lisp_parser::match(
    std::initializer_list<yaksha_lisp_token_type> types) {
  return std::any_of(types.begin(), types.end(),
                     [this](yaksha_lisp_token_type t) {
                       if (this->check(t)) {
                         this->advance();
                         return true;
                       }
                       return false;
                     });
}
bool yaksha_lisp_parser::check(yaksha_lisp_token_type t) {
  if (is_at_end()) { return false; }
  return peek()->type_ == t;
}
yaksha_lisp_token *yaksha_lisp_parser::consume(yaksha_lisp_token_type t,
                                               const std::string &message) {
  if (check(t)) return advance();
  throw error(peek(), message);
}
parsing_error yaksha_lisp_parser::error(yaksha_lisp_token *tok,
                                        const std::string &message) {
  auto err = parsing_error{message, tok->file_, tok->line_, tok->pos_};
  errors_.push_back(err);
  return err;
}
yaksha_lisp_token *
yaksha_lisp_parser::consume_or_eof(yaksha_lisp_token_type t,
                                   const std::string &message) {
  if (check(t)) return advance();
  if (is_at_end()) return peek();
  throw error(peek(), message);
}
void yaksha_lisp_parser::print() {
  // print all expressions
  for (auto &e : exprs_) { print_exp(e); }
}
void yaksha_lisp_parser::print_exp(yaksha_lisp_expr *exp) {
  std::cout << exp << std::endl;
}
yaksha_lisp_parser::yaksha_lisp_parser() : mm_{nullptr}, dt_{nullptr} {}
bool yaksha_lisp_parser::has_prev_prev() { return current_ > 1; }
yaksha_lisp_token *yaksha_lisp_parser::peek_prev_prev() {
  assert(current_ > 1);
  return dt_->tokens_[current_ - 2];
}
bool yaksha_lisp_parser::has_previous() { return current_ > 0; }
bool yaksha_lisp_parser::has_next_next() {
  return !(current_ + 3 >= dt_->tokens_.size() ||
           dt_->tokens_[current_ + 2]->type_ ==
               yaksha_lisp_token_type::YAKSHA_LISP_EOF);
}
yaksha_lisp_token *yaksha_lisp_parser::peek_next_next() {
  return dt_->tokens_[current_ + 2];
}
bool yaksha_lisp_parser::has_next() {
  return !(current_ + 2 >= dt_->tokens_.size() ||
           dt_->tokens_[current_ + 1]->type_ ==
               yaksha_lisp_token_type::YAKSHA_LISP_EOF);
}
yaksha_lisp_token *yaksha_lisp_parser::peek_next() {
  return dt_->tokens_[current_ + 1];
}
void yaksha_lisp_parser::clean_state() {
  this->mm_ = nullptr;
  this->dt_ = nullptr;
  this->exprs_.clear();
  this->errors_.clear();
  this->current_ = 0;
}
// ----------------------------------------
// Internals
// ----------------------------------------
yaksha_envmap::yaksha_envmap(yaksha_envmap *parent, yk_memory_manager *pool)
    : parent_(parent), symbols_{}, mm_{pool} {}
yaksha_envmap::yaksha_envmap(yk_memory_manager *pool)
    : parent_(nullptr), symbols_{}, mm_{pool} {}
yaksha_envmap::yaksha_envmap() : parent_(nullptr), symbols_{}, mm_{nullptr} {}
yaksha_envmap::~yaksha_envmap() = default;
yaksha_lisp_value *yaksha_envmap::get_internal(const std::string &symbol) {
  if (symbols_.find(symbol) != symbols_.end()) { return symbols_[symbol]; }
  if (parent_ != nullptr) {
    auto v = parent_->get(symbol);
    if (v != nullptr) { return v; }
  }
  auto closure = peek_closure();
  if (closure != nullptr && closure != this) {
    auto val = closure->get(symbol);
    if (val != nullptr) { return val; }
  }
  return nullptr;
}
yaksha_lisp_value *yaksha_envmap::get(const std::string &symbol) {
#ifdef YAKSHA_LISP_EVAL_DEBUG_IS_PRINTED
  auto v = get_internal(symbol);
  if (v == nullptr) {
    std::cout << indent_ << ">>> "
              << "env(" << this << ")." << symbol << " -> "
              << "NULL" << std::endl;
  } else {
    std::cout << indent_ << ">>> "
              << "env(" << this << ")." << symbol << " -> " << v << std::endl;
  }
  return v;
#else
  return get_internal(symbol);
#endif
}
void yaksha_envmap::set(const std::string &symbol, yaksha_lisp_value *value) {
  this->set(symbol, value, true);
}
void yaksha_envmap::set(const std::string &symbol, yaksha_lisp_value *value,
                        bool defining) {
  if (locked_down_env_) {
    throw parsing_error{"cannot mutate locked down environment", "", 0, 0};
  }
  LOG_COMP("not locked can try setting to this env");
#ifdef YAKSHA_LISP_EVAL_DEBUG_IS_PRINTED
  std::cout << indent_ << ">>> "
            << "env(" << this << ")." << symbol << " = " << value << std::endl;
#endif
  // Define if not defined
  // Do not define in closure, only in current env
  if (defining) {
    define_internal(symbol, value);
    return;
  }
  setq_internal(symbol, value);
}
void yaksha_envmap::setq_internal(const std::string &symbol,
                                  yaksha_lisp_value *value) {
  if (symbols_.find(symbol) != symbols_.end()) {
    symbols_[symbol] = value;
    LOG_COMP("set successful: " << symbol);
    return;
  }
  std::queue<yaksha_envmap *> queue{};
  auto closure = peek_closure();
  if (parent_ != nullptr) { queue.push(parent_); }
  if (closure != nullptr) { queue.push(closure); }
  bool lock_down_triggered = false;
  while (!queue.empty() && !lock_down_triggered) {
    yaksha_envmap *c = queue.front();
    queue.pop();
    if (c == this) { continue; }
    if (c->symbols_.find(symbol) != c->symbols_.end()) {
      if (c->locked_down_env_) {
        LOG_COMP("trying to mutate builtin (failed): " << symbol);
        lock_down_triggered = true;
        break;
      }
      c->symbols_[symbol] = value;
      LOG_COMP("set successful: " << symbol);
      return;
    } else {
      if (c->parent_ != nullptr) { queue.push(c->parent_); }
      auto c_closure = c->peek_closure();
      if (c_closure != nullptr) { queue.push(c_closure); }
    }
  }
  if (lock_down_triggered) {
    throw parsing_error{"cannot mutate locked down environment", "", 0, 0};
  } else {
    throw parsing_error("symbol not defined: " + symbol, "", 0, 0);
  }
}
void yaksha_envmap::define_internal(const std::string &symbol,
                                    yaksha_lisp_value *value) {
  LOG_COMP("is it defined: " << symbol);
  if (symbols_.find(symbol) == symbols_.end()) {
    symbols_[symbol] = value;// insert
    return;
    LOG_COMP("defined: " << symbol);
  }
  throw parsing_error{"symbol already defined: " + symbol, "", 0, 0};
}
yaksha_envmap *yaksha_envmap::spawn() {
  auto de = mm_->create_env();
  de->cleanup();
  de->parent_ = this;
  de->mm_ = mm_;
  de->ir_ = ir_;
  return de;
}
yaksha_envmap *yaksha_envmap::get_parent() const { return parent_; }
yk_memory_manager *yaksha_envmap::get_memory_manager() const { return mm_; }
const std::unordered_map<std::string, yaksha_lisp_value *> &
yaksha_envmap::get_symbols() const {
  return symbols_;
}
yaksha_lisp_value *yaksha_envmap::create_number(std::int64_t num) {
  auto v = create_val();
  v->type_ = yaksha_lisp_value_type::NUMBER;
  v->num_ = num;
  return v;
}
yaksha_lisp_value *yaksha_envmap::create_string(const std::string &str) {
  auto v = create_val();
  v->type_ = yaksha_lisp_value_type::STRING;
  v->str_ = str;
  return v;
}
yaksha_lisp_value *yaksha_envmap::create_expr_val(yaksha_lisp_expr *exp) {
  auto v = create_val();
  v->type_ = yaksha_lisp_value_type::EXPR;
  v->expr_ = exp;
  return v;
}
yaksha_lisp_value *yaksha_envmap::create_val() { return mm_->create_value(); }
yaksha_lisp_value *
yaksha_envmap::eval(const std::vector<yaksha_lisp_expr *> &expressions_) {
#ifdef GC_POOL_DEBUG
  std::cout << ">>======= begin " << identifier_ << " =========" << std::endl;
#endif
  yaksha_lisp_value *last = nullptr;
  for (auto exp : expressions_) {
    yaksha_lisp_value *prev = last;
#ifdef GC_POOL_DEBUG
    std::cout << ">>======= exec " << identifier_ << " =========" << std::endl;
    std::cout << ">>======= " << exp << " =========" << std::endl;
#endif
    last = eval(exp);
    mm_->gc_mark();
    for (auto exp_i : expressions_) { exp_i->gc_mark(mm_); }
    if (prev != nullptr) { prev->gc_mark(mm_); }
    if (last != nullptr) { last->gc_mark(mm_); }
    mm_->sweep();
  }
#ifdef GC_POOL_DEBUG
  std::cout << ">>======= end " << identifier_ << " =========" << std::endl;
#endif
  if (last == nullptr) { return create_nil(); }
  return last;
}
yaksha_lisp_value *yaksha_envmap::eval_internal(yaksha_lisp_expr *exp) {
  if (exp->type_ == yaksha_lisp_expr_type::TERMINAL) {
    if (exp->token_->type_ == yaksha_lisp_token_type::NUMBER) {
      return create_number(std::stoll(exp->token_->token_));
    }
    if (exp->token_->type_ == yaksha_lisp_token_type::STRING) {
      return create_string(exp->token_->token_);
    }
    if (exp->token_->type_ == yaksha_lisp_token_type::SYMBOL) {
      auto v = get(exp->token_->token_);
      if (v == nullptr) {
        throw parsing_error{"unknown symbol: " + exp->token_->token_,
                            exp->token_->file_, exp->token_->line_,
                            exp->token_->pos_};
      }
      return v;
    }
    throw parsing_error{"unsupported terminal type", exp->token_->file_,
                        exp->token_->line_, exp->token_->pos_};
  }
  if (exp->type_ == yaksha_lisp_expr_type::MAP_LITERAL) {
    auto val = create_val();
    val->type_ = yaksha_lisp_value_type::MAP;
    val->closure_ = mm_->create_env();
    for (size_t i = 0; i < exp->list_.size(); i += 2) {
      auto key = exp->list_[i];
      if (key->type_ == yaksha_lisp_expr_type::TERMINAL &&
          (key->token_->type_ == yaksha_lisp_token_type::SYMBOL ||
           key->token_->type_ == yaksha_lisp_token_type::STRING ||
           key->token_->type_ == yaksha_lisp_token_type::NUMBER)) {
        auto value = eval(exp->list_[i + 1]);
        val->closure_->set_map(create_string(key->token_->token_), value);
      } else {
        throw parsing_error{"invalid map key", key->token_->file_,
                            key->token_->line_, key->token_->pos_};
      }
    }
    return val;
  }
  if (exp->type_ == yaksha_lisp_expr_type::S_EXPR) {
    if (exp->list_.empty()) {
      throw parsing_error{"empty S-Expression", exp->token_->file_,
                          exp->token_->line_, exp->token_->pos_};
    }
    auto symbol = create_expr_val(exp->list_.front());
    auto cur = exp->list_.begin() + 1;
    auto end = exp->list_.end();
    auto arg_vals = std::vector<yaksha_lisp_value *>{};
    while (cur != end) {
      arg_vals.emplace_back(create_expr_val(*cur));
      ++cur;
    }
    return eval_call(symbol, arg_vals);
  }
  // Q-EXPR
  auto val = create_val();
  val->type_ = yaksha_lisp_value_type::LIST;
  for (auto e : exp->list_) { val->list_.emplace_back(create_expr_val(e)); }
  return val;
}
yaksha_lisp_value *yaksha_envmap::eval(yaksha_lisp_expr *exp) {
  try {
#ifdef YAKSHA_LISP_EVAL_DEBUG_IS_PRINTED
    increase_indent();
    auto result = eval_internal(exp);
    decrease_indent();
    std::cout << indent_ << ">>> " << exp << " -> " << result << std::endl;
    return result;
#else
    return eval_internal(exp);
#endif
  } catch (const parsing_error &raised_error) {
    if (!(raised_error.tok_.line_ == 0 && raised_error.tok_.pos_ == 0)) {
      throw;
    }
    // enrich exception!
    throw parsing_error{raised_error.message_, exp->token_->file_,
                        exp->token_->line_, exp->token_->pos_};
  }
}
yaksha_lisp_value *yaksha_envmap::eval_internal(yaksha_lisp_value *val_) {
  if (val_->type_ == yaksha_lisp_value_type::STRING ||
      val_->type_ == yaksha_lisp_value_type::NUMBER ||
      val_->type_ == yaksha_lisp_value_type::LIST ||
      val_->type_ == yaksha_lisp_value_type::BUILTIN ||
      val_->type_ == yaksha_lisp_value_type::LAMBDA ||
      val_->type_ == yaksha_lisp_value_type::MAP ||
      val_->type_ == yaksha_lisp_value_type::METAMACRO ||
      val_->type_ == yaksha_lisp_value_type::MODULE) {
    return val_;
  }
  return eval(val_->expr_);
}
yaksha_lisp_value *yaksha_envmap::eval(yaksha_lisp_value *val_) {
  return eval_internal(val_);
}
yaksha_lisp_value *yaksha_envmap::eval_call_internal(
    yaksha_lisp_value *symbol_value,
    const std::vector<yaksha_lisp_value *> &args) {
  // This is likely the core of the language
  // This is too complicated, consider refactoring and simplifying this?
  auto callable = eval(symbol_value);
  if (callable->type_ != yaksha_lisp_value_type::BUILTIN &&
      callable->type_ != yaksha_lisp_value_type::LAMBDA &&
      callable->type_ != yaksha_lisp_value_type::METAMACRO) {
    throw parsing_error{"calling a non callable (nor metamacro): " +
                            to_string(callable),
                        "", 0, 0};
  }
  // builtins do not care about closures
  if (callable->type_ == yaksha_lisp_value_type::BUILTIN) {
    return callable->builtin_(args, this);
  }
  // we already know params is an s-expr of symbols
  auto params_val = callable->list_[0];
  auto body = callable->list_[1];
  // get each name of params to a vector
  auto params = std::vector<std::string>{};
  auto params_actual = std::vector<std::string>{};
  for (auto p : params_val->expr_->list_) {
    params.emplace_back(p->token_->token_);
  }
  auto param_len = params.size();
  for (std::size_t j = 1; j < param_len + 1; j++) {
    int i = (int) j - 1;
    if (params[i] == "&" && i != param_len - 2) {
      throw parsing_error{"& must be present only as penultimate param: " +
                              callable->str_,
                          "", 0, 0};
    }
    if (params[i] != "&") { params_actual.emplace_back(params[i]); }
  }
  // check if args count is correct
  bool variadic = params.size() > 1 && params[param_len - 2] == "&";
  if (variadic) {
    if (args.size() + 1 < params_actual.size()) {
      throw parsing_error{"too few arguments: " + callable->str_, "", 0, 0};
    }
  } else {
    if (args.size() != params_actual.size()) {
      throw parsing_error{"wrong number of arguments: " + callable->str_, "", 0,
                          0};
    }
  }
  // Always evaluate args in current env
  std::vector<yaksha_lisp_value *> e_args;
  if (callable->type_ == yaksha_lisp_value_type::METAMACRO) {
    e_args = args;
  } else {
    e_args = eval_args(args, this);
  }
  yaksha_envmap *child_scope;
  if (callable->foreign_) {
    child_scope = callable->foreign_env_->spawn();
  } else {
    child_scope = spawn();
  }
  for (std::size_t i = 1; i < params_actual.size(); i++) {
    child_scope->set(params_actual[i - 1], e_args[i - 1]);
  }
  if (variadic && !params_actual.empty()) {
    auto last_param = params_actual.back();
    auto variadic_args = std::vector<yaksha_lisp_value *>{};
    for (std::size_t i = params_actual.size(); i < args.size() + 1; i++) {
      variadic_args.emplace_back(e_args[i - 1]);
    }
    auto v = create_val();
    v->type_ = yaksha_lisp_value_type::LIST;
    v->list_ = variadic_args;
    child_scope->set(last_param, v);
  } else if (!params_actual.empty()) {
    auto last_param = params_actual.back();
    child_scope->set(last_param, e_args.back());
  }
  child_scope->push_closure(callable->closure_);
  yaksha_lisp_value *last_val = nullptr;
  for (auto e : body->list_) { last_val = child_scope->eval(e); }
  if (last_val == nullptr) { return create_nil(); }
  yaksha_lisp_value *result = last_val;
  // Always eval metamacro result in same env it was executed?
  if (callable->type_ == yaksha_lisp_value_type::METAMACRO) {
    if (last_val->type_ != yaksha_lisp_value_type::LIST) {
      throw parsing_error{"metamacro must return a list", "", 0, 0};
    }
    result = create_nil();
    for (auto &x : last_val->list_) {
      result = child_scope->parent_->eval(x);
      // ensure we eval in parent of child> foreign scope or current scope!
      // this means imported meta macros cannot capture locals?
      // TODO revisit this!
    }
  }
  return result;
}
yaksha_lisp_value *
yaksha_envmap::eval_call(yaksha_lisp_value *symbol_value,
                         const std::vector<yaksha_lisp_value *> &args) {
#ifdef YAKSHA_LISP_EVAL_DEBUG_IS_PRINTED
  increase_indent();
  auto result = eval_call_internal(symbol_value, args);
  decrease_indent();
  std::cout << indent_ << ">>> (" << symbol_value << " " << args << ")"
            << " -> " << result << std::endl;
  return result;
#else
  return eval_call_internal(symbol_value, args);
#endif
}
yaksha_lisp_value *yaksha_envmap::create_nil() {
  auto v = create_val();
  v->type_ = yaksha_lisp_value_type::LIST;
  return v;
}
bool yaksha_envmap::is_truthy(yaksha_lisp_value *val) {
  if (val->type_ == yaksha_lisp_value_type::NUMBER) { return val->num_ != 0; }
  if (val->type_ == yaksha_lisp_value_type::STRING) {
    return !val->str_.empty();
  }
  if (val->type_ == yaksha_lisp_value_type::LIST) {
    return !val->list_.empty();
  }
  if (val->type_ == yaksha_lisp_value_type::MAP) {
    return !val->closure_->symbols_.empty();
  }
  return false;
}
static yaksha_lisp_value *
create_builtin(yaksha_envmap *env, const std::string &name,
               yaksha_lisp_builtin_callable builtin_callable) {
  auto v = env->create_val();
  v->type_ = yaksha_lisp_value_type::BUILTIN;
  v->builtin_ = builtin_callable;
  v->str_ = name;
  return v;
}
#if (_WIN32 || _WIN64)
#define T_NEWLINE "\r\n"
#else
#define T_NEWLINE "\n"
#endif
void yaksha_envmap::setup_builtins() {
  set("nil", create_nil());
  set("true", create_number(1));
  set("false", create_number(0));
  set("newline", create_string(T_NEWLINE));
  set("+", create_builtin(this, "+", yaksha_lisp_builtins::add_));
  set("-", create_builtin(this, "-", yaksha_lisp_builtins::sub_));
  set("*", create_builtin(this, "*", yaksha_lisp_builtins::mul_));
  set("/", create_builtin(this, "/", yaksha_lisp_builtins::div_));
  set("modulo", create_builtin(this, "modulo", yaksha_lisp_builtins::mod_));
  set("==", create_builtin(this, "==", yaksha_lisp_builtins::eq_));
  set("!=", create_builtin(this, "!=", yaksha_lisp_builtins::neq_));
  set("<", create_builtin(this, "<", yaksha_lisp_builtins::lt_));
  set(">", create_builtin(this, ">", yaksha_lisp_builtins::gt_));
  set("<=", create_builtin(this, "<=", yaksha_lisp_builtins::lte_));
  set(">=", create_builtin(this, ">=", yaksha_lisp_builtins::gte_));
  set("and", create_builtin(this, "and", yaksha_lisp_builtins::and_));
  set("or", create_builtin(this, "or", yaksha_lisp_builtins::or_));
  set("not", create_builtin(this, "not", yaksha_lisp_builtins::not_));
  set("if", create_builtin(this, "if", yaksha_lisp_builtins::if_));
  // def and define is the same thing :)
  set("def", create_builtin(this, "def", yaksha_lisp_builtins::def_));
  set("define", create_builtin(this, "define", yaksha_lisp_builtins::def_));
  // (= x 1) will try to set the value of x in the current env, if x is not found in the current env then it will
  // create a new symbol in the current env and set its value to 1
  set("=", create_builtin(this, "=", yaksha_lisp_builtins::setdef_));
  set("do", create_builtin(this, "do", yaksha_lisp_builtins::do_));
  set("scope", create_builtin(this, "scope", yaksha_lisp_builtins::scope_));
  set("quote", create_builtin(this, "quote", yaksha_lisp_builtins::quote_));
  set("for", create_builtin(this, "for", yaksha_lisp_builtins::for_));
  set("range", create_builtin(this, "range", yaksha_lisp_builtins::range_));
  set("while", create_builtin(this, "while", yaksha_lisp_builtins::while_));
  set("eval", create_builtin(this, "eval", yaksha_lisp_builtins::eval_));
  set("list", create_builtin(this, "list", yaksha_lisp_builtins::list_));
  set("head", create_builtin(this, "head", yaksha_lisp_builtins::head_));
  set("tail", create_builtin(this, "tail", yaksha_lisp_builtins::tail_));
  set("cons", create_builtin(this, "cons", yaksha_lisp_builtins::cons_));
  set("len", create_builtin(this, "len", yaksha_lisp_builtins::len_));
  set("push", create_builtin(this, "push", yaksha_lisp_builtins::push_));
  set("pop", create_builtin(this, "pop", yaksha_lisp_builtins::pop_));
  set("defun", create_builtin(this, "defun", yaksha_lisp_builtins::defun_));
  set("lambda", create_builtin(this, "lambda", yaksha_lisp_builtins::lambda_));
  set("print", create_builtin(this, "print", yaksha_lisp_builtins::print_));
  set("println",
      create_builtin(this, "println", yaksha_lisp_builtins::println_));
  set("raise_error",
      create_builtin(this, "raise_error", yaksha_lisp_builtins::raise_error_));
  set("try", create_builtin(this, "try", yaksha_lisp_builtins::try_));
  set("try_catch",
      create_builtin(this, "try_catch", yaksha_lisp_builtins::try_catch_));
  set("is_list",
      create_builtin(this, "is_list", yaksha_lisp_builtins::is_list_));
  set("is_string",
      create_builtin(this, "is_string", yaksha_lisp_builtins::is_string_));
  set("is_int",
      create_builtin(this, "is_number", yaksha_lisp_builtins::is_int_));
  set("is_truthy",
      create_builtin(this, "is_truthy", yaksha_lisp_builtins::is_truthy_));
  set("is_callable",
      create_builtin(this, "is_callable", yaksha_lisp_builtins::is_callable_));
  set("is_nil", create_builtin(this, "is_nil", yaksha_lisp_builtins::is_nil_));
  set("filter", create_builtin(this, "filter", yaksha_lisp_builtins::filter_));
  set("map", create_builtin(this, "map", yaksha_lisp_builtins::map_));
  set("reduce", create_builtin(this, "reduce", yaksha_lisp_builtins::reduce_));
  set("to_string",
      create_builtin(this, "to_string", yaksha_lisp_builtins::to_string_));
  set("to_int", create_builtin(this, "to_int", yaksha_lisp_builtins::to_int_));
  set("io_read_file",
      create_builtin(this, "io_read_file", yaksha_lisp_builtins::read_file_));
  set("io_write_file",
      create_builtin(this, "io_write_file", yaksha_lisp_builtins::write_file_));
  set("input", create_builtin(this, "input", yaksha_lisp_builtins::input_));
  set("random", create_builtin(this, "random", yaksha_lisp_builtins::random_));
  set("time", create_builtin(this, "time", yaksha_lisp_builtins::time_));
  set("insert", create_builtin(this, "insert", yaksha_lisp_builtins::insert_));
  set("remove", create_builtin(this, "remove", yaksha_lisp_builtins::remove_));
  set("parse", create_builtin(this, "parse", yaksha_lisp_builtins::parse_));
  set("bitwise_and",
      create_builtin(this, "bitwise_and", yaksha_lisp_builtins::bitwise_and_));
  set("bitwise_or",
      create_builtin(this, "bitwise_or", yaksha_lisp_builtins::bitwise_or_));
  set("bitwise_xor",
      create_builtin(this, "bitwise_xor", yaksha_lisp_builtins::bitwise_xor_));
  set("bitwise_not",
      create_builtin(this, "bitwise_not", yaksha_lisp_builtins::bitwise_not_));
  set("bitwise_left_shift",
      create_builtin(this, "bitwise_left_shift",
                     yaksha_lisp_builtins::bitwise_left_shift_));
  set("bitwise_right_shift",
      create_builtin(this, "bitwise_right_shift",
                     yaksha_lisp_builtins::bitwise_right_shift_));
  // set builtin will update the value of a symbol in the current scope or parent scope(s)
  // as long as the symbol is defined
  set("set", create_builtin(this, "set", yaksha_lisp_builtins::set_));
  set("index", create_builtin(this, "index", yaksha_lisp_builtins::index_));
  set("map_get",
      create_builtin(this, "map_get", yaksha_lisp_builtins::map_get_));
  set("map_set",
      create_builtin(this, "map_set", yaksha_lisp_builtins::map_set_));
  set("map_remove",
      create_builtin(this, "map_remove", yaksha_lisp_builtins::map_remove_));
  set("map_keys",
      create_builtin(this, "map_keys", yaksha_lisp_builtins::map_keys_));
  set("map_values",
      create_builtin(this, "map_values", yaksha_lisp_builtins::map_values_));
  set("map_has",
      create_builtin(this, "map_has", yaksha_lisp_builtins::map_has_));
  set("this", create_builtin(this, "this", yaksha_lisp_builtins::this_));
  set("parent", create_builtin(this, "parent", yaksha_lisp_builtins::parent_));
  set("repr", create_builtin(this, "repr", yaksha_lisp_builtins::repr_));
  set("cond", create_builtin(this, "cond", yaksha_lisp_builtins::cond_));
  set("ghost", create_builtin(this, "ghost", yaksha_lisp_builtins::ghost_));
  set("metamacro",
      create_builtin(this, "metamacro", yaksha_lisp_builtins::metamacro_));
  set("is_metamacro", create_builtin(this, "is_metamacro",
                                     yaksha_lisp_builtins::is_metamacro_));
  set("is_module",
      create_builtin(this, "is_module", yaksha_lisp_builtins::is_module_));
  set("access_module", create_builtin(this, "access_module",
                                      yaksha_lisp_builtins::access_module_));
  // magic_dot -> map_get or access_module
  set("magic_dot",
      create_builtin(this, "magic_dot", yaksha_lisp_builtins::magic_dot_));
  // ---
  set("system_enable_gc",
      create_builtin(this, "system_enable_gc", yaksha_lisp_builtins::system_enable_gc_));
  set("system_disable_gc",
      create_builtin(this, "system_disable_gc", yaksha_lisp_builtins::system_disable_gc_));
  set("system_lock_current_scope",
      create_builtin(this, "system_lock_current_scope", yaksha_lisp_builtins::system_lock_current_scope_));
  set("system_unlock_current_scope",
      create_builtin(this, "system_unlock_current_scope", yaksha_lisp_builtins::system_unlock_current_scope_));
  builtins_created_ = true;
}
void yaksha_envmap::push_closure(yaksha_envmap *env) {
  closures_.push_back(env);
}
void yaksha_envmap::pop_closure() {
  if (closures_.empty()) { return; }
  closures_.pop_back();
}
yaksha_envmap *yaksha_envmap::peek_closure() {
  if (closures_.empty()) { return nullptr; }
  return closures_.back();
}
std::string yaksha_envmap::to_string(yaksha_lisp_value *value) {
  std::ostringstream ss;
  ss << value;
  return ss.str();
}
void yaksha_envmap::increase_indent() { indent_ += " "; }
void yaksha_envmap::decrease_indent() {
  if (!indent_.empty()) { indent_.pop_back(); }
}
void yaksha_envmap::cleanup() {
  parent_ = nullptr;
  symbols_.clear();
  closures_.clear();
  indent_.clear();
}
bool yaksha_envmap::has_map(yaksha_lisp_value *key) {
  return has_map(derive_key(key));
}
bool yaksha_envmap::has_map(std::string key) {
  return symbols_.find(key) != symbols_.end();
}
void yaksha_envmap::set_map(yaksha_lisp_value *key, yaksha_lisp_value *value) {
  set_map(derive_key(key), value);
}
void yaksha_envmap::set_map(std::string key, yaksha_lisp_value *value) {
  if (locked_down_env_) {
    throw parsing_error{"Cannot mutate locked down environment", "", 0, 0};
  }
  symbols_[key] = value;
}
std::string yaksha_envmap::derive_key(yaksha_lisp_value *key) {
  std::string key_str;
  if (key->type_ == yaksha_lisp_value_type::STRING) {
    key_str = key->str_;
  } else if (key->type_ == yaksha_lisp_value_type::NUMBER) {
    key_str = std::to_string(key->num_);
  } else if (key->type_ == yaksha_lisp_value_type::EXPR &&
             key->expr_->type_ == yaksha_lisp_expr_type::TERMINAL &&
             key->expr_->token_->type_ == yaksha_lisp_token_type::SYMBOL) {
    key_str = key->expr_->token_->token_;
  } else {
    throw parsing_error{"Invalid key type for map", "", 0, 0};
  }
  return key_str;
}
yaksha_lisp_value *yaksha_envmap::get_map(yaksha_lisp_value *key,
                                          yaksha_lisp_value *default_value) {
  return get_map(derive_key(key), default_value);
}
yaksha_lisp_value *yaksha_envmap::get_map(std::string key,
                                          yaksha_lisp_value *default_value) {
  auto it = symbols_.find(key);
  if (it != symbols_.end()) { return it->second; }
  return default_value;
}
yaksha_lisp_value *yaksha_envmap::keys_map(yaksha_envmap *env) {
  auto result = env->create_val();
  result->type_ = yaksha_lisp_value_type::LIST;
  for (auto &i : symbols_) {
    result->list_.emplace_back(env->create_string(i.first));
  }
  return result;
}
void yaksha_envmap::remove_map(yaksha_lisp_value *key) {
  remove_map(derive_key(key));
}
void yaksha_envmap::remove_map(std::string key) {
  if (locked_down_env_) {
    throw parsing_error{"Cannot mutate locked down environment", "", 0, 0};
  }
  auto it = symbols_.find(key);
  if (it != symbols_.end()) { symbols_.erase(it); }
}
yaksha_lisp_value *yaksha_envmap::values_map(yaksha_envmap *env) {
  auto result = env->create_val();
  result->type_ = yaksha_lisp_value_type::LIST;
  for (auto &i : symbols_) { result->list_.emplace_back(i.second); }
  return result;
}
void yaksha_envmap::setup_prelude() {
  LOG_COMP("create tokenizer to parse prelude");
  auto tok = mm_->create_tokenizer();
  LOG_COMP("created tokenizer to parse prelude");
  tok->tokenize("prelude.yaksha_lisp", YAKSHA_LISP_PRELUDE,
                mm_->get_yk_token_pool());
  LOG_COMP("tokenized");
  if (!tok->errors_.empty()) {
    throw parsing_error{"prelude.yaksha_lisp failed to tokenize", "", 0, 0};
  }
  LOG_COMP("create parser parse prelude");
  auto parser = mm_->create_parser(tok);
  LOG_COMP("parsing");
  parser->parse();
  if (!parser->errors_.empty()) {
    throw parsing_error{"prelude.yaksha_lisp failed to parse", "", 0, 0};
  }
  LOG_COMP("parsed");
  // Execute prelude!
  for (auto e : parser->exprs_) {
    LOG_COMP("prelude eval: " << e);
    eval(e);
  }
  LOG_COMP("prelude initialized");
  prelude_evaluate_success_ = true;
}
void yaksha_envmap::lockdown() { this->locked_down_env_ = true; }
void yaksha_envmap::unlock() { this->locked_down_env_ = false; }
void yaksha_envmap::gc_enable() {
  if (this->mm_ != nullptr) { this->mm_->enable_gc(); }
}
void yaksha_envmap::gc_disable() {
  if (this->mm_ != nullptr) { this->mm_->disable_gc(); }
}
void yaksha_envmap::gc_mark() {
  if (get_bit(&mark_, GC_POOL_MARK_BIT)) { return; }
  mm_->mark(this);
  for (auto &kv : symbols_) { kv.second->gc_mark(mm_); }
}
void yaksha_envmap::clean_state() {
  this->parent_ = nullptr;
  this->symbols_.clear();
  this->closures_.clear();
  this->indent_.clear();
  this->identifier_.clear();
  this->mm_ = nullptr;
  this->locked_down_env_ = false;
  this->ir_ = nullptr;
}
std::ostream &operator<<(std::ostream &outs, yaksha_lisp_token_type p) {
  switch (p) {
    case yaksha_lisp_token_type::NUMBER:
      outs << "NUMBER";
      break;
    case yaksha_lisp_token_type::STRING:
      outs << "STRING";
      break;
    case yaksha_lisp_token_type::SYMBOL:
      outs << "SYMBOL";
      break;
    case yaksha_lisp_token_type::PAREN_OPEN:
      outs << "PAREN_OPEN";
      break;
    case yaksha_lisp_token_type::PAREN_CLOSE:
      outs << "PAREN_CLOSE";
      break;
    case yaksha_lisp_token_type::CURLY_OPEN:
      outs << "CURLY_OPEN";
      break;
    case yaksha_lisp_token_type::CURLY_CLOSE:
      outs << "CURLY_CLOSE";
      break;
    case yaksha_lisp_token_type::AT:
      outs << "AT_SYMBOL";
      break;
    case yaksha_lisp_token_type::YAKSHA_LISP_EOF:
      outs << "YAKSHA_LISP_EOF";
      break;
    default:
      outs << "INVALID";
      break;
  }
  return outs;
}
std::ostream &yaksha::operator<<(std::ostream &outs, yaksha_lisp_expr_type p) {
  switch (p) {
    case yaksha_lisp_expr_type::TERMINAL:
      outs << "TERMINAL";
      break;
    case yaksha_lisp_expr_type::Q_EXPR:
      outs << "Q_EXPR";
      break;
    case yaksha_lisp_expr_type::S_EXPR:
      outs << "S_EXPR";
      break;
    case yaksha_lisp_expr_type::MAP_LITERAL:
      outs << "MAP_LITERAL";
      break;
  }
  return outs;
}
std::ostream &yaksha::operator<<(std::ostream &outs, yaksha_lisp_token *p) {
#ifdef YASKSHA_LISP_PRINT_TYPE
  outs << "`";
#endif
  if (p->type_ == yaksha_lisp_token_type::STRING) {
    outs << "\"" << string_utils::escape(p->token_) << "\"";
  } else {
    outs << p->token_;
  }
#ifdef YASKSHA_LISP_PRINT_TYPE
  outs << "`";
#endif
  return outs;
}
std::ostream &yaksha::operator<<(std::ostream &outs, yaksha_lisp_expr *p) {
#ifdef YASKSHA_LISP_PRINT_TYPE
  outs << "'";
#endif
  if (p->type_ == yaksha_lisp_expr_type::TERMINAL) {
    outs << p->token_;
  } else {
    outs << p->token_ << p->list_ << p->close_token_;
  }
#ifdef YASKSHA_LISP_PRINT_TYPE
  outs << "'";
#endif
  return outs;
}
std::ostream &yaksha::operator<<(std::ostream &outs, yaksha_lisp_value *p) {
#ifdef YASKSHA_LISP_PRINT_TYPE
  outs << "<";
#endif
  if (p->type_ == yaksha_lisp_value_type::NUMBER) {
    outs << p->num_;
  } else if (p->type_ == yaksha_lisp_value_type::STRING) {
    outs << "\"" << string_utils::escape(p->str_) << "\"";
  } else if (p->type_ == yaksha_lisp_value_type::LIST) {
    outs << "{" << p->list_ << "}";
  } else if (p->type_ == yaksha_lisp_value_type::EXPR) {
    outs << p->expr_;
  } else if (p->type_ == yaksha_lisp_value_type::BUILTIN) {
    outs << "(builtin " << p->str_ << ")";
  } else if (p->type_ == yaksha_lisp_value_type::LAMBDA) {
    if (p->str_.empty()) {
      outs << "(lambda " << p->list_ << ")";
    } else {
      outs << "(defun " << p->str_ << " " << p->list_ << ")";
    }
  } else if (p->type_ == yaksha_lisp_value_type::METAMACRO) {
    outs << "(metamacro " << p->str_ << " " << p->list_ << ")";
  } else if (p->type_ == yaksha_lisp_value_type::MODULE) {
    outs << "(module " << p->str_ << ")";
  } else if (p->type_ == yaksha_lisp_value_type::MAP) {
    outs << "@{";
    bool first = true;
    for (auto &i : p->closure_->symbols_) {
      if (first) {
        first = false;
      } else {
        outs << ", ";
      }
      outs << i.first << ": " << i.second;
    }
    outs << "}";
  }
#ifdef YASKSHA_LISP_PRINT_TYPE
  outs << ">";
#endif
  return outs;
}
std::ostream &yaksha::operator<<(std::ostream &outs,
                                 const std::vector<yaksha_lisp_value *> &p) {
  bool first = true;
  for (auto &i : p) {
    if (first) {
      first = false;
    } else {
      outs << " ";
    }
    outs << i;
  }
  return outs;
}
std::ostream &yaksha::operator<<(std::ostream &outs,
                                 const std::vector<yaksha_lisp_expr *> &p) {
  bool first = true;
  for (auto &i : p) {
    if (first) {
      first = false;
    } else {
      outs << " ";
    }
    outs << i;
  }
  return outs;
}
std::ostream &yaksha::operator<<(std::ostream &outs, yaksha_envmap *p) {
  outs << "environment:" << p->identifier_;
  return outs;
}
// --------------------- YakshaLisp macros for Yaksha ---------------------
yaksha_macros::yaksha_macros() = default;
yaksha_macros::~yaksha_macros() = default;
yaksha_lisp_expr *yaksha_macros::expand(yaksha_lisp_expr *expr,
                                        yaksha_envmap *env) {
  return nullptr;
}
yaksha_lisp_value *yaksha_macros::create_value() {
  auto val = value_pool_.allocate();
  val->clean_state();
  return val;
}
yaksha_envmap *yaksha_macros::create_env() {
  auto val = env_pool_.allocate();
  val->clean_state();
  val->mm_ = this;
  val->ir_ = this;
  val->identifier_ = human_id::human_id();
  return val;
}
yaksha_lisp_expr *yaksha_macros::create_expr() {
  auto val = expr_pool_.allocate();
  val->clean_state();
  return val;
}
yaksha_lisp_token *yaksha_macros::create_token() {
  auto val = token_pool_.allocate();
  val->clean_state();
  return val;
}
void yaksha_macros::init_mark_sweep() {
  if (!enable_gc_) { return; }
  value_pool_.initialize_mark_sweep();
  env_pool_.initialize_mark_sweep();
  expr_pool_.initialize_mark_sweep();
  token_pool_.initialize_mark_sweep();
  tokenizer_pool_.initialize_mark_sweep();
  parser_pool_.initialize_mark_sweep();
}
void yaksha_macros::mark(yaksha_lisp_value *value) { value_pool_.mark(value); }
void yaksha_macros::mark(yaksha_envmap *env) { env_pool_.mark(env); }
void yaksha_macros::mark(yaksha_lisp_expr *expr) { expr_pool_.mark(expr); }
void yaksha_macros::mark(yaksha_lisp_token *token) { token_pool_.mark(token); }
size_t yaksha_macros::sweep() {
  if (!enable_gc_) { return 0; }
  size_t freed = 0;
  size_t vap = value_pool_.sweep();
#ifdef GC_POOL_DEBUG
  std::cout << "\n// GC values = " << vap << std::endl;
#endif
  size_t enp = env_pool_.sweep();
#ifdef GC_POOL_DEBUG
  std::cout << "\n// GC envs = " << enp << std::endl;
#endif
  size_t exp = expr_pool_.sweep();
#ifdef GC_POOL_DEBUG
  std::cout << "\n// GC expressions = " << exp << std::endl;
#endif
  size_t top = token_pool_.sweep();
#ifdef GC_POOL_DEBUG
  std::cout << "\n// GC tokens = " << top << std::endl;
#endif
  size_t tkp = tokenizer_pool_.sweep();
#ifdef GC_POOL_DEBUG
  std::cout << "\n// GC tokenizers = " << tkp << std::endl;
#endif
  size_t pap = parser_pool_.sweep();
#ifdef GC_POOL_DEBUG
  std::cout << "\n// GC parsers = " << pap << std::endl;
#endif
  freed = vap + enp + exp + top + tkp + pap;
#ifdef GC_POOL_DEBUG
  std::cout << "\n// GC total = " << freed << std::endl;
#endif
  return freed;
}
void yaksha_macros::execute(
    std::string &filepath, std::vector<token *> &lisp_code,
    std::unordered_map<std::string, import_stmt *> &imports) {
  yaksha_envmap *env = validate_and_get_environment_root(filepath);
  yaksha_lisp_tokenizer *dtk = this->create_tokenizer();
  dtk->tokenize(filepath, lisp_code);
  if (!dtk->errors_.empty()) {
    throw parsing_error{dtk->errors_.back().message_, "", 0, 0};
  }
  if (dtk->tokens_.empty()) { return; }
  yaksha_lisp_parser *dpr = this->create_parser(dtk);
  dpr->parse();
  if (!dpr->errors_.empty()) {
    throw parsing_error{dpr->errors_.back().message_, "", 0, 0};
  }
  if (dpr->exprs_.empty()) { return; }
  env->eval(dpr->exprs_);
}
std::vector<token *> yaksha_macros::expand_dsl(
    std::string &filepath,
    std::unordered_map<std::string, import_stmt *> &imports,
    std::string &dsl_macro_name, std::vector<token *> &dsl_macro_input,
    std::string imported_macro) {
  yaksha_envmap *env;
  if (imported_macro.empty()) {
    env = validate_and_get_environment_root(filepath);
  } else {
    if (imports.find(imported_macro) == imports.end()) {
      throw parsing_error{"invalid import: " + imported_macro, filepath, 0, 0};
    }
    env = validate_and_get_environment_root(
        imports[imported_macro]->data_->filepath_.string());
  }
  auto callable = "yaksha#macro#dsl#" + dsl_macro_name;
  auto callable_value = env->get_map(callable, nullptr);
  if (callable_value == nullptr) {
    throw parsing_error{
        "DSL macro " + dsl_macro_name + " not found",
        "",
        0,
        0,
    };
  }
  yaksha_lisp_value *result = nullptr;
  if (dsl_macro_input.empty()) {
    result = env->eval_call(callable_value, {});
  } else {
    result = env->eval_call(
        callable_value,
        create_token_maps_from_yaksha_tokens(dsl_macro_input, env));
  }
  return create_yaksha_tokens_from_result(dsl_macro_name, result);
}
yaksha_envmap *
yaksha_macros::validate_and_get_environment_root(const std::string &filepath) {
  yaksha_envmap *env;
  if (roots_.find(filepath) != roots_.end()) {
    env = roots_[filepath];
  } else {
    throw parsing_error{"root lisp macro env not found for: " + filepath,
                        filepath, 0, 0};
  }
  return env;
}
std::vector<yaksha_lisp_value *>
yaksha_macros::create_token_maps_from_yaksha_tokens(
    std::vector<token *> &dsl_macro_input, yaksha_envmap *env) {
  std::vector<yaksha_lisp_value *> dsl_macro_input_list{};
  for (auto &i : dsl_macro_input) {
    auto token_object = create_value();
    token_object->type_ = yaksha_lisp_value_type::MAP;
    token_object->closure_ = create_env();
    token_object->closure_->set_map(
        "yk_what", env->create_number(token_to_numeric_id(i->type_)));
    token_object->closure_->set_map("yk_type", env->create_string("yk_token"));
    token_object->closure_->set_map("value", env->create_string(i->token_));
    token_object->closure_->set_map("line", env->create_number(i->line_));
    token_object->closure_->set_map("pos", env->create_number(i->pos_));
    dsl_macro_input_list.emplace_back(token_object);
  }
  return dsl_macro_input_list;
}
std::vector<token *> yaksha_macros::create_yaksha_tokens_from_result(
    const std::string &dsl_macro_name, yaksha_lisp_value *result) {
  if (result->type_ != yaksha_lisp_value_type::LIST) {
    throw parsing_error{
        "DSL macro " + dsl_macro_name + " did not return a list",
        "",
        0,
        0,
    };
  }
  auto result_list = std::vector<token *>{};
  for (auto &r : result->list_) {
    if (r->type_ != yaksha_lisp_value_type::MAP) {
      throw parsing_error{
          "DSL macro " + dsl_macro_name + " did not return a list of maps",
          "",
          0,
          0,
      };
    }
    auto object_type = r->closure_->get_map("yk_type", nullptr);
    if (object_type == nullptr) {
      throw parsing_error{
          "DSL macro " + dsl_macro_name +
              " did not return a list of maps with yk_type",
          "",
          0,
          0,
      };
    }
    if (object_type->str_ != "yk_token") {
      throw parsing_error{
          "DSL macro " + dsl_macro_name +
              " did not return a list of maps with yk_type as yk_token",
          "",
          0,
          0,
      };
    }
    auto token_type = r->closure_->get_map("yk_what", nullptr);
    if (token_type == nullptr) {
      throw parsing_error{
          "DSL macro " + dsl_macro_name +
              " did not return a list of maps with yk_what",
          "",
          0,
          0,
      };
    }
    auto token_value = r->closure_->get_map("value", nullptr);
    if (token_value == nullptr) {
      throw parsing_error{
          "DSL macro " + dsl_macro_name +
              " did not return a list of maps with value",
          "",
          0,
          0,
      };
    }
    auto token_line = r->closure_->get_map("line", nullptr);
    if (token_line == nullptr) {
      throw parsing_error{
          "DSL macro " + dsl_macro_name +
              " did not return a list of maps with line",
          "",
          0,
          0,
      };
    }
    auto token_pos = r->closure_->get_map("pos", nullptr);
    if (token_pos == nullptr) {
      throw parsing_error{
          "DSL macro " + dsl_macro_name +
              " did not return a list of maps with pos",
          "",
          0,
          0,
      };
    }
    auto token = yk_token_pool_.allocate();
    if (token_value->type_ == yaksha_lisp_value_type::NUMBER) {
      token->token_ = std::to_string(token_value->num_);
    } else if (token_value->type_ == yaksha_lisp_value_type::STRING) {
      token->token_ = token_value->str_;
    } else {
      throw parsing_error{
          "DSL macro " + dsl_macro_name +
              " did not return a list of maps with value as string or number",
          "",
          0,
          0,
      };
    }
    token->line_ = (int) token_line->num_;
    token->pos_ = (int) token_pos->num_;
    token->type_ = numeric_id_to_token((int) token_type->num_);
    token->original_ = token->token_;
    result_list.emplace_back(token);
  }
  return result_list;
}
yaksha_lisp_tokenizer *yaksha_macros::create_tokenizer() {
  auto result = tokenizer_pool_.allocate();
  result->clean_state();
  result->mm_ = this;
  return result;
}
yaksha_lisp_parser *yaksha_macros::create_parser(yaksha_lisp_tokenizer *dt) {
  auto result = parser_pool_.allocate();
  result->clean_state();
  result->dt_ = dt;
  result->mm_ = this;
  return result;
}
void yaksha_macros::mark(yaksha_lisp_tokenizer *tokenizer) {
  tokenizer_pool_.mark(tokenizer);
}
void yaksha_macros::mark(yaksha_lisp_parser *parser) {
  parser_pool_.mark(parser);
}
gc_pool<token> *yaksha_macros::get_yk_token_pool() { return &yk_token_pool_; }
void yaksha_macros::init_env(
    std::string filepath,
    std::unordered_map<std::string, import_stmt *> &imports) {
  // Only setup builtins and prelude once, by creating a super root environment
  // Advantage - saves time setting up prelude, etc
  if (builtins_root_ == nullptr) {
    LOG_COMP("creating builtins_root");
    builtins_root_ = this->create_env();
    LOG_COMP("setting up builtins");
    builtins_root_->setup_builtins();
    LOG_COMP("setting up prelude");
    if (builtins_root_->builtins_created_) { builtins_root_->setup_prelude(); }
  }
  if (roots_.find(filepath) != roots_.end()) {
    LOG_COMP("found env for " << filepath);
    return;
  }
  LOG_COMP("created new env for file " << filepath);
  auto env = builtins_root_->spawn();
  for (auto &i : imports) {
    LOG_COMP("creating mod value in env:"
             << i.second->name_->token_ << " --> "
             << i.second->data_->filepath_.string());
    auto mod = env->create_val();
    mod->type_ = yaksha_lisp_value_type::MODULE;
    mod->str_ = i.second->data_->filepath_.string();
    auto name = i.second->name_->token_;
    env->set_map(name, mod);
  }
  roots_[filepath] = env;
}
void yaksha_macros::gc_mark() {
  if (!enable_gc_) { return; }
  init_mark_sweep();
  builtins_root_->gc_mark();
  for (auto &root : roots_) { root.second->gc_mark(); }
}
void yaksha_macros::enable_gc() { this->enable_gc_ = true; }
void yaksha_macros::disable_gc() { this->enable_gc_ = false; }
void yaksha_lisp_value::gc_mark(yk_memory_manager *memory_manager) {
  if (get_bit(&mark_, GC_POOL_MARK_BIT)) { return; }
  memory_manager->mark(this);// this is used
  if (this->type_ == yaksha_lisp_value_type::NUMBER ||
      this->type_ == yaksha_lisp_value_type::STRING ||
      this->type_ == yaksha_lisp_value_type::BUILTIN ||
      this->type_ == yaksha_lisp_value_type::MODULE) {
    return;// nothing else to mark
  }
  if (this->type_ == yaksha_lisp_value_type::LIST ||
      this->type_ == yaksha_lisp_value_type::LAMBDA ||
      this->type_ == yaksha_lisp_value_type::METAMACRO) {
    for (auto t : this->list_) {
      if (t != nullptr) { t->gc_mark(memory_manager); }
    }
  }
  if (this->type_ == yaksha_lisp_value_type::LAMBDA ||
      this->type_ == yaksha_lisp_value_type::METAMACRO ||
      this->type_ == yaksha_lisp_value_type::MAP) {
    if (this->closure_ != nullptr) { this->closure_->gc_mark(); }
    if (this->foreign_env_ != nullptr) { this->foreign_env_->gc_mark(); }
  }
  if (this->type_ == yaksha_lisp_value_type::EXPR) {
    if (this->expr_ != nullptr) { this->expr_->gc_mark(memory_manager); }
  }
}
void yaksha_lisp_value::clean_state() {
  this->type_ = yaksha_lisp_value_type::NUMBER;
  this->num_ = 0;
  this->str_ = "";
  this->list_.clear();
  this->expr_ = nullptr;
  this->builtin_ = nullptr;
  this->closure_ = nullptr;
  this->foreign_ = false;
  this->foreign_env_ = nullptr;
}
void yaksha_lisp_expr::gc_mark(yk_memory_manager *memory_manager) {
  if (get_bit(&mark_, GC_POOL_MARK_BIT)) { return; }
  memory_manager->mark(this);
  memory_manager->mark(this->token_);
  if (this->type_ == yaksha_lisp_expr_type::TERMINAL) {
    return;// nothing else to mark
  }
  memory_manager->mark(this->close_token_);
  if (this->type_ == yaksha_lisp_expr_type::S_EXPR ||
      this->type_ == yaksha_lisp_expr_type::Q_EXPR ||
      this->type_ == yaksha_lisp_expr_type::MAP_LITERAL) {
    for (auto e : this->list_) { e->gc_mark(memory_manager); }
  }
}
void yaksha_lisp_expr::clean_state() {
  this->token_ = nullptr;
  this->type_ = yaksha_lisp_expr_type::TERMINAL;
  this->list_.clear();
  this->close_token_ = nullptr;
}
void yaksha_lisp_token::clean_state() {
  this->token_ = "";
  this->type_ = yaksha_lisp_token_type::NUMBER;
  this->line_ = 0;
  this->pos_ = 0;
  this->file_ = "";
}
