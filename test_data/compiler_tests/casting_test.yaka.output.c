// YK
#include "yk__lib.h"
// --forward declarations-- 
struct yy__B;
#define yy__A void*
yy__A yy__toA(struct yy__B*);
int32_t yy__main();
// --structs-- 
struct yy__B {
    int32_t yy__a;
};
// --functions-- 
yy__A yy__toA(struct yy__B* yy__b) 
{
    yy__A t__0 = ((yy__A)yy__b);
    return t__0;
}
int32_t yy__main() 
{
    struct yy__B* yy__b = calloc(1, sizeof(struct yy__B));
    yy__b->yy__a = 1;
    yy__A yy__a = ((yy__A)yy__b);
    yy__A yy__a2 = yy__toA(yy__b);
    return 0;
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif