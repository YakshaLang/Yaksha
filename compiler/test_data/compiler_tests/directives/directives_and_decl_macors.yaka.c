// YK
#include "yk__lib.h"
#define yy__get_global_state get_global_state
#define yy__set_global_state set_global_state
struct yy__MyState;
struct yy__MyState {
    int32_t yy__x;
    int32_t yy__y;
};
int32_t yy__main();

void* GLOBAL_STATE = NULL;

void* get_global_state() {
  return GLOBAL_STATE;
}

void set_global_state(void* state) {
  GLOBAL_STATE = state;
}
;
int32_t yy__main() 
{
    struct yy__MyState* yy__state = calloc(1, sizeof(struct yy__MyState));
    yy__state->yy__x = INT32_C(1);
    yy__state->yy__y = INT32_C(2);
    yy__set_global_state(yy__state);
    yk__printlnint((intmax_t)yy__state->yy__x);
    yk__printlnint((intmax_t)yy__state->yy__y);
    yk__printlnint((intmax_t)yy__get_global_state()->yy__x);
    yk__printlnint((intmax_t)yy__get_global_state()->yy__y);
    yy__state->yy__x = INT32_C(5);
    yk__printlnint((intmax_t)yy__get_global_state()->yy__x);
    free(yy__state);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif