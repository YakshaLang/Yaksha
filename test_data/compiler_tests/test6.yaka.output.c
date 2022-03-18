// YK
#include "yk__lib.h"
// --forward declarations-- 
int32_t yy__main();
// --structs-- 
// --functions-- 
int32_t yy__main() 
{
    int32_t* yy__a = NULL;
    yk__arrput(yy__a, 1);
    yk__arrput(yy__a, 2);
    yk__arrput(yy__a, 3);
    printf("%jd", ((intmax_t)yy__a[0]));
    yy__a[(0 + 0)] = 0;
    printf("%jd", ((intmax_t)yy__a[0]));
    yk__sds t__0 = yk__sdsnew("\n");
    yk__printstr((t__0));
    yk__arrfree(yy__a);
    yk__sdsfree(t__0);
    return 0;
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif