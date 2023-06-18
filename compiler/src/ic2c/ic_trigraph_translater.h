// ic_trigraph_translater.h
#ifndef IC_TRIGRAPH_TRANSLATER_H
#define IC_TRIGRAPH_TRANSLATER_H
#include "ic2c/ic_simple_character_iter.h"
#include "tokenizer/string_utils.h"
namespace yaksha {
  struct ic_trigraph_translater : public ic_simple_character_iter {
    explicit ic_trigraph_translater(std::string &data);
    ~ic_trigraph_translater() override;
    void next() override;
    [[nodiscard]] bool reached_end() override;
    [[nodiscard]] utf8::uint32_t get_current() override;
    [[nodiscard]] int get_column() override;
    [[nodiscard]] int get_line() override;

private:
    int line_;
    int column_;
    std::string::iterator iter_;
    std::string::iterator end_;
    std::string &data_;
    utf8::uint32_t current_;
    bool increment_line_;
    void read();
  };
}// namespace yaksha
#endif
