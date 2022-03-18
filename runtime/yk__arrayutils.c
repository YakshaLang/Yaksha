#include "yk__arrayutils.h"
#include <stdarg.h>
yk__sds *yk__newsdsarray(size_t count, ...) {
  va_list args;
  yk__sds *array_val = NULL;
  va_start(args, count);
  for (size_t x = 0; x < count; x++) {
    yk__sds tmp = va_arg(args, yk__sds);
    yk__arrput(array_val, tmp);
  }
  va_end(args);
  return array_val;
}