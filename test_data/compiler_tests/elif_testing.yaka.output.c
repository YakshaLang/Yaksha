// YK
#include "yk__lib.h"
// --forward declarations-- 
int32_t yy__main();
// --structs-- 
// --functions-- 
int32_t yy__main() 
{
    int32_t yy__x = 0;
    int32_t yy__y = 1;
    if ((yy__y == 0))
    {
        yy__x = 0;
    }
    else
    {
        if ((yy__y == 1))
        {
            yy__x = 1;
        }
        else
        {
            if ((yy__y == 2))
            {
                yy__x = 2;
            }
            else
            {
                yy__x = 100;
            }
        }
    }
    int32_t t__0 = yy__x;
    return t__0;
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif