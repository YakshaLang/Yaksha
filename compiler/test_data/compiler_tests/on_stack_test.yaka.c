// YK
#include "yk__lib.h"
struct yy__AnotherFriend;
struct yy__Enemy;
struct yy__Friend;
struct yy__class_stuff_C;
typedef int32_t (*yt_fn_in_out_i32)(void);
struct yy__Enemy {
    int32_t yy__x;
    int32_t yy__y;
    int32_t yy__hp;
};
struct yy__Friend {
    int32_t yy__x;
};
struct yy__class_stuff_C {
    int32_t yy__class_stuff_c;
};
struct yy__AnotherFriend {
    int32_t yy__x;
};
int32_t yy__a();
int32_t yy__main();
int32_t yy__a() 
{
    return INT32_C(0);
}
int32_t yy__main() 
{
    yt_fn_in_out_i32 yy__b = yy__a;
    yt_fn_in_out_i32 yy__d = yy__a;
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