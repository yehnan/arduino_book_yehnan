#define SERIAL_BAUDRATE 19200
#define LED_PIN 11
#define FSR_PIN A0 // 壓力感測器（force sensitive resistor）
 
void setup() {
  Serial.begin(SERIAL_BAUDRATE);
}
void loop() {
  int r = analogRead(FSR_PIN);
  Serial.println(r);
  // 施加力量越大，LED越亮
  int b = map(r, 0, 1023, 0, 255);
  // 施加力量越弱，LED越亮
  // int b = map(r, 0, 1023, 255, 0);
  analogWrite(LED_PIN, b);
}

