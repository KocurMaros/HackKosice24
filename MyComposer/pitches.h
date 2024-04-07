/*************************************************
   Public Constants
 *************************************************/

#include <QString>
#include <QStringList>

#define NOTE_C1 33
#define NOTE_D1 37
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_G1 49
#define NOTE_A1 55
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_D2 73
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_G2 98
#define NOTE_A2 110
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_D3 147
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_G3 196
#define NOTE_A3 220
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_D5 587
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_G5 784
#define NOTE_A5 880
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_D6 1175
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_G6 1568
#define NOTE_A6 1760
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_D7 2349
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_G7 3136
#define NOTE_A7 3520
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_D8 4699
#define REST 0

class MelodyDataStructure{
public:
    //constructors
    MelodyDataStructure();
    MelodyDataStructure(int freq, int t, int b);

    QString toText();
    // Deserialization from text function
    void fromText(const QString& text);

    //setters
    void setFrequency(int freq);
    void setType(int t);
    void setBpm(int b);
    //getters
    int getFrequency();
    int getType();
    int getBpm();
private:
    int frequency;
    int type;
    int bpm;
    //magnitude?
};

