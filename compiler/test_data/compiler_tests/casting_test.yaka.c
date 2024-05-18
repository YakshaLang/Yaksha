// YK
#include "yk__lib.h"
#define yy__A void*
struct yy__B;
struct yy__B {
    int32_t yy__a;
};
yy__A yy__toA(struct yy__B*);
int32_t yy__main();
yy__A yy__toA(struct yy__B* yy__b) 
{
    yy__A t__0 = ((yy__A)yy__b);
    return t__0;
}
int32_t yy__main() 
{
    struct yy__B* yy__b = calloc(1, sizeof(struct yy__B));
    yy__b->yy__a = INT32_C(1);
    yy__A yy__a = ((yy__A)yy__b);
    yy__A yy__a2 = yy__toA(yy__b);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif