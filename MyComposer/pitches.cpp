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

QString Tone::toText() {
        return QString("%1,%2,%3").arg(frequency).arg(type).arg(bpm);
}

void Tone::fromText(const QString& text) {
    QStringList parts = text.split(",");
    if (parts.size() >= 3) {
        frequency = parts[0].toInt();
        type = parts[1].toInt();
        bpm = parts[2].toInt();
    }
}
