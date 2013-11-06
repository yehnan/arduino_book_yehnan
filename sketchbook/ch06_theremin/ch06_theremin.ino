#include "pitches.h"
#define PR_PIN A0 // photo resistor，光敏電阻腳位
#define BUZZER_PIN 3 // 蜂鳴器或小喇叭腳位

void setup() {
}
void loop() {
  int v = analogRead(PR_PIN);
  int pitch = NOTE_C5 + v/4; // 根據光亮度算出某個音高值
  tone(BUZZER_PIN, pitch); // 持續發聲
}

