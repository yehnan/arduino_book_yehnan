#include <Arduino.h>
#include "pitches.h"

void play(int *melody, int *noteDurations, int num){
  for(int note = 0; note < num; note++){
    int noteDuration = 3000 / noteDurations[note];
    tone(BUZZER_PIN, melody[note], noteDuration);
    delay(noteDuration * 1.30);
  }
}


