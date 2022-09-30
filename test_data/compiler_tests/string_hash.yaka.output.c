// YK
#include "yk__lib.h"
// --forward declarations-- 
struct ykentry0;
struct ykentry1;
int32_t yy__main();
// --structs-- 
struct ykentry0 { yk__sds key; int32_t value; };
struct ykentry1 { yk__sds key; float value; };
// --functions-- 
int32_t yy__main() 
{
    struct ykentry0* yy__m = NULL;
    yk__sh_new_strdup(yy__m);
    yk__sds t__0 = yk__sdsnew("hello");
    yk__shput(yy__m, t__0, INT32_C(42));
    yk__sds t__1 = yk__sdsnew("world");
    yk__shput(yy__m, t__1, INT32_C(10000));
    yk__sds t__2 = yk__sdsnew("hello = ");
    yk__printstr((t__2));
    yk__sds t__3 = yk__sdsnew("hello");
    yk__printlnint(((intmax_t)yk__shget(yy__m, t__3)));
    yk__sds t__4 = yk__sdsnew("length of this map is = ");
    yk__printstr((t__4));
    yk__printlnint(((intmax_t)yk__shlen(yy__m)));
    yk__sds t__5 = yk__sdsnew("\"hello\" is located at = ");
    yk__printstr((t__5));
    yk__sds t__6 = yk__sdsnew("hello");
    yk__printlnint(((intmax_t)yk__shgeti(yy__m, t__6)));
    yk__sds t__7 = yk__sdsnew("\"unknown\" is located at = ");
    yk__printstr((t__7));
    yk__sds t__8 = yk__sdsnew("unknown");
    yk__printlnint(((intmax_t)yk__shgeti(yy__m, t__8)));
    yk__shfree(yy__m);
    struct ykentry1* yy__m2 = NULL;
    yk__sh_new_strdup(yy__m2);
    yk__sds t__9 = yk__sdsnew("hello");
    yk__shput(yy__m2, t__9, 42.0f);
    yk__sds t__10 = yk__sdsnew("hello in m2 = ");
    yk__printstr((t__10));
    yk__sds t__11 = yk__sdsnew("hello");
    yk__printlndbl((yk__shget(yy__m2, t__11)));
    struct ykentry1* yy__m3 = NULL;
    yk__sh_new_strdup(yy__m3);
    yk__sds t__12 = yk__sdsnew("hello");
    yk__shput(yy__m3, t__12, 123.0f);
    yk__sds t__13 = yk__sdsnew("hello in m3 = ");
    yk__printstr((t__13));
    yk__sds t__14 = yk__sdsnew("hello");
    yk__printlndbl((yk__shget(yy__m3, t__14)));
    yk__sds t__15 = yk__sdsnew("bye!");
    yk__printlnstr((t__15));
    yk__sdsfree(t__15);
    yk__sdsfree(t__14);
    yk__sdsfree(t__13);
    yk__sdsfree(t__12);
    yk__sdsfree(t__11);
    yk__sdsfree(t__10);
    yk__sdsfree(t__9);
    yk__sdsfree(t__8);
    yk__sdsfree(t__7);
    yk__sdsfree(t__6);
    yk__sdsfree(t__5);
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