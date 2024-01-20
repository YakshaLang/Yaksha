// YK
#include "yk__lib.h"
// --forward declarations-- 
int32_t yy__bin_numbers();
int32_t yy__oct_numbers();
int32_t yy__dec_numbers();
int32_t yy__hex_numbers();
int32_t yy__main();
// --structs-- 
// --functions-- 
int32_t yy__bin_numbers() 
{
    int8_t yy__a = INT8_C(15);
    int16_t yy__b = INT16_C(14);
    int32_t yy__c = INT32_C(13);
    int64_t yy__d = INT64_C(11);
    uint8_t yy__e = UINT8_C(7);
    uint16_t yy__f = UINT16_C(14);
    uint32_t yy__g = UINT32_C(11);
    uint64_t yy__h = UINT64_C(13);
    return INT32_C(0);
}
int32_t yy__oct_numbers() 
{
    int8_t yy__a = INT8_C(11);
    int16_t yy__b = INT16_C(10);
    int32_t yy__c = INT32_C(31);
    int64_t yy__d = INT64_C(39);
    uint8_t yy__e = UINT8_C(15);
    uint16_t yy__f = UINT16_C(12);
    uint32_t yy__g = UINT32_C(47);
    uint64_t yy__h = UINT64_C(55);
    return INT32_C(0);
}
int32_t yy__dec_numbers() 
{
    int8_t yy__a = INT8_C(1);
    int16_t yy__b = INT16_C(2);
    int32_t yy__c = INT32_C(3);
    int64_t yy__d = INT64_C(4);
    uint8_t yy__e = UINT8_C(1);
    uint16_t yy__f = UINT16_C(2);
    uint32_t yy__g = UINT32_C(3);
    uint64_t yy__h = UINT64_C(4);
    return INT32_C(0);
}
int32_t yy__hex_numbers() 
{
    int8_t yy__a = INT8_C(10);
    int16_t yy__b = INT16_C(11);
    int32_t yy__c = INT32_C(12);
    int64_t yy__d = INT64_C(13);
    uint8_t yy__e = UINT8_C(14);
    uint16_t yy__f = UINT16_C(15);
    uint32_t yy__g = UINT32_C(9);
    uint64_t yy__h = UINT64_C(8);
    return INT32_C(0);
}
int32_t yy__main() 
{
    yy__bin_numbers();
    yy__oct_numbers();
    yy__dec_numbers();
    yy__hex_numbers();
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif