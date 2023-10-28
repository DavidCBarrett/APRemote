#pragma once

#include <pitches.h>

class Beeper
{
private:
    // change this to make the song slower or faster
    int tempo = 60;

    // change this to whichever pin you want to use
    int beeperPin;
 
    // notes of the melody followed by the duration.
    // a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
    // !!negative numbers are used to represent dotted notes,
    // so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
    const int melody[6] = {
    
        NOTE_A4, 16, NOTE_B4, 16, NOTE_C5, 16
    };

    // sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
    // there are two values per note (pitch and duration), so for each note there are four bytes
    int notes = sizeof(melody) / sizeof(melody[0]) / 2;

    // this calculates the duration of a whole note in ms
    int wholenote = (60000 * 4) / tempo;

    int divider = 0, noteDuration = 0;

public:
    Beeper(int _beeperPin);
    void Setup();
    void Loop();

    void ShortBeep();
    void FailBeep();
};