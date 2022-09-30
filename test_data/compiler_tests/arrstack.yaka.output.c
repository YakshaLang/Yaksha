// YK
#include "yk__lib.h"
// --forward declarations-- 
int32_t yy__main();
// --structs-- 
// --functions-- 
int32_t yy__main() 
{
    int32_t* yy__a = NULL;
    yk__arrput(yy__a, INT32_C(1));
    yk__arrput(yy__a, INT32_C(2));
    yk__arrput(yy__a, INT32_C(3));
    while (1) {
        if (!((yk__arrlen(yy__a) > INT32_C(0)))) { break; } // Check
        // Body of while loop

        {
            yk__printlnint(((intmax_t)yk__arrpop(yy__a)));
        }
    }
    yk__arrfree(yy__a);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif