// YK
#include "yk__lib.h"
// --forward declarations-- 
typedef yk__sds (*ykfncptr0)(yk__sds);
typedef void (*ykfncptr2)(int32_t);
typedef yk__sds (*ykfncptr1)(ykfncptr2);
void yy__a(ykfncptr0);
void yy__b(ykfncptr0);
void yy__c(ykfncptr1);
int32_t yy__main();
// --structs-- 
// --functions-- 
void yy__a(ykfncptr0 yy__formatter) 
{
    yk__printstr("hello");
    return;
}
void yy__b(ykfncptr0 yy__formatter) 
{
    yk__printstr("hello");
    return;
}
void yy__c(ykfncptr1 yy__formatter) 
{
    yk__printstr("hello");
    return;
}
int32_t yy__main() 
{
    yk__printlnstr("Hello World");
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif