// YK:graphicutils,wasm4#
#include "yk__lib.h"
#define yy__c_Size size_t
#define yy__c_calloc calloc
#define yy__w4_set_draw_colors(nn__value) *((uint16_t*)0x14) = nn__value
#define yy__w4_gamepad1() (*((const uint8_t*)0x16))
uint8_t const  yy__w4_BUTTON_1 = UINT8_C(1);
uint8_t const  yy__w4_BUTTON_2 = UINT8_C(2);
uint8_t const  yy__w4_BUTTON_LEFT = UINT8_C(16);
uint8_t const  yy__w4_BUTTON_RIGHT = UINT8_C(32);
uint8_t const  yy__w4_BUTTON_UP = UINT8_C(64);
uint8_t const  yy__w4_BUTTON_DOWN = UINT8_C(128);
int32_t const  yy__MAX_NOTES = INT32_C(256);
int32_t const  yy__FONT_WIDTH = INT32_C(8);
int32_t const  yy__NOTE_WRAP_AROUND = INT32_C(55);
uint8_t const  yy__NOTE_C = UINT8_C(1);
uint8_t const  yy__NOTE_C_S = UINT8_C(2);
uint8_t const  yy__NOTE_D = UINT8_C(3);
uint8_t const  yy__NOTE_D_S = UINT8_C(4);
uint8_t const  yy__NOTE_E = UINT8_C(5);
uint8_t const  yy__NOTE_F = UINT8_C(6);
uint8_t const  yy__NOTE_F_S = UINT8_C(7);
uint8_t const  yy__NOTE_G = UINT8_C(8);
uint8_t const  yy__NOTE_G_S = UINT8_C(9);
uint8_t const  yy__NOTE_A = UINT8_C(10);
uint8_t const  yy__NOTE_A_S = UINT8_C(11);
uint8_t const  yy__NOTE_B = UINT8_C(12);
uint8_t const  yy__NOTE_REST = UINT8_C(13);
uint8_t const  yy__NOTE_NULL = UINT8_C(0);
uint8_t const  yy__TIME_64 = UINT8_C(6);
uint8_t const  yy__TIME_4 = UINT8_C(2);
uint8_t const  yy__TIME_FULL = UINT8_C(0);
uint8_t const  yy__OCTAVE_1 = UINT8_C(0);
uint8_t const  yy__OCTAVE_2 = UINT8_C(1);
uint8_t const  yy__OCTAVE_3 = UINT8_C(2);
uint8_t const  yy__MODE_TIME = UINT8_C(0);
uint8_t const  yy__MODE_NOTE = UINT8_C(1);
uint8_t const  yy__MODE_OCT = UINT8_C(2);
uint8_t const  yy__MODE_DEL = UINT8_C(3);
uint8_t const  yy__TOTAL_MODES = UINT8_C(4);
uint8_t const ykbindata0[] = {
UINT8_C(0x30), UINT8_C(0x31), UINT8_C(0x32), UINT8_C(0x33),
UINT8_C(0x34), UINT8_C(0x35), UINT8_C(0x36), UINT8_C(0x37),
UINT8_C(0x38), UINT8_C(0x39), UINT8_C(0x2d), UINT8_C(0x20),
UINT8_C(0x00)
};
uint8_t const ykbindata1[] = {
UINT8_C(0x6d), UINT8_C(0x6f), UINT8_C(0x64), UINT8_C(0x65),
UINT8_C(0x3a), UINT8_C(0x00)
};
uint8_t const ykbindata2[] = {
UINT8_C(0x70), UINT8_C(0x6c), UINT8_C(0x61), UINT8_C(0x79),
UINT8_C(0x00)
};
uint8_t const ykbindata3[] = {
UINT8_C(0x73), UINT8_C(0x74), UINT8_C(0x6f), UINT8_C(0x70),
UINT8_C(0x00)
};
uint8_t const ykbindata4[] = {
UINT8_C(0x74), UINT8_C(0x69), UINT8_C(0x6d), UINT8_C(0x65),
UINT8_C(0x00)
};
uint8_t const ykbindata5[] = {
UINT8_C(0x61), UINT8_C(0x64), UINT8_C(0x64), UINT8_C(0x85),
UINT8_C(0x00)
};
uint8_t const ykbindata6[] = {
UINT8_C(0x6e), UINT8_C(0x6f), UINT8_C(0x74), UINT8_C(0x65),
UINT8_C(0x00)
};
uint8_t const ykbindata7[] = {
UINT8_C(0x6f), UINT8_C(0x63), UINT8_C(0x74), UINT8_C(0x61),
UINT8_C(0x00)
};
uint8_t const ykbindata8[] = {
UINT8_C(0x61), UINT8_C(0x64), UINT8_C(0x64), UINT8_C(0x84),
UINT8_C(0x00)
};
uint8_t const ykbindata9[] = {
UINT8_C(0x64), UINT8_C(0x65), UINT8_C(0x6c), UINT8_C(0x20),
UINT8_C(0x00)
};
uint8_t const ykbindata10[] = {
UINT8_C(0x80), UINT8_C(0x00)
};
uint8_t const ykbindata11[] = {
UINT8_C(0x81), UINT8_C(0x00)
};
uint8_t const ykbindata12[] = {
UINT8_C(0x80), UINT8_C(0x2b), UINT8_C(0x81), UINT8_C(0x00)
};
uint8_t const ykbindata13[] = {
UINT8_C(0x6d), UINT8_C(0x6f), UINT8_C(0x64), UINT8_C(0x65),
UINT8_C(0x00)
};
uint8_t const ykbindata14[] = {
UINT8_C(0x63), UINT8_C(0x64), UINT8_C(0x65), UINT8_C(0x66),
UINT8_C(0x67), UINT8_C(0x61), UINT8_C(0x62), UINT8_C(0x52),
UINT8_C(0x23), UINT8_C(0x30)
};
struct yy__State;
struct yt_tuple_u8_u8_u8_u8 { uint8_t e1; uint8_t e2; uint8_t e3; uint8_t e4; };
struct yy__State {
    int32_t yy__width;
    int32_t yy__height;
    uint64_t yy__frame_count;
    uint8_t yy__gamepad_prev;
    uint8_t* yy__text_buf;
    struct yt_tuple_u8_u8_u8_u8* yy__note_buf;
    int32_t* yy__note_freq;
    int32_t* yy__note_time;
    int32_t yy__cursor;
    int32_t yy__prev_cursor;
    int32_t yy__v_start;
    int32_t yy__v_end;
    int32_t yy__note_count;
    uint8_t yy__mode;
    bool yy__playing;
    uint64_t yy__play_on;
};
void yy__w4_set_palette(uint32_t, uint32_t, uint32_t, uint32_t);
void yy__w4_hline(int32_t, int32_t, uint32_t);
void yy__w4_vline(int32_t, int32_t, uint32_t);
void yy__w4_text_u8(uint8_t const * const , int32_t, int32_t);
void yy__w4_tone(uint32_t, uint32_t, uint32_t, uint32_t);
void yy__w4_set_game_state(void*);
void yy__clear_buf(uint8_t*);
bool yy__i2s(int32_t, uint8_t*);
void yy__del_note(struct yy__State*);
void yy__add_left(struct yy__State*);
void yy__add_right(struct yy__State*);
void yy__up_note(struct yy__State*);
void yy__down_note(struct yy__State*);
void yy__handle_input(struct yy__State*);
void yy__draw_board(struct yy__State*);
void yy__draw_note(struct yy__State*, int32_t, int32_t, bool);
void yy__draw_notes(struct yy__State*);
void yy__play_notes(struct yy__State*);
void yy__game_step(void*);
struct yy__State* yy__init_state();
void yy__del_state(void*);
int32_t yy__main();
void yy__w4_set_palette(uint32_t nn__c1, uint32_t nn__c2, uint32_t nn__c3, uint32_t nn__c4) 
{
    
    PALETTE[0] = nn__c1;
    PALETTE[1] = nn__c2;
    PALETTE[2] = nn__c3;
    PALETTE[3] = nn__c4;
    ;
}
void yy__w4_hline(int32_t nn__x, int32_t nn__y, uint32_t nn__length) { hline(nn__x, nn__y, nn__length); }
void yy__w4_vline(int32_t nn__x, int32_t nn__y, uint32_t nn__length) { vline(nn__x, nn__y, nn__length); }
void yy__w4_text_u8(uint8_t const * const  nn__text_data, int32_t nn__x, int32_t nn__y) 
{
    text((const char *)nn__text_data, nn__x, nn__y);
}
void yy__w4_tone(uint32_t nn__frequency, uint32_t nn__duration, uint32_t nn__volume, uint32_t nn__flags) { tone(nn__frequency, nn__duration, nn__volume, nn__flags); }
void yy__w4_set_game_state(void* nn__data) 
{
    yk__set_game_state(nn__data);;
}
void yy__clear_buf(uint8_t* yy__target) 
{
    yy__target[INT32_C(0)] = UINT8_C(0);
    yy__target[INT32_C(1)] = UINT8_C(0);
    yy__target[INT32_C(2)] = UINT8_C(0);
    yy__target[INT32_C(3)] = UINT8_C(0);
    yy__target[INT32_C(4)] = UINT8_C(0);
    yy__target[INT32_C(5)] = UINT8_C(0);
    yy__target[INT32_C(6)] = UINT8_C(0);
    yy__target[INT32_C(7)] = UINT8_C(0);
    yy__target[INT32_C(8)] = UINT8_C(0);
    yy__target[INT32_C(9)] = UINT8_C(0);
    yy__target[INT32_C(10)] = UINT8_C(0);
    return;
}
bool yy__i2s(int32_t yy__x, uint8_t* yy__target) 
{
    uint8_t const * yy__charset = ykbindata0;
    yy__clear_buf(yy__target);
    int32_t yy__pos = INT32_C(0);
    int32_t yy__y = yy__x;
    if ((yy__x > INT32_C(999999999)) || (yy__x < INT32_C(-99999999)))
    {
        yy__target[INT32_C(0)] = ((uint8_t)(((yk__sds)yy__charset)[INT32_C(10)]));
        return false;
    }
    if (yy__x < INT32_C(0))
    {
        yy__y *= INT32_C(-1);
        yy__target[yy__pos] = ((uint8_t)(((yk__sds)yy__charset)[INT32_C(10)]));
    }
    else
    {
        yy__target[yy__pos] = ((uint8_t)(((yk__sds)yy__charset)[INT32_C(11)]));
    }
    yy__pos += INT32_C(1);
    if (yy__y == INT32_C(0))
    {
        yy__target[yy__pos] = ((uint8_t)(((yk__sds)yy__charset)[INT32_C(0)]));
        yy__pos += INT32_C(1);
    }
    while (true)
    {
        if (!(((yy__y != INT32_C(0)))))
        {
            break;
        }
        int32_t yy__character = (yy__y % INT32_C(10));
        yy__target[yy__pos] = ((uint8_t)(((yk__sds)yy__charset)[yy__character]));
        yy__pos += INT32_C(1);
        yy__y /= INT32_C(10);
    }
    int32_t yy__rpos = INT32_C(1);
    int32_t yy__rmax = (((yy__pos / INT32_C(2))) + INT32_C(1));
    while (true)
    {
        if (!(yy__rpos < yy__rmax))
        {
            break;
        }
        uint8_t yy__temp = yy__target[yy__rpos];
        yy__target[yy__rpos] = yy__target[(yy__pos - yy__rpos)];
        yy__target[(yy__pos - yy__rpos)] = yy__temp;
        yy__rpos += INT32_C(1);
    }
    return true;
}
void yy__del_note(struct yy__State* yy__s) 
{
    if (yy__s->yy__note_count == INT32_C(0))
    {
        return;
    }
    int32_t yy__x = (yy__s->yy__cursor + INT32_C(1));
    int32_t yy__last = (yy__s->yy__note_count - INT32_C(1));
    while (true)
    {
        if (!(yy__x <= yy__last))
        {
            break;
        }
        yy__s->yy__note_buf[(yy__x - INT32_C(1))].e1 = yy__s->yy__note_buf[yy__x].e1;
        yy__s->yy__note_buf[(yy__x - INT32_C(1))].e2 = yy__s->yy__note_buf[yy__x].e2;
        yy__s->yy__note_buf[(yy__x - INT32_C(1))].e3 = yy__s->yy__note_buf[yy__x].e3;
        yy__s->yy__note_buf[(yy__x - INT32_C(1))].e4 = yy__s->yy__note_buf[yy__x].e4;
        yy__x += INT32_C(1);
    }
    yy__s->yy__note_buf[yy__last].e1 = yy__NOTE_NULL;
    yy__s->yy__note_buf[yy__last].e2 = yy__NOTE_NULL;
    yy__s->yy__note_buf[yy__last].e3 = yy__NOTE_NULL;
    yy__s->yy__note_buf[yy__last].e4 = yy__NOTE_NULL;
    yy__s->yy__note_count -= INT32_C(1);
    if (yy__s->yy__cursor >= yy__s->yy__note_count)
    {
        yy__s->yy__cursor = (yy__s->yy__note_count - INT32_C(1));
    }
    if (yy__s->yy__cursor < INT32_C(0))
    {
        yy__s->yy__cursor = INT32_C(0);
    }
    return;
}
void yy__add_left(struct yy__State* yy__s) 
{
    if (yy__s->yy__note_count == yy__MAX_NOTES)
    {
        return;
    }
    if (yy__s->yy__note_count == INT32_C(0))
    {
        yy__s->yy__note_buf[INT32_C(0)].e1 = yy__TIME_4;
        yy__s->yy__note_buf[INT32_C(0)].e2 = yy__NOTE_C;
        yy__s->yy__note_buf[INT32_C(0)].e3 = yy__OCTAVE_2;
        yy__s->yy__note_buf[INT32_C(0)].e4 = UINT8_C(0);
        yy__s->yy__note_count = INT32_C(1);
        yy__s->yy__cursor = INT32_C(0);
        return;
    }
    int32_t yy__x = (yy__s->yy__note_count - INT32_C(1));
    while (true)
    {
        if (!(yy__x >= yy__s->yy__cursor))
        {
            break;
        }
        yy__s->yy__note_buf[(yy__x + INT32_C(1))].e1 = yy__s->yy__note_buf[yy__x].e1;
        yy__s->yy__note_buf[(yy__x + INT32_C(1))].e2 = yy__s->yy__note_buf[yy__x].e2;
        yy__s->yy__note_buf[(yy__x + INT32_C(1))].e3 = yy__s->yy__note_buf[yy__x].e3;
        yy__s->yy__note_buf[(yy__x + INT32_C(1))].e4 = yy__s->yy__note_buf[yy__x].e4;
        yy__x -= INT32_C(1);
    }
    yy__s->yy__note_buf[yy__s->yy__cursor].e1 = yy__TIME_4;
    if ((yy__s->yy__note_count % INT32_C(2)) != INT32_C(0))
    {
        yy__s->yy__note_buf[yy__s->yy__cursor].e2 = yy__NOTE_C;
    }
    else
    {
        yy__s->yy__note_buf[yy__s->yy__cursor].e2 = yy__NOTE_REST;
    }
    yy__s->yy__note_buf[yy__s->yy__cursor].e3 = yy__OCTAVE_2;
    yy__s->yy__note_buf[yy__s->yy__cursor].e4 = UINT8_C(0);
    yy__s->yy__note_count += INT32_C(1);
    return;
}
void yy__add_right(struct yy__State* yy__s) 
{
    if (yy__s->yy__note_count == yy__MAX_NOTES)
    {
        return;
    }
    if (yy__s->yy__note_count == INT32_C(0))
    {
        yy__s->yy__note_buf[INT32_C(0)].e1 = yy__TIME_4;
        yy__s->yy__note_buf[INT32_C(0)].e2 = yy__NOTE_C;
        yy__s->yy__note_buf[INT32_C(0)].e3 = yy__OCTAVE_2;
        yy__s->yy__note_buf[INT32_C(0)].e4 = UINT8_C(0);
        yy__s->yy__note_count = INT32_C(1);
        yy__s->yy__cursor = INT32_C(0);
        return;
    }
    int32_t yy__x = (yy__s->yy__note_count - INT32_C(1));
    while (true)
    {
        if (!(((yy__x >= (yy__s->yy__cursor + INT32_C(1))))))
        {
            break;
        }
        yy__s->yy__note_buf[(yy__x + INT32_C(1))].e1 = yy__s->yy__note_buf[yy__x].e1;
        yy__s->yy__note_buf[(yy__x + INT32_C(1))].e2 = yy__s->yy__note_buf[yy__x].e2;
        yy__s->yy__note_buf[(yy__x + INT32_C(1))].e3 = yy__s->yy__note_buf[yy__x].e3;
        yy__s->yy__note_buf[(yy__x + INT32_C(1))].e4 = yy__s->yy__note_buf[yy__x].e4;
        yy__x -= INT32_C(1);
    }
    yy__s->yy__note_buf[(yy__s->yy__cursor + INT32_C(1))].e1 = yy__TIME_4;
    if ((yy__s->yy__note_count % INT32_C(2)) != INT32_C(0))
    {
        yy__s->yy__note_buf[(yy__s->yy__cursor + INT32_C(1))].e2 = yy__NOTE_C;
    }
    else
    {
        yy__s->yy__note_buf[(yy__s->yy__cursor + INT32_C(1))].e2 = yy__NOTE_REST;
    }
    yy__s->yy__note_buf[(yy__s->yy__cursor + INT32_C(1))].e3 = yy__OCTAVE_2;
    yy__s->yy__note_buf[(yy__s->yy__cursor + INT32_C(1))].e4 = UINT8_C(0);
    yy__s->yy__note_count += INT32_C(1);
    yy__s->yy__cursor += INT32_C(1);
    return;
}
void yy__up_note(struct yy__State* yy__s) 
{
    if (yy__s->yy__note_count == INT32_C(0))
    {
        return;
    }
    if (yy__s->yy__mode == yy__MODE_TIME)
    {
        yy__s->yy__note_buf[yy__s->yy__cursor].e1 += UINT8_C(1);
        if (yy__s->yy__note_buf[yy__s->yy__cursor].e1 > yy__TIME_64)
        {
            yy__s->yy__note_buf[yy__s->yy__cursor].e1 = yy__TIME_FULL;
        }
    }
    if (yy__s->yy__mode == yy__MODE_NOTE)
    {
        yy__s->yy__note_buf[yy__s->yy__cursor].e2 += UINT8_C(1);
        if (yy__s->yy__note_buf[yy__s->yy__cursor].e2 > yy__NOTE_REST)
        {
            yy__s->yy__note_buf[yy__s->yy__cursor].e2 = yy__NOTE_C;
        }
    }
    if (yy__s->yy__mode == yy__MODE_OCT)
    {
        yy__s->yy__note_buf[yy__s->yy__cursor].e3 += UINT8_C(1);
        if (yy__s->yy__note_buf[yy__s->yy__cursor].e3 > yy__OCTAVE_3)
        {
            yy__s->yy__note_buf[yy__s->yy__cursor].e3 = yy__OCTAVE_1;
        }
    }
    return;
}
void yy__down_note(struct yy__State* yy__s) 
{
    if (yy__s->yy__note_count == INT32_C(0))
    {
        return;
    }
    if (yy__s->yy__mode == yy__MODE_TIME)
    {
        if (yy__s->yy__note_buf[yy__s->yy__cursor].e1 == yy__TIME_FULL)
        {
            yy__s->yy__note_buf[yy__s->yy__cursor].e1 = yy__TIME_64;
        }
        else
        {
            yy__s->yy__note_buf[yy__s->yy__cursor].e1 -= UINT8_C(1);
        }
    }
    if (yy__s->yy__mode == yy__MODE_NOTE)
    {
        if (yy__s->yy__note_buf[yy__s->yy__cursor].e2 == yy__NOTE_C)
        {
            yy__s->yy__note_buf[yy__s->yy__cursor].e2 = yy__NOTE_REST;
        }
        else
        {
            yy__s->yy__note_buf[yy__s->yy__cursor].e2 -= UINT8_C(1);
        }
    }
    if (yy__s->yy__mode == yy__MODE_OCT)
    {
        if (yy__s->yy__note_buf[yy__s->yy__cursor].e3 == yy__OCTAVE_1)
        {
            yy__s->yy__note_buf[yy__s->yy__cursor].e3 = yy__OCTAVE_3;
        }
        else
        {
            yy__s->yy__note_buf[yy__s->yy__cursor].e3 -= UINT8_C(1);
        }
    }
    return;
}
void yy__handle_input(struct yy__State* yy__s) 
{
    uint8_t yy__just_pressed = (yy__w4_gamepad1() & ((yy__w4_gamepad1() ^ yy__s->yy__gamepad_prev)));
    if ((yy__just_pressed & yy__w4_BUTTON_2) != UINT8_C(0))
    {
        if (yy__s->yy__playing)
        {
            yy__s->yy__playing = false;
            yy__s->yy__cursor = yy__s->yy__prev_cursor;
            yy__s->yy__mode = yy__MODE_NOTE;
        }
        else
        {
            if ((yy__w4_gamepad1() & yy__w4_BUTTON_1) != UINT8_C(0))
            {
                if (yy__s->yy__note_count == INT32_C(0))
                {
                    return;
                }
                yy__s->yy__prev_cursor = yy__s->yy__cursor;
                yy__s->yy__cursor = INT32_C(0);
                yy__s->yy__playing = true;
            }
            else
            {
                if (yy__s->yy__mode == yy__MODE_DEL)
                {
                    yy__del_note(yy__s);
                }
                else
                {
                    if (yy__s->yy__mode == yy__MODE_OCT)
                    {
                        yy__add_left(yy__s);
                    }
                    else
                    {
                        yy__add_right(yy__s);
                    }
                }
            }
        }
    }
    if (!(yy__s->yy__playing))
    {
        if ((yy__just_pressed & yy__w4_BUTTON_1) != UINT8_C(0))
        {
            yy__s->yy__mode += UINT8_C(1);
            yy__s->yy__mode %= yy__TOTAL_MODES;
        }
        if ((yy__just_pressed & yy__w4_BUTTON_UP) != UINT8_C(0))
        {
            yy__up_note(yy__s);
        }
        if ((yy__just_pressed & yy__w4_BUTTON_DOWN) != UINT8_C(0))
        {
            yy__down_note(yy__s);
        }
        if ((yy__just_pressed & yy__w4_BUTTON_LEFT) != UINT8_C(0))
        {
            yy__s->yy__cursor -= INT32_C(1);
            if (yy__s->yy__cursor < INT32_C(0))
            {
                yy__s->yy__cursor = (yy__s->yy__note_count - INT32_C(1));
            }
        }
        if ((yy__just_pressed & yy__w4_BUTTON_RIGHT) != UINT8_C(0))
        {
            yy__s->yy__cursor += INT32_C(1);
            if (yy__s->yy__cursor > (yy__s->yy__note_count - INT32_C(1)))
            {
                yy__s->yy__cursor = INT32_C(0);
            }
        }
    }
    yy__s->yy__gamepad_prev = yy__w4_gamepad1();
    return;
}
void yy__draw_board(struct yy__State* yy__s) 
{
    yy__w4_set_draw_colors(UINT16_C(20));
    yy__w4_text_u8(ykbindata1, INT32_C(2), INT32_C(2));
    yy__i2s(yy__s->yy__note_count, yy__s->yy__text_buf);
    yy__w4_text_u8(((uint8_t const * const )yy__s->yy__text_buf), INT32_C(120), INT32_C(2));
    yy__w4_vline(INT32_C(118), INT32_C(0), UINT32_C(10));
    yy__w4_vline(INT32_C(79), INT32_C(0), UINT32_C(10));
    yy__w4_set_draw_colors(UINT16_C(18));
    if (yy__s->yy__note_count == INT32_C(0))
    {
        yy__i2s(INT32_C(0), yy__s->yy__text_buf);
    }
    else
    {
        yy__i2s((yy__s->yy__cursor + INT32_C(1)), yy__s->yy__text_buf);
    }
    yy__w4_text_u8(((uint8_t const * const )yy__s->yy__text_buf), INT32_C(80), INT32_C(2));
    yy__w4_hline(INT32_C(0), INT32_C(10), UINT32_C(160));
    yy__w4_hline(INT32_C(0), (yy__s->yy__height - INT32_C(10)), UINT32_C(160));
    if (yy__s->yy__playing)
    {
        yy__w4_text_u8(ykbindata2, INT32_C(44), INT32_C(2));
        yy__w4_text_u8(ykbindata3, INT32_C(55), ((yy__s->yy__height - INT32_C(10)) + INT32_C(2)));
    }
    else
    {
        if (yy__s->yy__mode == yy__MODE_TIME)
        {
            yy__w4_text_u8(ykbindata4, INT32_C(44), INT32_C(2));
            yy__w4_text_u8(ykbindata5, INT32_C(55), ((yy__s->yy__height - INT32_C(10)) + INT32_C(2)));
        }
        else
        {
            if (yy__s->yy__mode == yy__MODE_NOTE)
            {
                yy__w4_text_u8(ykbindata6, INT32_C(44), INT32_C(2));
                yy__w4_text_u8(ykbindata5, INT32_C(55), ((yy__s->yy__height - INT32_C(10)) + INT32_C(2)));
            }
            else
            {
                if (yy__s->yy__mode == yy__MODE_OCT)
                {
                    yy__w4_text_u8(ykbindata7, INT32_C(44), INT32_C(2));
                    yy__w4_text_u8(ykbindata8, INT32_C(55), ((yy__s->yy__height - INT32_C(10)) + INT32_C(2)));
                }
                else
                {
                    if (yy__s->yy__mode == yy__MODE_DEL)
                    {
                        yy__w4_set_draw_colors(UINT16_C(19));
                        yy__w4_text_u8(ykbindata9, INT32_C(44), INT32_C(2));
                        yy__w4_text_u8(ykbindata9, INT32_C(55), ((yy__s->yy__height - INT32_C(10)) + INT32_C(2)));
                    }
                }
            }
        }
    }
    yy__w4_set_draw_colors(UINT16_C(20));
    if (!(yy__s->yy__playing))
    {
        yy__w4_text_u8(ykbindata10, INT32_C(2), ((yy__s->yy__height - INT32_C(10)) + INT32_C(2)));
    }
    yy__w4_text_u8(ykbindata11, INT32_C(45), ((yy__s->yy__height - INT32_C(10)) + INT32_C(2)));
    if (!(yy__s->yy__playing))
    {
        yy__w4_text_u8(ykbindata12, INT32_C(88), ((yy__s->yy__height - INT32_C(10)) + INT32_C(2)));
        yy__w4_set_draw_colors(UINT16_C(18));
        yy__w4_text_u8(ykbindata13, INT32_C(12), ((yy__s->yy__height - INT32_C(10)) + INT32_C(2)));
    }
    if (!(yy__s->yy__playing))
    {
        yy__w4_text_u8(ykbindata2, INT32_C(114), ((yy__s->yy__height - INT32_C(10)) + INT32_C(2)));
    }
    return;
}
void yy__draw_note(struct yy__State* yy__s, int32_t yy__grid_pos, int32_t yy__note_pos, bool yy__cursor) 
{
    uint8_t* yy__note_data = ((uint8_t*)ykbindata14);
    if (yy__s->yy__note_buf[yy__note_pos].e2 == yy__NOTE_NULL)
    {
        return;
    }
    int32_t yy__x = (INT32_C(4) + (((yy__grid_pos % INT32_C(4))) * INT32_C(40)));
    int32_t yy__y = (INT32_C(12) + (((yy__grid_pos / INT32_C(4))) * INT32_C(10)));
    int32_t yy__x_delta = INT32_C(0);
    yy__clear_buf(yy__s->yy__text_buf);
    yy__s->yy__text_buf[INT32_C(0)] = (yy__note_data[INT32_C(9)] + yy__s->yy__note_buf[yy__note_pos].e1);
    if (yy__cursor)
    {
        yy__w4_set_draw_colors(UINT16_C(66));
    }
    else
    {
        yy__w4_set_draw_colors(UINT16_C(18));
    }
    yy__w4_text_u8(((uint8_t const * const )yy__s->yy__text_buf), (yy__x + yy__x_delta), yy__y);
    yy__x_delta += yy__FONT_WIDTH;
    uint8_t yy__note = yy__s->yy__note_buf[yy__note_pos].e2;
    if ((yy__note == yy__NOTE_C) || (yy__note == yy__NOTE_C_S))
    {
        yy__s->yy__text_buf[INT32_C(0)] = yy__note_data[INT32_C(0)];
    }
    if ((yy__note == yy__NOTE_D) || (yy__note == yy__NOTE_D_S))
    {
        yy__s->yy__text_buf[INT32_C(0)] = yy__note_data[INT32_C(1)];
    }
    if (yy__note == yy__NOTE_E)
    {
        yy__s->yy__text_buf[INT32_C(0)] = yy__note_data[INT32_C(2)];
    }
    if ((yy__note == yy__NOTE_F) || (yy__note == yy__NOTE_F_S))
    {
        yy__s->yy__text_buf[INT32_C(0)] = yy__note_data[INT32_C(3)];
    }
    if ((yy__note == yy__NOTE_G) || (yy__note == yy__NOTE_G_S))
    {
        yy__s->yy__text_buf[INT32_C(0)] = yy__note_data[INT32_C(4)];
    }
    if ((yy__note == yy__NOTE_A) || (yy__note == yy__NOTE_A_S))
    {
        yy__s->yy__text_buf[INT32_C(0)] = yy__note_data[INT32_C(5)];
    }
    if (yy__note == yy__NOTE_B)
    {
        yy__s->yy__text_buf[INT32_C(0)] = yy__note_data[INT32_C(6)];
    }
    if (yy__note == yy__NOTE_REST)
    {
        yy__s->yy__text_buf[INT32_C(0)] = yy__note_data[INT32_C(7)];
    }
    else
    {
        if (((((yy__note == yy__NOTE_C_S) || (yy__note == yy__NOTE_D_S)) || (yy__note == yy__NOTE_F_S)) || (yy__note == yy__NOTE_G_S)) || (yy__note == yy__NOTE_A_S))
        {
            yy__s->yy__text_buf[INT32_C(1)] = yy__note_data[INT32_C(8)];
        }
    }
    if (yy__cursor)
    {
        yy__w4_set_draw_colors(UINT16_C(67));
    }
    else
    {
        yy__w4_set_draw_colors(UINT16_C(19));
    }
    yy__w4_text_u8(((uint8_t const * const )yy__s->yy__text_buf), (yy__x + yy__x_delta), yy__y);
    yy__x_delta += yy__FONT_WIDTH;
    if (yy__s->yy__text_buf[INT32_C(1)] != UINT8_C(0))
    {
        yy__x_delta += yy__FONT_WIDTH;
    }
    yy__s->yy__text_buf[INT32_C(1)] = UINT8_C(0);
    if (yy__note != yy__NOTE_REST)
    {
        yy__s->yy__text_buf[INT32_C(0)] = ((yy__note_data[INT32_C(9)] + UINT8_C(1)) + yy__s->yy__note_buf[yy__note_pos].e3);
        if (yy__cursor)
        {
            yy__w4_set_draw_colors(UINT16_C(65));
        }
        else
        {
            yy__w4_set_draw_colors(UINT16_C(20));
        }
        yy__w4_text_u8(((uint8_t const * const )yy__s->yy__text_buf), (yy__x + yy__x_delta), yy__y);
    }
    return;
}
void yy__draw_notes(struct yy__State* yy__s) 
{
    if (yy__s->yy__note_count == INT32_C(0))
    {
        return;
    }
    if (yy__s->yy__cursor < yy__s->yy__v_start)
    {
        yy__s->yy__v_start = yy__s->yy__cursor;
        yy__s->yy__v_end = (yy__s->yy__v_start + yy__NOTE_WRAP_AROUND);
    }
    else
    {
        if (yy__s->yy__cursor > yy__s->yy__v_end)
        {
            yy__s->yy__v_end = yy__s->yy__cursor;
            yy__s->yy__v_start = (yy__s->yy__v_end - yy__NOTE_WRAP_AROUND);
        }
        else
        {
            yy__s->yy__v_end = (yy__s->yy__v_start + yy__NOTE_WRAP_AROUND);
        }
    }
    if (yy__s->yy__v_start < INT32_C(0))
    {
        yy__s->yy__v_start = INT32_C(0);
    }
    if (yy__s->yy__v_end > (yy__s->yy__note_count - INT32_C(1)))
    {
        yy__s->yy__v_end = (yy__s->yy__note_count - INT32_C(1));
    }
    int32_t yy__x = yy__s->yy__v_start;
    int32_t yy__grid_pos = INT32_C(0);
    while (true)
    {
        if (!((((yy__x < yy__s->yy__note_count) && (yy__x <= yy__s->yy__v_end)))))
        {
            break;
        }
        bool yy__current = (yy__x == yy__s->yy__cursor);
        if (yy__s->yy__playing)
        {
            int32_t yy__prev = (yy__x - INT32_C(1));
            if (yy__prev < INT32_C(0))
            {
                yy__prev = (yy__s->yy__note_count - INT32_C(1));
            }
            yy__current = (yy__prev == yy__s->yy__cursor);
        }
        yy__draw_note(yy__s, yy__grid_pos, yy__x, yy__current);
        yy__x += INT32_C(1);
        yy__grid_pos += INT32_C(1);
    }
    return;
}
void yy__play_notes(struct yy__State* yy__s) 
{
    if (!(yy__s->yy__playing))
    {
        return;
    }
    if (yy__s->yy__play_on > yy__s->yy__frame_count)
    {
        return;
    }
    uint8_t yy__time = yy__s->yy__note_buf[yy__s->yy__cursor].e1;
    uint8_t yy__note = yy__s->yy__note_buf[yy__s->yy__cursor].e2;
    uint8_t yy__octv = yy__s->yy__note_buf[yy__s->yy__cursor].e3;
    uint8_t yy__actual_note = ((yy__octv * UINT8_C(12)) + yy__note);
    uint32_t yy__note_time = ((uint32_t)yy__s->yy__note_time[yy__time]);
    yy__s->yy__play_on = (yy__s->yy__frame_count + ((uint64_t)yy__note_time));
    if (yy__note != yy__NOTE_REST)
    {
        uint32_t yy__note_freq = ((uint32_t)yy__s->yy__note_freq[yy__actual_note]);
        yy__w4_tone(yy__note_freq, yy__note_time, UINT32_C(50), UINT32_C(0));
    }
    yy__s->yy__cursor += INT32_C(1);
    if (yy__s->yy__cursor > (yy__s->yy__note_count - INT32_C(1)))
    {
        yy__s->yy__cursor = INT32_C(0);
    }
    return;
}
void yy__game_step(void* yy__d) 
{
    struct yy__State* yy__s = ((struct yy__State*)yy__d);
    yy__s->yy__frame_count += UINT64_C(1);
    yy__handle_input(yy__s);
    yy__draw_board(yy__s);
    yy__draw_notes(yy__s);
    yy__play_notes(yy__s);
    return;
}
struct yy__State* yy__init_state() 
{
    struct yy__State* yy__s = calloc(1, sizeof(struct yy__State));
    yy__s->yy__width = INT32_C(160);
    yy__s->yy__height = INT32_C(160);
    yy__s->yy__frame_count = UINT64_C(0);
    yy__s->yy__play_on = UINT64_C(0);
    yy__s->yy__gamepad_prev = UINT8_C(0);
    yy__s->yy__cursor = INT32_C(0);
    yy__s->yy__note_count = INT32_C(0);
    yy__s->yy__v_start = INT32_C(0);
    yy__s->yy__v_end = INT32_C(0);
    yy__s->yy__mode = yy__MODE_NOTE;
    yy__s->yy__playing = false;
    int32_t* t__0 = NULL;
    yk__arrsetcap(t__0, 37);
    yk__arrput(t__0, INT32_C(0));
    yk__arrput(t__0, INT32_C(262));
    yk__arrput(t__0, INT32_C(277));
    yk__arrput(t__0, INT32_C(294));
    yk__arrput(t__0, INT32_C(311));
    yk__arrput(t__0, INT32_C(330));
    yk__arrput(t__0, INT32_C(349));
    yk__arrput(t__0, INT32_C(370));
    yk__arrput(t__0, INT32_C(392));
    yk__arrput(t__0, INT32_C(415));
    yk__arrput(t__0, INT32_C(440));
    yk__arrput(t__0, INT32_C(466));
    yk__arrput(t__0, INT32_C(495));
    yk__arrput(t__0, INT32_C(523));
    yk__arrput(t__0, INT32_C(554));
    yk__arrput(t__0, INT32_C(587));
    yk__arrput(t__0, INT32_C(622));
    yk__arrput(t__0, INT32_C(659));
    yk__arrput(t__0, INT32_C(698));
    yk__arrput(t__0, INT32_C(740));
    yk__arrput(t__0, INT32_C(784));
    yk__arrput(t__0, INT32_C(830));
    yk__arrput(t__0, INT32_C(880));
    yk__arrput(t__0, INT32_C(932));
    yk__arrput(t__0, INT32_C(988));
    yk__arrput(t__0, INT32_C(1047));
    yk__arrput(t__0, INT32_C(1109));
    yk__arrput(t__0, INT32_C(1175));
    yk__arrput(t__0, INT32_C(1245));
    yk__arrput(t__0, INT32_C(1319));
    yk__arrput(t__0, INT32_C(1397));
    yk__arrput(t__0, INT32_C(1480));
    yk__arrput(t__0, INT32_C(1568));
    yk__arrput(t__0, INT32_C(1661));
    yk__arrput(t__0, INT32_C(1760));
    yk__arrput(t__0, INT32_C(1865));
    yk__arrput(t__0, INT32_C(1976));
    yy__s->yy__note_freq = t__0;
    int32_t* t__1 = NULL;
    yk__arrsetcap(t__1, 7);
    yk__arrput(t__1, INT32_C(60));
    yk__arrput(t__1, INT32_C(30));
    yk__arrput(t__1, INT32_C(15));
    yk__arrput(t__1, INT32_C(8));
    yk__arrput(t__1, INT32_C(4));
    yk__arrput(t__1, INT32_C(2));
    yk__arrput(t__1, INT32_C(1));
    yy__s->yy__note_time = t__1;
    yy__s->yy__text_buf = ((uint8_t*)yy__c_calloc(((yy__c_Size)INT32_C(1)), ((yy__c_Size)INT32_C(11))));
    yk__arrsetlen(yy__s->yy__note_buf, yy__MAX_NOTES);
    int32_t yy__x = INT32_C(0);
    while (true)
    {
        if (!(yy__x < yy__MAX_NOTES))
        {
            break;
        }
        yy__s->yy__note_buf[yy__x].e1 = yy__NOTE_NULL;
        yy__s->yy__note_buf[yy__x].e2 = yy__NOTE_NULL;
        yy__s->yy__note_buf[yy__x].e3 = yy__NOTE_NULL;
        yy__s->yy__note_buf[yy__x].e4 = yy__NOTE_NULL;
        yy__x += INT32_C(1);
    }
    struct yy__State* t__2 = yy__s;
    return t__2;
}
void yy__del_state(void* yy__current) 
{
    free(yy__current);
    return;
}
int32_t yy__main() 
{
    yy__w4_set_palette(UINT32_C(16774776), UINT32_C(2073791), UINT32_C(14307260), UINT32_C(1776476));
    struct yy__State* yy__s = yy__init_state();
    yy__w4_set_game_state(yy__s);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif