/*
Copyright 2021 0xCB - Conor Burns

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H
#include "common.h"

// 组合键区定义 SK1+SK2->NEXT_LAYER  S1+S3->RESET
#define LHM_SK1 KC_NLCK
#define LHM_SK2 KC_LSFT
#define LHM_SK3 KC_CALC

#define LF2_SK1 KC_1
#define LF2_SK2 KC_2

#define LF3_SK1 KC_PSCR
#define LF3_SK2 KC_INS

#define LF4_SK1 KC_F1
#define LF4_SK2 KC_F2

//按键名显示

uint8_t oled_layer_name_map[6][4] =
{
    "HOME", "GAME", "SPEC", "RGB ", "NUML", "    "
};

uint8_t oled_key_name_map[4][22][3] =
{
    {"NUM", "SFT", "CLC", "BSC", "7|&", "8|*", "9|(", "4|$", "5|%", "6|^", "1|!", "2|@", "3|#", " + ", "ENT", "0|)", " . ", " * ", " - ", " / ", "VUP", "VDN"},
    {" 1 ", " 2 ", " 3 ", "MUT", " 4 ", " 5 ", " 6 ", " Q ", " W ", " E ", " A ", " S ", " D ", "TAB", "ENT", " Z ", " X ", " C ", "SPC", "SFT", "VUP", "VDN"},
    {"PSC", "INS", "DEL", "CAP", "F1 ", "F2 ", "F3 ", "F4 ", "F5 ", "F6 ", "F7 ", "F8 ", "F9 ", " + ", "ENT", "F10", "F11", "F12", " - ", " / ", "UP ", "DN "},
    {"F1 ", "F2 ", "O/F", "O/F", "HUI", "SAI", "VAI", "HUD", "SAD", "VAD", "MDP", "MDB", "MDR", "NDF", "MDU", "NDF", "NDF", "NDF", "NDF", "MDD", "MDU", "MDD"}
};

//按键显示坐标
uint8_t oled_key_addr[22][2] =
{
    {3, 14}, {23, 14}, {43, 14}, {63, 14}, \
    {3, 24}, {23, 24}, {43, 24}, \
    {3, 34}, {23, 34}, {43, 34}, \
    {3, 44}, {23, 44}, {43, 44}, {63, 44}, {83, 44}, \
    {3, 54}, {23, 54}, {43, 54}, {63, 54}, {83, 54}, \
    {83, 14}, {83, 24}
};

// clang-format off
enum layer_names
{
    _HOME,
    _FN2,
    _FN3,
    _FN4
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] =
{

    /* Base 小键盘层
     * ,----------------------------------.
     * |  NL  |  LS  | CALC | <--- |  Vu  |
     * |------+------|------|------+------|
     * |   7  |   8  |  9/( |      |  Vd  |
     * |------+------|------|------+------|
     * |   4  |   5  |   6  |      |      |
     * |------+------|------|------+------|
     * |   1  |   2  |   3  |  +   | ENT  |
     * |------+------|------|------+------|
     * |  0/) |  .   |   *  |  -   |  /   |
     * `----------------------------------'
     */
    [_HOME] = LAYOUT( \
                      LHM_SK1,   LHM_SK2,   LHM_SK3,   KC_BSPC,   \
                      KC_7,      KC_8,      KC_9,      \
                      KC_4,      KC_5,      KC_6,      \
                      KC_1,      KC_2,      KC_3,      KC_PPLS,   KC_ENT,   \
                      KC_0,      KC_PDOT,   KC_PAST,   KC_PMNS,   KC_PSLS  \
                    ),

    /* _FN2 游戏层
     * ,----------------------------------.
     * |   1  |   2  |   3  | MUTE |  Vu  |
     * |------+------|------|------+------|
     * |   4  |   5  |   6  |      |  Vd  |
     * |------+------|------|------+------|
     * |   Q  |   W  |   E  |      |      |
     * |------+------|------|------+------|
     * |   A  |   S  |   D  | TAB  | ENT  |
     * |------+------|------|------+------|
     * |   Z  |   X  |   C  | |--| | LS   |
     * `----------------------------------'
     */
    [_FN2] = LAYOUT( \
                     LF2_SK1,  LF2_SK2,   KC_3,   KC_MUTE,  \
                     KC_4,     KC_5,      KC_6,   \
                     KC_Q,     KC_W,      KC_E,   \
                     KC_A,     KC_S,      KC_D,   KC_TAB,   KC_ENT,   \
                     KC_Z,     KC_X,      KC_C,   KC_SPC,   KC_LSFT    \
                   ),

    /* _FN3 特殊按键层
     * 、----------------------------------.
     * | PSCR |  INS |  DEL | CAPS |  UP  |
     * |------+------|------|------+------|
     * |  F1  |  F2  |  F3  |      |  DN  |
     * |------+------|------|------+------|
     * |  F4  |  F5  |  F6  |      |      |
     * |------+------|------|------+------|
     * |  F7  |  F8  |  F9  |  +   | ENT  |
     * |------+------|------|------+------|
     * |  F10 |  F11 |  F12 |  -   |  /   |
     * `----------------------------------'
     */
    [_FN3] = LAYOUT( \
                     LF3_SK1,   LF3_SK2,   KC_DEL,   KC_CAPS,   \
                     KC_F1,     KC_F2,     KC_F3,   \
                     KC_F4,     KC_F5,     KC_F6,   \
                     KC_F7,     KC_F8,     KC_F9,   KC_PGUP,   KC_BSPC,   \
                     KC_F10,    KC_F11,    KC_F12,  KC_PGDN,   KC_ENT     \
                   ),

    /* _FN4 灯光层
     * ,---------------------------------.
     * |  F1  |  F2  |  O/F |  O/F | MODU |
     * |------+------|------|------+------|
     * |  HUI |  SAI |  VAI |      | MODD |
     * |------+------|------|------+------|
     * |  HUD |  SAD |  VAD |      |      |
     * |------+------|------|------+------|
     * |  MP  |  MB  |  MR  |      | MODU |
     * |------+------|------|------+------|
     * |      |      |      |      | MODD |
     * `----------------------------------'
     */
    [_FN4] = LAYOUT( \
                     LF4_SK1,   LF4_SK2,   RGB_TOG,   RGB_TOG,   \
                     RGB_HUI,   RGB_SAI,   RGB_VAI,   \
                     RGB_HUD,   RGB_SAD,   RGB_VAD,   \
                     RGB_M_P,   RGB_M_B,   RGB_M_R,   _______,   RGB_MOD,   \
                     _______,   _______,   _______,   _______,   RGB_RMOD   \
                   ),
};


// Combos 组合键
enum combos
{
    CMB_RESET,
    CMB_LAYER_HOME,
    CMB_LAYER_FN2,
    CMB_LAYER_FN3,
    CMB_LAYER_FN4
};

const uint16_t PROGMEM combo_reset[]    =    {LHM_SK1, LHM_SK3, COMBO_END};
const uint16_t PROGMEM combo_layer_home[]  = {LF4_SK1, LF4_SK2, COMBO_END};
const uint16_t PROGMEM combo_layer_fn2[]  =  {LHM_SK1, LHM_SK2, COMBO_END};
const uint16_t PROGMEM combo_layer_fn3[]  =  {LF2_SK1, LF2_SK2, COMBO_END};
const uint16_t PROGMEM combo_layer_fn4[]  =  {LF3_SK1, LF3_SK2, COMBO_END};


combo_t key_combos[COMBO_COUNT] =
{
    [CMB_RESET]      = COMBO_ACTION(combo_reset),
    [CMB_LAYER_HOME] = COMBO_ACTION(combo_layer_home),
    [CMB_LAYER_FN2]  = COMBO_ACTION(combo_layer_fn2),
    [CMB_LAYER_FN3]  = COMBO_ACTION(combo_layer_fn3),
    [CMB_LAYER_FN4]  = COMBO_ACTION(combo_layer_fn4),
};

void process_combo_event(uint16_t combo_index, bool pressed)
{
    switch(combo_index)
    {
    case CMB_RESET:
        if (pressed)
        {
            reset_keyboard();
        }
        break;

    case CMB_LAYER_HOME:
        if (pressed)
        {
            layer_move(_HOME);
        }
        break;

    case CMB_LAYER_FN2:
        if (pressed)
        {
            layer_move(_FN2);
        }
        break;

    case CMB_LAYER_FN3:
        if (pressed)
        {
            layer_move(_FN3);
        }
        break;

    case CMB_LAYER_FN4:
        if (pressed)
        {
            layer_move(_FN4);
        }
        break;
    }
}


// /*layer switcher */
// layer_state_t layer_state_set_user(layer_state_t state) {
// state = update_tri_layer_state(state, _FN2, _FN3, _FN4);
// return state;
// }

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise)
{
    if (IS_LAYER_ON(_FN4))
    {
        if (clockwise)
        {
            rgblight_step();
        }
        else
        {
            rgblight_step_reverse();
        }
    }
    else if (IS_LAYER_ON(_FN3))
    {
        if (clockwise)
        {
            tap_code(KC_UP);
        }
        else
        {
            tap_code(KC_DOWN);
        }
    }
    else if (IS_LAYER_ON(_FN2))
    {
        if (clockwise)
        {
            tap_code(KC_VOLU);
        }
        else
        {
            tap_code(KC_VOLD);
        }
    }
    else if (IS_LAYER_ON(_HOME))
    {
        if (clockwise)
        {
            tap_code(KC_VOLU);
        }
        else
        {
            tap_code(KC_VOLD);
        }
    }
    return true;
}
#endif

/* oled stuff :) */
#ifdef OLED_DRIVER_ENABLE
uint16_t startup_timer;

oled_rotation_t oled_init_user(oled_rotation_t rotation)
{
    startup_timer = timer_read();
    return rotation;
}

static void render_logo(void)
{
    static const uint8_t raw_logo[] =
    {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF0, 0xF0, 0xF8, 0xF8, 0xF8, 0xF8,
        0xF8, 0xF8, 0xF8, 0xF8, 0xF0, 0xF0, 0xF0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0xF0, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x9F,
        0x9F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xF0, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x0F, 0x71, 0xC1, 0x81, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x06, 0x0C, 0x09,
        0x09, 0x0C, 0x06, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x81, 0xC1, 0x71, 0x0F, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x06, 0x0C, 0x08, 0x08, 0x10, 0x10, 0x10, 0x10,
        0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x0C, 0x06, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };
    oled_draw_bitmap(raw_logo, 48, 16, 32, 32, false);

    //oled_draw_rectangle(0, 0, 127, 63);
}

static void render_frame_init(void)
{
    //外框
    oled_draw_rectangle(0, 0, 127, 63, false);
    oled_draw_rectangle(1, 1, 126, 62, false);
    //横线
    oled_draw_line(2, 11, 125, 11, false);
    oled_draw_line(2, 12, 125, 12, false);
    oled_draw_line(2, 22, 125, 22, false);
    oled_draw_line(2, 32, 125, 32, false);
    oled_draw_line(2, 42, 125, 42, false);
    oled_draw_line(2, 52, 125, 52, false);
    //竖线
    oled_draw_line(21, 13, 21, 61, false);
    oled_draw_line(41, 13, 41, 61, false);
    oled_draw_line(61, 13, 61, 61, false);
    oled_draw_line(81, 13, 81, 61, false);
    oled_draw_line(101, 13, 101, 61, false);
    oled_draw_line(102, 13, 102, 61, false);


    // uint8_t aa[4] = {'N','N','N','F'};
    // oled_draw_string(3,14,aa,3,false);

}

void draw_key_map(uint8_t num)
{
    for(int i = 0; i < 22; i++)
    {
        oled_draw_string(oled_key_addr[i][0], oled_key_addr[i][1], oled_key_name_map[num][i], 3, false);
    }
}

int8_t layer_old = -1;
int8_t numl_old = -1;
/* Shows the name of the current layer and locks for the host (CAPS etc.) */
static void render_info(void)
{
    uint8_t layer = get_highest_layer(layer_state);
    if(layer != layer_old)
    {
        switch (layer)
        {
        case _HOME:
            oled_draw_string(3, 3, oled_layer_name_map[0], 4, false);
            draw_key_map(_HOME);
            break;
        case _FN2:
            oled_draw_string(3, 3, oled_layer_name_map[1], 4, false);
            draw_key_map(_FN2);
            break;
        case _FN3:
            oled_draw_string(3, 3, oled_layer_name_map[2], 4, false);
            draw_key_map(_FN3);
            break;
        case _FN4:
            oled_draw_string(3, 3, oled_layer_name_map[3], 4, false);
            draw_key_map(_FN4);
            break;
        default:
            oled_draw_string(3, 3, oled_layer_name_map[5], 4, false);
            break;
        }
        layer_old = layer;
    }

    led_t led_state = host_keyboard_led_state();
    if(numl_old != led_state.num_lock)
    {
        if(led_state.num_lock)
        {
            oled_draw_string(102, 3, oled_layer_name_map[4], 4, true);
            oled_draw_rectangle(101, 2, 125, 10, false);
        }
        else
        {
            oled_draw_string(102, 3, oled_layer_name_map[4], 4, false);
            oled_draw_rectangle(101, 2, 125, 10, true);
        }
    }
    numl_old = led_state.num_lock;
}

#ifdef RGBLIGHT_ENABLE
int8_t mode_o = -1, hue_o = -1, sat_o = -1, val_o = -1, enable_o = -1;
static void render_rgbled_status(bool full)
{
    if(enable_o != rgblight_is_enabled())
    {
        if (RGBLIGHT_MODES > 1 && rgblight_is_enabled())
        {
            oled_draw_string(106, 14, oled_layer_name_map[3], 3, true);
            oled_draw_rectangle(105, 13, 123, 21, false);
        }
        else
        {
            oled_draw_string(106, 14, oled_layer_name_map[3], 3, false);
            oled_draw_rectangle(105, 13, 123, 21, true);
        }
    }
    enable_o = rgblight_is_enabled();

    if(full)
    {
        int8_t mode = -2, hue = -2, sat = -2, val = -2;
        mode = rgblight_get_mode();
        hue = rgblight_get_hue() / RGBLIGHT_HUE_STEP;
        sat = rgblight_get_sat() / RGBLIGHT_SAT_STEP;
        val = rgblight_get_val() / RGBLIGHT_VAL_STEP;

        if(mode_o != mode)
        {
            oled_draw_string(109, 24, oled_layer_name_map[5], 2, false);
            oled_draw_num(109, 24, mode, false);
        }

        if(hue_o != hue)
        {
            oled_draw_string(109, 34, oled_layer_name_map[5], 2, false);
            oled_draw_num(109, 34, hue, false);
        }

        if(sat_o != sat)
        {
            oled_draw_string(109, 44, oled_layer_name_map[5], 2, false);
            oled_draw_num(109, 44, sat, false);
        }

        if(val_o != val)
        {
            oled_draw_string(109, 54, oled_layer_name_map[5], 2, false);
            oled_draw_num(109, 54, val, false);
        }

        mode_o = mode;
        hue_o = hue;
        sat_o = sat;
        val_o = val;
    }
    else
    {
        int8_t mode = -1;
        mode = rgblight_get_mode();

        if(mode_o != mode)
        {
            oled_draw_string(109, 24, oled_layer_name_map[5], 2, false);
            oled_draw_num(109, 24, mode, false);
        }

        mode_o = mode;
    }
}
#endif

void oled_task_user(void)
{
    static bool finished_timer = false;
    if (!finished_timer && (timer_elapsed(startup_timer) < 3000))
    {
        render_logo();
    }
    else
    {
        if (!finished_timer)
        {
            oled_clear();
            finished_timer = true;
            render_frame_init();
        }
        render_info();
#ifdef RGBLIGHT_ENABLE
        render_rgbled_status(true);
#endif
    }
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    // uint8_t col = record->event.key.col;
    // uint8_t row = record->event.key.row;

    // if (record->event.pressed)
    // {
    //     char name[MAX_SWITCH_NAME_LENGTH];
    //     switch_name(switches[row][col], name);
    //     send_string(name);
    //     SEND_STRING("\n");
    // }
    return true;
}

// /* Resets via on eep reset - thank you drashna! */
// void eeconfig_init_kb(void) {
//     via_eeprom_set_valid(false);
//     via_init();
//     eeconfig_init_user();
// }
