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

enum custom_layers { _MACRO = 0, _CALC, _ADJ };
enum  custom_keycodes { CALC_0 = SAFE_RANGE, CALC_1, CALC_2, CALC_3, CALC_4, CALC_5, CALC_6, CALC_7, CALC_8, CALC_9, CALC_EQUAL, CALC_DOT, CALC_PLUS, CALC_MINUS, CALC_MULT, CALC_DIV, CALC_AC, CALC_C, CALC_SQRT};

#define SPECIAL LT(0, KC_NO)

uint16_t startup_timer;
bool finished_logo = false;
bool clear_logo = true;

float term_1 = 0;
float term_2 = 0;
float res = 0;
uint8_t operator = 0;
bool term_1_ok = false;
bool calc_finished = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_MACRO] = LAYOUT(
		KC_MPLY,    /* 			LEAVE EMPTY			   */
		/* L  E */  SPECIAL,	KC_CALC,  KC_MPRV,  KC_MNXT,
		/* E  M */	KC_E,	KC_F,     KC_G,		KC_H,
		/* A  P */	KC_I,  	KC_J,     KC_K,		KC_L,
		/* V  T */	KC_M,	KC_N,     KC_O,		KC_P,
		/* E  Y */	KC_Q,	KC_R,     KC_S,		KC_T
	),

	[_CALC] = LAYOUT(
		KC_MPLY,	/* 				LEAVE EMPTY			   		*/
		/* L  E */	_______,   	CALC_SQRT,  KC_C,        CALC_AC,
		/* E  M */	CALC_7, 	CALC_8,     CALC_9,      CALC_DIV,
        /* A  P */	CALC_4, 	CALC_5,     CALC_6,      CALC_MULT,
        /* V  T */	CALC_1, 	CALC_2,     CALC_3,      CALC_MINUS,
        /* E  Y */	CALC_0,		CALC_DOT,   CALC_EQUAL,  CALC_PLUS
	),

	[_ADJ] = LAYOUT(
		KC_MPLY,	/* 				LEAVE EMPTY			   		*/
		/* L  E */	_______,     	RGB_TOG,  	RGB_M_G,  	RGB_M_SW,
        /* E  M */	RGB_HUI,  	RGB_HUD,  	RGB_SAI,  	RGB_SAD,
        /* A  P */	RGB_VAI,  	RGB_VAD,  	RGB_SPI,  	RGB_SPD,
        /* V  T */	xxx,      	xxx,      	xxx,      	xxx,
        /* E  Y */	RESET,    	xxx,      	xxx,      	EEP_RST
	)
};

void keyboard_post_init_user(void) {
#ifdef OLED_ENABLE
    oled_clear();
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
                if (layer_state_is(_CALC)) {
                    oled_clear();
                    layer_off(_CALC);
                } else {
                    oled_clear();
                    layer_on(_CALC);
                }
            } else if (record->event.pressed) {
                layer_on(_ADJ);
            } else {
                layer_off(_ADJ);
            }
            return false;
            break;

        case CALC_SQRT:
            if (record->event.pressed) {
                if ((term_1_ok) && (!calc_finished) && (operator== 0)) {
                    if (term_1 <= 0) {
                    } else {
                        res = sqrt(term_1);
                    }
                    calc_finished = true;
                } else if (!calc_finished) {
                    calc_finished = true;
                }
            }
            return false;
            break;

        case CALC_AC:
            if (record->event.pressed) {
                term_1  = 0;
                term_2  = 0;
                res     = 0;
                operator= 0;
                // clear display and reset cursor putting a zero in the first position
                term_1_ok     = false;
                calc_finished = false;
                oled_clear();
            }
            return false;
            break;

        case CALC_PLUS:
            if (record->event.pressed) {
                if (!calc_finished) {
                    operator  = 1;
                    term_1_ok = true;
                }
            }
            return false;
            break;

        case CALC_MINUS:
            if (record->event.pressed) {
                if (!calc_finished) {
                    operator  = 2;
                    term_1_ok = true;
                }
            }
            return false;
            break;

        case CALC_MULT:
            if (record->event.pressed) {
                if (!calc_finished) {
                    operator= 3;
                }
            }
            return false;
            break;

        case CALC_DIV:
            if (record->event.pressed) {
                operator= 4;
            }
            return false;
            break;

        case CALC_EQUAL:
            if (record->event.pressed) {
                if ((term_1_ok) && (!calc_finished) && (operator!= 0)) {
                    switch (operator) {
                        case 1:
                            res = term_1 + term_2;
                            break;
                        case 2:
                            res = term_1 - term_2;
                            break;
                        case 3:
                            res = term_1 * term_2;
                            break;
                        case 4:
                            if ((term_1 == 0) || (term_2 == 0)) {
                                res = 0;
                            } else if (term_2 != 0) {
                                res = term_1 / term_2;
                            }
                            break;
                        default:
                            break;
                    }
                    calc_finished = true;
                } else if (!calc_finished) {
                    calc_finished = true;
                }
            }
            return false;
            break;
    }
    return true;
}
/*
layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t layer = get_highest_layer(state);

    switch (layer) {
		case _CALC:
#ifdef OLED_ENABLE
			//stuff
#endif
			return false;
			break;
		default:
			break;
	}
	return state;
}
*/
#ifdef ENCODER_ENABLE
    bool encoder_update_user(uint8_t index, bool clockwise) {
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
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
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }
}

void oled_task_user(void) {
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