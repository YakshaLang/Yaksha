// YK
#include "yk__lib.h"
// --forward declarations-- 
struct yk__bstr const yy__BANANA = ((struct yk__bstr){.data.s = "Banana", .l = 6, .t = yk__bstr_static});
yk__sds const  yy__f1(yk__sds const );
struct yk__bstr yy__f2(yk__sds const );
struct yk__bstr const  yy__f3(struct yk__bstr const );
struct yk__bstr const  yy__f4(struct yk__bstr);
struct yk__bstr const  yy__f5(yk__sds);
yk__sds yy__f6(yk__sds const );
int32_t yy__main();
// --structs-- 
// --functions-- 
yk__sds const  yy__f1(yk__sds const  yy__v) 
{
    yk__sds const  t__0 = yy__v;
    return t__0;
}
struct yk__bstr yy__f2(yk__sds const  yy__v) 
{
    return yk__bstr_h(yy__v);
}
struct yk__bstr const  yy__f3(struct yk__bstr const  yy__v) 
{
    struct yk__bstr const  t__1 = yy__v;
    return t__1;
}
struct yk__bstr const  yy__f4(struct yk__bstr yy__v) 
{
    struct yk__bstr t__2 = yy__v;
    return t__2;
}
struct yk__bstr const  yy__f5(yk__sds yy__v) 
{
    return yk__bstr_h(yy__v);
}
yk__sds yy__f6(yk__sds const  yy__v) 
{
    yk__sds const  t__3 = yy__v;
    return t__3;
}
int32_t yy__main() 
{
    yk__sds yy__a = yk__bstr_copy_to_sds(yy__f4(yk__bstr_s("Banana", 6)));
    yk__sds const  yy__b = yk__sdsnewlen("Banana" , 6);
    struct yk__bstr const  yy__c = yy__f5(yk__sdsnewlen("Banana", 6));
    struct yk__bstr yy__d = yk__bstr_s("Banana" , 6);
    struct yk__bstr yy__e = yk__bstr_s("Banana" , 6);
    yk__sds t__4 = yk__concat_sds_lit(yy__f1(yk__sdsdup(yy__a)), "Banana", 6);
    yk__printlnstr(t__4);
    yk__sds t__5 = yk__concat_bstr_bstr(yy__f2(yk__sdsdup(yy__b)), yy__BANANA);
    yk__printlnstr(t__5);
    yk__sds t__6 = yk__concat_bstr_lit(yy__f3(yy__c), "Banana", 6);
    yk__printlnstr(t__6);
    yk__sds t__7 = yk__concat_sds_lit(yy__f1(yk__bstr_copy_to_sds(yy__d)), "Banana", 6);
    yk__printlnstr(t__7);
    yk__sds t__8 = yk__concat_bstr_lit(yy__e, "Banana", 6);
    yk__printlnstr(t__8);
    yy__a = yk__append_sds_sds(yy__a, yy__b);
    yk__sds t__9 = yy__f6(yk__bstr_copy_to_sds(yy__d));
    yy__a = yk__append_sds_sds(yy__a, t__9);
    yy__a = yk__append_sds_bstr(yy__a, yy__e);
    yk__printlnstr(yy__f1(yk__sdsdup(yy__a)));
    yk__sds t__10 = yk__concat_bstr_lit(yy__BANANA, "Banana", 6);
    yk__printlnstr(t__10);
    yk__sdsfree(t__10);
    yk__sdsfree(t__9);
    yk__sdsfree(t__8);
    yk__sdsfree(t__7);
    yk__sdsfree(t__6);
    yk__sdsfree(t__5);
    yk__sdsfree(t__4);
    yk__sdsfree(yy__b);
    yk__sdsfree(yy__a);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif