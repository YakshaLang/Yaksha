// YK
#include "yk__lib.h"
// --forward declarations-- 
void yy__world(yk__sds*);
int32_t yy__main();
// --structs-- 
// --functions-- 
void yy__world(yk__sds* nn__a) 
{
    yk__printstr(*nn__a);
    yk__printstr(" world\n");
}
int32_t yy__main() 
{
    yk__sds t__0 = yk__sdsnew("hello");
    yk__sds yy__hello = yk__sdsdup(t__0);
    int32_t yy__i = INT32_C(10);
    while (1) {
        if (!((yy__i > INT32_C(0)))) { break; } // Check
        // Body of while loop

        {
            yy__world((&(yy__hello)));
            yy__i = (yy__i - INT32_C(1));
        }
    }
    yk__sdsfree(yy__hello);
    yk__sdsfree(t__0);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif