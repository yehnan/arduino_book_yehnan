#define LED_NUM 1
#define BUZZER_PIN 3
int ledPins[LED_NUM] = {
  2, //3, 4, 
};
#define NOTE_C5  523
void setup() {
  for(int i = 0; i < LED_NUM; i++){
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  tone(BUZZER_PIN, NOTE_C5, 3000/8);
  for(int i = 0; i < LED_NUM; i++){
    digitalWrite(ledPins[i], HIGH);
  }
  delay(1000);
  for(int i = 0; i < LED_NUM; i++){
    digitalWrite(ledPins[i], LOW);
  }
  delay(1000);
}

