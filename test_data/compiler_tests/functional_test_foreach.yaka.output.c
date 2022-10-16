// YK
#include "yk__lib.h"
// --forward declarations-- 
typedef bool (*ykfncptr0)(yk__sds, int32_t);
typedef bool (*ykfncptr1)(int32_t, int32_t);
bool yy__print_str(yk__sds, int32_t);
bool yy__print_add_n(int32_t, int32_t);
bool yy__print_upto_n(int32_t, int32_t);
int32_t yy__main();
// --structs-- 
// --functions-- 
bool yy__print_str(yk__sds yy__a, int32_t yy__b) 
{
    yk__printint(((intmax_t)yy__b));
    yk__sds t__0 = yk__sdsnewlen(" : ", 3);
    yk__printstr((t__0));
    yk__printlnstr((yy__a));
    yk__sdsfree(t__0);
    yk__sdsfree(yy__a);
    return true;
}
bool yy__print_add_n(int32_t yy__a, int32_t yy__n) 
{
    yk__printlnint(((intmax_t)(yy__a + yy__n)));
    return true;
}
bool yy__print_upto_n(int32_t yy__a, int32_t yy__n) 
{
    if ((yy__a > yy__n))
    {
        return false;
    }
    yk__printlnint(((intmax_t)yy__a));
    return true;
}
int32_t yy__main() 
{
    yk__sds t__1 = yk__sdsnewlen(">> foreach str test <<", 22);
    yk__printlnstr((t__1));
    ykfncptr0 yy__f = yy__print_str;
    yk__sds t__2 = yk__sdsnewlen("Hello", 5);
    yk__sds t__3 = yk__sdsnewlen("World", 5);
    yk__sds t__4 = yk__sdsnewlen("How", 3);
    yk__sds t__5 = yk__sdsnewlen("Are", 3);
    yk__sds t__6 = yk__sdsnewlen("You", 3);
    yk__sds* t__7 = NULL;
    yk__arrsetcap(t__7, 5);
    yk__arrput(t__7, yk__sdsdup(t__2));
    yk__arrput(t__7, yk__sdsdup(t__3));
    yk__arrput(t__7, yk__sdsdup(t__4));
    yk__arrput(t__7, yk__sdsdup(t__5));
    yk__arrput(t__7, yk__sdsdup(t__6));
    yk__sds* yy__ar = t__7;
    yk__sds* t__10 = yy__ar;
    int32_t t__12 = INT32_C(10);
    size_t t__9 = yk__arrlenu(t__10);
    bool t__13 = true;
    for (size_t t__8 = 0; t__8 < t__9; t__8++) { 
        yk__sds t__11 = yk__sdsdup(t__10[t__8]);
        bool t__14 = yy__f(t__11, t__12);
        if (!t__14) {t__13 = false; break; }
    }
    t__13;
    yk__sds* t__17 = yy__ar;
    int32_t t__19 = INT32_C(20);
    size_t t__16 = yk__arrlenu(t__17);
    bool t__20 = true;
    for (size_t t__15 = 0; t__15 < t__16; t__15++) { 
        yk__sds t__18 = yk__sdsdup(t__17[t__15]);
        bool t__21 = yy__print_str(t__18, t__19);
        if (!t__21) {t__20 = false; break; }
    }
    t__20;
    yk__sds t__22 = yk__sdsnewlen(">> foreach int test <<", 22);
    yk__printlnstr((t__22));
    ykfncptr1 yy__fi = yy__print_add_n;
    int32_t* t__23 = NULL;
    yk__arrsetcap(t__23, 10);
    yk__arrput(t__23, INT32_C(1));
    yk__arrput(t__23, INT32_C(2));
    yk__arrput(t__23, INT32_C(3));
    yk__arrput(t__23, INT32_C(4));
    yk__arrput(t__23, INT32_C(5));
    yk__arrput(t__23, INT32_C(6));
    yk__arrput(t__23, INT32_C(7));
    yk__arrput(t__23, INT32_C(8));
    yk__arrput(t__23, INT32_C(9));
    yk__arrput(t__23, INT32_C(10));
    int32_t* yy__ai = t__23;
    int32_t* t__26 = yy__ai;
    int32_t t__28 = INT32_C(100);
    size_t t__25 = yk__arrlenu(t__26);
    bool t__29 = true;
    for (size_t t__24 = 0; t__24 < t__25; t__24++) { 
        int32_t t__27 = t__26[t__24];
        bool t__30 = yy__fi(t__27, t__28);
        if (!t__30) {t__29 = false; break; }
    }
    t__29;
    int32_t* t__33 = yy__ai;
    int32_t t__35 = INT32_C(5);
    size_t t__32 = yk__arrlenu(t__33);
    bool t__36 = true;
    for (size_t t__31 = 0; t__31 < t__32; t__31++) { 
        int32_t t__34 = t__33[t__31];
        bool t__37 = yy__print_upto_n(t__34, t__35);
        if (!t__37) {t__36 = false; break; }
    }
    t__36;
    yk__sds t__38 = yk__sdsnewlen("completed.", 10);
    yk__printlnstr((t__38));
    yk__sdsfree(t__38);
    yk__sdsfree(t__22);
    yk__sdsfree(t__6);
    yk__sdsfree(t__5);
    yk__sdsfree(t__4);
    yk__sdsfree(t__3);
    yk__sdsfree(t__2);
    yk__sdsfree(t__1);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif