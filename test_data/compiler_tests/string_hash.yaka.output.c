// YK
#include "yk__lib.h"
// --forward declarations-- 
struct ykentry0;
int32_t yy__main();
// --structs-- 
struct ykentry0 { yk__sds key; int32_t value; };
// --functions-- 
int32_t yy__main() 
{
    struct ykentry0* yy__m = NULL;
    yk__sh_new_strdup(yy__m);
    yk__sds t__0 = yk__sdsnew("hello");
    yk__shput(yy__m, t__0, 42);
    yk__sds t__1 = yk__sdsnew("world");
    yk__shput(yy__m, t__1, 10000);
    yk__sds t__2 = yk__sdsnew("hello = ");
    yk__printstr((t__2));
    yk__sds t__3 = yk__sdsnew("hello");
    yk__printlnint(((intmax_t)yk__shget(yy__m, t__3)));
    yk__sds t__4 = yk__sdsnew("length of this map is = ");
    yk__printstr((t__4));
    yk__printlnint(((intmax_t)yk__shlen(yy__m)));
    yk__shfree(yy__m);
    yk__sds t__5 = yk__sdsnew("bye!");
    yk__printlnstr((t__5));
    yk__sdsfree(t__5);
    yk__sdsfree(t__4);
    yk__sdsfree(t__3);
    yk__sdsfree(t__2);
    yk__sdsfree(t__1);
    yk__sdsfree(t__0);
    return 0;
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif