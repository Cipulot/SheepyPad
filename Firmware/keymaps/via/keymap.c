/* Copyright 2021 Cipulot
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "timer.h"
#include "calc.h"

enum custom_layers {_NUMPAD = 0, _MACRO, _CALC, _ADJ };
enum  custom_keycodes { CALC_0 = SAFE_RANGE, CALC_1, CALC_2, CALC_3, CALC_4, CALC_5, CALC_6, CALC_7, CALC_8, CALC_9, CALC_EQUAL, CALC_DOT, CALC_PLUS, CALC_MINUS, CALC_MULT, CALC_DIV, CALC_AC, CALC_POSNEG, CALC_SQRT};

#define SPECIAL LT(0, KC_NO)

uint16_t startup_timer;
bool finished_logo = false;
bool clear_logo = true;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_NUMPAD] = LAYOUT(
		KC_MPLY,    /* 			LEAVE EMPTY			   */
		/* L  E */  SPECIAL,	KC_LBRC,  KC_RBRC,  KC_PSLS,
		/* E  M */	KC_PENT,	S(KC_9),  S(KC_0),	KC_PAST,
		/* A  P */	KC_P7,      KC_P8,    KC_P9,	KC_PMNS,
		/* V  T */	KC_P4,	    KC_P5,    KC_P6,	KC_PPLS,
		/* E  Y */	KC_P1,	    KC_P2,    KC_P3,	KC_P0
	),

    [_MACRO] = LAYOUT(
		KC_MPLY,    /* 			LEAVE EMPTY			   */
		/* L  E */  _______,	_______,  _______,  _______,
		/* E  M */	_______,	_______,  _______,	_______,
		/* A  P */	_______,    _______,  _______,	_______,
		/* V  T */	_______,	_______,  _______,	_______,
		/* E  Y */	_______,	_______,  _______,	_______
	),

	[_CALC] = LAYOUT(
		KC_MPLY,	/* 				LEAVE EMPTY			   		*/
		/* L  E */	_______,   	CALC_SQRT,  CALC_POSNEG, CALC_AC,
		/* E  M */	CALC_7, 	CALC_8,     CALC_9,      CALC_DIV,
        /* A  P */	CALC_4, 	CALC_5,     CALC_6,      CALC_MULT,
        /* V  T */	CALC_1, 	CALC_2,     CALC_3,      CALC_MINUS,
        /* E  Y */	CALC_0,		CALC_DOT,   CALC_EQUAL,  CALC_PLUS
	),

	[_ADJ] = LAYOUT(
		KC_MPLY,	/* 				LEAVE EMPTY			   		*/
		/* L  E */	_______,    RGB_TOG,  	RGB_M_G,  	RGB_M_SW,
        /* E  M */	RGB_HUI,  	RGB_HUD,  	RGB_SAI,  	RGB_SAD,
        /* A  P */	RGB_VAI,  	RGB_VAD,  	RGB_SPI,  	RGB_SPD,
        /* V  T */	xxx,      	xxx,      	xxx,      	xxx,
        /* E  Y */	RESET,    	xxx,      	xxx,      	EEP_RST
	)
};

void keyboard_post_init_user(void) {
#ifdef OLED_ENABLE
    oled_clear();
    clear_calc_vars();
#endif
}

