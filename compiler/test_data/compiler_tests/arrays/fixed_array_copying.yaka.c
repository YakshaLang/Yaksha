// YK
#include "yk__lib.h"
typedef int32_t yt_arr_i32_3[3];
int32_t yy__main();
int32_t yy__main() 
{
    yt_arr_i32_3 yy__a = {};
    yy__a[INT32_C(0)] = INT32_C(1);
    yy__a[INT32_C(1)] = INT32_C(2);
    yy__a[INT32_C(2)] = INT32_C(3);
    yt_arr_i32_3 yy__b = {};
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