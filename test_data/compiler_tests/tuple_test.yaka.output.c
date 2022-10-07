// YK
#include "yk__lib.h"
// --forward declarations-- 
struct yktuple0;
struct yktuple1;
int32_t yy__main();
// --structs-- 
struct yktuple0 { int32_t e1; int32_t e2; int32_t e3; };
struct yktuple1 { yk__sds e1; };
// --functions-- 
int32_t yy__main() 
{
    struct yktuple0 yy__a;
    struct yktuple0 yy__b;
    yy__a.e2 = INT32_C(1);
    yy__a.e2 = INT32_C(2);
    yy__a.e3 = INT32_C(3);
    yy__a.e1 = INT32_C(100);
    yk__printlnint(((intmax_t)yy__a.e2));
    yk__printlnint(((intmax_t)yy__a.e3));
    yk__printlnint(((intmax_t)yy__a.e1));
    struct yktuple1 yy__c;
    yk__sds t__0 = yk__sdsnew("Hello");
    yy__c.e1 = yk__sdsdup(t__0);
    yk__printlnstr((yy__c.e1));
    yk__sdsfree(yy__c.e1);
    yk__sdsfree(t__0);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif