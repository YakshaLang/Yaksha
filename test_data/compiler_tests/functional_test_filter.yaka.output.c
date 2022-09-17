// YK
#include "yk__lib.h"
// --forward declarations-- 
typedef bool (*ykfncptr0)(yk__sds, int32_t);
typedef bool (*ykfncptr1)(int32_t, int32_t);
bool yy__keep_len_n(yk__sds, int32_t);
bool yy__keep_all(yk__sds, int32_t);
bool yy__keep_upto(int32_t, int32_t);
bool yy__print_str(yk__sds, int32_t);
bool yy__print_int(int32_t, int32_t);
int32_t yy__main();
// --structs-- 
// --functions-- 
bool yy__keep_len_n(yk__sds yy__a, int32_t yy__n) 
{
    int32_t t__0 = (yk__sdslen(yy__a) == yy__n);
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
    yk__sds t__1 = yk__sdsnew(">> filter str test <<");
    yk__printlnstr((t__1));
    ykfncptr0 yy__f = yy__keep_len_n;
    yk__sds t__2 = yk__sdsnew("Hello");
    yk__sds t__3 = yk__sdsnew("World");
    yk__sds t__4 = yk__sdsnew("How");
    yk__sds t__5 = yk__sdsnew("Are");
    yk__sds t__6 = yk__sdsnew("You");
    yk__sds* t__7 = NULL;
    yk__arrsetcap(t__7, 5);
    yk__arrput(t__7, yk__sdsdup(t__2));
    yk__arrput(t__7, yk__sdsdup(t__3));
    yk__arrput(t__7, yk__sdsdup(t__4));
    yk__arrput(t__7, yk__sdsdup(t__5));
    yk__arrput(t__7, yk__sdsdup(t__6));
    yk__sds* yy__ar = t__7;
    yk__sds t__8 = yk__sdsnew("Before =>> ");
    yk__printlnstr((t__8));
    yk__sds* t__11 = yy__ar;
    int32_t t__13 = 0;
    size_t t__10 = yk__arrlenu(t__11);
    bool t__14 = true;
    for (size_t t__9 = 0; t__9 < t__10; t__9++) { 
        yk__sds t__12 = yk__sdsdup(t__11[t__9]);
        bool t__15 = yy__print_str(t__12, t__13);
        if (!t__15) {t__14 = false; break; }
    }
    t__14;
    yk__sds* t__18 = yy__ar;
    int32_t t__20 = 3;
    size_t t__17 = yk__arrlenu(t__18);
    yk__sds* t__21 = NULL;
    for (size_t t__16 = 0; t__16 < t__17; t__16++) { 
        yk__sds t__19 = yk__sdsdup(t__18[t__16]);
        bool t__22 = yy__keep_len_n(t__19, t__20);
        t__19 = yk__sdsdup(t__18[t__16]);if (t__22) {yk__arrput(t__21, t__19); }
    }
    yk__sds* yy__ar2 = t__21;
    yk__sds t__23 = yk__sdsnew("Filtered =>> ");
    yk__printlnstr((t__23));
    yk__sds* t__26 = yy__ar2;
    int32_t t__28 = 0;
    size_t t__25 = yk__arrlenu(t__26);
    bool t__29 = true;
    for (size_t t__24 = 0; t__24 < t__25; t__24++) { 
        yk__sds t__27 = yk__sdsdup(t__26[t__24]);
        bool t__30 = yy__print_str(t__27, t__28);
        if (!t__30) {t__29 = false; break; }
    }
    t__29;
    yk__sds t__31 = yk__sdsnew("Keep All =>> ");
    yk__printlnstr((t__31));
    yk__sds* t__34 = yy__ar;
    int32_t t__36 = 0;
    size_t t__33 = yk__arrlenu(t__34);
    yk__sds* t__37 = NULL;
    for (size_t t__32 = 0; t__32 < t__33; t__32++) { 
        yk__sds t__35 = yk__sdsdup(t__34[t__32]);
        bool t__38 = yy__keep_all(t__35, t__36);
        t__35 = yk__sdsdup(t__34[t__32]);if (t__38) {yk__arrput(t__37, t__35); }
    }
    yk__sds* t__41 = t__37;
    int32_t t__43 = 0;
    size_t t__40 = yk__arrlenu(t__41);
    bool t__44 = true;
    for (size_t t__39 = 0; t__39 < t__40; t__39++) { 
        yk__sds t__42 = yk__sdsdup(t__41[t__39]);
        bool t__45 = yy__print_str(t__42, t__43);
        if (!t__45) {t__44 = false; break; }
    }
    t__44;
    yk__sds t__46 = yk__sdsnew(">> filter int test <<");
    yk__printlnstr((t__46));
    ykfncptr1 yy__fi = yy__keep_upto;
    int32_t* t__47 = NULL;
    yk__arrsetcap(t__47, 10);
    yk__arrput(t__47, 1);
    yk__arrput(t__47, 2);
    yk__arrput(t__47, 3);
    yk__arrput(t__47, 4);
    yk__arrput(t__47, 5);
    yk__arrput(t__47, 6);
    yk__arrput(t__47, 7);
    yk__arrput(t__47, 8);
    yk__arrput(t__47, 9);
    yk__arrput(t__47, 10);
    int32_t* yy__ai = t__47;
    yk__sds t__48 = yk__sdsnew("Keep Upto 5 =>> ");
    yk__printlnstr((t__48));
    int32_t* t__51 = yy__ai;
    int32_t t__53 = 5;
    size_t t__50 = yk__arrlenu(t__51);
    int32_t* t__54 = NULL;
    for (size_t t__49 = 0; t__49 < t__50; t__49++) { 
        int32_t t__52 = t__51[t__49];
        bool t__55 = yy__keep_upto(t__52, t__53);
        if (t__55) {yk__arrput(t__54, t__52); }
    }
    int32_t* t__58 = t__54;
    int32_t t__60 = 0;
    size_t t__57 = yk__arrlenu(t__58);
    bool t__61 = true;
    for (size_t t__56 = 0; t__56 < t__57; t__56++) { 
        int32_t t__59 = t__58[t__56];
        bool t__62 = yy__print_int(t__59, t__60);
        if (!t__62) {t__61 = false; break; }
    }
    t__61;
    yk__sds t__63 = yk__sdsnew("Keep Upto 7 =>> ");
    yk__printlnstr((t__63));
    int32_t* t__66 = yy__ai;
    int32_t t__68 = 7;
    size_t t__65 = yk__arrlenu(t__66);
    int32_t* t__69 = NULL;
    for (size_t t__64 = 0; t__64 < t__65; t__64++) { 
        int32_t t__67 = t__66[t__64];
        bool t__70 = yy__keep_upto(t__67, t__68);
        if (t__70) {yk__arrput(t__69, t__67); }
    }
    int32_t* t__73 = t__69;
    int32_t t__75 = 0;
    size_t t__72 = yk__arrlenu(t__73);
    bool t__76 = true;
    for (size_t t__71 = 0; t__71 < t__72; t__71++) { 
        int32_t t__74 = t__73[t__71];
        bool t__77 = yy__print_int(t__74, t__75);
        if (!t__77) {t__76 = false; break; }
    }
    t__76;
    yk__sds t__78 = yk__sdsnew(">> completed.");
    yk__printlnstr((t__78));
    yk__sdsfree(t__78);
    yk__sdsfree(t__63);
    yk__sdsfree(t__48);
    yk__sdsfree(t__46);
    yk__sdsfree(t__31);
    yk__sdsfree(t__23);
    yk__sdsfree(t__8);
    yk__sdsfree(t__6);
    yk__sdsfree(t__5);
    yk__sdsfree(t__4);
    yk__sdsfree(t__3);
    yk__sdsfree(t__2);
    yk__sdsfree(t__1);
    return 0;
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif