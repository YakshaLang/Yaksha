// YK
#include "yk__lib.h"
int32_t yy__main();
int32_t yy__main() 
{
    bool yy__a = true;
    bool yy__b = false;
    yk__sds yy__c = yk__sdsnewlen("Hello Word" , 10);
    yk__printlnstr(yy__a ? "True" : "False");
    yk__printlnstr(yy__b ? "True" : "False");
    yk__printlnstr((NULL == yy__c) ? "True" : "False");
    yk__printlnstr((yy__c == NULL) ? "True" : "False");
    yk__sdsfree(yy__c);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif