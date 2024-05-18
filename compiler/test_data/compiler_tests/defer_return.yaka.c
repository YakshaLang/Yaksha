// YK
#include "yk__lib.h"
struct yy__B;
struct yy__B {
    int32_t yy__a;
};
int32_t yy__f2(struct yy__B*);
int32_t yy__f1();
int32_t yy__main();
int32_t yy__f2(struct yy__B* yy__b) 
{
    int32_t t__0 = yy__b->yy__a;
    return t__0;
}
int32_t yy__f1() 
{
    struct yy__B* yy__b = calloc(1, sizeof(struct yy__B));
    yy__b->yy__a = INT32_C(4);
    int32_t t__1 = yy__f2(yy__b);
    free(yy__b);
    return t__1;
}
int32_t yy__main() 
{
    yk__printlnint((intmax_t)yy__f1());
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif