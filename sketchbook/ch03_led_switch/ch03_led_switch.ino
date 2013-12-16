// 定義連接腳位
#define LED_PIN 11
#define SWITCH_PIN 7

void setup() {
  // 設定腳位模式
  pinMode(LED_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT);
}
void loop() {
  // 讀取開關狀態
  boolean switch_status = digitalRead(SWITCH_PIN);
  // 根據開關狀態設定LED明滅
  digitalWrite(LED_PIN, switch_status);
}

