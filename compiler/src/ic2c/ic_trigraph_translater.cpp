// ic_trigraph_translater.cpp
#include "ic_trigraph_translater.h"
using namespace yaksha;
ic_trigraph_translater::ic_trigraph_translater(std::string &data)
    : data_(data), current_(0), iter_(data.begin()), end_(data.end()), line_(0),
      column_(1), increment_line_(false) {
  read();
}
ic_trigraph_translater::~ic_trigraph_translater() = default;
void ic_trigraph_translater::next() {
  if (!reached_end()) {
    utf8::next(iter_, end_);
    column_++;
  }
  read();
}
[[nodiscard]] bool ic_trigraph_translater::reached_end() {
  return iter_ == end_;
}
[[nodiscard]] utf8::uint32_t ic_trigraph_translater::get_current() {
  return current_;
}
[[nodiscard]] int ic_trigraph_translater::get_column() { return column_; }
[[nodiscard]] int ic_trigraph_translater::get_line() { return line_; }
void ic_trigraph_translater::read() {
  if (increment_line_) {
    increment_line_ = false;
    line_++;
    column_ = 1;
  }
  auto characters = string_utils::peek3(iter_, end_);
  utf8::uint32_t prev = current_;
  utf8::uint32_t current = std::get<0>(characters);
  utf8::uint32_t next = std::get<1>(characters);
  utf8::uint32_t after_next = std::get<2>(characters);
  bool read_skip_ = false;
  if ((current == '\r' && next == '\n') || current == '\r' || (current == '\n' && prev != '\r')) {
    increment_line_ = true;
  }
  if (current == '?' && next == '?') {
    read_skip_ = true;
    if (after_next == '=') {
      current = '#';
    } else if (after_next == '/') {
      current = '\\';
    } else if (after_next == '\'') {
      current = '^';
    } else if (after_next == '(') {
      current = '[';
    } else if (after_next == ')') {
      current = ']';
    } else if (after_next == '!') {
      current = '|';
    } else if (after_next == '<') {
      current = '{';
    } else if (after_next == '>') {
      current = '}';
    } else if (after_next == '-') {
      current = '~';
    } else {
      read_skip_ = false;
    }
  }
  if (read_skip_) {
    if (!reached_end()) {
      utf8::next(iter_, end_);
      column_++;
    }
    if (!reached_end()) {
      utf8::next(iter_, end_);
      column_++;
    }
    if (!reached_end()) {
      utf8::next(iter_, end_);
      column_++;
    }
  }
  current_ = current;
}
