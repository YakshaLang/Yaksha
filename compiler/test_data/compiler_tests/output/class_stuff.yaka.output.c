// YK
#include "yk__lib.h"
// --forward declarations-- 
struct yy__A;
struct yy__B;
int32_t yy__main();
// --structs-- 
struct yy__A {
    int32_t yy__a;
};
struct yy__B {
    int32_t yy__b;
};
// --functions-- 
int32_t yy__main() 
{
    struct yy__A* yy__a = calloc(1, sizeof(struct yy__A));
    yy__a->yy__a = INT32_C(1);
    struct yy__B* yy__b = calloc(1, sizeof(struct yy__B));
    yy__b->yy__b = INT32_C(10);
    yk__printlnint((intmax_t)yy__a->yy__a);
    int32_t t__0 = yy__b->yy__b;
    free(yy__b);
    free(yy__a);
    return t__0;
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif