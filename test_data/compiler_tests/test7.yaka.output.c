#include "yk__lib.h"
// --forward declarations-- 
int32_t yy__main();
// --structs-- 
// --functions-- 
int32_t yy__main() 
{
    int32_t** yy__a = NULL;
    int32_t* yy__b = NULL;
    yk__arrput(yy__b, 1);
    yk__arrput(yy__a, yy__b);
    printf("%jd", ((intmax_t)yy__a[0][0]));
    yk__sds t__0 = yk__sdsnew("\n");
    printf("%s", (t__0));
    yy__a[0][0] = 100;
    printf("%jd", ((intmax_t)yy__a[0][0]));
    yk__sds t__1 = yk__sdsnew("\n");
    printf("%s", (t__1));
    yk__arrfree(yy__b);
    yk__arrfree(yy__a);
    yk__sdsfree(t__1);
    yk__sdsfree(t__0);
    return 0;
}
int main(void) { return yy__main(); }