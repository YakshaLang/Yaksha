// YK
#include "yk__lib.h"
int32_t yy__factorial(int32_t);
int32_t yy__on_end(int32_t);
int32_t yy__main();
int32_t yy__factorial(int32_t yy__x) 
{
    if (yy__x <= INT32_C(0))
    {
        return INT32_C(1);
    }
    int32_t t__0 = (yy__x * yy__factorial((yy__x - INT32_C(1))));
    return t__0;
}
int32_t yy__on_end(int32_t yy__n) 
{
    yk__printint((intmax_t)yy__n);
    yk__printstr(" From defer --> Program Completed\n");
    return INT32_C(0);
}
int32_t yy__main() 
{
    int32_t yy__a = INT32_C(10);
    yk__sds yy__b = yk__sdsnewlen("b" , 1);
    while (true)
    {
        if (!(((yy__a > INT32_C(0)))))
        {
            break;
        }
        yk__printint((intmax_t)yy__factorial(yy__a));
        yk__printstr("\n");
        yy__a = (yy__a - INT32_C(1));
        yk__sds t__1 = yk__concat_lit_sds("a", 1, yy__b);
        yk__sdsfree(yy__b);
        yy__b = yk__sdsdup(t__1);
        yk__sdsfree(t__1);
    }
    yk__printstr(yy__b);
    yk__printstr("\n");
    (yy__on_end(INT32_C(2)));
    (yy__on_end(INT32_C(1)));
    yk__sdsfree(yy__b);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif