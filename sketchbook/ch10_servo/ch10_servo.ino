#include <Servo.h>
#define SERVO_PIN 9
Servo s; // 建立Servo物件
void setup() {
  s.attach(SERVO_PIN); // 連接伺服馬達（訊號線）
}
void loop() {
  int i;
  for(i = 0; i <= 180; i++){
    s.write(i); // 使用write，傳入角度，從0度轉到180度
    delay(20);
  }
  for(i = 180; i >= 0; i--){
    s.write(i); // 從180度轉回到0度
    delay(20);
  }
}

