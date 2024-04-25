// YK:graphicutils,raylib#
#include "yk__lib.h"
// --forward declarations-- 
#define yy__random_init_random yk__init_random
#define yy__perlin_noise1df(nn__x) ((float)yk__perlin1d((double) nn__x))
#define yy__numbers_f2i(nn__a) ((int32_t)(nn__a))
#define yy__numbers_uu2f(nn__a) ((float)nn__a)
#define yy__utils_sin_deg(nn__x) sin(nn__x * DEG2RAD)
#define yy__utils_cos_deg(nn__x) cos(nn__x * DEG2RAD)
#define yy__c_CStr char*
#define yy__c_CUChar unsigned char
#define yy__raylib_Vector2 Vector2
#define yy__raylib_vector2(nn__x, nn__y) (Vector2){nn__x, nn__y}
#define yy__raylib_Color Color
#define yy__raylib_color(nn__r, nn__g, nn__b, nn__a) (Color){(unsigned char)nn__r, (unsigned char)nn__g, (unsigned char)nn__b, (unsigned char)nn__a}
#define yy__raylib_init_window(nn__width, nn__height, nn__title) InitWindow((int)nn__width, (int)nn__height, nn__title)
#define yy__raylib_window_should_close() WindowShouldClose()
#define yy__raylib_close_window() CloseWindow()
#define yy__raylib_clear_background(nn__p_color) ClearBackground(nn__p_color)
#define yy__raylib_begin_drawing() BeginDrawing()
#define yy__raylib_end_drawing() EndDrawing()
#define yy__raylib_set_target_fps(nn__fps) SetTargetFPS((int)nn__fps)
#define yy__raylib_draw_line_ex(nn__start_pos, nn__end_pos, nn__thick, nn__p_color) DrawLineEx(nn__start_pos, nn__end_pos, nn__thick, nn__p_color)
#define yy__raylib_draw_ellipse(nn__center_x, nn__center_y, nn__radius_h, nn__radius_v, nn__p_color) DrawEllipse((int)nn__center_x, (int)nn__center_y, nn__radius_h, nn__radius_v, nn__p_color)
#define yy__raylib_draw_fps(nn__pos_x, nn__pos_y) DrawFPS((int)nn__pos_x, (int)nn__pos_y)
struct yy__State;
void yy__random_set_seed(uint64_t);
float yy__random_randomf();
float yy__random_random_betweenf(float, float);
float yy__utils_remap(float, float, float, float, float);
yy__raylib_Color yy__utils_lerp_color(yy__raylib_Color, yy__raylib_Color, float);
void yy__branch(float, float, float, float, struct yy__State*);
void yy__update_draw_frame(struct yy__State*);
int32_t yy__main();
// --structs-- 
struct yy__State {
    float yy__width;
    float yy__height;
    float yy__angle;
    uint64_t yy__frame_count;
    yy__raylib_Color yy__blue;
    yy__raylib_Color yy__green;
    yy__raylib_Color yy__color3;
};
// --functions-- 
void yy__random_set_seed(uint64_t nn__seed) 
{
    srand((unsigned) nn__seed);
}
float yy__random_randomf() 
{
    float val;
    #if defined(YK__WASM4)
    val = ((float)rand() / 32767.0f);
    #else
    val = ((float)rand() / (float)RAND_MAX);
    #endif
    return val;
}
float yy__random_random_betweenf(float yy__random_a, float yy__random_b) 
{
    float yy__random_min = yy__random_a;
    float yy__random_max = yy__random_b;
    if (yy__random_a > yy__random_b)
    {
        yy__random_min = yy__random_b;
        yy__random_max = yy__random_a;
    }
    float t__0 = (yy__random_min + ((yy__random_randomf() * (yy__random_max - yy__random_min))));
    return t__0;
}
float yy__utils_remap(float yy__utils_x, float yy__utils_a, float yy__utils_b, float yy__utils_c, float yy__utils_d) 
{
    if (yy__utils_a == yy__utils_b)
    {
        return 0.0f;
    }
    float t__0 = ((((yy__utils_x - yy__utils_a) / (yy__utils_b - yy__utils_a)) * (yy__utils_d - yy__utils_c)) + yy__utils_c);
    return t__0;
}
yy__raylib_Color yy__utils_lerp_color(yy__raylib_Color nn__a, yy__raylib_Color nn__b, float nn__fraction) 
{
    float x = nn__fraction;
    if (x > 1.0f) {
        x = 1.0f;
    }
    if (x < 0.0f) {
        x = 0.0f;
    }
    float r = (nn__b.r - nn__a.r) * x + (nn__a.r);
    float g = (nn__b.g - nn__a.g) * x + (nn__a.g);
    float b = (nn__b.b - nn__a.b) * x + (nn__a.b);
    float a = (nn__b.a - nn__a.a) * x + (nn__a.a);
    return (Color){(unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a}
    ;
}
void yy__branch(float yy__x, float yy__y, float yy__length, float yy__angle, struct yy__State* yy__s) 
{
    if (yy__length < 4.0f)
    {
        float yy__leaf_width = yy__random_random_betweenf(1.0f, 3.0f);
        float yy__leaf_height = yy__random_random_betweenf(3.0f, 6.0f);
        yy__raylib_Color yy__lerped_green = yy__utils_lerp_color(yy__s->yy__green, yy__s->yy__blue, (yy__utils_remap(yy__x, 0.0f, yy__s->yy__width, 0.0f, 1.0f) * 2.0f));
        yy__raylib_Color yy__color = yy__utils_lerp_color(yy__lerped_green, yy__s->yy__color3, (yy__utils_remap(yy__y, 0.0f, yy__s->yy__height, 0.0f, 1.0f) * 1.5f));
        yy__raylib_draw_ellipse(yy__numbers_f2i(yy__x), yy__numbers_f2i(yy__y), yy__leaf_height, yy__leaf_width, yy__color);
        return;
    }
    float yy__wind = ((yy__utils_sin_deg(yy__perlin_noise1df((yy__numbers_uu2f(yy__s->yy__frame_count) / 50.0f))) * 100.0f) * yy__utils_sin_deg((yy__numbers_uu2f(yy__s->yy__frame_count) / 2.0f)));
    float yy__next_y = (yy__y - (yy__length * yy__utils_cos_deg(yy__angle)));
    float yy__next_x = (yy__x + (yy__length * yy__utils_sin_deg(yy__angle)));
    float yy__thick = yy__utils_remap(yy__length, 0.0f, (yy__s->yy__height / 4.0f), 2.0f, 6.0f);
    yy__raylib_draw_line_ex(yy__raylib_vector2(yy__x, yy__y), yy__raylib_vector2(yy__next_x, yy__next_y), yy__thick, yy__raylib_color(INT32_C(152), INT32_C(50), INT32_C(1), INT32_C(255)));
    float yy__r1 = yy__random_random_betweenf(0.3f, 0.9f);
    float yy__r2 = yy__random_random_betweenf(0.5f, 0.8f);
    yy__branch(yy__next_x, yy__next_y, (yy__length * yy__r2), ((yy__angle + yy__s->yy__angle) + (yy__wind * 10.0f)), yy__s);
    yy__branch(yy__next_x, yy__next_y, (yy__length * yy__r1), ((yy__angle - yy__s->yy__angle) + (yy__wind * 10.0f)), yy__s);
    return;
}
void yy__update_draw_frame(struct yy__State* yy__s) 
{
    yy__raylib_clear_background(yy__raylib_color(INT32_C(255), INT32_C(255), INT32_C(255), INT32_C(255)));
    yy__branch((yy__s->yy__width / 2.0f), yy__s->yy__height, (yy__s->yy__height / 4.0f), 0.0f, yy__s);
    return;
}
int32_t yy__main() 
{
    struct yy__State* yy__s = calloc(1, sizeof(struct yy__State));
    yy__s->yy__angle = yy__random_random_betweenf(30.0f, 45.0f);
    yy__s->yy__width = 600.0f;
    yy__s->yy__height = 600.0f;
    yy__s->yy__frame_count = UINT64_C(0);
    yy__s->yy__blue = yy__raylib_color(INT32_C(0), INT32_C(255), INT32_C(214), INT32_C(255));
    yy__s->yy__green = yy__raylib_color(INT32_C(0), INT32_C(255), INT32_C(0), INT32_C(255));
    yy__s->yy__color3 = yy__raylib_color(INT32_C(255), INT32_C(45), INT32_C(156), INT32_C(255));
    yy__raylib_init_window(yy__numbers_f2i(yy__s->yy__width), yy__numbers_f2i(yy__s->yy__height), "Fractal Tree in the Wind");
    yy__raylib_set_target_fps(INT32_C(120));
    uint64_t yy__seed = yy__random_init_random();
    while (true)
    {
        if (!(((!(yy__raylib_window_should_close())))))
        {
            break;
        }
        yy__raylib_begin_drawing();
        yy__update_draw_frame(yy__s);
        yy__raylib_draw_fps(INT32_C(0), INT32_C(0));
        yy__raylib_end_drawing();
        yy__s->yy__frame_count += UINT64_C(1);
        yy__random_set_seed(yy__seed);
    }
    yy__raylib_close_window();
    free(yy__s);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif