// YK
#include "yk__lib.h"
// --forward declarations-- 
struct yy__Captain;
struct yy__Spaceship;
int32_t yy__print_str_item(yk__sds, yk__sds);
int32_t yy__print_int_item(yk__sds, int32_t);
int32_t yy__print_captain(struct yy__Captain*);
int32_t yy__print_ship(struct yy__Spaceship*);
int32_t yy__main();
// --structs-- 
struct yy__Captain {
    yk__sds yy__name;
    int32_t yy__age;
};
struct yy__Spaceship {
    yk__sds yy__name;
    yk__sds yy__class_;
    struct yy__Captain* yy__captain;
};
// --functions-- 
int32_t yy__print_str_item(yk__sds yy__item, yk__sds yy__value) 
{
    yk__printstr((yy__item));
    yk__sds t__0 = yk__sdsnew(":\t");
    yk__printstr((t__0));
    yk__printstr((yy__value));
    yk__sds t__1 = yk__sdsnew("\n");
    yk__printstr((t__1));
    yk__sdsfree(t__1);
    yk__sdsfree(t__0);
    yk__sdsfree(yy__value);
    yk__sdsfree(yy__item);
    return INT32_C(0);
}
int32_t yy__print_int_item(yk__sds yy__item, int32_t yy__value) 
{
    yk__printstr((yy__item));
    yk__sds t__2 = yk__sdsnew(":\t");
    yk__printstr((t__2));
    yk__printint(((intmax_t)yy__value));
    yk__sds t__3 = yk__sdsnew("\n");
    yk__printstr((t__3));
    yk__sdsfree(t__3);
    yk__sdsfree(t__2);
    yk__sdsfree(yy__item);
    return INT32_C(0);
}
int32_t yy__print_captain(struct yy__Captain* yy__c) 
{
    yk__sds t__4 = yk__sdsnew("Captain.Name");
    yy__print_str_item(yk__sdsdup(t__4), yk__sdsdup(yy__c->yy__name));
    yk__sds t__5 = yk__sdsnew("Captain.Age");
    yy__print_int_item(yk__sdsdup(t__5), yy__c->yy__age);
    yk__sdsfree(t__5);
    yk__sdsfree(t__4);
    return INT32_C(0);
}
int32_t yy__print_ship(struct yy__Spaceship* yy__s) 
{
    yk__sds t__6 = yk__sdsnew("Name");
    yy__print_str_item(yk__sdsdup(t__6), yk__sdsdup(yy__s->yy__name));
    yk__sds t__7 = yk__sdsnew("Class");
    yy__print_str_item(yk__sdsdup(t__7), yk__sdsdup(yy__s->yy__class_));
    yy__print_captain(yy__s->yy__captain);
    yk__sdsfree(t__7);
    yk__sdsfree(t__6);
    return INT32_C(0);
}
int32_t yy__main() 
{
    struct yy__Spaceship* yy__myship = calloc(1, sizeof(struct yy__Spaceship));
    yk__sds t__8 = yk__sdsnew("USS Enterprise");
    yk__sdsfree(yy__myship->yy__name);
    yy__myship->yy__name = yk__sdsdup(t__8);
    yk__sds t__9 = yk__sdsnew("Galaxy");
    yk__sdsfree(yy__myship->yy__class_);
    yy__myship->yy__class_ = yk__sdsdup(t__9);
    yy__myship->yy__captain = calloc(1, sizeof(struct yy__Captain));
    yk__sds t__10 = yk__sdsnew("Picard");
    yk__sdsfree(yy__myship->yy__captain->yy__name);
    yy__myship->yy__captain->yy__name = yk__sdsdup(t__10);
    yy__myship->yy__captain->yy__age = INT32_C(59);
    yy__print_ship(yy__myship);
    yk__sdsfree(yy__myship->yy__captain->yy__name);
    free(yy__myship->yy__captain);
    yk__sdsfree(yy__myship->yy__name);
    yk__sdsfree(yy__myship->yy__class_);
    free(yy__myship);
    yk__sdsfree(t__10);
    yk__sdsfree(t__9);
    yk__sdsfree(t__8);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif