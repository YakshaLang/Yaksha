// ic_line_splicer.cpp
#include "ic_line_splicer.h"
using namespace yaksha;
ic_line_splicer::ic_line_splicer(ic_trigraph_translater &tt)
    : tt_(tt), current_(0), consumed_extra_(false) {
  read();
}
void ic_line_splicer::next() {
  if (consumed_extra_) {
    read();
    return;
  }
  if (!reached_end()) { tt_.next(); }
  read();
}
[[nodiscard]] bool ic_line_splicer::reached_end() { return tt_.reached_end(); }
[[nodiscard]] uint32_t ic_line_splicer::get_current() { return current_; }
[[nodiscard]] int ic_line_splicer::get_column() {
  return consumed_extra_ ? tt_.get_column() - 1 : tt_.get_column();
}
[[nodiscard]] int ic_line_splicer::get_line() { return tt_.get_line(); }
ic_line_splicer::~ic_line_splicer() = default;
void ic_line_splicer::read() {
  consumed_extra_ = false;
  current_ = tt_.get_current();
  if (current_ != '\\') return;
  if (tt_.reached_end()) return;
  tt_.next();
  if (tt_.get_current() == '\r' && !tt_.reached_end()) {
    tt_.next();
    if (tt_.get_current() == '\n') {
      if (tt_.reached_end()) {
        current_ = 0;
      } else {
        tt_.next();
        current_ = tt_.get_current();
      }
    } else {
      current_ = tt_.get_current();
    }
  } else if (tt_.get_current() == '\n' && !tt_.reached_end()) {
    tt_.next();
    current_ = tt_.get_current();
  } else if (tt_.reached_end()) {
    current_ = 0;
  } else {
    consumed_extra_ = true;
  }
}
