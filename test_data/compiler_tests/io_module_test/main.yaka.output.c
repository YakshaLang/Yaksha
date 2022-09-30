// YK
#include "yk__lib.h"
// --forward declarations-- 
bool yy__strings_is_empty_str(yk__sds);
yk__sds yy__io_readfile(yk__sds);
int32_t yy__main();
// --structs-- 
// --functions-- 
bool yy__strings_is_empty_str(yk__sds nn__s) 
{
    bool x = yk__sdslen(nn__s) == 0;
    yk__sdsfree(nn__s);
    return x;
}
yk__sds yy__io_readfile(yk__sds nn__fname) 
{
    size_t ln;
    int err;
    char *out = yk__bhalib_read_file(nn__fname, &ln, &err);
    yk__sdsfree(nn__fname); // clean up filename as it will be copied
    if (err == 0) { return yk__sdsnewlen(out, ln); }
    return yk__sdsempty();
}
int32_t yy__main() 
{
    yk__sds t__0 = yk__sdsnew("// ----->>> this is my code <<<<------\n");
    yk__printstr((t__0));
    yk__sds t__1 = yk__sdsnew("test.c");
    yk__sds t__2 = yy__io_readfile(yk__sdsdup(t__1));
    yk__sds yy__a = yk__sdsdup((t__2));
    if (yy__strings_is_empty_str(yk__sdsdup(yy__a)))
    {
        yk__sds t__3 = yk__sdsnew("test.c is empty or not found");
        yk__printstr((t__3));
        yk__sdsfree(t__3);
    }
    else
    {
        yk__printstr((yy__a));
    }
    yk__sdsfree(yy__a);
    yk__sdsfree(t__2);
    yk__sdsfree(t__1);
    yk__sdsfree(t__0);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif