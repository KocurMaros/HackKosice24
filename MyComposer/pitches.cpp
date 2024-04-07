#include "pitches.h"

MelodyDataStructure::MelodyDataStructure(){}

MelodyDataStructure::MelodyDataStructure(int freq, int t, int b){
    frequency = freq;
    type = t;
    bpm = b;
}

void MelodyDataStructure::setFrequency(int freq){
    frequency = freq;
}

void MelodyDataStructure::setType(int t){
    type = t;
}

void MelodyDataStructure::setBpm(int b){
    bpm = b;
}

int MelodyDataStructure::getFrequency(){
    return frequency;
}

int MelodyDataStructure::getType(){
    return type;
}

int MelodyDataStructure::getBpm(){
    return bpm;
}

QString MelodyDataStructure::toText() {
        return QString("%1,%2,%3").arg(frequency).arg(type).arg(bpm);
}

void MelodyDataStructure::fromText(const QString& text) {
    QStringList parts = text.split(",");
    if (parts.size() >= 3) {
        frequency = parts[0].toInt();
        type = parts[1].toInt();
        bpm = parts[2].toInt();
    }
}
