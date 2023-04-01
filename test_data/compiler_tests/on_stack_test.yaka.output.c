// YK
#include "yk__lib.h"
// --forward declarations-- 
struct yy__Enemy;
int32_t yy__main();
// --structs-- 
struct yy__Enemy {
    int32_t yy__x;
    int32_t yy__y;
    int32_t yy__hp;
};
// --functions-- 
int32_t yy__main() 
{
    struct yy__Enemy* t__0 = NULL;
    yk__arrsetlen(t__0, INT32_C(2));
    struct yy__Enemy* yy__enemies = t__0;
    yy__enemies[INT32_C(0)].yy__x = INT32_C(1);
    yy__enemies[INT32_C(1)].yy__x = INT32_C(2);
    yk__printlnint(((intmax_t)(yy__enemies[INT32_C(0)].yy__x + yy__enemies[INT32_C(1)].yy__x)));
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif