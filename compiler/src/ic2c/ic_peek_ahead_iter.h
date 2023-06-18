// ic_peek_ahead_iter.h
#ifndef IC_PEEK_AHEAD_ITER_H
#define IC_PEEK_AHEAD_ITER_H
#include "ic_simple_character_iter.h"
namespace yaksha {
  struct ic_peek_ahead_iter : public ic_simple_character_iter {
    explicit ic_peek_ahead_iter(ic_simple_character_iter &tt);
    void next() override;
    [[nodiscard]] bool reached_end() override;
    [[nodiscard]] utf8::uint32_t get_current() override;
    [[nodiscard]] utf8::uint32_t get_next();
    [[nodiscard]] utf8::uint32_t get_after_next();
    [[nodiscard]] utf8::uint32_t get_fourth();
    int get_column() override;
    int get_line() override;
    ~ic_peek_ahead_iter() override;

private:
    ic_simple_character_iter &tt_;
    utf8::uint32_t current_;
    int current_c_;
    int current_l_;
    bool current_e_;
    utf8::uint32_t next_;
    int next_c_;
    int next_l_;
    bool next_e_;
    utf8::uint32_t after_next_;
    int after_next_c_;
    int after_next_l_;
    bool after_next_e_;
    utf8::uint32_t fourth_;
    int fourth_c_;
    int fourth_l_;
    bool fourth_e_;
  };
}
#endif
