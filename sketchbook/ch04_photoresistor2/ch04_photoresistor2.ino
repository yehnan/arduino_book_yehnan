#define SERIAL_BAUDRATE 19200
#define LED_PIN 11
#define PR_PIN A0 // 光敏電阻（photo resistor）

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
}
void loop() {
  int r = analogRead(PR_PIN);

  // 環境光線越強，LED就越亮
  int b = map(r, 0, 1023, 0, 255);
  
  // 環境光線越弱強，LED就越亮
  // int b = map(r, 0, 1023, 255, 0);
  
  analogWrite(LED_PIN, b);
}

