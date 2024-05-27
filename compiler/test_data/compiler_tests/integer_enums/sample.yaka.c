// YK
#include "yk__lib.h"
struct yy__My;
struct yy__My {
    int32_t yy__a;
    int32_t yy__b;
    int32_t yy__c;
    int32_t yy__d;
};
int32_t yy__main();
int32_t yy__main() 
{
    struct yy__My* t__0 = calloc(1, sizeof(struct yy__My));
    t__0->yy__a = (INT32_C(0));
    t__0->yy__b = (INT32_C(0));
    t__0->yy__c = (0);
    t__0->yy__d = (0);
    struct yy__My* yy__g = t__0;
    int32_t yy__a = 0;
    int32_t yy__b = 1;
    int32_t yy__c = 2;
    int32_t yy__a0 = 0;
    int32_t yy__bx = 0;
    int32_t yy__by = 1;
    int32_t yy__d = INT32_C(0);
    if (yy__a == yy__a0)
    {
        yy__d += INT32_C(2);
    }
    if (yy__a != yy__b)
    {
        yy__d += INT32_C(3);
    }
    else
    {
        yy__d += INT32_C(100);
    }
    if (yy__c == yy__c)
    {
        yy__d += INT32_C(1);
    }
    if (yy__c != yy__c)
    {
        yy__d += INT32_C(1000);
    }
    if ((yy__bx == 0) && (yy__bx == yy__g->yy__c))
    {
        yy__d += INT32_C(5);
    }
    if (yy__bx != yy__by)
    {
        yy__d += INT32_C(7);
    }
    else
    {
        yy__d += INT32_C(10000);
    }
    int32_t t__1 = yy__d;
    return t__1;
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif