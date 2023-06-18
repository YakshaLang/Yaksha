// ic_peek_ahead_iter.cpp
#include "ic_peek_ahead_iter.h"
using namespace yaksha;
 ic_peek_ahead_iter::ic_peek_ahead_iter(ic_simple_character_iter &tt)
    : tt_(tt), current_(0), next_(0), after_next_(0), fourth_(0) {
  current_ = tt_.get_current();
  current_l_ = tt_.get_line();
  current_c_ = tt_.get_column();
  current_e_ = tt_.reached_end();
  tt_.next();
  next_ = tt_.get_current();
  next_l_ = tt_.get_line();
  next_c_ = tt_.get_column();
  next_e_ = tt_.reached_end();
  tt_.next();
  after_next_ = tt_.get_current();
  after_next_l_ = tt_.get_line();
  after_next_c_ = tt_.get_column();
  after_next_e_ = tt_.reached_end();
  tt_.next();
  fourth_ = tt_.get_current();
  fourth_l_ = tt_.get_line();
  fourth_c_ = tt_.get_column();
  fourth_e_ = tt_.reached_end();
}
void ic_peek_ahead_iter::next() {
  current_ = next_;
  current_l_ = next_l_;
  current_c_ = next_c_;
  current_e_ = next_e_;
  next_ = after_next_;
  next_l_ = after_next_l_;
  next_c_ = after_next_c_;
  next_e_ = after_next_e_;
  after_next_ = fourth_;
  after_next_l_ = fourth_l_;
  after_next_c_ = fourth_c_;
  after_next_e_ = fourth_e_;
  tt_.next();
  fourth_ = tt_.get_current();
  fourth_l_ = tt_.get_line();
  fourth_c_ = tt_.get_column();
  fourth_e_ = tt_.reached_end();
}
[[nodiscard]] bool ic_peek_ahead_iter::reached_end() { return current_e_; }
[[nodiscard]] utf8::uint32_t ic_peek_ahead_iter::get_current() {
  return current_;
}
[[nodiscard]] utf8::uint32_t ic_peek_ahead_iter::get_next() { return next_; }
[[nodiscard]] utf8::uint32_t ic_peek_ahead_iter::get_after_next() {
  return after_next_;
}
[[nodiscard]] utf8::uint32_t ic_peek_ahead_iter::get_fourth() {
  return fourth_;
}
int ic_peek_ahead_iter::get_column() { return current_c_; }
int ic_peek_ahead_iter::get_line() { return current_l_; }
ic_peek_ahead_iter::~ic_peek_ahead_iter() = default;
