// YK
#include "yk__lib.h"
// --forward declarations-- 
typedef int32_t ykfxa0[3];
int32_t yy__main();
// --structs-- 
// --functions-- 
int32_t yy__main() 
{
    ykfxa0 yy__a = {};
    yy__a[INT32_C(0)] = INT32_C(1);
    yy__a[INT32_C(1)] = INT32_C(2);
    yy__a[INT32_C(2)] = INT32_C(3);
    ykfxa0 yy__b = {};
    yy__b[INT32_C(0)] = yy__a[INT32_C(0)];
    yy__b[INT32_C(1)] = yy__a[INT32_C(1)];
    yy__b[INT32_C(2)] = yy__a[INT32_C(2)];
    yk__printlnint((intmax_t)((yy__a[INT32_C(0)] + yy__a[INT32_C(1)]) + yy__a[INT32_C(2)]));
    yk__printlnint((intmax_t)((yy__b[INT32_C(0)] + yy__b[INT32_C(1)]) + yy__b[INT32_C(2)]));
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif