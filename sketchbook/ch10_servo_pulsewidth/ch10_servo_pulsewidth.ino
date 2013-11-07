#include <Servo.h>
#define SERVO_PIN 9
// 定義脈衝寬度上下限，此處以Tower Pro SG90為例
#define PL_LOWER_BOUND 500 // PL是Pulse Width脈衝寬度
#define PL_UPPER_BOUND 2400
Servo s; // 建立Servo物件
void setup() {
  // 自行指定脈衝寬度上下限  
  s.attach(SERVO_PIN, PL_LOWER_BOUND, PL_UPPER_BOUND);
}
void loop() {
  s.writeMicroseconds(PL_LOWER_BOUND); // 直接指定脈衝寬度
  delay(1000);
  s.write(0);
  delay(1000);
  s.writeMicroseconds((PL_LOWER_BOUND+PL_UPPER_BOUND)/2);
  delay(1000);
  s.write(90);
  delay(1000);
  s.writeMicroseconds(PL_UPPER_BOUND);
  delay(1000);
  s.write(180);
  delay(1000);
}

