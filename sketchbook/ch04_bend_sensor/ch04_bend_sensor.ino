#define SERIAL_BAUDRATE 19200
#define LED_PIN 11
#define BS_PIN A0 // 彎曲感測器（bend sensor）
 
void setup() {
  Serial.begin(SERIAL_BAUDRATE);
}
void loop() {
  int r = analogRead(BS_PIN);
  Serial.println(r);
  // 若彎曲程度越小（直挺挺），LED就越亮。
  // 請根據你的彎曲感測器與需求，修改底下的限制數值
  int b = constrain(r, 180, 320);
  b = map(b, 180, 320, 0, 255);
  analogWrite(LED_PIN, b);
}

