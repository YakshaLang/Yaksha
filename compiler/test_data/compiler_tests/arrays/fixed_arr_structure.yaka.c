// YK
#include "yk__lib.h"
// --forward declarations-- 
struct yy__A;
struct yy__B;
typedef int32_t (*yt_fn_in_int_out_int)(int32_t);
typedef int32_t yt_arr_int_3[3];
typedef int32_t yt_arr_int_2[2];
typedef yt_arr_int_2 yt_arr_arr_int_2_2[2];
typedef int32_t* yt_arr_ptr_int_2[2];
typedef int32_t** yt_arr_ptr_ptr_int_2[2];
typedef yt_fn_in_int_out_int yt_arr_fn_in_int_out_int_2[2];
typedef int32_t* const  yt_arr_const_ptr_int_2[2];
int32_t yy__main();
// --structs-- 
struct yy__A {
    int32_t yy__a;
    yt_arr_int_3 yy__b;
    yt_arr_int_3 yy__c;
};
struct yy__B {
    yt_arr_arr_int_2_2 yy__nested;
    yt_arr_int_2* yy__ptr_nested;
    yt_arr_ptr_int_2 yy__nested_ptr;
    yt_arr_ptr_int_2* yy__ptr_nested_ptr;
    yt_arr_ptr_ptr_int_2 yy__nested_ptr_ptr;
    yt_arr_fn_in_int_out_int_2 yy__nested_func;
    yt_arr_const_ptr_int_2 yy__nested_const_ptr;
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