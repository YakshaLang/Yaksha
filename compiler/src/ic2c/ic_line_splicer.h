// ic_line_splicer.h
#ifndef IC_LINE_SPLICER_H
#define IC_LINE_SPLICER_H
#include "ic_simple_character_iter.h"
#include "ic_trigraph_translater.h"
namespace yaksha {
  struct ic_line_splicer : public ic_simple_character_iter {
    explicit ic_line_splicer(ic_trigraph_translater &tt);
    void next() override;
    [[nodiscard]] bool reached_end() override;
    [[nodiscard]] uint32_t get_current() override;
    [[nodiscard]] int get_column() override;
    [[nodiscard]] int get_line() override;
    ~ic_line_splicer() override;

private:
    void read();
    ic_trigraph_translater &tt_;
    utf8::uint32_t current_;
    bool consumed_extra_;
  };
}// namespace yaksha
#endif
