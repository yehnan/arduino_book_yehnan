#include <Servo.h>
#define SERVO_PIN 9
#define PW_LOWER_BOUND 1000 // PL是Pulse Width脈衝寬度
#define PW_UPPER_BOUND 2000
Servo s; // 建立Servo物件
void setup() {
  // 連接伺服馬達，開始輸出脈衝訊號
  s.attach(SERVO_PIN, PW_LOWER_BOUND, PW_UPPER_BOUND);
}
void loop() {
  for(int i = 0; i <= 180; i += 45){
    s.write(i);
    delay(3000);
  }
}

