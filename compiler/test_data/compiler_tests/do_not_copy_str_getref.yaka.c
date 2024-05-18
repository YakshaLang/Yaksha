// YK
#include "yk__lib.h"
void yy__world(yk__sds*);
int32_t yy__main();
void yy__world(yk__sds* nn__a) 
{
    yk__printstr(*nn__a);
    yk__printstr(" world\n");
}
int32_t yy__main() 
{
    yk__sds yy__hello = yk__sdsnewlen("hello" , 5);
    int32_t yy__i = INT32_C(10);
    while (true)
    {
        if (!(((yy__i > INT32_C(0)))))
        {
            break;
        }
        yy__world((&(yy__hello)));
        yy__i = (yy__i - INT32_C(1));
    }
    yk__sdsfree(yy__hello);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif