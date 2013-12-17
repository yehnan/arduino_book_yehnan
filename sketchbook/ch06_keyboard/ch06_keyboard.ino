#include "pitches.h"
// 定義代表某音階的腳位
#define DO_PIN 12
#define RE_PIN 11
#define MI_PIN 10
#define FA_PIN 9
#define SO_PIN 8
#define LA_PIN 7
#define SI_PIN 6
#define DO_HIGH_PIN 5
#define RE_HIGH_PIN 4
#define BUZZER_PIN 3 // 蜂鳴器連接腳位

#define KEY_NUM 9 // 9個音階
#define DURATION 400

typedef struct{
  int pin;
  int pitch;
} PinPitch;
PinPitch data[KEY_NUM] = {
  {DO_PIN, NOTE_C5}, {RE_PIN, NOTE_D5}, {MI_PIN, NOTE_E5}, {FA_PIN, NOTE_F5}, {SO_PIN, NOTE_G5},
  {LA_PIN, NOTE_A5}, {SI_PIN, NOTE_B5}, {DO_HIGH_PIN, NOTE_C6}, {RE_HIGH_PIN, NOTE_D6},
};

void setup() {
  for(int i = 0; i < KEY_NUM; i++){
    pinMode(data[i].pin, INPUT_PULLUP); // 啟用內建的上拉電阻
  }
}
void loop() {
  for(int i = 0; i < KEY_NUM; i++){
    int s = digitalRead(data[i].pin);
    if(s == LOW){
      tone(BUZZER_PIN, data[i].pitch, DURATION);
      delay(DURATION * 1.3);
    }
  }
}

