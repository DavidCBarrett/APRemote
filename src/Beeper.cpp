#include "Arduino.h"

#include "Beeper.h"

Beeper::Beeper(int _beeperPin){
  beeperPin = _beeperPin;
}

void Beeper::Setup() {

  // iterate over the notes of the melody. 
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(beeperPin, melody[thisNote], noteDuration*0.9);
    
    // Wait for the specief duration before playing the next note.
    delay(noteDuration*0.1);  
  }
}

void Beeper::ShortBeep() {
  tone(beeperPin, NOTE_C5, wholenote/64);
}

void Beeper::FailBeep() {
  tone(beeperPin, NOTE_D4, wholenote/64);
}

void Beeper::Loop() {
}
