// YK
#include "yk__lib.h"
// --forward declarations-- 
struct yy__A;
struct yy__B;
typedef int32_t (*yt_fn_in_int_out_int)(int32_t);
typedef int32_t ykfxa0[3];
typedef int32_t ykfxa1[2];
typedef ykfxa1 ykfxa2[2];
typedef int32_t* ykfxa3[2];
typedef int32_t** ykfxa4[2];
typedef yt_fn_in_int_out_int ykfxa5[2];
typedef int32_t* const  ykfxa6[2];
int32_t yy__main();
// --structs-- 
struct yy__A {
    int32_t yy__a;
    ykfxa0 yy__b;
    ykfxa0 yy__c;
};
struct yy__B {
    ykfxa2 yy__nested;
    ykfxa1* yy__ptr_nested;
    ykfxa3 yy__nested_ptr;
    ykfxa3* yy__ptr_nested_ptr;
    ykfxa4 yy__nested_ptr_ptr;
    ykfxa5 yy__nested_func;
    ykfxa6 yy__nested_const_ptr;
};
// --functions-- 
int32_t yy__main() 
{
    struct yy__A yy__a;
    yy__a.yy__a = INT32_C(1);
    yy__a.yy__b[INT32_C(0)] = INT32_C(2);
    yy__a.yy__b[INT32_C(1)] = INT32_C(3);
    yy__a.yy__b[INT32_C(2)] = INT32_C(4);
    yy__a.yy__c[INT32_C(0)] = INT32_C(5);
    yy__a.yy__c[INT32_C(1)] = INT32_C(6);
    yy__a.yy__c[INT32_C(2)] = INT32_C(7);
    struct yy__B yy__b;
    yy__b.yy__nested[INT32_C(0)][INT32_C(0)] = INT32_C(8);
    yy__b.yy__nested[INT32_C(0)][INT32_C(1)] = INT32_C(9);
    yy__b.yy__nested[INT32_C(1)][INT32_C(0)] = INT32_C(10);
    yy__b.yy__nested[INT32_C(1)][INT32_C(1)] = INT32_C(11);
    yk__printlnint((intmax_t)yy__b.yy__nested[INT32_C(0)][INT32_C(0)]);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif