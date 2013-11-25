#include <Wire.h> // I2C
#include <Adafruit_MotorShield.h>

// 建立代表馬達控制板的物件
Adafruit_MotorShield motorShield = Adafruit_MotorShield(); 
// 取得代表馬達的物件，假定直流馬達連接M1，
// 傳入1便可得到指向馬達物件的指標
Adafruit_DCMotor *motor = motorShield.getMotor(1);

void setup() {
  motorShield.begin(); // 啟用並初始化
}
void loop() {
  int i;
  // FORWARD是往前轉，BACKWARD往後轉，RELEASE停止
  motor->run(FORWARD); // 往前轉
  for(i = 0; i <= 255; i++){ // 漸快
    motor->setSpeed(i); // 設定轉速，0是關閉，255是最快轉速
    delay(10);
  }
  for(i = 255; i >= 0; i--){ // 漸慢
    motor->setSpeed(i);
    delay(10);
  }
  delay(1000);
  motor->run(BACKWARD); // 往後轉
  for(i = 0; i <= 255; i++){ // 漸快
    motor->setSpeed(i);
    delay(10);
  }
  for(i = 255; i >= 0; i--){ // 漸慢
    motor->setSpeed(i);
    delay(10);
  }
  motor->run(RELEASE); // 停止
  delay(1000);
}

