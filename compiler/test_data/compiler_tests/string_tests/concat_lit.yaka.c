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
    yy__do_something(yk__bstr_s("Oi Hello there Another", 22));
    yy__takes_str(yk__sdsnewlen("Oi Hello there Another", 22));
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif