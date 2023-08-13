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
    yk__printstr("len=");
    yk__printlnint((intmax_t)yk__arrlen(yy__x));
    int32_t yy__pos = INT32_C(0);
    int32_t yy__length = yk__arrlen(yy__x);
    while (true)
    {
        if (!(yy__pos < yy__length))
        {
            break;
        }
        yk__printint((intmax_t)yy__x[yy__pos]);
        yk__printstr(" ");
        yy__pos = (yy__pos + INT32_C(1));
    }
    yk__printlnstr("");
    return;
}
int32_t yy__main() 
{
    int32_t* t__1 = NULL;
    yk__arrsetcap(t__1, 8);
    yk__arrput(t__1, INT32_C(1));
    yk__arrput(t__1, INT32_C(2));
    yk__arrput(t__1, INT32_C(3));
    yk__arrput(t__1, INT32_C(3));
    yk__arrput(t__1, INT32_C(2));
    yk__arrput(t__1, INT32_C(1));
    yk__arrput(t__1, INT32_C(5));
    yk__arrput(t__1, INT32_C(4));
    int32_t* yy__x1 = t__1;
    yk__printlnstr("before x1:");
    yy__print_array(yy__x1);
    (yk__quicksort(yy__x1,sizeof(int32_t),yk__arrlenu(yy__x1),yy__sorters_cmp_int) == 0);
    yk__printlnstr("after x1:");
    yy__print_array(yy__x1);
    int32_t* t__2 = NULL;
    yk__arrsetcap(t__2, 8);
    yk__arrput(t__2, INT32_C(1));
    yk__arrput(t__2, INT32_C(2));
    yk__arrput(t__2, INT32_C(3));
    yk__arrput(t__2, INT32_C(3));
    yk__arrput(t__2, INT32_C(2));
    yk__arrput(t__2, INT32_C(1));
    yk__arrput(t__2, INT32_C(5));
    yk__arrput(t__2, INT32_C(4));
    int32_t* yy__x2 = t__2;
    ykfncptr0 yy__cmp = yy__cmp_int;
    yk__printlnstr("before x2:");
    yy__print_array(yy__x2);
    (yk__quicksort(yy__x2,sizeof(int32_t),yk__arrlenu(yy__x2),yy__cmp) == 0);
    yk__printlnstr("after x2:");
    yy__print_array(yy__x2);
    int32_t* t__3 = NULL;
    yk__arrsetcap(t__3, 8);
    yk__arrput(t__3, INT32_C(1));
    yk__arrput(t__3, INT32_C(2));
    yk__arrput(t__3, INT32_C(3));
    yk__arrput(t__3, INT32_C(3));
    yk__arrput(t__3, INT32_C(2));
    yk__arrput(t__3, INT32_C(1));
    yk__arrput(t__3, INT32_C(5));
    yk__arrput(t__3, INT32_C(4));
    int32_t* yy__x3 = t__3;
    yy__cmp = yy__sorters_cmp_int;
    yk__printlnstr("before x3:");
    yy__print_array(yy__x3);
    (yk__quicksort(yy__x3,sizeof(int32_t),yk__arrlenu(yy__x3),yy__cmp) == 0);
    yk__printlnstr("after x3:");
    yy__print_array(yy__x3);
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
    int32_t* yy__x4 = t__4;
    ykfncptr0 yy__cmp4 = yy__sorters_cmp_int;
    ykfncptr0 yy__cmp4_reassign = yy__cmp4;
    yk__printlnstr("before x4:");
    yy__print_array(yy__x4);
    (yk__quicksort(yy__x4,sizeof(int32_t),yk__arrlenu(yy__x4),yy__cmp4_reassign) == 0);
    yk__printlnstr("after x4:");
    yy__print_array(yy__x4);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif