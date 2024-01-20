// YK
#include "yk__lib.h"
// --forward declarations-- 
int32_t yy__main();
// --structs-- 
// --functions-- 
int32_t yy__main() 
{
    uint8_t* g_yy__0 = (uint8_t*)&gKernelBase[0x6A8EB0];
    g_yy__0[INT32_C(0)] = UINT8_C(49);
    g_yy__0[INT32_C(1)] = UINT8_C(192);
    g_yy__0[INT32_C(2)] = UINT8_C(195);
    g_yy__0[INT32_C(3)] = UINT8_C(144);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif