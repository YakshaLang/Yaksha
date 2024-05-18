// YK
#include "yk__lib.h"
struct yk__bstr const yy__BANANA = ((struct yk__bstr){.data.s = "Banana", .l = 6, .t = yk__bstr_static});
int32_t yy__main();
int32_t yy__main() 
{
    yk__sds yy__a = yk__sdsnewlen("Banana" , 6);
    yk__sds const  yy__b = yk__sdsnewlen("Banana" , 6);
    struct yk__bstr const  yy__c = yk__bstr_s("Banana" , 6);
    struct yk__bstr yy__d = yk__bstr_s("Banana" , 6);
    struct yk__bstr yy__e = yk__bstr_s("Banana" , 6);
    yk__printlnstr(((yk__cmp_sds_lit(yy__a, "Banana", 6) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_sds_lit(yy__b, "Banana", 6) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_bstr_lit(yy__c, "Banana", 6) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_bstr_lit(yy__d, "Banana", 6) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_bstr_lit(yy__e, "Banana", 6) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_lit_sds("Banana", 6, yy__a) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_lit_sds("Banana", 6, yy__b) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_lit_bstr("Banana", 6, yy__c) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_lit_bstr("Banana", 6, yy__d) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_lit_bstr("Banana", 6, yy__e) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_sds_bstr(yy__a, yy__BANANA) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__sdscmp(yy__a , yy__a) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__sdscmp(yy__a , yy__b) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_sds_bstr(yy__a, yy__c) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_sds_bstr(yy__a, yy__d) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_sds_bstr(yy__a, yy__e) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_sds_bstr(yy__b, yy__BANANA) == 0)) ? "True" : "False");
    yk__printlnstr((yy__b == yy__a) ? "True" : "False");
    yk__printlnstr((yy__b == yy__b) ? "True" : "False");
    yk__printlnstr(((yk__cmp_sds_bstr(yy__b, yy__c) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_sds_bstr(yy__b, yy__d) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_sds_bstr(yy__b, yy__e) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_bstr_bstr(yy__c, yy__BANANA) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_bstr_sds(yy__c, yy__a) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_bstr_sds(yy__c, yy__b) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_bstr_bstr(yy__c, yy__c) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_bstr_bstr(yy__c, yy__d) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_bstr_bstr(yy__c, yy__e) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_bstr_bstr(yy__d, yy__BANANA) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_bstr_sds(yy__d, yy__a) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_bstr_sds(yy__d, yy__b) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_bstr_bstr(yy__d, yy__c) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_bstr_bstr(yy__d, yy__d) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_bstr_bstr(yy__d, yy__e) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_bstr_bstr(yy__e, yy__BANANA) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_bstr_sds(yy__e, yy__a) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_bstr_sds(yy__e, yy__b) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_bstr_bstr(yy__e, yy__c) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_bstr_bstr(yy__e, yy__d) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_bstr_bstr(yy__e, yy__e) == 0)) ? "True" : "False");
    yk__printlnstr(((yk__cmp_bstr_lit(yy__BANANA, "Banana", 6) == 0)) ? "True" : "False");
    yk__sdsfree(yy__b);
    yk__sdsfree(yy__a);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif