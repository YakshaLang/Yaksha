// YK
#include "yk__lib.h"
// --forward declarations-- 
typedef int32_t (*ykfncptr0)(void const* const , void const* const );
int32_t yy__sorters_cmp_int(void const* const , void const* const );
int32_t yy__cmp_int(void const* const , void const* const );
void yy__print_array(int32_t*);
int32_t yy__main();
// --structs-- 
// --functions-- 
int32_t yy__sorters_cmp_int(void const* const  nn__a, void const* const  nn__b) 
{
    return *((int32_t*)nn__a) - *((int32_t*)nn__b);
}
int32_t yy__cmp_int(void const* const  yy__a, void const* const  yy__b) 
{
    int32_t yy__val_a = (*(((int32_t*)yy__a)));
    int32_t yy__val_b = (*(((int32_t*)yy__b)));
    int32_t t__0 = (yy__val_b - yy__val_a);
    return t__0;
}
void yy__print_array(int32_t* yy__x) 
{
    yk__sds t__1 = yk__sdsnew("len=");
    yk__printstr((t__1));
    yk__printlnint(((intmax_t)yk__arrlen(yy__x)));
    int32_t yy__pos = INT32_C(0);
    int32_t yy__length = yk__arrlen(yy__x);
    while (1) {
        if (!((yy__pos < yy__length))) { break; } // Check
        // Body of while loop

        {
            yk__printint(((intmax_t)yy__x[yy__pos]));
            yk__sds t__2 = yk__sdsnew(" ");
            yk__printstr((t__2));
            yy__pos = (yy__pos + INT32_C(1));
            yk__sdsfree(t__2);
        }
    }
    yk__sds t__3 = yk__sdsempty();
    yk__printlnstr((t__3));
    yk__sdsfree(t__3);
    yk__sdsfree(t__1);
    return;
}
int32_t yy__main() 
{
    int32_t* t__4 = NULL;
    yk__arrsetcap(t__4, 8);
    yk__arrput(t__4, INT32_C(1));
    yk__arrput(t__4, INT32_C(2));
    yk__arrput(t__4, INT32_C(3));
    yk__arrput(t__4, INT32_C(3));
    yk__arrput(t__4, INT32_C(2));
    yk__arrput(t__4, INT32_C(1));
    yk__arrput(t__4, INT32_C(5));
    yk__arrput(t__4, INT32_C(4));
    int32_t* yy__x1 = t__4;
    yk__sds t__5 = yk__sdsnew("before x1:");
    yk__printlnstr((t__5));
    yy__print_array(yy__x1);
    (yk__quicksort(yy__x1,sizeof(int32_t),yk__arrlenu(yy__x1),yy__sorters_cmp_int) == 0);
    yk__sds t__6 = yk__sdsnew("after x1:");
    yk__printlnstr((t__6));
    yy__print_array(yy__x1);
    int32_t* t__7 = NULL;
    yk__arrsetcap(t__7, 8);
    yk__arrput(t__7, INT32_C(1));
    yk__arrput(t__7, INT32_C(2));
    yk__arrput(t__7, INT32_C(3));
    yk__arrput(t__7, INT32_C(3));
    yk__arrput(t__7, INT32_C(2));
    yk__arrput(t__7, INT32_C(1));
    yk__arrput(t__7, INT32_C(5));
    yk__arrput(t__7, INT32_C(4));
    int32_t* yy__x2 = t__7;
    ykfncptr0 yy__cmp = yy__cmp_int;
    yk__sds t__8 = yk__sdsnew("before x2:");
    yk__printlnstr((t__8));
    yy__print_array(yy__x2);
    (yk__quicksort(yy__x2,sizeof(int32_t),yk__arrlenu(yy__x2),yy__cmp) == 0);
    yk__sds t__9 = yk__sdsnew("after x2:");
    yk__printlnstr((t__9));
    yy__print_array(yy__x2);
    int32_t* t__10 = NULL;
    yk__arrsetcap(t__10, 8);
    yk__arrput(t__10, INT32_C(1));
    yk__arrput(t__10, INT32_C(2));
    yk__arrput(t__10, INT32_C(3));
    yk__arrput(t__10, INT32_C(3));
    yk__arrput(t__10, INT32_C(2));
    yk__arrput(t__10, INT32_C(1));
    yk__arrput(t__10, INT32_C(5));
    yk__arrput(t__10, INT32_C(4));
    int32_t* yy__x3 = t__10;
    yy__cmp = yy__sorters_cmp_int;
    yk__sds t__11 = yk__sdsnew("before x3:");
    yk__printlnstr((t__11));
    yy__print_array(yy__x3);
    (yk__quicksort(yy__x3,sizeof(int32_t),yk__arrlenu(yy__x3),yy__cmp) == 0);
    yk__sds t__12 = yk__sdsnew("after x3:");
    yk__printlnstr((t__12));
    yy__print_array(yy__x3);
    int32_t* t__13 = NULL;
    yk__arrsetcap(t__13, 8);
    yk__arrput(t__13, INT32_C(1));
    yk__arrput(t__13, INT32_C(2));
    yk__arrput(t__13, INT32_C(3));
    yk__arrput(t__13, INT32_C(3));
    yk__arrput(t__13, INT32_C(2));
    yk__arrput(t__13, INT32_C(1));
    yk__arrput(t__13, INT32_C(5));
    yk__arrput(t__13, INT32_C(4));
    int32_t* yy__x4 = t__13;
    ykfncptr0 yy__cmp4 = yy__sorters_cmp_int;
    ykfncptr0 yy__cmp4_reassign = yy__cmp4;
    yk__sds t__14 = yk__sdsnew("before x4:");
    yk__printlnstr((t__14));
    yy__print_array(yy__x4);
    (yk__quicksort(yy__x4,sizeof(int32_t),yk__arrlenu(yy__x4),yy__cmp4_reassign) == 0);
    yk__sds t__15 = yk__sdsnew("after x4:");
    yk__printlnstr((t__15));
    yy__print_array(yy__x4);
    yk__sdsfree(t__15);
    yk__sdsfree(t__14);
    yk__sdsfree(t__12);
    yk__sdsfree(t__11);
    yk__sdsfree(t__9);
    yk__sdsfree(t__8);
    yk__sdsfree(t__6);
    yk__sdsfree(t__5);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif