// YK
#include "yk__lib.h"
// --forward declarations-- 
typedef bool (*ykfncptr0)(yk__sds, int32_t);
bool yy__keep_len_n(yk__sds, int32_t);
bool yy__keep_upto_n(int32_t, int32_t);
int32_t yy__main();
// --structs-- 
// --functions-- 
bool yy__keep_len_n(yk__sds yy__a, int32_t yy__n) 
{
    if ((yk__sdslen(yy__a) == yy__n))
    {
        yk__sdsfree(yy__a);
        return true;
    }
    yk__sdsfree(yy__a);
    return false;
}
bool yy__keep_upto_n(int32_t yy__a, int32_t yy__n) 
{
    if ((yy__a > yy__n))
    {
        return false;
    }
    return true;
}
int32_t yy__main() 
{
    yk__sds t__0 = yk__sdsnewlen(">> countif str test <<", 22);
    yk__printlnstr((t__0));
    ykfncptr0 yy__f = yy__keep_len_n;
    yk__sds t__1 = yk__sdsnewlen("Hello", 5);
    yk__sds t__2 = yk__sdsnewlen("World", 5);
    yk__sds t__3 = yk__sdsnewlen("How", 3);
    yk__sds t__4 = yk__sdsnewlen("Are", 3);
    yk__sds t__5 = yk__sdsnewlen("You", 3);
    yk__sds* t__6 = NULL;
    yk__arrsetcap(t__6, 5);
    yk__arrput(t__6, yk__sdsdup(t__1));
    yk__arrput(t__6, yk__sdsdup(t__2));
    yk__arrput(t__6, yk__sdsdup(t__3));
    yk__arrput(t__6, yk__sdsdup(t__4));
    yk__arrput(t__6, yk__sdsdup(t__5));
    yk__sds* yy__ar = t__6;
    yk__sds t__7 = yk__sdsnewlen("count len 3 ==> ", 16);
    yk__printstr((t__7));
    yk__sds* t__10 = yy__ar;
    int32_t t__12 = INT32_C(3);
    size_t t__9 = yk__arrlenu(t__10);
    int32_t t__13 = 0;
    for (size_t t__8 = 0; t__8 < t__9; t__8++) { 
        yk__sds t__11 = yk__sdsdup(t__10[t__8]);
        bool t__14 = yy__keep_len_n(t__11, t__12);
        if (t__14) {t__13++; }
    }
    yk__printlnint(((intmax_t)t__13));
    yk__sds t__15 = yk__sdsnewlen("count len 5 ==> ", 16);
    yk__printstr((t__15));
    yk__sds* t__18 = yy__ar;
    int32_t t__20 = INT32_C(5);
    size_t t__17 = yk__arrlenu(t__18);
    int32_t t__21 = 0;
    for (size_t t__16 = 0; t__16 < t__17; t__16++) { 
        yk__sds t__19 = yk__sdsdup(t__18[t__16]);
        bool t__22 = yy__f(t__19, t__20);
        if (t__22) {t__21++; }
    }
    yk__printlnint(((intmax_t)t__21));
    yk__sds t__23 = yk__sdsnewlen(">> countif int test <<", 22);
    yk__printlnstr((t__23));
    int32_t* t__24 = NULL;
    yk__arrsetcap(t__24, 10);
    yk__arrput(t__24, INT32_C(1));
    yk__arrput(t__24, INT32_C(2));
    yk__arrput(t__24, INT32_C(3));
    yk__arrput(t__24, INT32_C(4));
    yk__arrput(t__24, INT32_C(5));
    yk__arrput(t__24, INT32_C(6));
    yk__arrput(t__24, INT32_C(7));
    yk__arrput(t__24, INT32_C(8));
    yk__arrput(t__24, INT32_C(9));
    yk__arrput(t__24, INT32_C(10));
    int32_t* yy__ai = t__24;
    yk__sds t__25 = yk__sdsnewlen("count up to 5 ==> ", 18);
    yk__printstr((t__25));
    int32_t* t__28 = yy__ai;
    int32_t t__30 = INT32_C(5);
    size_t t__27 = yk__arrlenu(t__28);
    int32_t t__31 = 0;
    for (size_t t__26 = 0; t__26 < t__27; t__26++) { 
        int32_t t__29 = t__28[t__26];
        bool t__32 = yy__keep_upto_n(t__29, t__30);
        if (t__32) {t__31++; }
    }
    yk__printlnint(((intmax_t)t__31));
    yk__sds t__33 = yk__sdsnewlen("completed.", 10);
    yk__printlnstr((t__33));
    yk__sdsfree(t__33);
    yk__sdsfree(t__25);
    yk__sdsfree(t__23);
    yk__sdsfree(t__15);
    yk__sdsfree(t__7);
    yk__sdsfree(t__5);
    yk__sdsfree(t__4);
    yk__sdsfree(t__3);
    yk__sdsfree(t__2);
    yk__sdsfree(t__1);
    yk__sdsfree(t__0);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif