// YK
#include "yk__lib.h"
// --forward declarations-- 
struct yy__class_stuff_A;
struct yy__class_stuff_B;
struct yy__class_stuff_C;
struct yy__Enemy;
struct yy__Friend;
struct yy__AnotherFriend;
typedef int32_t (*ykfncptr0)(void);
int32_t yy__class_stuff_main();
int32_t yy__a();
int32_t yy__main();
// --structs-- 
struct yy__class_stuff_A {
    int32_t yy__class_stuff_a;
};
struct yy__class_stuff_B {
    int32_t yy__class_stuff_b;
};
struct yy__class_stuff_C {
    int32_t yy__class_stuff_c;
};
struct yy__Enemy {
    int32_t yy__x;
    int32_t yy__y;
    int32_t yy__hp;
};
struct yy__Friend {
    int32_t yy__x;
};
struct yy__AnotherFriend {
    int32_t yy__x;
};
// --functions-- 
int32_t yy__class_stuff_main() 
{
    struct yy__class_stuff_A* yy__class_stuff_a = calloc(1, sizeof(struct yy__class_stuff_A));
    yy__class_stuff_a->yy__class_stuff_a = INT32_C(1);
    struct yy__class_stuff_B* yy__class_stuff_b = calloc(1, sizeof(struct yy__class_stuff_B));
    yy__class_stuff_b->yy__class_stuff_b = INT32_C(10);
    yk__printlnint((intmax_t)yy__class_stuff_a->yy__class_stuff_a);
    int32_t t__0 = yy__class_stuff_b->yy__class_stuff_b;
    free(yy__class_stuff_b);
    free(yy__class_stuff_a);
    return t__0;
}
int32_t yy__a() 
{
    return INT32_C(0);
}
int32_t yy__main() 
{
    ykfncptr0 yy__b = yy__a;
    ykfncptr0 yy__d = yy__a;
    struct yk__bstr yy__e = yk__bstr_s("Hello world" , 11);
    struct yy__Enemy* t__0 = NULL;
    yk__arrsetlen(t__0, INT32_C(2));
    struct yy__Enemy* yy__enemies = t__0;
    yy__enemies[INT32_C(0)].yy__x = INT32_C(1);
    yy__enemies[INT32_C(1)].yy__x = INT32_C(2);
    struct yy__Friend yy__good_person = ((struct yy__Friend){.yy__x = (INT32_C(0))});
    struct yy__class_stuff_C yy__my_obj = ((struct yy__class_stuff_C){.yy__class_stuff_c = (INT32_C(0))});
    struct yy__AnotherFriend* t__1 = calloc(1, sizeof(struct yy__AnotherFriend));
    t__1->yy__x = (INT32_C(0));
    struct yy__AnotherFriend* yy__another_friend = t__1;
    struct yy__Enemy yy__big_enemy;
    yy__big_enemy.yy__x = INT32_C(4);
    yk__printlnint((intmax_t)(((((yy__enemies[INT32_C(0)].yy__x + yy__enemies[INT32_C(1)].yy__x) + yy__big_enemy.yy__x) + yy__good_person.yy__x) + yy__my_obj.yy__class_stuff_c) + yy__another_friend->yy__x));
    free(yy__another_friend);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif