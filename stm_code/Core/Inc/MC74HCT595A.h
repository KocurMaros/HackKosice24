#ifndef MC74HCT595A_H
#define MC74HCT595A_H

#include <stdint.h>

// Define the pins connected to the shift register
#define DATA_PIN 0
#define CLOCK_PIN 1
#define LATCH_PIN 2

// Function prototypes
void MC74HCT595A_init(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin);
void MC74HCT595A_shiftIn(uint8_t data);
void MC74HCT595A_shiftOut();

#endif // MC74HCT595A_H