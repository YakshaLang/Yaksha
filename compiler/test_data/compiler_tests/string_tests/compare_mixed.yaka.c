// YK
#include "yk__lib.h"
// --forward declarations-- 
int32_t yy__main();
// --structs-- 
// --functions-- 
int32_t yy__main() 
{
    yk__sds yy__a = yk__sdsnewlen("a" , 1);
    struct yk__bstr yy__b = yk__bstr_s("oi" , 2);
    yk__printlnstr(((yk__cmp_bstr_bstr(yy__b, yy__b) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__sdscmp(yy__a , yy__a) == 0)) ? "True" : "False");
    yk__printlnstr(((((yk__cmp_sds_bstr(yy__a, yy__b) == 0)) || ((yk__cmp_sds_bstr(yy__a, yy__b) != 0)))) ? "True" : "False");
    yk__printlnstr(((yk__cmp_lit_sds("a", 1, yy__a) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_bstr_sds(yy__b, yy__a) != 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_bstr_lit(yy__b, "x", 1) != 0)) ? "True" : "False");
    yk__sdsfree(yy__a);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif