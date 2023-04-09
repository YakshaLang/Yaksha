// YK
#include "yk__lib.h"
// --forward declarations-- 
int32_t yy__main();
// --structs-- 
// --functions-- 
int32_t yy__main() 
{
    int32_t* t__6 = NULL;
    yk__arrsetcap(t__6, 3);
    yk__arrput(t__6, INT32_C(1));
    yk__arrput(t__6, INT32_C(2));
    yk__arrput(t__6, INT32_C(3));
    int32_t* yy__e1 = t__6;
    int32_t* t__7 = NULL;
    yk__arrsetcap(t__7, 4);
    yk__arrput(t__7, INT32_C(4));
    yk__arrput(t__7, INT32_C(5));
    yk__arrput(t__7, INT32_C(6));
    yk__arrput(t__7, INT32_C(7));
    int32_t* yy__e2 = t__7;
    int32_t* yy__0t = yy__e1;
    int32_t yy__1t = INT32_C(0);
    int32_t yy__2t = yk__arrlen(yy__0t);
    while (true)
    {
        if ((! (((yy__1t < yy__2t)))))
        {
            break;
        }
        int32_t* yy__3t = yy__e2;
        int32_t yy__4t = INT32_C(0);
        int32_t yy__5t = yk__arrlen(yy__3t);
        while (true)
        {
            if ((! (((yy__4t < yy__5t)))))
            {
                break;
            }
            yk__printint(((intmax_t)(yy__0t[yy__1t])));
            yk__sds t__8 = yk__sdsnewlen(" - ", 3);
            yk__printstr((t__8));
            yk__printlnint(((intmax_t)(yy__3t[yy__4t])));
            yy__4t += INT32_C(1);
            yk__sdsfree(t__8);
        }
        yy__1t += INT32_C(1);
    }
    yk__arrfree(yy__e1);
    yk__arrfree(yy__e2);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif