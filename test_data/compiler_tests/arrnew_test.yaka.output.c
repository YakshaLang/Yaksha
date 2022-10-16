// YK
#include "yk__lib.h"
// --forward declarations-- 
int32_t yy__main();
// --structs-- 
// --functions-- 
int32_t yy__main() 
{
    int32_t* t__0 = NULL;
    yk__arrsetlen(t__0, INT32_C(10));
    int32_t* yy__a = t__0;
    int32_t yy__pos = INT32_C(0);
    int32_t yy__count = yk__arrlen(yy__a);
    yk__sds t__1 = yk__sdsnewlen("Printing garbage int values", 27);
    yk__printlnstr((t__1));
    while (1) {
        if (!((yy__pos < yy__count))) { break; } // Check
        // Body of while loop

        {
            yk__printlnint(((intmax_t)yy__a[yy__pos]));
            yy__pos = (yy__pos + INT32_C(1));
        }
    }
    yk__sds t__2 = yk__sdsnewlen("Success", 7);
    yk__printlnstr((t__2));
    yk__sdsfree(t__2);
    yk__sdsfree(t__1);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif