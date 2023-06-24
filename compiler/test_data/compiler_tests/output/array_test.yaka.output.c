// YK
#include "yk__lib.h"
// --forward declarations-- 
int32_t yy__main();
// --structs-- 
// --functions-- 
int32_t yy__main() 
{
    int32_t* t__0 = NULL;
    yk__arrsetcap(t__0, 7);
    yk__arrput(t__0, INT32_C(1));
    yk__arrput(t__0, INT32_C(2));
    yk__arrput(t__0, INT32_C(3));
    yk__arrput(t__0, INT32_C(4));
    yk__arrput(t__0, INT32_C(5));
    yk__arrput(t__0, INT32_C(6));
    yk__arrput(t__0, INT32_C(7));
    int32_t* yy__a = t__0;
    yk__sds t__1 = yk__sdsnewlen("Hello", 5);
    yk__sds t__2 = yk__sdsnewlen("World", 5);
    yk__sds t__3 = yk__sdsnewlen("Haha", 4);
    yk__sds* t__4 = NULL;
    yk__arrsetcap(t__4, 3);
    yk__arrput(t__4, yk__sdsdup(t__1));
    yk__arrput(t__4, yk__sdsdup(t__2));
    yk__arrput(t__4, yk__sdsdup(t__3));
    yk__sds* yy__b = t__4;
    yk__sds t__5 = yk__sdsnewlen("Printing [a]", 12);
    yk__printlnstr((t__5));
    int32_t yy__pos = INT32_C(0);
    int32_t yy__length = yk__arrlen(yy__a);
    while (true)
    {
        if ((! (((yy__pos < yy__length)))))
        {
            break;
        }
        yk__printlnint(((intmax_t)yy__a[yy__pos]));
        yy__pos = (yy__pos + INT32_C(1));
    }
    yk__sds t__6 = yk__sdsnewlen("Printing [b]", 12);
    yk__printlnstr((t__6));
    yy__pos = INT32_C(0);
    yy__length = yk__arrlen(yy__b);
    while (true)
    {
        if ((! (((yy__pos < yy__length)))))
        {
            break;
        }
        yk__printlnstr((yy__b[yy__pos]));
        yy__pos = (yy__pos + INT32_C(1));
    }
    yk__sdsfree(t__6);
    yk__sdsfree(t__5);
    yk__sdsfree(t__3);
    yk__sdsfree(t__2);
    yk__sdsfree(t__1);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif