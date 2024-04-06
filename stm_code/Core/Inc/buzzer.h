/*
 * buzzer.h
 *
 *  Created on: Apr 6, 2024
 *      Author: laptop
 */

#ifndef _BUZZER_H_
#define _BUZZER_H_

#include "tim.h"
#include "stm32g0xx_hal.h" // replace fxxx with your specific STM32 series
#include "stm32g0xx_hal_tim.h" // replace fxxx with your specific STM32 series



void buzzer_tone(int freq, int duration);
void buzzer_freq(int freq);
void buzzer_stop(void);


#endif /* INC_BUZZER_H_ */
