// ic_simple_charcter_iter.h
#ifndef IC_SIMPLE_CHARCTER_ITER_H
#define IC_SIMPLE_CHARCTER_ITER_H
#include <utf8.h>
namespace yaksha {
  struct ic_simple_character_iter {
    virtual void next() = 0;
    virtual bool reached_end() = 0;
    virtual utf8::uint32_t get_current() = 0;
    virtual int get_column() = 0;
    virtual int get_line() = 0;
    virtual ~ic_simple_character_iter() = default;
  };
}// namespace yaksha
#endif