void suspend_power_down_user(void) {
#ifdef OLED_ENABLE
    oled_clear();
#endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SPECIAL:
            if (record->tap.count && record->event.pressed) {
                if (layer_state_is(_NUMPAD)) {
                    layer_off(_NUMPAD);
                    layer_on(_MACRO);
                } else if (layer_state_is(_MACRO)) {
                    layer_off(_MACRO);
                    clear_calc_vars();
                    oled_clear();
                    layer_on(_CALC);
                } else if (layer_state_is(_CALC)) {
                    oled_clear();
                    layer_off(_CALC);
                    layer_on(_NUMPAD);
                }
            } else if (record->event.pressed) {
                clear_calc_vars();
                oled_clear();
                layer_on(_ADJ);
            } else {
                layer_off(_ADJ);
            }
            return false;
            break;

        case CALC_0:
            if (record->event.pressed) {
                digit_handling(0);
            }
            return false;
            break;

        case CALC_1:
            if (record->event.pressed) {
                digit_handling(1);
            }
            return false;
            break;

        case CALC_2:
            if (record->event.pressed) {
                digit_handling(2);
            }
            return false;
            break;

        case CALC_3:
            if (record->event.pressed) {
                digit_handling(3);
            }
            return false;
            break;

        case CALC_4:
            if (record->event.pressed) {
                digit_handling(4);
            }
            return false;
            break;

        case CALC_5:
            if (record->event.pressed) {
                digit_handling(5);
            }
            return false;
            break;

        case CALC_6:
            if (record->event.pressed) {
                digit_handling(6);
            }
            return false;
            break;

        case CALC_7:
            if (record->event.pressed) {
                digit_handling(7);
            }
            return false;
            break;

        case CALC_8:
            if (record->event.pressed) {
                digit_handling(8);
            }
            return false;
            break;

        case CALC_9:
            if (record->event.pressed) {
                digit_handling(9);
            }
            return false;
            break;

        case CALC_SQRT:
            if (record->event.pressed) {
                root_op();
            }
            return false;
            break;

        case CALC_AC:
            if (record->event.pressed) {
                clear_calc_vars();
                oled_clear();
            }
            return false;
            break;

        case CALC_POSNEG:
            if (record->event.pressed) {
                neg_num_op();
            }
            return false;
            break;

        case CALC_PLUS:
            if (record->event.pressed) {
                if (!calc_finished) {
                    operator  = 1;
                    term_1_ok = true;
                    oled_set_cursor(0, 3);
                    oled_write_P(PSTR("+\n"), false);
                }
            }
            return false;
            break;

        case CALC_MINUS:
            if (record->event.pressed) {
                if (!calc_finished) {
                    operator  = 2;
                    term_1_ok = true;
                    oled_set_cursor(0, 3);
                    oled_write_P(PSTR("-\n"), false);
                }
            }
            return false;
            break;

        case CALC_MULT:
            if (record->event.pressed) {
                if (!calc_finished) {
                    operator  = 3;
                    term_1_ok = true;
                    oled_set_cursor(0, 3);
                    oled_write_P(PSTR("*\n"), false);
                }
            }
            return false;
            break;

        case CALC_DIV:
            if (record->event.pressed) {
                if (!calc_finished) {
                    operator  = 4;
                    term_1_ok = true;
                    oled_set_cursor(0, 3);
                    oled_write_P(PSTR("/\n"), false);
                }
            }
            return false;
            break;

        case CALC_EQUAL:
            if (record->event.pressed) {
                equal_op();
            }
            return false;
            break;
    }
    return true;
}

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
    return false;
}
#endif

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    startup_timer = timer_read();
    return rotation;
}

static void render_logo(void) {
    static const char PROGMEM my_logo[] = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xbf, 0xdf, 0xe7, 0xe7,
		0x67, 0x37, 0xdb, 0xcb, 0x0b, 0x0b, 0x0b, 0xcb, 0xcf, 0xed, 0xf5, 0xf5, 0xf5, 0xf5, 0xf5, 0xf5,
		0xf5, 0xf5, 0xf5, 0xf5, 0xfb, 0xfb, 0x8b, 0x0d, 0x05, 0xc5, 0x45, 0x45, 0x65, 0xbd, 0xc3, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe3, 0xe6, 0xc7, 0xcf, 0xdf,
		0xfe, 0xfe, 0xfd, 0xba, 0x8a, 0xc2, 0x00, 0xff, 0xf3, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xf9, 0xf1, 0xfb, 0xf8, 0x04, 0x0e, 0xfe, 0xfe, 0x31, 0x87, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbf, 0xdf, 0xcf, 0xcf, 0xff,
		0xfd, 0xf8, 0xf1, 0xf3, 0xf3, 0xff, 0xff, 0xf0, 0x67, 0x0f, 0x3f, 0x7f, 0xff, 0xff, 0xaf, 0x6f,
		0x4f, 0x0f, 0x0f, 0x4f, 0x6f, 0xbf, 0x1f, 0xc1, 0xcc, 0xfe, 0x3f, 0x1f, 0x9e, 0xe1, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xef, 0xcf,
		0xcf, 0xdf, 0xdf, 0xdf, 0xd9, 0xf9, 0xf8, 0xf8, 0xec, 0xee, 0xdf, 0xdf, 0xfe, 0xfc, 0xdd, 0xd9,
		0xd9, 0xd9, 0xd9, 0xd9, 0xc1, 0xee, 0xff, 0xff, 0xff, 0xcf, 0x0e, 0x06, 0xe1, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    oled_write_raw_P(my_logo, sizeof(my_logo));
}

static void render_led(void) {
    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
}

static void render_status(void) {
    // Host Keyboard Layer Status

    switch (get_highest_layer(layer_state)) {
        case _NUMPAD:
            oled_write_P(PSTR("Layer: "), false);
            oled_write_P(PSTR("Numpad\n"), false);
            render_led();
            break;

        case _MACRO:
            oled_write_P(PSTR("Layer: "), false);
            oled_write_P(PSTR("Macro\n"), false);
            render_led();
            break;

        case _CALC:
            oled_write_P(PSTR(" ---- Calculator ----\n"), false);
            // Insert here calc display function
            break;

        case _ADJ:
            oled_write_P(PSTR("Layer: "), false);
            oled_write_P(PSTR("ADJ\n"), false);
            render_led();
            break;
        default:
            oled_write_P(PSTR("Layer: "), false);
            oled_write_ln_P(PSTR("Undefined"), false);
    }
}

void oled_task_user(void) {
    // Change 3000 with the time (in ms) that you want the logo to be displayed
    if ((timer_elapsed(startup_timer) < 3000) && !(finished_logo)) {
        render_logo();
    } else {
        finished_logo = true;
        if (clear_logo) {
            oled_clear();
            clear_logo = false;
        }
        render_status();
    }
}
#endif