// YK
int32_t yy__add(int32_t, int32_t);

#ifndef max
#define max(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifndef min
#define min(a, b) ((a) < (b) ? (a) : (b))
#endif
;
int32_t yy__add(int32_t yy__a, int32_t yy__b) 
{
    int32_t t__0 = (min(yy__a, yy__b) + max(yy__a, yy__b));
    return t__0;
}
