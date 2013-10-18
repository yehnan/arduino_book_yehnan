#define LED_PIN 11
#define SWITCH_PIN 7

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT);
}

void loop() {
  boolean switch_status = digitalRead(SWITCH_PIN);
  digitalWrite(LED_PIN, switch_status);
}

