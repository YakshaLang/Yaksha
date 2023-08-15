// YK
#include "yk__lib.h"
// --forward declarations-- 
struct yy__Spaceship;
int32_t yy__main();
// --structs-- 
struct yy__Spaceship {
    yk__sds yy__name;
    yk__sds yy__class_;
};
// --functions-- 
int32_t yy__main() 
{
    struct yy__Spaceship* yy__myship = calloc(1, sizeof(struct yy__Spaceship));
    int32_t yy__a = INT32_C(10);
    while (true)
    {
        if (!(((yy__a != INT32_C(0)))))
        {
            break;
        }
        yk__printint((intmax_t)yy__a);
        yk__printstr("\n");
        yy__a = (yy__a - INT32_C(1));
    }
    free(yy__myship);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif