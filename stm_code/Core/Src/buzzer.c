/*
 * buzzer.c
 *
 *  Created on: Apr 6, 2024
 *      Author: laptop
 */
#include "buzzer.h"

uint32_t Channel = TIM_CHANNEL_2;
//TIM_HandleTypeDef htim1; // declare the timer handle


void buzzer_freq(int freq) {
	int arr = 1000000/freq;   //ARR diveder
	TIM1->CCR2 = 50;  //duty cycle
	TIM1->ARR = arr;
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);

}
void buzzer_stop(void){
    HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2); // Stop the PWM signal
}
