#pragma once

extern float   term_1;
extern float   term_2;
extern  float   res;
extern  char    str_temp[20];
extern uint8_t operator;
extern bool    term_1_ok;
extern bool    calc_finished;

#define MAX_PRECISION (5)

float concatenate(float x, int y);
char *ftoa(double f, char *buf, int precision);
void clear_calc_vars(void);
void digit_handling(int digit);
void op_handling(void);
void equal_op(void);
void root_op(void);
void neg_num_op(void);
void print_res(bool im_root);