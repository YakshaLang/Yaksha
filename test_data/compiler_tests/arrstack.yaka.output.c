#include "yk__lib.h"
// --forward declarations-- 
int32_t yy__main();
// --structs-- 
// --functions-- 
int32_t yy__main() 
{
    int32_t* yy__a = NULL;
    yk__arrput(yy__a, 1);
    yk__arrput(yy__a, 2);
    yk__arrput(yy__a, 3);
    while (1) {
        if (!((yk__arrlen(yy__a) > 0))) { break; } // Check
        // Body of while loop

        {
            printf("%jd\n", ((intmax_t)yk__arrpop(yy__a)));
        }
    }
    return 0;
}
int main(void) { return yy__main(); }