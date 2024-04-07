#ifndef MC74HCT595A_H
#define MC74HCT595A_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "gpio.h"
// Define the pins connected to the shift register


// Number of shift registers
#define REGISTERS 2

// Total number of pins
#define PINS REGISTERS * 8

typedef enum{
    SEG_DOT = 0,
    SEG_G,
    SEG_F,
    SEG_E,
    SEG_D,
    SEG_C,
    SEG_B,
    SEG_A,
    SEG_1 = 15,
    SEG_2 = 14,
    SEG_3 = 13,
    SEG_4 = 12
}Bits_segm_t;
typedef struct{
    uint8_t number;
    uint8_t segments;
}numbers_t;
// Function prototypes
void MC74HCT595A_init();
void MC74HCT595A_shiftIn(uint16_t data);
void MC74HCT595A_shiftOut(uint16_t data);
void writeToRegisters(uint16_t data);
#endif // MC74HCT595A_H
