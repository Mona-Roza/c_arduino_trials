#ifndef __SEVEN_SEGMENT_H_

#define __SEVEN_SEGMENT_H_

#include <stdint.h>

#define NUMBERS_SIZE 11
#define LETTERS_SIZE 21

/***********NUMERIC_CHARACTERS***********/
#define ssn_0 0x3F
#define ssn_1 0x06
#define ssn_2 0x5B
#define ssn_3 0x4F
#define ssn_4 0x66
#define ssn_5 0x6D
#define ssn_6 0x7D
#define ssn_7 0x07
#define ssn_8 0x7F
#define ssn_9 0x6F
#define ssn_DOT 0x80

/***********ALPHANUMERIC_CHARACTERS***********/
#define ssan_A 0x77
#define ssan_B 0x7C
#define ssan_C 0x58
#define ssan_D 0x5E
#define ssan_E 0x79
#define ssan_F 0x71
#define ssan_G 0x6F
#define ssan_H 0x76
#define ssan_I 0x04
#define ssan_J 0x0E
#define ssan_L 0x38
#define ssan_N 0x54
#define ssan_O 0x5C
#define ssan_P 0x73
#define ssan_R 0x50
#define ssan_S 0x6D
#define ssan_U 0x1C
#define ssan_Y 0x6E
#define ssan_MINUS 0x40
#define ssan_ERROR 0x49
#define ssan_BLANK 0x00

uint8_t ss_numbers[] = {ssn_0, ssn_1, ssn_2, ssn_3, ssn_4, ssn_5, ssn_6, ssn_7, ssn_8, ssn_9, ssn_DOT};
uint8_t ss_letters[] = {ssan_A, ssan_B, ssan_C, ssan_D, ssan_E, ssan_F, ssan_G, ssan_H, ssan_I, ssan_J, ssan_L, ssan_N, ssan_O, ssan_P, ssan_R, ssan_S, ssan_U, ssan_Y, ssan_MINUS, ssan_ERROR, ssan_BLANK};

#endif