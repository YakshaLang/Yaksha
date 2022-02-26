#include "yk__lib.h"
// --forward declarations-- 
int32_t yy__factorial(int32_t);
int32_t yy__on_end(int32_t);
int32_t yy__main();
// --structs-- 
// --functions-- 
int32_t yy__factorial(int32_t yy__x) 
{
    if ((yy__x <= 0))
    {
        return 1;
    }
    return (yy__x * yy__factorial((yy__x - 1)));
}
int32_t yy__on_end(int32_t yy__n) 
{
    printf("%jd", ((intmax_t)yy__n));
    yk__sds t__0 = yk__sdsnew(" From defer --> Program Completed\n");
    printf("%s", (t__0));
    yk__sdsfree(t__0);
    return 0;
}
int32_t yy__main() 
{
    int32_t yy__a = 10;
    yk__sds t__1 = yk__sdsnew("b");
    yk__sds yy__b = yk__sdsdup(t__1);
    while (1) {
        if (!((yy__a > 0))) { break; } // Check
        // Body of while loop

        {
            printf("%jd", ((intmax_t)yy__factorial(yy__a)));
            yk__sds t__2 = yk__sdsnew("\n");
            printf("%s", (t__2));
            yy__a = (yy__a - 1);
            yk__sds t__3 = yk__sdsnew("a");
            yk__sds t__4 = yk__sdscatsds(yk__sdsdup(t__3), yy__b);
            yk__sdsfree(yy__b);
            yy__b = yk__sdsdup(t__4);
            yk__sdsfree(t__4);
            yk__sdsfree(t__3);
            yk__sdsfree(t__2);
        }
    }
    printf("%s", (yy__b));
    yk__sds t__5 = yk__sdsnew("\n");
    printf("%s", (t__5));
    (yy__on_end(2));
    (yy__on_end(1));
    yk__sdsfree(t__5);
    yk__sdsfree(yy__b);
    yk__sdsfree(t__1);
    return 0;
}
int main(void) { return yy__main(); }