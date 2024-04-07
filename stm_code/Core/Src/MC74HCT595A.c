#include "MC74HCT595A.h"

// Will point to our light patterns. A byte is an 8-bit BINARY variable to match the 8 lights
uint8_t * registerPatterns;

void clearRegisters();
numbers_t segments[10];
void MC74HCT595A_init(){
    registerPatterns = malloc(REGISTERS * sizeof(uint8_t));
    registerPatterns[0] = 5;
    registerPatterns[1] = 6;
    for(size_t i = 0; i < 10; i++){
        segments[i].number = i;
        switch (i){
        case 0:
            segments[i].segments = 255 & (1 << SEG_G);
            break;
        case 1:
            segments[i].segments =255 & ~((1 << SEG_B) | (1 << SEG_C));
            break;
        case 2:
            segments[i].segments = 255 & ~ ((1 << SEG_A) | (1 << SEG_B) | (1 << SEG_G) | (1 << SEG_E) | (1 << SEG_D));
            break;
        case 3:
            segments[i].segments = 255 & ~ ((1 << SEG_A) | (1 << SEG_B) | (1 << SEG_G) | (1 << SEG_C) | (1 << SEG_D));
            break;
        case 4:
            segments[i].segments = 255 & ~ ((1 << SEG_F) | (1 << SEG_B) | (1 << SEG_G) | (1 << SEG_C));
            break;
        case 5:
            segments[i].segments = 255 & ~ ((1 << SEG_A) | (1 << SEG_F) | (1 << SEG_G) | (1 << SEG_C) | (1 << SEG_D));
            break;
        case 6:
            segments[i].segments = 255 & ~ ((1 << SEG_A) | (1 << SEG_F) | (1 << SEG_G) | (1 << SEG_C) | (1 << SEG_D) | (1 << SEG_E));
            break;
        case 7:
            segments[i].segments = 255 & ~ ((1 << SEG_A) | (1 << SEG_B) | (1 << SEG_C));
            break;
        case 8:
            segments[i].segments = 0;
            break;
        case 9:
            segments[i].segments = 255 & ~ ((1 << SEG_A) | (1 << SEG_B) | (1 << SEG_G) | (1 << SEG_C) | (1 << SEG_D) | (1 << SEG_F));
            break;
        }
    }
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
uint8_t calc_segments(uint8_t data){
    uint8_t result = 0;
    result = segments[data].segments;
    return result;
}
void MC74HCT595A_shiftOut(uint16_t data){
	//clock PA8
	//LATch PB5
	//data pa9
    uint8_t temp; 
    uint16_t segm = 0;
 
    uint16_t printofka;
    for(int i = 0;i<4;i++){
    	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
       temp  = calc_segments(data%10);
       data = data/10;
		segm = (1 << SEG_4+i);
       printofka = segm | temp;
       printofka |= 0b1;
        for(int j = 0;j<16;j++){
            if(printofka & (1 << j)){
                HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
                HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8);
                HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            }
            else{
                HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
            }
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8);
        }
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
	}
}

void writeToRegisters(uint16_t freq) {

  // Lock the registers to ready them to be written
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
    MC74HCT595A_shiftOut(freq);
  // Go through each of our stored patterns and write them back to the registers in order
  
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
  // Unlock the registers
}





void clearRegisters() {

  // For each register, set it's pattern to 0 (which, rember is 00000000 in bytes, meaning all lights off)
  for (size_t i = 0; i < REGISTERS; i++) {
    registerPatterns[i] = 0;
  }
}
