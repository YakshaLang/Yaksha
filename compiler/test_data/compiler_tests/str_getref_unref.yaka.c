// YK
#include "yk__lib.h"
// --forward declarations-- 
void yy__world1(yk__sds*);
void yy__world2(yk__sds*);
void yy__world3(void*);
int32_t yy__main();
// --structs-- 
// --functions-- 
void yy__world1(yk__sds* yy__a) 
{
    yk__printstr((*(yy__a)));
    yk__printlnstr(" world");
    return;
}
void yy__world2(yk__sds* yy__a) 
{
    yk__sds yy__b = yk__sdsdup((*(yy__a)));
    yk__printstr(yy__b);
    yk__printlnstr(" world");
    yk__sdsfree(yy__b);
    return;
}
void yy__world3(void* yy__a) 
{
    yk__sds* yy__b = ((yk__sds*)yy__a);
    yy__world1(yy__b);
    return;
}
int32_t yy__main() 
{
yk__sds yy__my_empty = yk__sdsempty();
    yk__sds yy__hello = yk__sdsnewlen("hello" , 5);
    int32_t yy__i = INT32_C(5);
    while (true)
    {
        if (!(((yy__i > INT32_C(0)))))
        {
            break;
        }
        yy__world1((&(yy__hello)));
        yy__world2((&(yy__hello)));
        yy__world3(((&(yy__hello))));
        yy__i = (yy__i - INT32_C(1));
    }
    yk__printlnstr((yy__my_empty != NULL) ? "True" : "False");
    yy__world1((&(yy__my_empty)));
    yk__sdsfree(yy__hello);
    yk__sdsfree(yy__my_empty);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif