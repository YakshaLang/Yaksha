// YK
#include "yk__lib.h"
// --forward declarations-- 
void yy__print_a(int32_t);
int32_t yy__augment_equal_a();
void yy__print_b(float);
int32_t yy__augment_equal_b();
void yy__print_c(double);
int32_t yy__augment_equal_c();
int32_t yy__additional_operators();
int32_t yy__main();
// --structs-- 
// --functions-- 
void yy__print_a(int32_t yy__a) 
{
    yk__printstr("a is now ");
    yk__printlnint((intmax_t)yy__a);
    return;
}
int32_t yy__augment_equal_a() 
{
    int32_t yy__a = INT32_C(0);
    yy__print_a(yy__a);
    yy__a += INT32_C(4);
    yy__print_a(yy__a);
    yy__a -= INT32_C(2);
    yy__print_a(yy__a);
    yy__a >>= INT32_C(1);
    yy__print_a(yy__a);
    yy__a <<= INT32_C(1);
    yy__print_a(yy__a);
    yy__a *= INT32_C(2);
    yy__print_a(yy__a);
    yy__a %= INT32_C(5);
    yy__print_a(yy__a);
    yy__a /= INT32_C(2);
    yy__print_a(yy__a);
    yy__a |= INT32_C(12);
    yy__print_a(yy__a);
    yy__a ^= INT32_C(78);
    yy__print_a(yy__a);
    yy__a &= INT32_C(2);
    yy__print_a(yy__a);
    return INT32_C(1);
}
void yy__print_b(float yy__b) 
{
    yk__printstr("b is now ");
    yk__printlndbl(yy__b);
    return;
}
int32_t yy__augment_equal_b() 
{
    float yy__b = 0.0f;
    yy__print_b(yy__b);
    yy__b += 4.0f;
    yy__print_b(yy__b);
    yy__b -= 2.0f;
    yy__print_b(yy__b);
    yy__b *= 2.0f;
    yy__print_b(yy__b);
    yy__b = remainderf(yy__b, 5.0f);
    yy__print_b(yy__b);
    yy__b /= 2.0f;
    yy__print_b(yy__b);
    return INT32_C(2);
}
void yy__print_c(double yy__c) 
{
    yk__printstr("c is now ");
    yk__printlndbl(yy__c);
    return;
}
int32_t yy__augment_equal_c() 
{
    double yy__c = 0.0;
    yy__print_c(yy__c);
    yy__c += 4.0;
    yy__print_c(yy__c);
    yy__c -= 2.0;
    yy__print_c(yy__c);
    yy__c *= 2.0;
    yy__print_c(yy__c);
    yy__c = remainder(yy__c, 5.0);
    yy__print_c(yy__c);
    yy__c /= 2.0;
    yy__print_c(yy__c);
    return INT32_C(3);
}
int32_t yy__additional_operators() 
{
    yk__sds yy__a = yk__sdsnewlen("Hello" , 5);
    yk__sds yy__b = yk__sdsnewlen("World" , 5);
    bool yy__c = (yk__sdscmp(yy__a , yy__b) != 0);
    float yy__d = 5.0f;
    float yy__e = 4.0f;
    double yy__f = 10.0;
    double yy__g = 20.0;
    if (yy__c)
    {
        yy__e = remainderf(yy__d, yy__e);
    }
    else
    {
        yy__g = remainder(yy__f, yy__g);
    }
    yk__sdsfree(yy__b);
    yk__sdsfree(yy__a);
    return INT32_C(0);
}
int32_t yy__main() 
{
    int32_t yy__v = INT32_C(0);
    yy__v += yy__augment_equal_a();
    yy__v += yy__augment_equal_b();
    yy__v += yy__augment_equal_c();
    yy__v += yy__additional_operators();
    yk__printstr("v=");
    yk__printlnint((intmax_t)yy__v);
    yk__printstr("r=");
    int32_t yy__r = (((INT32_C(1) << INT32_C(2)) ^ (INT32_C(57005) & INT32_C(51966))) | (INT32_C(48864) >> INT32_C(1)));
    yk__printlnint((intmax_t)yy__r);
    yk__sds yy__s = yk__sdsnewlen("Hello" , 5);
    yy__s = yk__append_sds_lit(yy__s, " World" , 6);
    yk__printlnstr(yy__s);
    yk__sdsfree(yy__s);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif