// YK
#include "yk__lib.h"
// --forward declarations-- 
typedef yk__sds (*ykfncptr0)(yk__sds);
yk__sds yy__normal(yk__sds);
yk__sds yy__sqb(yk__sds);
int32_t yy__main();
// --structs-- 
// --functions-- 
yk__sds yy__normal(yk__sds yy__s) 
{
    yk__sds t__0 = yy__s;
    return t__0;
}
yk__sds yy__sqb(yk__sds yy__s) 
{
    yk__sds t__1 = yk__sdsnew("[");
    yk__sds t__2 = yk__sdscatsds(yk__sdsdup(t__1), yy__s);
    yk__sds t__3 = yk__sdsnew("]");
    yk__sds t__4 = yk__sdscatsds(yk__sdsdup(t__2), t__3);
    yk__sds t__5 = t__4;
    yk__sdsfree(t__3);
    yk__sdsfree(t__2);
    yk__sdsfree(t__1);
    yk__sdsfree(yy__s);
    return t__5;
}
int32_t yy__main() 
{
    ykfncptr0 yy__a;
    yy__a = (true ? yy__normal : yy__sqb);
    yk__sds t__6 = yk__sdsnew("Hello World");
    yk__sds t__7 = yy__a(yk__sdsdup(t__6));
    yk__printlnstr(((t__7)));
    yy__a = (false ? yy__normal : yy__sqb);
    yk__sds t__8 = yk__sdsnew("Hello");
    yk__sds t__9 = yk__sdsnew("World");
    yk__sds t__10 = yy__a(yk__sdsdup((true ? t__8 : t__9)));
    yk__printlnstr(((t__10)));
    yk__sdsfree(t__10);
    yk__sdsfree(t__9);
    yk__sdsfree(t__8);
    yk__sdsfree(t__7);
    yk__sdsfree(t__6);
    return 0;
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif