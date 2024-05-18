// YK
#include "yk__lib.h"
struct yy__A;
struct yy__A {
    yk__sds yy__a;
};
struct yy__A* yy__new_a();
void yy__del_a(struct yy__A*);
yk__sds yy__get_a(struct yy__A*);
void yy__use_a(struct yy__A*);
int32_t yy__main();
struct yy__A* yy__new_a() 
{
    struct yy__A* yy__x = calloc(1, sizeof(struct yy__A));
    yy__x->yy__a = yk__sdsnewlen("hello world", 11);
    struct yy__A* t__0 = yy__x;
    return t__0;
}
void yy__del_a(struct yy__A* yy__x) 
{
    yk__sdsfree(yy__x->yy__a);
    free(yy__x);
    return;
}
yk__sds yy__get_a(struct yy__A* yy__x) 
{
    yk__sds yy__a = yk__sdsdup(yy__x->yy__a);
    yk__sds t__1 = yy__a;
    return t__1;
}
void yy__use_a(struct yy__A* yy__x) 
{
    yk__sds yy__y = yk__sdsnewlen("" , 0);
    yk__sds t__2 = yy__get_a(yy__x);
    yk__sdsfree(yy__y);
    yy__y = yk__sdsdup(t__2);
    yk__printlnstr(yy__y);
    yk__sdsfree(t__2);
    yk__sdsfree(yy__y);
    return;
}
int32_t yy__main() 
{
    struct yy__A* yy__x = yy__new_a();
    yy__use_a(yy__x);
    yy__use_a(yy__x);
    yy__use_a(yy__x);
    yy__del_a(yy__x);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif