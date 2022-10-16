// YK
#include "yk__lib.h"
// --forward declarations-- 
typedef bool (*ykfncptr0)(yk__sds, int32_t);
typedef bool (*ykfncptr1)(int32_t, int32_t);
bool yy__keep_len_n(yk__sds, int32_t);
bool yy__keep_all(yk__sds, int32_t);
bool yy__keep_upto(int32_t, int32_t);
bool yy__keep_div(int32_t, int32_t);
bool yy__print_str(yk__sds, int32_t);
bool yy__print_int(int32_t, int32_t);
int32_t yy__main();
// --structs-- 
// --functions-- 
bool yy__keep_len_n(yk__sds yy__a, int32_t yy__n) 
{
    bool t__0 = (yk__sdslen(yy__a) == yy__n);
    yk__sdsfree(yy__a);
    return t__0;
}
bool yy__keep_all(yk__sds yy__a, int32_t yy__n) 
{
    yk__sdsfree(yy__a);
    return true;
}
bool yy__keep_upto(int32_t yy__a, int32_t yy__n) 
{
    if ((yy__a > yy__n))
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
bool yy__print_str(yk__sds yy__a, int32_t yy__ignored) 
{
    yk__printlnstr((yy__a));
    yk__sdsfree(yy__a);
    return true;
}
bool yy__print_int(int32_t yy__a, int32_t yy__ignored) 
{
    yk__printlnint(((intmax_t)yy__a));
    return true;
}
int32_t yy__main() 
{
    yk__sds t__2 = yk__sdsnewlen(">> filter str test <<", 21);
    yk__printlnstr((t__2));
    ykfncptr0 yy__f = yy__keep_len_n;
    yk__sds t__3 = yk__sdsnewlen("Hello", 5);
    yk__sds t__4 = yk__sdsnewlen("World", 5);
    yk__sds t__5 = yk__sdsnewlen("How", 3);
    yk__sds t__6 = yk__sdsnewlen("Are", 3);
    yk__sds t__7 = yk__sdsnewlen("You", 3);
    yk__sds* t__8 = NULL;
    yk__arrsetcap(t__8, 5);
    yk__arrput(t__8, yk__sdsdup(t__3));
    yk__arrput(t__8, yk__sdsdup(t__4));
    yk__arrput(t__8, yk__sdsdup(t__5));
    yk__arrput(t__8, yk__sdsdup(t__6));
    yk__arrput(t__8, yk__sdsdup(t__7));
    yk__sds* yy__ar = t__8;
    yk__sds t__9 = yk__sdsnewlen("Before =>> ", 11);
    yk__printlnstr((t__9));
    yk__sds* t__12 = yy__ar;
    int32_t t__14 = INT32_C(0);
    size_t t__11 = yk__arrlenu(t__12);
    bool t__15 = true;
    for (size_t t__10 = 0; t__10 < t__11; t__10++) { 
        yk__sds t__13 = yk__sdsdup(t__12[t__10]);
        bool t__16 = yy__print_str(t__13, t__14);
        if (!t__16) {t__15 = false; break; }
    }
    t__15;
    yk__sds* t__19 = yy__ar;
    int32_t t__21 = INT32_C(3);
    size_t t__18 = yk__arrlenu(t__19);
    yk__sds* t__22 = NULL;
    for (size_t t__17 = 0; t__17 < t__18; t__17++) { 
        yk__sds t__20 = yk__sdsdup(t__19[t__17]);
        bool t__23 = yy__keep_len_n(t__20, t__21);
        t__20 = yk__sdsdup(t__19[t__17]); if (t__23) {yk__arrput(t__22, t__20); } else { yk__sdsfree(t__20); }
    }
    yk__sds* yy__ar2 = t__22;
    yk__sds t__24 = yk__sdsnewlen("Filtered =>> ", 13);
    yk__printlnstr((t__24));
    yk__sds* t__27 = yy__ar2;
    int32_t t__29 = INT32_C(0);
    size_t t__26 = yk__arrlenu(t__27);
    bool t__30 = true;
    for (size_t t__25 = 0; t__25 < t__26; t__25++) { 
        yk__sds t__28 = yk__sdsdup(t__27[t__25]);
        bool t__31 = yy__print_str(t__28, t__29);
        if (!t__31) {t__30 = false; break; }
    }
    t__30;
    yk__sds t__32 = yk__sdsnewlen("Keep All =>> ", 13);
    yk__printlnstr((t__32));
    yk__sds* t__35 = yy__ar;
    int32_t t__37 = INT32_C(0);
    size_t t__34 = yk__arrlenu(t__35);
    yk__sds* t__38 = NULL;
    for (size_t t__33 = 0; t__33 < t__34; t__33++) { 
        yk__sds t__36 = yk__sdsdup(t__35[t__33]);
        bool t__39 = yy__keep_all(t__36, t__37);
        t__36 = yk__sdsdup(t__35[t__33]); if (t__39) {yk__arrput(t__38, t__36); } else { yk__sdsfree(t__36); }
    }
    yk__sds* t__42 = t__38;
    int32_t t__44 = INT32_C(0);
    size_t t__41 = yk__arrlenu(t__42);
    bool t__45 = true;
    for (size_t t__40 = 0; t__40 < t__41; t__40++) { 
        yk__sds t__43 = yk__sdsdup(t__42[t__40]);
        bool t__46 = yy__print_str(t__43, t__44);
        if (!t__46) {t__45 = false; break; }
    }
    t__45;
    yk__sds t__47 = yk__sdsnewlen(">> filter int test <<", 21);
    yk__printlnstr((t__47));
    ykfncptr1 yy__fi = yy__keep_upto;
    int32_t* t__48 = NULL;
    yk__arrsetcap(t__48, 10);
    yk__arrput(t__48, INT32_C(1));
    yk__arrput(t__48, INT32_C(2));
    yk__arrput(t__48, INT32_C(3));
    yk__arrput(t__48, INT32_C(4));
    yk__arrput(t__48, INT32_C(5));
    yk__arrput(t__48, INT32_C(6));
    yk__arrput(t__48, INT32_C(7));
    yk__arrput(t__48, INT32_C(8));
    yk__arrput(t__48, INT32_C(9));
    yk__arrput(t__48, INT32_C(10));
    int32_t* yy__ai = t__48;
    yk__sds t__49 = yk__sdsnewlen("Keep Upto 5 =>> ", 16);
    yk__printlnstr((t__49));
    int32_t* t__52 = yy__ai;
    int32_t t__54 = INT32_C(5);
    size_t t__51 = yk__arrlenu(t__52);
    int32_t* t__55 = NULL;
    for (size_t t__50 = 0; t__50 < t__51; t__50++) { 
        int32_t t__53 = t__52[t__50];
        bool t__56 = yy__keep_upto(t__53, t__54);
        if (t__56) {yk__arrput(t__55, t__53); }
    }
    int32_t* t__59 = t__55;
    int32_t t__61 = INT32_C(0);
    size_t t__58 = yk__arrlenu(t__59);
    bool t__62 = true;
    for (size_t t__57 = 0; t__57 < t__58; t__57++) { 
        int32_t t__60 = t__59[t__57];
        bool t__63 = yy__print_int(t__60, t__61);
        if (!t__63) {t__62 = false; break; }
    }
    t__62;
    yk__sds t__64 = yk__sdsnewlen("Keep Upto 7 =>> ", 16);
    yk__printlnstr((t__64));
    int32_t* t__67 = yy__ai;
    int32_t t__69 = INT32_C(7);
    size_t t__66 = yk__arrlenu(t__67);
    int32_t* t__70 = NULL;
    for (size_t t__65 = 0; t__65 < t__66; t__65++) { 
        int32_t t__68 = t__67[t__65];
        bool t__71 = yy__keep_upto(t__68, t__69);
        if (t__71) {yk__arrput(t__70, t__68); }
    }
    int32_t* t__74 = t__70;
    int32_t t__76 = INT32_C(0);
    size_t t__73 = yk__arrlenu(t__74);
    bool t__77 = true;
    for (size_t t__72 = 0; t__72 < t__73; t__72++) { 
        int32_t t__75 = t__74[t__72];
        bool t__78 = yy__print_int(t__75, t__76);
        if (!t__78) {t__77 = false; break; }
    }
    t__77;
    yk__sds t__79 = yk__sdsnewlen("Keep div 2 (even) =>> ", 22);
    yk__printlnstr((t__79));
    int32_t* t__82 = yy__ai;
    int32_t t__84 = INT32_C(2);
    size_t t__81 = yk__arrlenu(t__82);
    int32_t* t__85 = NULL;
    for (size_t t__80 = 0; t__80 < t__81; t__80++) { 
        int32_t t__83 = t__82[t__80];
        bool t__86 = yy__keep_div(t__83, t__84);
        if (t__86) {yk__arrput(t__85, t__83); }
    }
    int32_t* t__89 = t__85;
    int32_t t__91 = INT32_C(0);
    size_t t__88 = yk__arrlenu(t__89);
    bool t__92 = true;
    for (size_t t__87 = 0; t__87 < t__88; t__87++) { 
        int32_t t__90 = t__89[t__87];
        bool t__93 = yy__print_int(t__90, t__91);
        if (!t__93) {t__92 = false; break; }
    }
    t__92;
    yk__sds t__94 = yk__sdsnewlen(">> completed.", 13);
    yk__printlnstr((t__94));
    yk__sdsfree(t__94);
    yk__sdsfree(t__79);
    yk__sdsfree(t__64);
    yk__sdsfree(t__49);
    yk__sdsfree(t__47);
    yk__sdsfree(t__32);
    yk__sdsfree(t__24);
    yk__sdsfree(t__9);
    yk__sdsfree(t__7);
    yk__sdsfree(t__6);
    yk__sdsfree(t__5);
    yk__sdsfree(t__4);
    yk__sdsfree(t__3);
    yk__sdsfree(t__2);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif