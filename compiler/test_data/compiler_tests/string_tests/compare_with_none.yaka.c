// YK
#include "yk__lib.h"
// --forward declarations-- 
int32_t yy__main();
// --structs-- 
// --functions-- 
int32_t yy__main() 
{
    struct yk__bstr yy__a = yk__bstr_s("a" , 1);
    yk__sds yy__b = yk__sdsnewlen("b" , 1);
    yk__printlnstr(((yk__bstr_get_reference(yy__a) == NULL)) ? "True" : "False");
    yk__printlnstr((yy__b == NULL) ? "True" : "False");
    yk__printlnstr("True");
    yk__printlnstr("False");
    yk__printlnstr(((NULL != yk__bstr_get_reference(yy__a))) ? "True" : "False");
    yk__printlnstr((NULL != yy__b) ? "True" : "False");
    yk__printlnstr("False");
    yk__printlnstr("True");
    yk__sdsfree(yy__b);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif