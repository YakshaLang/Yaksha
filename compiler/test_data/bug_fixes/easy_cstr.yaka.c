// YK
#include "yk__lib.h"
#define yy__c_CStr char*
void yy__myfunc(yy__c_CStr);
int32_t yy__main();
void yy__myfunc(yy__c_CStr yy__d) 
{
    // pass;
    return;
}
int32_t yy__main() 
{
    yy__myfunc(((yy__c_CStr)"hello\nworld\n"));
    struct yk__bstr yy__a = yk__bstr_s("bug\nfix\nis good" , 15);
    yy__myfunc(((yy__c_CStr)yk__bstr_get_reference(yy__a)));
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif