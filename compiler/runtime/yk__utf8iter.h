#if !defined(YK__UTF8_ITER)
#define YK__UTF8_ITER
#include "utf8proc.h"
struct utf8proc_iter_state {
  utf8proc_uint8_t *str_original;
  utf8proc_uint8_t *str_position;
  utf8proc_ssize_t length;
  utf8proc_ssize_t step_size;
  utf8proc_int32_t codepoint;
};
#endif// YK__UTF8_ITER