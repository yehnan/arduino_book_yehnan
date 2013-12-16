#define LED_PIN 11 // 連接LED的腳位

void setup() {
  pinMode(LED_PIN, OUTPUT); // 設定腳位輸出入模式
}

void loop() {
  digitalWrite(LED_PIN, HIGH); // 點亮LED
  delay(1000); // 暫停1000毫秒（1秒）
  digitalWrite(LED_PIN, LOW); // 熄滅LED
  delay(1000); // 暫停1000毫秒（1秒）
}

