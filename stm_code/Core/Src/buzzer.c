/*
 * buzzer.c
 *
 *  Created on: Apr 6, 2024
 *      Author: laptop
 */
#include "buzzer.h"

uint32_t Channel = TIM_CHANNEL_2;
//TIM_HandleTypeDef htim1; // declare the timer handle
void buzzer_tone(int note, int duration){
	buzzer_freq(note);
	HAL_Delay(duration);
}

void play_note(int note, int duration){
	buzzer_tone(note,9*duration/10);
	buzzer_stop();
	HAL_Delay(duration/10);
}

//note type je +-  2, 4, 8, 16 pricom + su normalne noty, - su ako keby noty s bodkou....
//2 je cela nota
//4 je dvojdoba
//8 je pol doba
//

int calculate_duration(int bpm, int note_type){
	int beat = 4*60000/bpm; // preco je tu 4?
	int duration = 0;
	if (note_type > 0) {
	      // regular note, just proceed
		duration = (beat) / note_type;
	    } else if (note_type < 0) {
	      // dotted notes are represented with negative durations!!
	    	duration = (beat) / abs(note_type);
	    	duration *= 1.5; // increases the duration in half for dotted notes
	    }
	return duration;
}

void play_scale(){
	int whole_note = 4;
	int scale[8]={NOTE_C4,NOTE_D4,NOTE_E4,NOTE_F4,NOTE_G4,NOTE_A4,NOTE_B4,NOTE_C5};
	for (int i=0;i<8;i++){
		play_note(scale[i],calculate_duration(90, whole_note));
	}
}

void play_rick_roll(){
	int bpm = 115;
	int melody[] = {
	  NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
	  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
	  NOTE_E5,-8, NOTE_E5,-8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,-8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16, //18
	  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,8, NOTE_A4,8, NOTE_A4,8,
	  NOTE_E5,4, NOTE_D5,2,
	};

	int for_cycle_end = sizeof(melody) / sizeof(melody[0]);

	for (int this_note = 0;this_note< for_cycle_end; this_note+=2){
		play_note(melody[this_note], calculate_duration(bpm,melody[this_note+1]));
	}

}

void play_swarowski(uint16_t frequency, uint16_t type, uint16_t bpm){
	play_note(frequency, calculate_duration(bpm, type));
}

void buzzer_freq_amp(int freq, int amp) {
	int arr = 1000000/freq;   //ARR diveder
//	TIM1->CCR1 = 1000;
	TIM1->CCR2 = arr/amp;//1150;  //duty cycle
	TIM1->ARR = arr;
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);

}
void buzzer_freq(int freq) {
	int arr = 1000000/freq;   //ARR diveder
//	TIM1->CCR1 = 1000;
	TIM1->CCR2 = arr/2;//1150;  //duty cycle
	TIM1->ARR = arr;
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);

}
void buzzer_stop(void){
    HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2); // Stop the PWM signal
}
