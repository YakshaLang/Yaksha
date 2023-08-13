// YK
#include "yk__lib.h"
// --forward declarations-- 
void yy__g3_g3();
void yy__g2_g2();
int32_t yy__main();
// --structs-- 
// --functions-- 
void yy__g3_g3() 
{
    int32_t yy__g3_a = INT32_C(1);
    yk__printlnint((intmax_t)yy__g3_a);
    int32_t g_yy__g3_0 = INT32_C(300);
    yk__printlnint((intmax_t)g_yy__g3_0);
    return;
}
void yy__g2_g2() 
{
    int32_t yy__g2_a = INT32_C(1);
    yk__printlnint((intmax_t)yy__g2_a);
    int32_t g_yy__g2_1 = INT32_C(200);
    yk__printlnint((intmax_t)g_yy__g2_1);
    yy__g3_g3();
    return;
}
int32_t yy__main() 
{
    int32_t yy__a = INT32_C(1);
    yk__printlnint((intmax_t)yy__a);
    int32_t g_yy__2 = INT32_C(2);
    yk__printlnint((intmax_t)g_yy__2);
    yy__g2_g2();
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif