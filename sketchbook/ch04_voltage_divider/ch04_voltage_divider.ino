#define SERIAL_BAUDRATE 19200
#define VD A0 // 分壓器（voltage divider）

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
}
void loop() {
  // 以float()將整數轉成浮點數型別，進行浮點數運算
  float v = float(analogRead(VD)) / 1023 * 5; // 假設兩端電壓是5V
  Serial.println(v);

  delay(1000);
}

