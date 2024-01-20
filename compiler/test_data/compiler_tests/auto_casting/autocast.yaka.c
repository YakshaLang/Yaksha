// YK
#include "yk__lib.h"
// --forward declarations-- 
int32_t const  yy__A = ((int32_t)(INT8_C(10)));
int8_t const  yy__B = INT8_C(10);
int8_t const  yy__C = ((int8_t)(((false) ? 1 : 0)));
int32_t yy__main();
// --structs-- 
// --functions-- 
int32_t yy__main() 
{
    int32_t const  yy__a = ((int32_t)(INT8_C(1)));
    int32_t const  yy__b = ((int32_t)(INT8_C(2)));
    int32_t yy__c = (yy__a + yy__b);
    int32_t yy__d = ((yy__c + yy__a) + yy__b);
    int32_t yy__e = (yy__d + INT32_C(1));
    int32_t yy__f = (yy__a + ((int32_t)(INT16_C(1))));
    float yy__g = ((float)(yy__d));
    double yy__h = ((double)((((float)(yy__a)) + yy__g)));
    float yy__i = (((float)(yy__a)) * yy__g);
    double yy__j = ((((double)((yy__a / yy__b))) * yy__h) + ((double)(((((INT32_C(1) == INT32_C(1)))) ? 1 : 0))));
    double yy__k = ((((double)((yy__a / yy__b))) * yy__h) + ((double)(INT64_C(5))));
    int32_t yy__l = ((int32_t)(((((INT32_C(2) != INT32_C(10)))) ? 1 : 0)));
    int32_t const  yy__m = ((int32_t)(INT8_C(10)));
    yk__printstr("\"a\"");
    yk__printstr(" = ");
    yk__printlnint((intmax_t)yy__a);
    yk__printstr("\"b\"");
    yk__printstr(" = ");
    yk__printlnint((intmax_t)yy__b);
    yk__printstr("\"c\"");
    yk__printstr(" = ");
    yk__printlnint((intmax_t)yy__c);
    yk__printstr("\"d\"");
    yk__printstr(" = ");
    yk__printlnint((intmax_t)yy__d);
    yk__printstr("\"e\"");
    yk__printstr(" = ");
    yk__printlnint((intmax_t)yy__e);
    yk__printstr("\"f\"");
    yk__printstr(" = ");
    yk__printlnint((intmax_t)yy__f);
    yk__printstr("\"g\"");
    yk__printstr(" = ");
    yk__printlndbl(yy__g);
    yk__printstr("\"h\"");
    yk__printstr(" = ");
    yk__printlndbl(yy__h);
    yk__printstr("\"i\"");
    yk__printstr(" = ");
    yk__printlndbl(yy__i);
    yk__printstr("\"j\"");
    yk__printstr(" = ");
    yk__printlndbl(yy__j);
    yk__printstr("\"k\"");
    yk__printstr(" = ");
    yk__printlndbl(yy__k);
    yk__printstr("\"l\"");
    yk__printstr(" = ");
    yk__printlnint((intmax_t)yy__l);
    yk__printstr("\"A\"");
    yk__printstr(" = ");
    yk__printlnint((intmax_t)yy__A);
    yk__printstr("\"B\"");
    yk__printstr(" = ");
    yk__printlnint((intmax_t)yy__B);
    yk__printstr("\"C\"");
    yk__printstr(" = ");
    yk__printlnint((intmax_t)yy__C);
    return INT8_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif