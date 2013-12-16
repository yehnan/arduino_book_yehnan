#include <Bounce.h> // 匯入Bounce程式庫的標頭檔
#define SERIAL_BAUDRATE 19200
#define LED_PIN 11
#define SWITCH_PIN 7
#define DEBOUNCE_DELAY 50 // milliseconds

// 建立Bounce物件
Bounce bouncer = Bounce(SWITCH_PIN, DEBOUNCE_DELAY);
boolean led_status;

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  pinMode(LED_PIN, OUTPUT);
  
  led_status = LOW;
  digitalWrite(LED_PIN, led_status);
}
void loop() {
  // 呼叫update更新狀態，若回傳true代表狀態改變，
  // 呼叫read讀取開關狀態
  if(bouncer.update() == true && bouncer.read() == HIGH){
    led_status = !led_status;
    digitalWrite(LED_PIN, led_status);
  }
}

