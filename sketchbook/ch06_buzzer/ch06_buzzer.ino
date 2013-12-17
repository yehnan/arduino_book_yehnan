#include "pitches.h"

int melody[] = { // 儲存音符（發聲頻率）
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_,
};
int noteDurations[] = { // 每個音符的發聲時間
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
};

void setup() {
}
void loop() {
  play(melody, noteDurations, sizeof(melody) / sizeof(int));
  delay(2000);
}

