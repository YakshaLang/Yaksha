// YK
#include "yk__lib.h"
// --forward declarations-- 
#define yy__min_int(nn__a, nn__b) ((nn__a < nn__b) ? nn__a : nn__b)
#define yy__max_int(nn__a, nn__b) ((nn__a > nn__b) ? nn__a : nn__b)
#define yy__banana banana
#define yy__Something something
#define yy__Color Color
#define yy__new yk__newsdsarray
yk__sds yy__get_arg(int32_t);
yk__sds yy__get_global_arg(int32_t);
int32_t yy__main();
// --structs-- 
// --functions-- 
yk__sds yy__get_arg(int32_t nn__n) { return getarg(nn__n); }
yk__sds yy__get_global_arg(int32_t nn__n) 
{
    yk__sdsdup(global_args[yy__n]);
}
int32_t yy__main() 
{
    yk__sds t__0 = yk__sdsnewlen("hello world", 11);
    yk__printlnstr((t__0));
    yk__sdsfree(t__0);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif