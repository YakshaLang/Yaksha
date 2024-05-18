// YK
#include "yk__lib.h"
int32_t yy__main();
int32_t yy__main() 
{
    int32_t yy__a = INT32_C(10);
    while (true)
    {
        if (!(((yy__a != INT32_C(0)))))
        {
            break;
        }
        yk__printint((intmax_t)yy__a);
        yk__printstr("\n");
        yy__a = (yy__a - INT32_C(1));
    }
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif