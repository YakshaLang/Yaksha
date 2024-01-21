// YK
#include "yk__lib.h"
// --forward declarations-- 
struct yt_tuple_int_int_int;
struct yt_tuple_str;
int32_t yy__main();
// --structs-- 
struct yt_tuple_int_int_int { int32_t e1; int32_t e2; int32_t e3; };
struct yt_tuple_str { yk__sds e1; };
// --functions-- 
int32_t yy__main() 
{
    struct yt_tuple_int_int_int yy__a;
    struct yt_tuple_int_int_int yy__b;
    yy__a.e2 = INT32_C(1);
    yy__a.e2 = INT32_C(2);
    yy__a.e3 = INT32_C(3);
    yy__a.e1 = INT32_C(100);
    yk__printlnint((intmax_t)yy__a.e2);
    yk__printlnint((intmax_t)yy__a.e3);
    yk__printlnint((intmax_t)yy__a.e1);
    struct yt_tuple_str yy__c;
    yy__c.e1 = yk__sdsnewlen("Hello", 5);
    yk__printlnstr(yy__c.e1);
    yk__sdsfree(yy__c.e1);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif