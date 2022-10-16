// YK
#include "yk__lib.h"
// --forward declarations-- 
int32_t yy__main();
// --structs-- 
// --functions-- 
int32_t yy__main() 
{
    bool yy__a = true;
    bool yy__b = false;
    yk__sds t__0 = yk__sdsnewlen("Hello Word", 10);
    yk__sds yy__c = yk__sdsdup(t__0);
    yk__printlnstr((yy__a) ? "True" : "False");
    yk__printlnstr((yy__b) ? "True" : "False");
    yk__printlnstr(((NULL == yy__c)) ? "True" : "False");
    yk__printlnstr(((yy__c == NULL)) ? "True" : "False");
    yk__sdsfree(yy__c);
    yk__sdsfree(t__0);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif