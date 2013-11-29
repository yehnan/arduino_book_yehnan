#include <Wire.h> // I2C
#include <Adafruit_MotorShield.h>
// 建立代表馬達控制板的物件
Adafruit_MotorShield motorShield = Adafruit_MotorShield(); 
// 取得代表馬達的物件，
// 假定右馬達連接M2，左馬達連接M1的端子台，
Adafruit_DCMotor *motorRight = motorShield.getMotor(2);
Adafruit_DCMotor *motorLeft = motorShield.getMotor(1);

void setup() {
  motorShield.begin(); // 啟用並初始化
}
void loop() {
  forward(); delay(3000); stop(); delay(1000);
  backward(); delay(3000); stop(); delay(1000);
  rotateRight(); delay(3000); stop(); delay(1000);
  rotateLeft(); delay(3000); stop(); delay(1000);
  turnRight(); delay(3000); stop(); delay(1000);
  turnLeft(); delay(3000); stop(); delay(1000);
  moveAndTurnRight(); delay(3000); stop(); delay(1000);
  moveAndTurnLeft(); delay(3000); stop(); delay(1000);
}
void forward(){ // 兩個馬達都正轉，往前進
  setMotorRight(255, false);
  setMotorLeft(255, false);
}
void backward(){ // 兩個馬達都逆轉，往後退
  setMotorRight(255, true);
  setMotorLeft(255, true);
}
void rotateRight(){ // 原地向右旋轉
  setMotorRight(255, true);
  setMotorLeft(255, false);
}
void rotateLeft(){ // 原地向左旋轉
  setMotorRight(255, false);
  setMotorLeft(255, true);
}
void turnRight(){ // 向右轉彎
  setMotorRight(0, false);
  setMotorLeft(255, false);
}
void turnLeft(){ // 向左轉彎
  setMotorRight(255, false);
  setMotorLeft(0, false);
}
void moveAndTurnRight(){ // 邊前進邊向右轉彎
  setMotorRight(127, false);
  setMotorLeft(255, false);
}
void moveAndTurnLeft(){ // 邊前進邊向左轉彎
  setMotorRight(255, false);
  setMotorLeft(127, false);
}
void stop(){ // 停止
  setMotorRight(0, false);
  setMotorLeft(0, false);
}
// 設定馬達的速度（0~255）與轉向
void setMotorRight(int speed, boolean reverse) {
  if(speed == 0){
    motorRight->run(RELEASE);
  }
  else{
    motorRight->setSpeed(speed);
    motorRight->run(reverse ? BACKWARD : FORWARD);
  } 
}
void setMotorLeft(int speed, boolean reverse) {
  if(speed == 0){
    motorLeft->run(RELEASE);
  }
  else{
    motorLeft->setSpeed(speed);
    motorLeft->run(reverse ? BACKWARD : FORWARD);
  }
}

