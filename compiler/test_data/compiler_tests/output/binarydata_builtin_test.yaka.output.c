// YK
#include "yk__lib.h"
// --forward declarations-- 
uint8_t const ykbindata0[] = {
UINT8_C(0x48), UINT8_C(0x65), UINT8_C(0x6c), UINT8_C(0x6c),
UINT8_C(0x6f), UINT8_C(0x20), UINT8_C(0x57), UINT8_C(0x6f),
UINT8_C(0x72), UINT8_C(0x6c), UINT8_C(0x64)
};
uint8_t const ykbindata1[] = {
UINT8_C(0x48), UINT8_C(0x65), UINT8_C(0x6c), UINT8_C(0x6c),
UINT8_C(0x6f), UINT8_C(0x20), UINT8_C(0x4c), UINT8_C(0x6f),
UINT8_C(0x6e), UINT8_C(0x64), UINT8_C(0x6f), UINT8_C(0x6e)
};
int32_t yy__main();
// --structs-- 
// --functions-- 
int32_t yy__main() 
{
    uint8_t const * yy__a = ykbindata0;
    uint8_t const * yy__b = ykbindata0;
    uint8_t const * yy__c = ykbindata1;
    yk__sds t__0 = yk__sdsnewlen("ok", 2);
    yk__printlnstr((t__0));
    yk__sdsfree(t__0);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif