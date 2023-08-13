// YK
#include "yk__lib.h"
// --forward declarations-- 
int32_t yy__to_lengths(struct yk__bstr, int32_t);
int32_t yy__to_pow2(int32_t, int32_t);
bool yy__print_int(int32_t, int32_t);
int32_t yy__main();
// --structs-- 
// --functions-- 
int32_t yy__to_lengths(struct yk__bstr yy__a, int32_t yy__ignored) 
{
    int32_t t__0 = yk__bstr_len(yy__a);
    return t__0;
}
int32_t yy__to_pow2(int32_t yy__a, int32_t yy__ignored) 
{
    int32_t t__1 = (yy__a * yy__a);
    return t__1;
}
bool yy__print_int(int32_t yy__a, int32_t yy__ignored) 
{
    yk__printlnint((intmax_t)yy__a);
    return true;
}
int32_t yy__main() 
{
    yk__printlnstr(">> map sr test <<");
    struct yk__bstr* t__2 = NULL;
    yk__arrsetcap(t__2, 5);
    yk__arrput(t__2, yk__bstr_s("Hello", 5));
    yk__arrput(t__2, yk__bstr_s("World", 5));
    yk__arrput(t__2, yk__bstr_s("How", 3));
    yk__arrput(t__2, yk__bstr_s("Are", 3));
    yk__arrput(t__2, yk__bstr_s("You", 3));
    struct yk__bstr* yy__ar = t__2;
    yk__printlnstr("map to_lengths ==> ");
    struct yk__bstr* t__5 = yy__ar;
    int32_t t__7 = INT32_C(0);
    size_t t__4 = yk__arrlenu(t__5);
    int32_t* t__8 = NULL;
    for (size_t t__3 = 0; t__3 < t__4; t__3++) { 
        struct yk__bstr t__6 = t__5[t__3];
        int32_t t__9 = yy__to_lengths(t__6, t__7);
        yk__arrput(t__8, t__9);
    }
    int32_t* t__12 = t__8;
    int32_t t__14 = INT32_C(0);
    size_t t__11 = yk__arrlenu(t__12);
    bool t__15 = true;
    for (size_t t__10 = 0; t__10 < t__11; t__10++) { 
        int32_t t__13 = t__12[t__10];
        bool t__16 = yy__print_int(t__13, t__14);
        if (!t__16) {t__15 = false; break; }
    }
    t__15;
    yk__printlnstr(">> countif int test <<");
    int32_t* t__17 = NULL;
    yk__arrsetcap(t__17, 10);
    yk__arrput(t__17, INT32_C(1));
    yk__arrput(t__17, INT32_C(2));
    yk__arrput(t__17, INT32_C(3));
    yk__arrput(t__17, INT32_C(4));
    yk__arrput(t__17, INT32_C(5));
    yk__arrput(t__17, INT32_C(6));
    yk__arrput(t__17, INT32_C(7));
    yk__arrput(t__17, INT32_C(8));
    yk__arrput(t__17, INT32_C(9));
    yk__arrput(t__17, INT32_C(10));
    int32_t* yy__ai = t__17;
    yk__printlnstr("map to_pow2 ==> ");
    int32_t* t__20 = yy__ai;
    int32_t t__22 = INT32_C(0);
    size_t t__19 = yk__arrlenu(t__20);
    int32_t* t__23 = NULL;
    for (size_t t__18 = 0; t__18 < t__19; t__18++) { 
        int32_t t__21 = t__20[t__18];
        int32_t t__24 = yy__to_pow2(t__21, t__22);
        yk__arrput(t__23, t__24);
    }
    int32_t* t__27 = t__23;
    int32_t t__29 = INT32_C(0);
    size_t t__26 = yk__arrlenu(t__27);
    bool t__30 = true;
    for (size_t t__25 = 0; t__25 < t__26; t__25++) { 
        int32_t t__28 = t__27[t__25];
        bool t__31 = yy__print_int(t__28, t__29);
        if (!t__31) {t__30 = false; break; }
    }
    t__30;
    yk__printlnstr("completed.");
    if (true)
    {
        yk__printlnstr("true");
    }
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif