#ifndef MC74HCT595A_H
#define MC74HCT595A_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "gpio.h"
#include "spi.h"
// Define the pins connected to the shift register


// Number of shift registers
#define REGISTERS 2

// Total number of pins
#define PINS REGISTERS * 8


// Function prototypes
void MC74HCT595A_init();
void MC74HCT595A_shiftIn(uint8_t data);
void MC74HCT595A_shiftOut();
void writeToRegisters();
#endif // MC74HCT595A_H
