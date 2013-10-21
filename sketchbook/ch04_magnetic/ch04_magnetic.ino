#define LED_PIN 11
#define MAGNETIC_PIN 7

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(MAGNETIC_PIN, INPUT);
}

void loop() {
  boolean s = digitalRead(MAGNETIC_PIN);
  digitalWrite(LED_PIN, s);
}

