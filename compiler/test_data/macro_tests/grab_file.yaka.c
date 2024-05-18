// YK
#include "yk__lib.h"
int32_t yy__main();
int32_t yy__main() 
{
    yk__printlnstr("hello");
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif