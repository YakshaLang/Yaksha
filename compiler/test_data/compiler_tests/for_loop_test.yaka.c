// YK
#include "yk__lib.h"
int32_t yy__add(int32_t, int32_t);
int32_t yy__main();
int32_t yy__add(int32_t yy__a, int32_t yy__b) 
{
    int32_t t__0 = (yy__a + yy__b);
    return t__0;
}
int32_t yy__main() 
{
    for (int32_t yy__x = INT32_C(0);(yy__x < INT32_C(10));yy__x = (yy__x + INT32_C(1)))
    {
        yk__printlnint((intmax_t)yy__x);
    }
    yk__sds yy__a = yk__sdsnewlen("" , 0);
    for (int32_t yy__x = INT32_C(0);(yy__x < INT32_C(4));yy__x += INT32_C(1))
    {
        yy__a = yk__append_sds_lit(yy__a, "hello " , 6);
    }
    yk__printlnstr(yy__a);
    yk__sds yy__b = yk__sdsnewlen("" , 0);
    yk__sds yy__c = yk__sdsnewlen("x" , 1);
    for (yy__b = yk__append_sds_sds(yy__b, yy__c);(yk__cmp_sds_lit(yy__b, "xxx", 3) != 0);yy__b = yk__append_sds_sds(yy__b, yy__c))
    {
        // pass;
    }
    yk__printlnstr(yy__b);
    for (int32_t yy__x = INT32_C(0);(yy__x < ((int32_t)(INT8_C(10))));yy__x = yy__add(yy__x, INT8_C(2)))
    {
        yk__printlnint((intmax_t)yy__x);
    }
    yk__sdsfree(yy__c);
    yk__sdsfree(yy__b);
    yk__sdsfree(yy__a);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif