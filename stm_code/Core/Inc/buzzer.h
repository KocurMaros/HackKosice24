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
#include "pitches.h"
#include <stdlib.h>


void buzzer_tone(int note, int duration);
void buzzer_freq_amp(int freq, int amp);
void buzzer_freq(int freq);
void buzzer_stop(void);
void play_scale();
int calculate_duration(int bpm, int note_type);
void play_note(int note, int duration);
void play_rick_roll();

#endif /* INC_BUZZER_H_ */
