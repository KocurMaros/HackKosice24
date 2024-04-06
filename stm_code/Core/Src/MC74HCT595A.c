#include "MC74HCT595A.h"

// Will point to our light patterns. A byte is an 8-bit BINARY variable to match the 8 lights
uint8_t * registerPatterns;

void clearRegisters();

void MC74HCT595A_init(){
    registerPatterns = malloc(REGISTERS * sizeof(uint8_t));
    registerPatterns[0] = 7;
    registerPatterns[1] = 6;
//    clearRegisters();
}
void writePinToByte(int pin, bool state) {
    // Which register are we looking at? 0=first, 1=second, etc. "/" will round down to an int
    int r = pin / 8;

    // Which pin on that register, finding the remainder of the pin division will give us 0-7
    int q = pin % 8;
    for (size_t i = 0; i < REGISTERS; i++) {
        // Point to the current pattern for this register
        uint8_t * pattern = &registerPatterns[i];
        // If this is the register that the pin we are editing is on...
        if (i == r) {
            // Take the "pattern" that holds the 8 bits, change the binary digit at position "q" (0-7) to "state" (LOW = 0, HIGH = 1)
            if(state)
                *pattern |= (1 << q);
            else
                *pattern &= ~(1 << q); 
        }
    }
}
void MC74HCT595A_shiftOut(uint8_t *data){

    HAL_SPI_Transmit(&hspi2, data, 1, 1000);
//    HAL_SPI_Transmit(hspi, data, 1, 1000);


}

void writeToRegisters() {

  // Lock the registers to ready them to be written
  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);

  // Go through each of our stored patterns and write them back to the registers in order
  for (size_t i = 0; i < REGISTERS; i++) {

    // Point to the current pattern for this register
    uint8_t * pattern = &registerPatterns[i];

    // Write the pattern back to the register chips byte by byte
    MC74HCT595A_shiftOut(*pattern);
  }
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
  // Unlock the registers
}



















void clearRegisters() {

  // For each register, set it's pattern to 0 (which, rember is 00000000 in bytes, meaning all lights off)
  for (size_t i = 0; i < REGISTERS; i++) {
    registerPatterns[i] = 0;
  }
}
