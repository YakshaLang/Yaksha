// YK
#include "yk__lib.h"
// --forward declarations-- 
#define yy__Foreign struct foreign
int32_t yy__main();
// --structs-- 
// --functions-- 
int32_t yy__main() 
{
    yy__Foreign* yy__a = calloc(1, sizeof(yy__Foreign));
    yy__Foreign* yy__b = make_foreign_ptr();
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif