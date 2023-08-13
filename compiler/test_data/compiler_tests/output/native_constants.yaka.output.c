// YK
#include "yk__lib.h"
// --forward declarations-- 
#define yy__ITEM (1 + 1)
int32_t yy__main();
// --structs-- 
// --functions-- 
int32_t yy__main() 
{
    int32_t yy__a = (yy__ITEM + INT32_C(1));
    yk__printlnint((intmax_t)yy__a);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif