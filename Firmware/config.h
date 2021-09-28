#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6969
#define DEVICE_VER      0x0001
#define MANUFACTURER    Cipulot
#define PRODUCT         SheepyPad
#define DESCRIPTION     ISO Enter Shaped Macropad w/ OLED

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 5

/* key matrix pins */
#define MATRIX_ROW_PINS { C6, F7, B5, B4, E6, D7 }
#define MATRIX_COL_PINS { D4, B1, B3, B2, B6 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW


/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5

/* ENCODER THINGS */
// #define ENCODER_DIRECTION_FLIP
// #define ENCODER_RESOLUTION
#define ENCODERS_PAD_A { D1 }
#define ENCODERS_PAD_B { D0 }

#define RGB_DI_PIN F6
#define RGBLED_NUM 6
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */

// #define RGBLIGHT_ANIMATIONS

#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_STATIC_GRADIENT

#define OLED_DISPLAY_128X32

#define DYNAMIC_KEYMAP_LAYER_COUNT 3