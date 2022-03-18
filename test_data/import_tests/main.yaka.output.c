// YK
#include "yk__lib.h"
// --forward declarations-- 
struct yy__jungle_banana;
struct yy__jungle_monkey;
struct yy__house_ColomboHouse;
struct yy__MainClass;
void yy__jungle_print_monkey(struct yy__jungle_monkey*);
void yy__jungle_print_banana(struct yy__jungle_banana*);
int32_t yy__main();
// --structs-- 
struct yy__jungle_banana {
    int32_t yy__jungle_id;
};
struct yy__jungle_monkey {
    int32_t yy__jungle_id;
    struct yy__jungle_banana* yy__jungle_food;
};
struct yy__house_ColomboHouse {
    int32_t yy__house_id;
};
struct yy__MainClass {
    int32_t yy__id;
};
// --functions-- 
void yy__jungle_print_monkey(struct yy__jungle_monkey* yy__jungle_m) 
{
    yk__sds t__0 = yk__sdsnew("Monkey ");
    yk__printstr((t__0));
    printf("%jd", ((intmax_t)yy__jungle_m->yy__jungle_id));
    yk__sds t__1 = yk__sdsnew(" has ");
    yk__printstr((t__1));
    yy__jungle_print_banana(yy__jungle_m->yy__jungle_food);
    yk__sdsfree(t__1);
    yk__sdsfree(t__0);
    return;
}
void yy__jungle_print_banana(struct yy__jungle_banana* yy__jungle_b) 
{
    yk__sds t__2 = yk__sdsnew("banana ");
    yk__printstr((t__2));
    printf("%jd", ((intmax_t)yy__jungle_b->yy__jungle_id));
    yk__sds t__3 = yk__sdsnew("\n");
    yk__printstr((t__3));
    yk__sdsfree(t__3);
    yk__sdsfree(t__2);
    return;
}
int32_t yy__main() 
{
    struct yy__MainClass* yy__mc = calloc(1, sizeof(struct yy__MainClass));
    struct yy__house_ColomboHouse* yy__hs = calloc(1, sizeof(struct yy__house_ColomboHouse));
    struct yy__jungle_monkey* yy__m = calloc(1, sizeof(struct yy__jungle_monkey));
    yy__m->yy__jungle_id = 10;
    yy__m->yy__jungle_food = calloc(1, sizeof(struct yy__jungle_banana));
    yy__m->yy__jungle_food->yy__jungle_id = 50;
    yy__jungle_print_monkey(yy__m);
    free(yy__m->yy__jungle_food);
    free(yy__m);
    free(yy__hs);
    free(yy__mc);
    return 0;
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif