#define LED_PIN 2 // LED
#define BUZZER_PIN 3 // 蜂鳴器
#define FAN_PIN 4 // 風扇
#define BULB_PIN 5 // 燈泡
#define NOTE_C5  523
#define NOTE_B5  988

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(BULB_PIN, OUTPUT);
}
void loop() {
  digitalWrite(LED_PIN, HIGH);
  tone(BUZZER_PIN, NOTE_C5, 3000 / 4);
  digitalWrite(FAN_PIN, HIGH);
  digitalWrite(BULB_PIN, HIGH);
  delay(3000);
  digitalWrite(LED_PIN, LOW);
  tone(BUZZER_PIN, NOTE_B5, 3000 / 4);
  digitalWrite(FAN_PIN, LOW);
  digitalWrite(BULB_PIN, LOW);
  delay(3000);
}

