// YK
#include "yk__lib.h"
// --forward declarations-- 
int32_t yy__main();
// --structs-- 
// --functions-- 
int32_t yy__main() 
{
    yk__printlnstr("Fixed Array looping");
    int32_t yy__a[3] = {};
    yy__a[INT32_C(0)] = INT32_C(1);
    yy__a[INT32_C(1)] = INT32_C(2);
    yy__a[INT32_C(2)] = INT32_C(3);
    struct yk__bstr yy__b[3] = {};
    yy__b[INT32_C(0)] = yk__bstr_s("hello", 5);
    yy__b[INT32_C(1)] = yk__bstr_s("world", 5);
    yy__b[INT32_C(2)] = yk__bstr_s("!", 1);
    int32_t[3]* yy__0t = (&(yy__a));
    int32_t yy__1t = INT32_C(0);
    while (true)
    {
        if (!(((yy__1t < INT32_C(3)))))
        {
            break;
        }
        yk__printlnint((intmax_t)(yy__0t[yy__1t]));
        yy__1t += INT32_C(1);
    }
    struct yk__bstr[3]* yy__2t = (&(yy__b));
    int32_t yy__3t = INT32_C(0);
    while (true)
    {
        if (!(((yy__3t < INT32_C(3)))))
        {
            break;
        }
        yk__printlnstr(yk__bstr_get_reference((yy__2t[yy__3t])));
        yy__3t += INT32_C(1);
    }
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif