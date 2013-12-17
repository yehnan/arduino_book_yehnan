#define SERIAL_BAUDRATE 19200
#define LED_PIN 11
#define PR_PIN A0 // 光敏電阻（photo resistor）
#define THRESHOLD 300 // 界限
#define VOLTAGE 5 // 兩端電壓

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  pinMode(LED_PIN, OUTPUT);
}
void loop() {
  int r = analogRead(PR_PIN);
  float v = float(r) / 1023 * VOLTAGE;

  if(r > THRESHOLD){ // 判斷是否超過界限，控制LED亮滅
    digitalWrite(LED_PIN, LOW);
  }
  else{
    digitalWrite(LED_PIN, HIGH);
  }
  // 輸出類比輸入腳位的讀數，以及換算後的電壓值
  Serial.print("A0 reading is: ");
  Serial.print(r);
  Serial.print(", voltage is ");
  Serial.println(v);
  delay(1000);
}

