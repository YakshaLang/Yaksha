// YK
#include "yk__lib.h"
typedef yk__sds (*yt_fn_in_str_out_str)(yk__sds);
yk__sds yy__world_formatter(yk__sds);
void yy__formatted_print(yt_fn_in_str_out_str, yk__sds);
int32_t yy__main();
yk__sds yy__world_formatter(yk__sds yy__item) 
{
    yk__sds t__0 = yk__concat_sds_lit(yy__item, " World", 6);
    yk__sds yy__result = yk__sdsdup(t__0);
    yk__sds t__1 = yy__result;
    yk__sdsfree(t__0);
    yk__sdsfree(yy__item);
    return t__1;
}
void yy__formatted_print(yt_fn_in_str_out_str yy__formatter, yk__sds yy__item) 
{
    yk__sds t__2 = yy__formatter(yk__sdsdup(yy__item));
    yk__printlnstr(t__2);
    yk__sdsfree(t__2);
    yk__sdsfree(yy__item);
    return;
}
int32_t yy__main() 
{
    yy__formatted_print(yy__world_formatter, yk__sdsnewlen("Hello", 5));
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif