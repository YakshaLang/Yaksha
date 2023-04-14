// YK
#include "yk__lib.h"
// --forward declarations-- 
int32_t yy__main();
// --structs-- 
// --functions-- 
int32_t yy__main() 
{
    int32_t** yy__a = NULL;
    int32_t* yy__b = NULL;
    yk__arrput(yy__b, INT32_C(1));
    yk__arrput(yy__a, yy__b);
    yk__printint(((intmax_t)yy__a[INT32_C(0)][INT32_C(0)]));
    yk__sds t__0 = yk__sdsnewlen("\n", 1);
    yk__printstr((t__0));
    yy__a[INT32_C(0)][INT32_C(0)] = INT32_C(100);
    yk__printint(((intmax_t)yy__a[INT32_C(0)][INT32_C(0)]));
    yk__sds t__1 = yk__sdsnewlen("\n", 1);
    yk__printstr((t__1));
    yk__arrfree(yy__b);
    yk__arrfree(yy__a);
    yk__sdsfree(t__1);
    yk__sdsfree(t__0);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif