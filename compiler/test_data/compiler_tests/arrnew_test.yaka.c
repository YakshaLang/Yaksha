// YK
#include "yk__lib.h"
int32_t yy__main();
int32_t yy__main() 
{
    int32_t* t__0 = NULL;
    yk__arrsetlen(t__0, INT32_C(10));
    int32_t* yy__a = t__0;
    int32_t yy__pos = INT32_C(0);
    int32_t yy__count = yk__arrlen(yy__a);
    yk__printlnstr("Printing garbage int values");
    while (true)
    {
        if (!(yy__pos < yy__count))
        {
            break;
        }
        yk__printlnint((intmax_t)yy__a[yy__pos]);
        yy__pos = (yy__pos + INT32_C(1));
    }
    yk__printlnstr("Success");
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif