#include QMK_KEYBOARD_H

#include "calc.h"
#include "math.h"
#include "string.h"

float   term_1 = 0;
float   term_2 = 0;
float   res    = 0;
char    str_temp[20];
uint8_t operator      = 0;
bool    term_1_ok     = false;
bool    calc_finished = false;

static const double rounders[MAX_PRECISION + 1] = {
    0.5,      // 0
    0.05,     // 1
    0.005,    // 2
    0.0005,   // 3
    0.00005,  // 4
    0.000005  // 5
};

float concatenate(float x, int y) {
    int pow = 10;
    while (y >= pow) pow *= 10;
    // subtract if original number is negative
    if (x < 0) return x * pow - y;
    // add id original number is positive
    return x * pow + y;
}

// Library-less implementation of Float-to-String
char *ftoa(double f, char *buf, int precision) {
    char *ptr = buf;
    char *p   = ptr;
    char *p1;
    char  c;
    long  intPart;

    // check precision bounds
    if (precision > MAX_PRECISION) precision = MAX_PRECISION;

    // sign stuff
    if (f < 0) {
        f      = -f;
        *ptr++ = '-';
    }

    if (precision < 0)  // negative precision == automatic precision guess
    {
        if (f < 1.0)
            precision = 6;
        else if (f < 10.0)
            precision = 5;
        else if (f < 100.0)
            precision = 4;
        else if (f < 1000.0)
            precision = 3;
        else if (f < 10000.0)
            precision = 2;
        else if (f < 100000.0)
            precision = 1;
        else
            precision = 0;
    }

    // round value according the precision
    if (precision) f += rounders[precision];

    // integer part...
    intPart = f;
    f -= intPart;

    if (!intPart)
        *ptr++ = '0';
    else {
        // save start pointer
        p = ptr;

        // convert (reverse order)
        while (intPart) {
            *p++ = '0' + intPart % 10;
            intPart /= 10;
        }

        // save end pos
        p1 = p;

        // reverse result
        while (p > ptr) {
            c      = *--p;
            *p     = *ptr;
            *ptr++ = c;
        }

        // restore end pos
        ptr = p1;
    }

    // decimal part
    if (precision) {
        // place decimal point
        *ptr++ = '.';

        // convert
        while (precision--) {
            f *= 10.0;
            c      = f;
            *ptr++ = '0' + c;
            f -= c;
        }
    }

    // terminating zero
    *ptr = 0;

    return buf;
}

void clear_calc_vars(void) {
    term_1        = 0;
    term_2        = 0;
    res           = 0;
    operator      = 0;
    term_1_ok     = false;
    calc_finished = false;
}

void digit_handling(int digit) {
    if (!calc_finished) {
        if (!term_1_ok) {
            term_1 = concatenate(term_1, digit);
            // Hereto fix intrinsic bug with ftoa function that I've implemented
            if (digit != 9)
                ftoa(term_1, str_temp, 0);
            else
                ftoa(term_1, str_temp, 1);
            ftoa(term_1, str_temp, 0);
            oled_clear();
            oled_set_cursor(21 - strlen(str_temp), 2);
            oled_write(str_temp, false);
        } else {
            term_2 = concatenate(term_2, digit);
            ftoa(term_2, str_temp, 0);
            oled_set_cursor(1, 3);
            oled_write_P(PSTR("                    \n"), false);
            oled_set_cursor(21 - strlen(str_temp), 3);
            oled_write(str_temp, false);
        }
    }
}

void equal_op(void) {
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
        ftoa(res, str_temp, -1);
        oled_clear();
        oled_set_cursor(0, 3);
        oled_write_char('=', false);
        oled_set_cursor(21 - strlen(str_temp), 3);
        oled_write(str_temp, false);
    } else if (!calc_finished) {
        calc_finished = true;
        ftoa(term_1, str_temp, -1);
        oled_clear();
        oled_set_cursor(0, 3);
        oled_write_char('=', false);
        oled_set_cursor(21 - strlen(str_temp), 3);
        oled_write(str_temp, false);
    }
}

void root_op(void) {
    if ((!term_1_ok) && (!calc_finished) && (operator== 0)) {
        if (term_1 >= 0) {
            res = sqrt(term_1);
            ftoa(res, str_temp, -1);
            oled_clear();
            oled_set_cursor(0, 3);
            oled_write_char('=', false);
            oled_set_cursor(21 - strlen(str_temp), 3);
            oled_write(str_temp, false);
        } else {
            oled_clear();
            oled_set_cursor(0, 3);
            oled_write_P(PSTR("=     Imaginary Root!\n"), false);
        }
        calc_finished = true;
    }
}

void neg_num_op(void) {
    if ((!calc_finished)) {
        if (!term_1_ok) {
            term_1 = -term_1;
            ftoa(term_1, str_temp, 0);
            oled_clear();
            oled_set_cursor(21 - strlen(str_temp), 2);
            oled_write(str_temp, false);
        } else {
            term_2 = -term_2;
            ftoa(term_2, str_temp, 0);
            oled_set_cursor(1, 3);
            oled_write_P(PSTR("                    \n"), false);
            oled_set_cursor(21 - strlen(str_temp), 3);
            oled_write(str_temp, false);
        }
    }
}