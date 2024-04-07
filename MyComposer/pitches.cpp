#include "pitches.h"

Tone::Tone(){}

Tone::Tone(int freq, int t, int b){
    frequency = freq;
    type = t;
    bpm = b;
}

void Tone::setFrequency(int freq){
    frequency = freq;
}

void Tone::setType(int t){
    type = t;
}

void Tone::setBpm(int b){
    bpm = b;
}

int Tone::getFrequency(){
    return frequency;
}

int Tone::getType(){
    return type;
}

int Tone::getBpm(){
    return bpm;
}


