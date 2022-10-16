// YK
#include "yk__lib.h"
// --forward declarations-- 
struct ykentry0;
int32_t yy__main();
// --structs-- 
struct ykentry0 { int32_t key; int32_t value; };
// --functions-- 
int32_t yy__main() 
{
    struct ykentry0* yy__m = NULL;
    ;
    yk__hmput(yy__m, INT32_C(1), INT32_C(42));
    yk__hmput(yy__m, INT32_C(100), INT32_C(10000));
    yk__sds t__0 = yk__sdsnewlen("1 = ", 4);
    yk__printstr((t__0));
    yk__printlnint(((intmax_t)yk__hmget(yy__m, INT32_C(1))));
    yk__sds t__1 = yk__sdsnewlen("length of this map is = ", 24);
    yk__printstr((t__1));
    yk__printlnint(((intmax_t)yk__hmlen(yy__m)));
    yk__sds t__2 = yk__sdsnewlen("1 is located at = ", 18);
    yk__printstr((t__2));
    yk__printlnint(((intmax_t)yk__hmgeti(yy__m, INT32_C(1))));
    yk__sds t__3 = yk__sdsnewlen("30 is located at = ", 19);
    yk__printstr((t__3));
    yk__printlnint(((intmax_t)yk__hmgeti(yy__m, INT32_C(30))));
    yk__hmfree(yy__m);
    yk__sds t__4 = yk__sdsnewlen("bye!", 4);
    yk__printlnstr((t__4));
    yk__sdsfree(t__4);
    yk__sdsfree(t__3);
    yk__sdsfree(t__2);
    yk__sdsfree(t__1);
    yk__sdsfree(t__0);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif