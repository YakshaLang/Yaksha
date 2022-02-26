#include "yk__lib.h"
// --forward declarations-- 
int32_t yy__main();
// --structs-- 
// --functions-- 
int32_t yy__main() 
{
    yk__sds t__0 = yk__sdsnew("Hello World\n");
    printf("%s", (t__0));
    yk__sdsfree(t__0);
    return 0;
}
int main(void) { return yy__main(); }