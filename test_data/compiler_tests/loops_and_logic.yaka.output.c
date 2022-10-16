// YK
#include "yk__lib.h"
// --forward declarations-- 
int32_t yy__main();
// --structs-- 
// --functions-- 
int32_t yy__main() 
{
    int32_t yy__a = INT32_C(0);
    int32_t yy__b = INT32_C(0);
    int32_t yy__c = INT32_C(1);
    while (1) {
        if (!((yy__c != INT32_C(0)))) { break; } // Check
        // Body of while loop

        {
            yk__sds t__0 = yk__sdsnewlen("Hello", 5);
            yk__sds yy__d = yk__sdsdup(t__0);
            yy__a += INT32_C(1);
            if ((((yy__a % INT32_C(10)) == INT32_C(0)) || (yy__b == INT32_C(0))))
            {
                yy__b += INT32_C(1);
                yk__sdsfree(yy__d);
                yk__sdsfree(t__0);
                continue;
            }
            yk__printlnint(((intmax_t)yy__a));
            yk__printlnstr((yy__d));
            yy__b += INT32_C(3);
            if ((((yy__b % INT32_C(3)) == INT32_C(0)) && (yy__b > INT32_C(0))))
            {
                yk__sdsfree(yy__d);
                yk__sdsfree(t__0);
                break;
            }
            yk__printlnint(((intmax_t)yy__b));
            yk__sdsfree(yy__d);
            yk__sdsfree(t__0);
        }
    }
    int32_t t__1 = yy__c;
    return t__1;
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif