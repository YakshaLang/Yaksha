// YK
#include "yk__lib.h"
// --forward declarations-- 
int32_t yy__takes_str(yk__sds);
int32_t yy__main();
// --structs-- 
// --functions-- 
int32_t yy__takes_str(yk__sds yy__s) 
{
    yk__printstr("Printing str: ");
    yk__printlnstr(yy__s);
    yk__sdsfree(yy__s);
    return INT32_C(0);
}
int32_t yy__main() 
{
    yk__sds yy__s = yk__sdsnewlen("Oi" , 2);
    yk__sds yy__s2 = yk__sdsnewlen(" Hello" , 6);
    yk__sds t__0 = yk__sdscatsds(yk__sdsdup(yy__s), yy__s2);
    yy__takes_str(yk__sdsdup(t__0));
    yk__sdsfree(t__0);
    yk__sdsfree(yy__s2);
    yk__sdsfree(yy__s);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif