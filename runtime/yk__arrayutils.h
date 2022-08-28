#if !defined(YK__ARRAY_UTILS)
#define YK__ARRAY_UTILS
#include "yk__lib.h"
yk__sds *yk__newsdsarray(size_t count, ...);
yk__sds *yk__sdsarraydup(yk__sds* a);
void yk__delsdsarray(yk__sds*arr);
#endif// YK__ARRAY_UTILS