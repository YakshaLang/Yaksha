// YK
#include "yk__lib.h"
// --forward declarations-- 
typedef yk__sds (*ykfncptr0)(yk__sds);
yk__sds yy__world_formatter(yk__sds);
void yy__formatted_print(ykfncptr0, yk__sds);
int32_t yy__main();
// --structs-- 
// --functions-- 
yk__sds yy__world_formatter(yk__sds yy__item) 
{
    yk__sds t__0 = yk__sdsnewlen(" World", 6);
    yk__sds t__1 = yk__sdscatsds(yk__sdsdup(yy__item), t__0);
    yk__sds yy__result = yk__sdsdup(t__1);
    yk__sds t__2 = yy__result;
    yk__sdsfree(t__1);
    yk__sdsfree(t__0);
    yk__sdsfree(yy__item);
    return t__2;
}
void yy__formatted_print(ykfncptr0 yy__formatter, yk__sds yy__item) 
{
    yk__sds t__3 = yy__formatter(yk__sdsdup(yy__item));
    yk__printlnstr(((t__3)));
    yk__sdsfree(t__3);
    yk__sdsfree(yy__item);
    return;
}
int32_t yy__main() 
{
    yk__sds t__4 = yk__sdsnewlen("Hello", 5);
    yy__formatted_print(yy__world_formatter, yk__sdsdup(t__4));
    yk__sdsfree(t__4);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif