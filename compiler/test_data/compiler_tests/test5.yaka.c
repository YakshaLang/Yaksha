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
    yk__printstr(yy__item);
    yk__printstr(":\t");
    yk__printstr(yy__value);
    yk__printstr("\n");
    yk__sdsfree(yy__value);
    yk__sdsfree(yy__item);
    return INT32_C(0);
}
int32_t yy__print_int_item(yk__sds yy__item, int32_t yy__value) 
{
    yk__printstr(yy__item);
    yk__printstr(":\t");
    yk__printint((intmax_t)yy__value);
    yk__printstr("\n");
    yk__sdsfree(yy__item);
    return INT32_C(0);
}
int32_t yy__print_captain(struct yy__Captain* yy__c) 
{
    yy__print_str_item(yk__sdsnewlen("Captain.Name", 12), yk__sdsdup(yy__c->yy__name));
    yy__print_int_item(yk__sdsnewlen("Captain.Age", 11), yy__c->yy__age);
    return INT32_C(0);
}
int32_t yy__print_ship(struct yy__Spaceship* yy__s) 
{
    yy__print_str_item(yk__sdsnewlen("Name", 4), yk__sdsdup(yy__s->yy__name));
    yy__print_str_item(yk__sdsnewlen("Class", 5), yk__sdsdup(yy__s->yy__class_));
    yy__print_captain(yy__s->yy__captain);
    return INT32_C(0);
}
int32_t yy__main() 
{
    struct yy__Spaceship* yy__myship = calloc(1, sizeof(struct yy__Spaceship));
    yy__myship->yy__name = yk__sdsnewlen("USS Enterprise", 14);
    yy__myship->yy__class_ = yk__sdsnewlen("Galaxy", 6);
    yy__myship->yy__captain = calloc(1, sizeof(struct yy__Captain));
    yy__myship->yy__captain->yy__name = yk__sdsnewlen("Picard", 6);
    yy__myship->yy__captain->yy__age = INT32_C(59);
    yy__print_ship(yy__myship);
    yk__sdsfree(yy__myship->yy__captain->yy__name);
    free(yy__myship->yy__captain);
    yk__sdsfree(yy__myship->yy__name);
    yk__sdsfree(yy__myship->yy__class_);
    free(yy__myship);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif