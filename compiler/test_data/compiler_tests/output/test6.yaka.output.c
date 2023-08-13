// YK
#include "yk__lib.h"
// --forward declarations-- 
int32_t yy__main();
// --structs-- 
// --functions-- 
int32_t yy__main() 
{
    int32_t* yy__a = NULL;
    yk__arrput(yy__a, INT32_C(1));
    yk__arrput(yy__a, INT32_C(2));
    yk__arrput(yy__a, INT32_C(3));
    yk__printint((intmax_t)yy__a[INT32_C(0)]);
    yy__a[(INT32_C(0) + INT32_C(0))] = INT32_C(0);
    yk__printint((intmax_t)yy__a[INT32_C(0)]);
    yk__printstr("\n");
    yk__arrfree(yy__a);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif