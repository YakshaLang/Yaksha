// YK
#include "yk__lib.h"
// --forward declarations-- 
int32_t yy__do_something(struct yk__bstr);
int32_t yy__takes_str(yk__sds);
int32_t yy__main();
// --structs-- 
// --functions-- 
int32_t yy__do_something(struct yk__bstr yy__s) 
{
    yk__printstr("Printing sr: ");
    yk__printlnstr(yk__bstr_get_reference(yy__s));
    return INT32_C(0);
}
int32_t yy__takes_str(yk__sds yy__s) 
{
    yk__printstr("Printing str: ");
    yk__printlnstr(yy__s);
    yk__sdsfree(yy__s);
    return INT32_C(0);
}
int32_t yy__main() 
{
    yk__sds yy__a = yk__sdsnewlen("Hello" , 5);
    struct yk__bstr yy__b = yk__bstr_s(" World" , 6);
    yk__sds t__0 = yk__concat_sds_bstr(yy__a, yy__b);
    yk__sds t__1 = yk__concat_sds_lit(t__0, " Hehe", 5);
    yk__sds yy__c = yk__sdsdup(t__1);
    yy__do_something(yk__bstr_h(yy__c));
    yy__takes_str(yk__sdsdup(yy__c));
    yk__sds t__2 = yk__concat_lit_bstr("Ha ", 3, yy__b);
    yk__sds t__3 = yk__concat_sds_lit(t__2, " ", 1);
    yk__sds t__4 = yk__sdscatsds(yk__sdsdup(t__3), yy__a);
    yk__sds yy__d = yk__sdsdup(t__4);
    yy__takes_str(yk__sdsdup(yy__d));
    yy__do_something(yk__bstr_h(yy__d));
    yk__sdsfree(yy__d);
    yk__sdsfree(t__4);
    yk__sdsfree(t__3);
    yk__sdsfree(t__2);
    yk__sdsfree(yy__c);
    yk__sdsfree(t__1);
    yk__sdsfree(t__0);
    yk__sdsfree(yy__a);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif