#include "yk__lib.h"
// --forward declarations-- 
struct yy__Student;
struct yy__Spaceship;
int32_t yy__main();
// --structs-- 
struct yy__Student {
    yk__sds yy__name;
    int32_t yy__age;
};
struct yy__Spaceship {
    yk__sds yy__name;
    yk__sds yy__class_;
};
// --functions-- 
int32_t yy__main() 
{
    struct yy__Spaceship* yy__myship = calloc(1, sizeof(struct yy__Spaceship));
    int32_t yy__a = 10;
    while (1) {
        if (!((yy__a != 0))) { break; } // Check
        // Body of while loop

        {
            printf("%jd", ((intmax_t)yy__a));
            yk__sds t__0 = yk__sdsnew("\n");
            printf("%s", (t__0));
            yy__a = (yy__a - 1);
            yk__sdsfree(t__0);
        }
    }
    free(yy__myship);
    return 0;
}
int main(void) { return yy__main(); }