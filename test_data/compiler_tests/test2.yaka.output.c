// YK
#include "yk__lib.h"
// --forward declarations-- 
int32_t yy__factorial(int32_t);
int32_t yy__on_end(int32_t);
int32_t yy__main();
// --structs-- 
// --functions-- 
int32_t yy__factorial(int32_t yy__x) 
{
    if ((yy__x <= INT32_C(0)))
    {
        return INT32_C(1);
    }
    int32_t t__0 = (yy__x * yy__factorial((yy__x - INT32_C(1))));
    return t__0;
}
int32_t yy__on_end(int32_t yy__n) 
{
    yk__printint(((intmax_t)yy__n));
    yk__sds t__1 = yk__sdsnewlen(" From defer --> Program Completed\n", 34);
    yk__printstr((t__1));
    yk__sdsfree(t__1);
    return INT32_C(0);
}
int32_t yy__main() 
{
    int32_t yy__a = INT32_C(10);
    yk__sds t__2 = yk__sdsnewlen("b", 1);
    yk__sds yy__b = yk__sdsdup(t__2);
    while (1) {
        if (!((yy__a > INT32_C(0)))) { break; } // Check
        // Body of while loop

        {
            yk__printint(((intmax_t)yy__factorial(yy__a)));
            yk__sds t__3 = yk__sdsnewlen("\n", 1);
            yk__printstr((t__3));
            yy__a = (yy__a - INT32_C(1));
            yk__sds t__4 = yk__sdsnewlen("a", 1);
            yk__sds t__5 = yk__sdscatsds(yk__sdsdup(t__4), yy__b);
            yk__sdsfree(yy__b);
            yy__b = yk__sdsdup(t__5);
            yk__sdsfree(t__5);
            yk__sdsfree(t__4);
            yk__sdsfree(t__3);
        }
    }
    yk__printstr((yy__b));
    yk__sds t__6 = yk__sdsnewlen("\n", 1);
    yk__printstr((t__6));
    (yy__on_end(INT32_C(2)));
    (yy__on_end(INT32_C(1)));
    yk__sdsfree(t__6);
    yk__sdsfree(yy__b);
    yk__sdsfree(t__2);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif