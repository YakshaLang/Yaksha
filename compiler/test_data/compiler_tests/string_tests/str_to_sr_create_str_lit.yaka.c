// YK
#include "yk__lib.h"
int32_t yy__do_something(struct yk__bstr);
int32_t yy__main();
int32_t yy__do_something(struct yk__bstr yy__s) 
{
    yk__printstr("Printing sr: ");
    yk__printlnstr(yk__bstr_get_reference(yy__s));
    return INT32_C(0);
}
int32_t yy__main() 
{
    yk__sds yy__s = yk__sdsnewlen("Oi" , 2);
    yk__sds yy__s2 = yk__sdsnewlen("Ha" , 2);
    yy__do_something(yk__bstr_h(yy__s));
    yy__do_something(yk__bstr_h(yy__s2));
    yk__sdsfree(yy__s2);
    yk__sdsfree(yy__s);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif