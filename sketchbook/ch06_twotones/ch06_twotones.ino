#include "pitches.h" // 含有各個頻率
#include <Tone.h>
#define SERIAL_BAUDRATE 19200
#define BUZZER_1_PIN 11 // 蜂鳴器或小喇叭
#define BUZZER_2_PIN 12 // 連接的腳位
Tone t1; // 使用Tone程式庫的類別建立兩個Tone發聲物件
Tone t2;

int notes1[8] = { // 給t1用的頻率，較低
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5,
};
int notes2[8] = { // 給t2用的頻率，較高
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6,
};
void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  t1.begin(BUZZER_1_PIN); // 連接Tone物件與腳位
  t2.begin(BUZZER_2_PIN);
}
void loop() {
  int c;
  if(Serial.available()){
    c = Serial.read(); // 讀取序列埠
    switch(c){ // 根據按鍵發出相對應的頻率
      case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8':
        t1.play(notes1[c - '1']);
        t2.play(notes2[c - '1']);
      break;
      case ' ': // 若是空白鍵就停止發聲
        t1.stop();
        t2.stop();
      break;
    }
  }
}

