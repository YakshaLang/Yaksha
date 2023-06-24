// YK
#include "yk__lib.h"
// --forward declarations-- 
int32_t yy__cmp_int(void const* const , void const* const );
int32_t yy__main();
// --structs-- 
// --functions-- 
int32_t yy__cmp_int(void const* const  yy__a, void const* const  yy__b) 
{
    int32_t yy__val_a = (*(((int32_t*)yy__a)));
    int32_t yy__val_b = (*(((int32_t*)yy__b)));
    int32_t t__0 = (yy__val_b - yy__val_a);
    return t__0;
}
int32_t yy__main() 
{
    int32_t* yy__x = NULL;
    yk__arrput(yy__x, INT32_C(5));
    yk__arrput(yy__x, INT32_C(3));
    yk__arrput(yy__x, INT32_C(1));
    yk__arrput(yy__x, INT32_C(4));
    yk__arrput(yy__x, INT32_C(4));
    yk__arrput(yy__x, INT32_C(4));
    yk__arrput(yy__x, INT32_C(4));
    yk__arrput(yy__x, INT32_C(2));
    yk__arrput(yy__x, INT32_C(50));
    yk__arrput(yy__x, INT32_C(30));
    yk__arrput(yy__x, INT32_C(10));
    yk__arrput(yy__x, INT32_C(40));
    yk__arrput(yy__x, (- (INT32_C(1))));
    yk__arrput(yy__x, INT32_C(20));
    yk__sds t__1 = yk__sdsnewlen("before:", 7);
    yk__printlnstr((t__1));
    yk__sds t__2 = yk__sdsnewlen("len=", 4);
    yk__printstr((t__2));
    yk__printlnint(((intmax_t)yk__arrlen(yy__x)));
    int32_t yy__pos = INT32_C(0);
    while (true)
    {
        if ((! (((yy__pos < yk__arrlen(yy__x))))))
        {
            break;
        }
        yk__printint(((intmax_t)yy__x[yy__pos]));
        yk__sds t__3 = yk__sdsnewlen(" ", 1);
        yk__printstr((t__3));
        yy__pos = (yy__pos + INT32_C(1));
        yk__sdsfree(t__3);
    }
    yk__sds t__4 = yk__sdsempty();
    yk__printlnstr((t__4));
    (yk__quicksort(yy__x,sizeof(int32_t),yk__arrlenu(yy__x),yy__cmp_int) == 0);
    yk__sds t__5 = yk__sdsnewlen("after:", 6);
    yk__printlnstr((t__5));
    yy__pos = INT32_C(0);
    yk__sds t__6 = yk__sdsnewlen("len=", 4);
    yk__printstr((t__6));
    yk__printlnint(((intmax_t)yk__arrlen(yy__x)));
    while (true)
    {
        if ((! (((yy__pos < yk__arrlen(yy__x))))))
        {
            break;
        }
        yk__printint(((intmax_t)yy__x[yy__pos]));
        yk__sds t__7 = yk__sdsnewlen(" ", 1);
        yk__printstr((t__7));
        yy__pos = (yy__pos + INT32_C(1));
        yk__sdsfree(t__7);
    }
    yk__sds t__8 = yk__sdsempty();
    yk__printlnstr((t__8));
    yk__sdsfree(t__8);
    yk__sdsfree(t__6);
    yk__sdsfree(t__5);
    yk__sdsfree(t__4);
    yk__sdsfree(t__2);
    yk__sdsfree(t__1);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif