// YK
#include "yk__lib.h"
// --forward declarations-- 
int32_t yy__main();
// --structs-- 
// --functions-- 
int32_t yy__main() 
{
    uint8_t const * yy__a = ((uint8_t const *)"Hello World");
    yk__sds t__0 = yk__sdsnewlen("ok", 2);
    yk__printlnstr((t__0));
    yk__sdsfree(t__0);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif