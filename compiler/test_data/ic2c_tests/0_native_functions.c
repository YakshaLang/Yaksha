// YK
#include "yk__lib.h" // --forward declarations--
#define yy__min_int(nn__a, nn__b) ((nn__a < nn__b) ? nn__a : nn__b)
#define yy__max_int(nn__a, nn__b) ((nn__a > nn__b) ? nn__a : nn__b)
#define yy__banana banana
#define yy__Something something
#define yy__Color Color
#define yy__new yk__newsdsarray
#define getarg(b) 1
int32_t yy__get_arg(int32_t);
int32_t yy__main();
// --structs--
// --functions--
int32_t yy__get_arg(int32_t nn__n) { return getarg(nn__n); }
int32_t yy__main()
{
  yk__sds t__0 = yk__sdsnewlen("hello world", 11);
  yk__printlnstr((t__0));
  if (yy__min_int(1, 0))
  {
    yk__sdsfree(t__0);
    return yy__get_arg(INT32_C(1000));
  }
  yk__sdsfree(t__0);
  return yy__get_arg(INT32_C(0));
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif
/**
* BLAH
*/
