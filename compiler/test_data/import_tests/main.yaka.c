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
    yk__printstr("Monkey ");
    yk__printint((intmax_t)yy__jungle_m->yy__jungle_id);
    yk__printstr(" has ");
    yy__jungle_print_banana(yy__jungle_m->yy__jungle_food);
    return;
}
void yy__jungle_print_banana(struct yy__jungle_banana* yy__jungle_b) 
{
    yk__printstr("banana ");
    yk__printint((intmax_t)yy__jungle_b->yy__jungle_id);
    yk__printstr("\n");
    return;
}
int32_t yy__main() 
{
    struct yy__MainClass* yy__mc = calloc(1, sizeof(struct yy__MainClass));
    struct yy__house_ColomboHouse* yy__hs = calloc(1, sizeof(struct yy__house_ColomboHouse));
    struct yy__jungle_monkey* yy__m = calloc(1, sizeof(struct yy__jungle_monkey));
    yy__m->yy__jungle_id = INT32_C(10);
    yy__m->yy__jungle_food = calloc(1, sizeof(struct yy__jungle_banana));
    yy__m->yy__jungle_food->yy__jungle_id = INT32_C(50);
    yy__jungle_print_monkey(yy__m);
    free(yy__m->yy__jungle_food);
    free(yy__m);
    free(yy__hs);
    free(yy__mc);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif