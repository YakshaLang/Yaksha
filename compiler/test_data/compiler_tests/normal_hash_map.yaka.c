// YK
#include "yk__lib.h"
// --forward declarations-- 
struct yt_pair_int_int;
int32_t yy__main();
// --structs-- 
struct yt_pair_int_int { int32_t key; int32_t value; };
// --functions-- 
int32_t yy__main() 
{
    struct yt_pair_int_int* yy__m = NULL;
    ;
    yk__hmput(yy__m, INT32_C(1), INT32_C(42));
    yk__hmput(yy__m, INT32_C(100), INT32_C(10000));
    yk__printstr("1 = ");
    yk__printlnint((intmax_t)yk__hmget(yy__m, INT32_C(1)));
    yk__printstr("length of this map is = ");
    yk__printlnint((intmax_t)yk__hmlen(yy__m));
    yk__printstr("1 is located at = ");
    yk__printlnint((intmax_t)yk__hmgeti(yy__m, INT32_C(1)));
    yk__printstr("30 is located at = ");
    yk__printlnint((intmax_t)yk__hmgeti(yy__m, INT32_C(30)));
    yk__hmfree(yy__m);
    yk__printlnstr("bye!");
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif