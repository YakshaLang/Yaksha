// YK:graphicutils,wasm4#
#include "yk__lib.h"
// --forward declarations-- 
uint8_t const  yy__w4_BUTTON_LEFT = UINT8_C(16);
uint8_t const  yy__w4_BUTTON_RIGHT = UINT8_C(32);
uint8_t const  yy__w4_BUTTON_UP = UINT8_C(64);
uint8_t const  yy__w4_BUTTON_DOWN = UINT8_C(128);
uint32_t const  yy__w4_BLIT_2BPP = UINT32_C(1);
uint8_t const ykbindata0[] = {
UINT8_C(0x00), UINT8_C(0xa0), UINT8_C(0x02), UINT8_C(0x00),
UINT8_C(0x0e), UINT8_C(0xf0), UINT8_C(0x36), UINT8_C(0x5c),
UINT8_C(0xd6), UINT8_C(0x57), UINT8_C(0xd5), UINT8_C(0x57),
UINT8_C(0x35), UINT8_C(0x5c), UINT8_C(0x0f), UINT8_C(0xf0)
};
#define yy__random_random_u64 yk__random_u64
#define yy__w4_set_draw_colors(nn__value) *((uint16_t*)0x14) = nn__value
#define yy__w4_gamepad1() (*((const uint8_t*)0x16))
struct yy__Point;
struct yy__Snake;
struct yy__State;
void yy__random_set_seed(uint64_t);
void yy__w4_set_palette(uint32_t, uint32_t, uint32_t, uint32_t);
void yy__w4_blit(uint8_t const *, int32_t, int32_t, uint32_t, uint32_t, uint32_t);
void yy__w4_rect(int32_t, int32_t, uint32_t, uint32_t);
void yy__w4_set_game_state(void*);
struct yy__Point* yy__point(int16_t, int16_t);
struct yy__Point* yy__set_random_point(struct yy__Point*);
void yy__draw_snake(struct yy__Snake*);
void yy__snake_push(struct yy__Snake*, struct yy__Point*);
void yy__snake_update(struct yy__Snake*);
void yy__snake_up(struct yy__Snake*);
void yy__snake_down(struct yy__Snake*);
void yy__snake_left(struct yy__Snake*);
void yy__snake_right(struct yy__Snake*);
bool yy__snake_isdead(struct yy__Snake*);
bool yy__del_point(struct yy__Point*, int32_t);
void yy__snake_reset(struct yy__Snake*);
void yy__handle_input(struct yy__State*);
void yy__game_step(void*);
int32_t yy__main();
// --structs-- 
struct yy__Point {
    int16_t yy__x;
    int16_t yy__y;
};
struct yy__Snake {
    struct yy__Point** yy__body;
    struct yy__Point* yy__direction;
};
struct yy__State {
    struct yy__Snake* yy__snake;
    uint8_t const * yy__fruit_sprite;
    struct yy__Point* yy__fruit;
    uint32_t yy__frame_count;
    uint8_t yy__gamepad_prev;
};
// --functions-- 
void yy__random_set_seed(uint64_t nn__seed) 
{
    srand((unsigned) nn__seed);
}
void yy__w4_set_palette(uint32_t nn__c1, uint32_t nn__c2, uint32_t nn__c3, uint32_t nn__c4) 
{
    
    PALETTE[0] = nn__c1;
    PALETTE[1] = nn__c2;
    PALETTE[2] = nn__c3;
    PALETTE[3] = nn__c4;
    ;
}
void yy__w4_blit(uint8_t const * nn__data, int32_t nn__x, int32_t nn__y, uint32_t nn__width, uint32_t nn__height, uint32_t nn__flags) { blit(nn__data, nn__x, nn__y, nn__width, nn__height, nn__flags); }
void yy__w4_rect(int32_t nn__x, int32_t nn__y, uint32_t nn__width, uint32_t nn__height) { rect(nn__x, nn__y, nn__width, nn__height); }
void yy__w4_set_game_state(void* nn__data) 
{
    yk__set_game_state(nn__data);;
}
struct yy__Point* yy__point(int16_t yy__x, int16_t yy__y) 
{
    struct yy__Point* yy__my_point = calloc(1, sizeof(struct yy__Point));
    yy__my_point->yy__x = yy__x;
    yy__my_point->yy__y = yy__y;
    struct yy__Point* t__0 = yy__my_point;
    return t__0;
}
struct yy__Point* yy__set_random_point(struct yy__Point* yy__p) 
{
    int16_t yy__x = ((int16_t)(yy__random_random_u64() % UINT64_C(20)));
    int16_t yy__y = ((int16_t)(yy__random_random_u64() % UINT64_C(20)));
    yy__p->yy__x = yy__x;
    yy__p->yy__y = yy__y;
    struct yy__Point* t__1 = yy__p;
    return t__1;
}
void yy__draw_snake(struct yy__Snake* yy__snake) 
{
    yy__w4_set_draw_colors(UINT16_C(67));
    int32_t yy__i = INT32_C(0);
    while (true)
    {
        if (!(((yy__i < yk__arrlen(yy__snake->yy__body)))))
        {
            break;
        }
        struct yy__Point* yy__body_part = yy__snake->yy__body[yy__i];
        int32_t yy__x = ((int32_t)(yy__body_part->yy__x * INT16_C(8)));
        int32_t yy__y = ((int32_t)(yy__body_part->yy__y * INT16_C(8)));
        yy__w4_rect(yy__x, yy__y, UINT32_C(8), UINT32_C(8));
        yy__i += INT32_C(1);
    }
    yy__w4_set_draw_colors(UINT16_C(4));
    struct yy__Point* yy__body_part = yy__snake->yy__body[INT32_C(0)];
    int32_t yy__x = ((int32_t)(yy__body_part->yy__x * INT16_C(8)));
    int32_t yy__y = ((int32_t)(yy__body_part->yy__y * INT16_C(8)));
    yy__w4_rect(yy__x, yy__y, UINT32_C(8), UINT32_C(8));
    return;
}
void yy__snake_push(struct yy__Snake* yy__snake, struct yy__Point* yy__p) 
{
    yk__arrput(yy__snake->yy__body, yy__p);
    return;
}
void yy__snake_update(struct yy__Snake* yy__snake) 
{
    int32_t yy__position = (yk__arrlen(yy__snake->yy__body) - INT32_C(1));
    while (true)
    {
        if (!(((yy__position > INT32_C(0)))))
        {
            break;
        }
        yy__snake->yy__body[yy__position]->yy__x = yy__snake->yy__body[(yy__position - INT32_C(1))]->yy__x;
        yy__snake->yy__body[yy__position]->yy__y = yy__snake->yy__body[(yy__position - INT32_C(1))]->yy__y;
        yy__position -= INT32_C(1);
    }
    yy__snake->yy__body[INT32_C(0)]->yy__x = (((yy__snake->yy__body[INT32_C(0)]->yy__x + yy__snake->yy__direction->yy__x)) % INT16_C(20));
    yy__snake->yy__body[INT32_C(0)]->yy__y = (((yy__snake->yy__body[INT32_C(0)]->yy__y + yy__snake->yy__direction->yy__y)) % INT16_C(20));
    if (yy__snake->yy__body[INT32_C(0)]->yy__x < INT16_C(0))
    {
        yy__snake->yy__body[INT32_C(0)]->yy__x = INT16_C(19);
    }
    if (yy__snake->yy__body[INT32_C(0)]->yy__y < INT16_C(0))
    {
        yy__snake->yy__body[INT32_C(0)]->yy__y = INT16_C(19);
    }
    return;
}
void yy__snake_up(struct yy__Snake* yy__snake) 
{
    if (yy__snake->yy__direction->yy__y == INT16_C(0))
    {
        yy__snake->yy__direction->yy__x = INT16_C(0);
        yy__snake->yy__direction->yy__y = INT16_C(-1);
    }
    return;
}
void yy__snake_down(struct yy__Snake* yy__snake) 
{
    if (yy__snake->yy__direction->yy__y == INT16_C(0))
    {
        yy__snake->yy__direction->yy__x = INT16_C(0);
        yy__snake->yy__direction->yy__y = INT16_C(1);
    }
    return;
}
void yy__snake_left(struct yy__Snake* yy__snake) 
{
    if (yy__snake->yy__direction->yy__x == INT16_C(0))
    {
        yy__snake->yy__direction->yy__x = INT16_C(-1);
        yy__snake->yy__direction->yy__y = INT16_C(0);
    }
    return;
}
void yy__snake_right(struct yy__Snake* yy__snake) 
{
    if (yy__snake->yy__direction->yy__x == INT16_C(0))
    {
        yy__snake->yy__direction->yy__x = INT16_C(1);
        yy__snake->yy__direction->yy__y = INT16_C(0);
    }
    return;
}
bool yy__snake_isdead(struct yy__Snake* yy__snake) 
{
    int32_t yy__part = INT32_C(1);
    while (true)
    {
        if (!(((yy__part < yk__arrlen(yy__snake->yy__body)))))
        {
            break;
        }
        if ((yy__snake->yy__body[yy__part]->yy__x == yy__snake->yy__body[INT32_C(0)]->yy__x) && (yy__snake->yy__body[yy__part]->yy__y == yy__snake->yy__body[INT32_C(0)]->yy__y))
        {
            return true;
        }
        yy__part += INT32_C(1);
    }
    return false;
}
bool yy__del_point(struct yy__Point* yy__p, int32_t yy__ignored) 
{
    free(yy__p);
    return true;
}
void yy__snake_reset(struct yy__Snake* yy__snake) 
{
    struct yy__Point** t__4 = yy__snake->yy__body;
    int32_t t__6 = INT32_C(0);
    size_t t__3 = yk__arrlenu(t__4);
    bool t__7 = true;
    for (size_t t__2 = 0; t__2 < t__3; t__2++) { 
        struct yy__Point* t__5 = t__4[t__2];
        bool t__8 = yy__del_point(t__5, t__6);
        if (!t__8) {t__7 = false; break; }
    }
    t__7;
    yk__arrfree(yy__snake->yy__body);
    struct yy__Point** yy__body = NULL;
    yk__arrput(yy__body, yy__point(INT16_C(2), INT16_C(0)));
    yk__arrput(yy__body, yy__point(INT16_C(1), INT16_C(0)));
    yk__arrput(yy__body, yy__point(INT16_C(0), INT16_C(0)));
    yy__snake->yy__body = yy__body;
    yy__snake->yy__direction->yy__x = INT16_C(1);
    yy__snake->yy__direction->yy__y = INT16_C(0);
    return;
}
void yy__handle_input(struct yy__State* yy__state) 
{
    uint8_t yy__just_pressed = (yy__w4_gamepad1() & ((yy__w4_gamepad1() ^ yy__state->yy__gamepad_prev)));
    if ((yy__just_pressed & yy__w4_BUTTON_UP) != UINT8_C(0))
    {
        yy__snake_up(yy__state->yy__snake);
    }
    if ((yy__just_pressed & yy__w4_BUTTON_DOWN) != UINT8_C(0))
    {
        yy__snake_down(yy__state->yy__snake);
    }
    if ((yy__just_pressed & yy__w4_BUTTON_LEFT) != UINT8_C(0))
    {
        yy__snake_left(yy__state->yy__snake);
    }
    if ((yy__just_pressed & yy__w4_BUTTON_RIGHT) != UINT8_C(0))
    {
        yy__snake_right(yy__state->yy__snake);
    }
    yy__state->yy__gamepad_prev = yy__w4_gamepad1();
    return;
}
void yy__game_step(void* yy__data) 
{
    struct yy__State* yy__state = ((struct yy__State*)yy__data);
    yy__state->yy__frame_count += UINT32_C(1);
    yy__random_set_seed(((uint64_t)yy__state->yy__frame_count));
    int32_t yy__x = (INT32_C(8) * ((int32_t)yy__state->yy__fruit->yy__x));
    int32_t yy__y = (INT32_C(8) * ((int32_t)yy__state->yy__fruit->yy__y));
    yy__handle_input(yy__state);
    if ((yy__state->yy__frame_count % UINT32_C(15)) == UINT32_C(0))
    {
        yy__snake_update(yy__state->yy__snake);
        if (yy__snake_isdead(yy__state->yy__snake))
        {
            yy__snake_reset(yy__state->yy__snake);
            yy__state->yy__fruit = yy__set_random_point(yy__state->yy__fruit);
        }
        if ((yy__state->yy__snake->yy__body[INT32_C(0)]->yy__x == yy__state->yy__fruit->yy__x) && (yy__state->yy__snake->yy__body[INT32_C(0)]->yy__y == yy__state->yy__fruit->yy__y))
        {
            int32_t yy__penultimate = (yk__arrlen(yy__state->yy__snake->yy__body) - INT32_C(1));
            yy__snake_push(yy__state->yy__snake, yy__point(yy__state->yy__snake->yy__body[yy__penultimate]->yy__x, yy__state->yy__snake->yy__body[yy__penultimate]->yy__y));
            yy__state->yy__fruit = yy__set_random_point(yy__state->yy__fruit);
        }
    }
    yy__draw_snake(yy__state->yy__snake);
    yy__w4_set_draw_colors(UINT16_C(17184));
    yy__w4_blit(yy__state->yy__fruit_sprite, yy__x, yy__y, UINT32_C(8), UINT32_C(8), yy__w4_BLIT_2BPP);
    return;
}
int32_t yy__main() 
{
    yy__random_set_seed(UINT64_C(32));
    yy__w4_set_palette(UINT32_C(16513011), UINT32_C(15052931), UINT32_C(4353629), UINT32_C(2107453));
    struct yy__State* yy__state = calloc(1, sizeof(struct yy__State));
    yy__state->yy__snake = calloc(1, sizeof(struct yy__Snake));
    yy__state->yy__fruit = yy__point(INT16_C(10), INT16_C(8));
    yy__state->yy__snake->yy__direction = yy__point(INT16_C(1), INT16_C(0));
    yy__state->yy__frame_count = UINT32_C(0);
    yy__state->yy__gamepad_prev = UINT8_C(0);
    struct yy__Point** yy__body = NULL;
    yk__arrput(yy__body, yy__point(INT16_C(2), INT16_C(0)));
    yk__arrput(yy__body, yy__point(INT16_C(1), INT16_C(0)));
    yk__arrput(yy__body, yy__point(INT16_C(0), INT16_C(0)));
    yy__state->yy__snake->yy__body = yy__body;
    yy__state->yy__fruit_sprite = ykbindata0;
    yy__w4_set_game_state(yy__state);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif