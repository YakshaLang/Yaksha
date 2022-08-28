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
yk__sds *yk__sdsarraydup(yk__sds *arr) {
  if (NULL == arr) { return NULL; }
  size_t length = yk__arrlenu(arr);
  yk__sds *newarr = NULL;
  for (size_t i = 0; i < length; i++) {
    yk__sds current = arr[i];
    yk__sds copy = yk__sdsdup(current);
    yk__arrput(newarr, copy);
  }
  return newarr;
}
void yk__delsdsarray(yk__sds *arr) {
  if (NULL == arr) return;
  size_t length = yk__arrlenu(arr);
  for (size_t x = 0; x < length; x++) { yk__sdsfree(arr[x]); }
  yk__arrfree(arr);
}