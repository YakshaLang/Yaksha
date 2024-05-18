// YK
#include "yk__lib.h"
struct yk__bstr yy__a();
yk__sds yy__b();
struct yk__bstr yy__c();
int32_t yy__main();
struct yk__bstr yy__a() 
{
    return yk__bstr_s("Hello", 5);
}
yk__sds yy__b() 
{
    struct yk__bstr yy__x = yk__bstr_s("Hello" , 5);
    return yk__bstr_copy_to_sds(yy__x);
}
struct yk__bstr yy__c() 
{
    struct yk__bstr yy__y = yk__bstr_s("Oi" , 2);
    struct yk__bstr t__0 = yy__y;
    return t__0;
}
int32_t yy__main() 
{
    yk__printlnstr(yk__bstr_get_reference(yy__a()));
    yk__sds t__1 = yy__b();
    yk__printlnstr(t__1);
    yk__printlnstr(yk__bstr_get_reference(yy__c()));
    yk__sdsfree(t__1);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif