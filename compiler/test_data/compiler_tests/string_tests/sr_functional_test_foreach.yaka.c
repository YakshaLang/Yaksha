// YK
#include "yk__lib.h"
// --forward declarations-- 
typedef bool (*ykfncptr0)(struct yk__bstr, int32_t);
typedef bool (*ykfncptr1)(int32_t, int32_t);
bool yy__print_sr(struct yk__bstr, int32_t);
bool yy__print_add_n(int32_t, int32_t);
bool yy__print_upto_n(int32_t, int32_t);
int32_t yy__main();
// --structs-- 
// --functions-- 
bool yy__print_sr(struct yk__bstr yy__a, int32_t yy__b) 
{
    yk__printint((intmax_t)yy__b);
    yk__printstr(" : ");
    yk__printlnstr(yk__bstr_get_reference(yy__a));
    return true;
}
bool yy__print_add_n(int32_t yy__a, int32_t yy__n) 
{
    yk__printlnint((intmax_t)(yy__a + yy__n));
    return true;
}
bool yy__print_upto_n(int32_t yy__a, int32_t yy__n) 
{
    if (yy__a > yy__n)
    {
        return false;
    }
    yk__printlnint((intmax_t)yy__a);
    return true;
}
int32_t yy__main() 
{
    yk__printlnstr(">> foreach sr test <<");
    ykfncptr0 yy__f = yy__print_sr;
    struct yk__bstr* t__0 = NULL;
    yk__arrsetcap(t__0, 5);
    yk__arrput(t__0, yk__bstr_s("Hello", 5));
    yk__arrput(t__0, yk__bstr_s("World", 5));
    yk__arrput(t__0, yk__bstr_s("How", 3));
    yk__arrput(t__0, yk__bstr_s("Are", 3));
    yk__arrput(t__0, yk__bstr_s("You", 3));
    struct yk__bstr* yy__ar = t__0;
    struct yk__bstr* t__3 = yy__ar;
    int32_t t__5 = INT32_C(10);
    size_t t__2 = yk__arrlenu(t__3);
    bool t__6 = true;
    for (size_t t__1 = 0; t__1 < t__2; t__1++) { 
        struct yk__bstr t__4 = t__3[t__1];
        bool t__7 = yy__f(t__4, t__5);
        if (!t__7) {t__6 = false; break; }
    }
    t__6;
    struct yk__bstr* t__10 = yy__ar;
    int32_t t__12 = INT32_C(20);
    size_t t__9 = yk__arrlenu(t__10);
    bool t__13 = true;
    for (size_t t__8 = 0; t__8 < t__9; t__8++) { 
        struct yk__bstr t__11 = t__10[t__8];
        bool t__14 = yy__print_sr(t__11, t__12);
        if (!t__14) {t__13 = false; break; }
    }
    t__13;
    yk__printlnstr(">> foreach int test <<");
    ykfncptr1 yy__fi = yy__print_add_n;
    int32_t* t__15 = NULL;
    yk__arrsetcap(t__15, 10);
    yk__arrput(t__15, INT32_C(1));
    yk__arrput(t__15, INT32_C(2));
    yk__arrput(t__15, INT32_C(3));
    yk__arrput(t__15, INT32_C(4));
    yk__arrput(t__15, INT32_C(5));
    yk__arrput(t__15, INT32_C(6));
    yk__arrput(t__15, INT32_C(7));
    yk__arrput(t__15, INT32_C(8));
    yk__arrput(t__15, INT32_C(9));
    yk__arrput(t__15, INT32_C(10));
    int32_t* yy__ai = t__15;
    int32_t* t__18 = yy__ai;
    int32_t t__20 = INT32_C(100);
    size_t t__17 = yk__arrlenu(t__18);
    bool t__21 = true;
    for (size_t t__16 = 0; t__16 < t__17; t__16++) { 
        int32_t t__19 = t__18[t__16];
        bool t__22 = yy__fi(t__19, t__20);
        if (!t__22) {t__21 = false; break; }
    }
    t__21;
    int32_t* t__25 = yy__ai;
    int32_t t__27 = INT32_C(5);
    size_t t__24 = yk__arrlenu(t__25);
    bool t__28 = true;
    for (size_t t__23 = 0; t__23 < t__24; t__23++) { 
        int32_t t__26 = t__25[t__23];
        bool t__29 = yy__print_upto_n(t__26, t__27);
        if (!t__29) {t__28 = false; break; }
    }
    t__28;
    yk__printlnstr("completed.");
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif