// YK
#include "yk__lib.h"
int32_t yy__main();
int32_t yy__main() 
{
    int32_t yy__a = INT32_C(0);
    int32_t* yy__b = (&(yy__a));
    *(yy__b) = INT32_C(42);
    int32_t t__0 = yy__a;
    return t__0;
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif