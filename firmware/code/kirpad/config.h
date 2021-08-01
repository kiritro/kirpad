/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEFE
#define PRODUCT_ID      0x2333
#define DEVICE_VER      0x0001
#define MANUFACTURER    KIRITRO
#define PRODUCT         NP_01
#define DESCRIPTION     QMK NUM PAD 

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 5

// ROWS: Top to bottom, COLS: Left to right

#define MATRIX_ROW_PINS { B2, B7, F4, F6, F7 }
#define MATRIX_COL_PINS { F5, E6, B0, B1, B3 }
#define UNUSED_PINS


/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define COMBO_COUNT 5

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* ws2812 RGB LED */
#define RGB_DI_PIN D4
#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
// #define RGBLIGHT_EFFECT_BREATHING
// #define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_SLEEP
#define RGBLED_NUM 27   
#define RGBLIGHT_LIMIT_VAL 128
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif

/* use 12864 oled*/
#define OLED_DISPLAY_128X64
#define OLED_FONT_END   127
#define OLED_BRIGHTNESS 127
#define OLED_FONT_H "gfxfont.c"

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT





