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

enum  custom_layers { _MACRO = 0, _CALC, _ADJ };
enum  custom_keycodes { TOGG, CALC_0, CALC_1, CALC_2, CALC_3, CALC_4, CALC_5, CALC_6, CALC_7, CALC_8, CALC_9, CALC_EQUAL, CALC_DOT, CALC_PLUS, CALC_MINUS, CALC_MULT, CALC_DIV, CALC_AC, CALC_C, CALC_SQRT};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_MACRO] = LAYOUT(
		KC_MPLY,  TOGG,  CALC_SQRT,  KC_C,  CALC_AC,
		          KC_E,  KC_F,       KC_G,  KC_H,
		          KC_I,  KC_J,       KC_K,  KC_L,
		          KC_M,  KC_N,       KC_O,  KC_P,
		          KC_Q,  KC_R,       KC_S,  KC_T
	),

	[_CALC] = LAYOUT(
		KC_MPLY,  TOGG,    CALC_SQRT,  KC_C,        CALC_AC,
				  CALC_7,  CALC_8,     CALC_9,      CALC_DIV,
				  CALC_4,  CALC_5,     CALC_6,      CALC_MULT,
				  CALC_1,  CALC_2,     CALC_3,      CALC_MINUS,
				  CALC_0,  CALC_DOT,   CALC_EQUAL,  CALC_PLUS
	),

	[_ADJ] = LAYOUT(
		KC_MPLY,  TOGG,  CALC_SQRT,  KC_C,  CALC_AC,
				  KC_E,  KC_F,       KC_G,  KC_H,
				  KC_I,  KC_J,       KC_K,  KC_L,
				  KC_M,  KC_N,       KC_O,  KC_P,
				  KC_Q,  KC_R,       KC_S,  KC_T
	)
};

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise)
{
	if (clockwise)
	{
		tap_code(KC_VOLD);
	}
	else
	{
		tap_code(KC_VOLU);
	}
	return false;
}
#endif

#ifdef OLED_ENABLE
void oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _MACRO:
            oled_write_P(PSTR("Macro\n"), false);
            break;
        case _CALC:
            oled_write_P(PSTR("Calculator\n"), false);
            break;
        case _ADJ:
            oled_write_P(PSTR("ADJ\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
}
#endif