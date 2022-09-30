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
    yk__sds t__0 = yk__sdsnew("1 = ");
    yk__printstr((t__0));
    yk__printlnint(((intmax_t)yk__hmget(yy__m, INT32_C(1))));
    yk__sds t__1 = yk__sdsnew("length of this map is = ");
    yk__printstr((t__1));
    yk__printlnint(((intmax_t)yk__hmlen(yy__m)));
    yk__sds t__2 = yk__sdsnew("1 is located at = ");
    yk__printstr((t__2));
    yk__printlnint(((intmax_t)yk__hmgeti(yy__m, INT32_C(1))));
    yk__sds t__3 = yk__sdsnew("30 is located at = ");
    yk__printstr((t__3));
    yk__printlnint(((intmax_t)yk__hmgeti(yy__m, INT32_C(30))));
    yk__hmfree(yy__m);
    yk__sds t__4 = yk__sdsnew("bye!");
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