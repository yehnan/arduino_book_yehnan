#define SERIAL_BAUDRATE 19200
#define VD A0 // voltage divider

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
}

void loop() {
  float v = float(analogRead(VD)) / 1023 * 5;
  Serial.println(v);

  delay(1000);
}

