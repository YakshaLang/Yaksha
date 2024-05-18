// YK
#include "yk__lib.h"
struct yy__Animation;
struct yy__Cat;
struct yy__Cookie;
struct yy__Sprite;
struct yy__State;
typedef uint8_t yt_arr_u8_16[16];
typedef yt_arr_u8_16 yt_arr_arr_u8_16_16[16];
struct yy__Sprite {
    int32_t yy__width;
    int32_t yy__height;
    int32_t yy__center_x;
    int32_t yy__center_y;
    yt_arr_arr_u8_16_16 yy__texture;
};
typedef struct yy__Sprite yt_arr_sprite_4[4];
struct yy__Animation {
    yt_arr_sprite_4 yy__sprites;
    int32_t yy__frame_count;
    int32_t yy__frame_delay;
};
typedef struct yy__Animation yt_arr_animation_12[12];
typedef yt_arr_sprite_4 yt_arr_arr_sprite_4_8[8];
struct yy__Cookie {
    int32_t yy__x;
    int32_t yy__y;
    float yy__speed;
    int32_t yy__animation_reference;
    int32_t yy__cookie_type;
    int32_t yy__current_frame;
    int32_t yy__frame_timer;
};
typedef struct yy__Cookie yt_arr_cookie_30[30];
struct yy__Cat {
    int32_t yy__x;
    int32_t yy__y;
    int32_t yy__speed;
    int32_t yy__direction;
    yt_arr_arr_sprite_4_8 yy__animations;
    int32_t yy__score;
    int32_t yy__lives;
    uint64_t yy__speed_reset;
    int32_t yy__frame_delay;
    int32_t yy__current_frame;
    int32_t yy__frame_timer;
};
struct yy__State {
    int32_t yy__width;
    int32_t yy__height;
    uint64_t yy__frame_count;
    int32_t yy__screen;
    yt_arr_animation_12 yy__animations;
    yt_arr_cookie_30 yy__cookies;
    struct yy__Cat yy__player;
};
int32_t yy__main();
int32_t yy__main() 
{
    struct yy__State* yy__state = calloc(1, sizeof(struct yy__State));
    yy__state->yy__width = INT32_C(800);
    yy__state->yy__height = INT32_C(600);
    yy__state->yy__frame_count = ((uint64_t)(UINT8_C(0)));
    yy__state->yy__screen = INT32_C(0);
    yy__state->yy__animations[INT32_C(0)].yy__sprites[INT32_C(0)].yy__width = INT32_C(64);
    yy__state->yy__animations[INT32_C(0)].yy__sprites[INT32_C(0)].yy__height = INT32_C(64);
    yy__state->yy__animations[INT32_C(0)].yy__sprites[INT32_C(0)].yy__center_x = INT32_C(32);
    yy__state->yy__animations[INT32_C(0)].yy__sprites[INT32_C(0)].yy__center_y = INT32_C(32);
    yy__state->yy__animations[INT32_C(0)].yy__frame_count = INT32_C(4);
    yy__state->yy__animations[INT32_C(0)].yy__frame_delay = INT32_C(10);
    yy__state->yy__cookies[INT32_C(0)].yy__x = INT32_C(0);
    yy__state->yy__cookies[INT32_C(0)].yy__y = INT32_C(0);
    yy__state->yy__cookies[INT32_C(0)].yy__speed = 0.0f;
    yy__state->yy__cookies[INT32_C(0)].yy__animation_reference = INT32_C(0);
    yy__state->yy__cookies[INT32_C(0)].yy__cookie_type = INT32_C(0);
    yy__state->yy__cookies[INT32_C(0)].yy__current_frame = INT32_C(0);
    yy__state->yy__cookies[INT32_C(0)].yy__frame_timer = INT32_C(0);
    yy__state->yy__player.yy__x = INT32_C(0);
    yy__state->yy__player.yy__y = INT32_C(0);
    yy__state->yy__player.yy__speed = INT32_C(0);
    yy__state->yy__player.yy__direction = INT32_C(0);
    yy__state->yy__player.yy__score = INT32_C(0);
    yy__state->yy__player.yy__lives = INT32_C(0);
    yy__state->yy__player.yy__speed_reset = ((uint64_t)(UINT8_C(0)));
    yy__state->yy__player.yy__current_frame = INT32_C(0);
    free(yy__state);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif