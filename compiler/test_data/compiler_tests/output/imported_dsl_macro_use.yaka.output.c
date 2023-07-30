// YK
#include "yk__lib.h"
// --forward declarations-- 
int32_t yy__main();
// --structs-- 
// --functions-- 
int32_t yy__main() 
{
    yk__printlnint(((intmax_t)INT32_C(2)));
    yk__printlnint(((intmax_t)INT32_C(4)));
    yk__printlnint(((intmax_t)INT32_C(6)));
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif