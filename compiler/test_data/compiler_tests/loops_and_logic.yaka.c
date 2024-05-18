// YK
#include "yk__lib.h"
int32_t yy__main();
int32_t yy__main() 
{
    int32_t yy__a = INT32_C(0);
    int32_t yy__b = INT32_C(0);
    int32_t yy__c = INT32_C(1);
    while (true)
    {
        if (!(((yy__c != INT32_C(0)))))
        {
            break;
        }
        yk__sds yy__d = yk__sdsnewlen("Hello" , 5);
        yy__a += INT32_C(1);
        if (((yy__a % INT32_C(10)) == INT32_C(0)) || (yy__b == INT32_C(0)))
        {
            yy__b += INT32_C(1);
            yk__sdsfree(yy__d);
            continue;
        }
        yk__printlnint((intmax_t)yy__a);
        yk__printlnstr(yy__d);
        yy__b += INT32_C(3);
        if (((yy__b % INT32_C(3)) == INT32_C(0)) && (yy__b > INT32_C(0)))
        {
            yk__sdsfree(yy__d);
            break;
        }
        yk__printlnint((intmax_t)yy__b);
        yk__sdsfree(yy__d);
    }
    int32_t t__0 = yy__c;
    return t__0;
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif