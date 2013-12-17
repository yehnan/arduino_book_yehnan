#define SERIAL_BAUDRATE 19200
#define VD0 A0 // 分壓器端點一
#define VD1 A1 // 分壓器端點二

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
}
void loop() {
  float v0 = float(analogRead(VD0)) / 1023 * 5;
  float v1 = float(analogRead(VD1)) / 1023 * 5;
  Serial.print("A0's voltage is ");
  Serial.println(v0);
  Serial.print("A1's voltage is ");
  Serial.println(v1);
  delay(1000);
}

