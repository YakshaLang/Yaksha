// YK
#include "yk__lib.h"
// --forward declarations-- 
int32_t yy__main();
// --structs-- 
// --functions-- 
int32_t yy__main() 
{
    int32_t yy__a = INT32_C(0);
    bool yy__b = true;
    for (int32_t yy__x = INT32_C(0);(yy__x < INT32_C(10));yy__x = (yy__x + INT32_C(1)))
    {
        yy__a += ((int32_t)(((yy__b) ? 1 : 0)));
    }
    yk__printlnint((intmax_t)yy__a);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif