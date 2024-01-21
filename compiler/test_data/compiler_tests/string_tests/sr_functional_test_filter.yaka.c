// YK
#include "yk__lib.h"
// --forward declarations-- 
typedef bool (*yt_fn_in_sr_int_out_bool)(struct yk__bstr, int32_t);
typedef bool (*yt_fn_in_int_int_out_bool)(int32_t, int32_t);
bool yy__keep_len_n(struct yk__bstr, int32_t);
bool yy__keep_all(struct yk__bstr, int32_t);
bool yy__keep_upto(int32_t, int32_t);
bool yy__keep_div(int32_t, int32_t);
bool yy__print_sr(struct yk__bstr, int32_t);
bool yy__print_int(int32_t, int32_t);
int32_t yy__main();
// --structs-- 
// --functions-- 
bool yy__keep_len_n(struct yk__bstr yy__a, int32_t yy__n) 
{
    bool t__0 = (yk__bstr_len(yy__a) == yy__n);
    return t__0;
}
bool yy__keep_all(struct yk__bstr yy__a, int32_t yy__n) 
{
    return true;
}
bool yy__keep_upto(int32_t yy__a, int32_t yy__n) 
{
    if (yy__a > yy__n)
    {
        return false;
    }
    return true;
}
bool yy__keep_div(int32_t yy__a, int32_t yy__n) 
{
    bool t__1 = ((yy__a % yy__n) == INT32_C(0));
    return t__1;
}
bool yy__print_sr(struct yk__bstr yy__a, int32_t yy__ignored) 
{
    yk__printlnstr(yk__bstr_get_reference(yy__a));
    return true;
}
bool yy__print_int(int32_t yy__a, int32_t yy__ignored) 
{
    yk__printlnint((intmax_t)yy__a);
    return true;
}
int32_t yy__main() 
{
    yk__printlnstr(">> filter sr test <<");
    yt_fn_in_sr_int_out_bool yy__f = yy__keep_len_n;
    struct yk__bstr* t__2 = NULL;
    yk__arrsetcap(t__2, 5);
    yk__arrput(t__2, yk__bstr_s("Hello", 5));
    yk__arrput(t__2, yk__bstr_s("World", 5));
    yk__arrput(t__2, yk__bstr_s("How", 3));
    yk__arrput(t__2, yk__bstr_s("Are", 3));
    yk__arrput(t__2, yk__bstr_s("You", 3));
    struct yk__bstr* yy__ar = t__2;
    yk__printlnstr("Before =>> ");
    struct yk__bstr* t__5 = yy__ar;
    int32_t t__7 = INT32_C(0);
    size_t t__4 = yk__arrlenu(t__5);
    bool t__8 = true;
    for (size_t t__3 = 0; t__3 < t__4; t__3++) { 
        struct yk__bstr t__6 = t__5[t__3];
        bool t__9 = yy__print_sr(t__6, t__7);
        if (!t__9) {t__8 = false; break; }
    }
    t__8;
    struct yk__bstr* t__12 = yy__ar;
    int32_t t__14 = INT32_C(3);
    size_t t__11 = yk__arrlenu(t__12);
    struct yk__bstr* t__15 = NULL;
    for (size_t t__10 = 0; t__10 < t__11; t__10++) { 
        struct yk__bstr t__13 = t__12[t__10];
        bool t__16 = yy__keep_len_n(t__13, t__14);
        if (t__16) {yk__arrput(t__15, t__13); }
    }
    struct yk__bstr* yy__ar2 = t__15;
    yk__printlnstr("Filtered =>> ");
    struct yk__bstr* t__19 = yy__ar2;
    int32_t t__21 = INT32_C(0);
    size_t t__18 = yk__arrlenu(t__19);
    bool t__22 = true;
    for (size_t t__17 = 0; t__17 < t__18; t__17++) { 
        struct yk__bstr t__20 = t__19[t__17];
        bool t__23 = yy__print_sr(t__20, t__21);
        if (!t__23) {t__22 = false; break; }
    }
    t__22;
    yk__printlnstr("Keep All =>> ");
    struct yk__bstr* t__26 = yy__ar;
    int32_t t__28 = INT32_C(0);
    size_t t__25 = yk__arrlenu(t__26);
    struct yk__bstr* t__29 = NULL;
    for (size_t t__24 = 0; t__24 < t__25; t__24++) { 
        struct yk__bstr t__27 = t__26[t__24];
        bool t__30 = yy__keep_all(t__27, t__28);
        if (t__30) {yk__arrput(t__29, t__27); }
    }
    struct yk__bstr* t__33 = t__29;
    int32_t t__35 = INT32_C(0);
    size_t t__32 = yk__arrlenu(t__33);
    bool t__36 = true;
    for (size_t t__31 = 0; t__31 < t__32; t__31++) { 
        struct yk__bstr t__34 = t__33[t__31];
        bool t__37 = yy__print_sr(t__34, t__35);
        if (!t__37) {t__36 = false; break; }
    }
    t__36;
    yk__printlnstr(">> filter int test <<");
    yt_fn_in_int_int_out_bool yy__fi = yy__keep_upto;
    int32_t* t__38 = NULL;
    yk__arrsetcap(t__38, 10);
    yk__arrput(t__38, INT32_C(1));
    yk__arrput(t__38, INT32_C(2));
    yk__arrput(t__38, INT32_C(3));
    yk__arrput(t__38, INT32_C(4));
    yk__arrput(t__38, INT32_C(5));
    yk__arrput(t__38, INT32_C(6));
    yk__arrput(t__38, INT32_C(7));
    yk__arrput(t__38, INT32_C(8));
    yk__arrput(t__38, INT32_C(9));
    yk__arrput(t__38, INT32_C(10));
    int32_t* yy__ai = t__38;
    yk__printlnstr("Keep Upto 5 =>> ");
    int32_t* t__41 = yy__ai;
    int32_t t__43 = INT32_C(5);
    size_t t__40 = yk__arrlenu(t__41);
    int32_t* t__44 = NULL;
    for (size_t t__39 = 0; t__39 < t__40; t__39++) { 
        int32_t t__42 = t__41[t__39];
        bool t__45 = yy__keep_upto(t__42, t__43);
        if (t__45) {yk__arrput(t__44, t__42); }
    }
    int32_t* t__48 = t__44;
    int32_t t__50 = INT32_C(0);
    size_t t__47 = yk__arrlenu(t__48);
    bool t__51 = true;
    for (size_t t__46 = 0; t__46 < t__47; t__46++) { 
        int32_t t__49 = t__48[t__46];
        bool t__52 = yy__print_int(t__49, t__50);
        if (!t__52) {t__51 = false; break; }
    }
    t__51;
    yk__printlnstr("Keep Upto 7 =>> ");
    int32_t* t__55 = yy__ai;
    int32_t t__57 = INT32_C(7);
    size_t t__54 = yk__arrlenu(t__55);
    int32_t* t__58 = NULL;
    for (size_t t__53 = 0; t__53 < t__54; t__53++) { 
        int32_t t__56 = t__55[t__53];
        bool t__59 = yy__keep_upto(t__56, t__57);
        if (t__59) {yk__arrput(t__58, t__56); }
    }
    int32_t* t__62 = t__58;
    int32_t t__64 = INT32_C(0);
    size_t t__61 = yk__arrlenu(t__62);
    bool t__65 = true;
    for (size_t t__60 = 0; t__60 < t__61; t__60++) { 
        int32_t t__63 = t__62[t__60];
        bool t__66 = yy__print_int(t__63, t__64);
        if (!t__66) {t__65 = false; break; }
    }
    t__65;
    yk__printlnstr("Keep div 2 (even) =>> ");
    int32_t* t__69 = yy__ai;
    int32_t t__71 = INT32_C(2);
    size_t t__68 = yk__arrlenu(t__69);
    int32_t* t__72 = NULL;
    for (size_t t__67 = 0; t__67 < t__68; t__67++) { 
        int32_t t__70 = t__69[t__67];
        bool t__73 = yy__keep_div(t__70, t__71);
        if (t__73) {yk__arrput(t__72, t__70); }
    }
    int32_t* t__76 = t__72;
    int32_t t__78 = INT32_C(0);
    size_t t__75 = yk__arrlenu(t__76);
    bool t__79 = true;
    for (size_t t__74 = 0; t__74 < t__75; t__74++) { 
        int32_t t__77 = t__76[t__74];
        bool t__80 = yy__print_int(t__77, t__78);
        if (!t__80) {t__79 = false; break; }
    }
    t__79;
    yk__printlnstr(">> completed.");
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif