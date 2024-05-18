// YK
#include "yk__lib.h"
typedef yk__sds (*yt_fn_in_str_out_str)(yk__sds);
yk__sds yy__normal(yk__sds);
yk__sds yy__sqb(yk__sds);
int32_t yy__main();
yk__sds yy__normal(yk__sds yy__s) 
{
    yk__sds t__0 = yy__s;
    return t__0;
}
yk__sds yy__sqb(yk__sds yy__s) 
{
    yk__sds t__1 = yk__concat_lit_sds("[", 1, yy__s);
    yk__sds t__2 = yk__concat_sds_lit(t__1, "]", 1);
    yk__sds t__3 = t__2;
    yk__sdsfree(t__1);
    yk__sdsfree(yy__s);
    return t__3;
}
int32_t yy__main() 
{
    yt_fn_in_str_out_str yy__a;
    yy__a = (true ? yy__normal : yy__sqb);
    yk__sds t__4 = yy__a(yk__sdsnewlen("Hello World", 11));
    yk__printlnstr(t__4);
    yy__a = (false ? yy__normal : yy__sqb);
    yk__sds t__5 = yy__a(yk__bstr_copy_to_sds((true ? yk__bstr_s("Hello", 5) : yk__bstr_s("World", 5))));
    yk__printlnstr(t__5);
    yk__sdsfree(t__5);
    yk__sdsfree(t__4);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif