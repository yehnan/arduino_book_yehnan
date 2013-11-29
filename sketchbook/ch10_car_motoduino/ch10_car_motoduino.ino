// 一個馬達以兩個腳位操控
// 以digitalWrite控制轉向：正轉、逆轉
// 以analogWrite控制轉速，0停止，255最快
#define M1_SPEED_PIN 6 // 馬達M1的轉速
#define M1_DIRECTION_PIN 7 // 馬達M1的轉向
#define M2_SPEED_PIN 5 // 馬達M2的轉速
#define M2_DIRECTION_PIN 8 // 馬達M2的轉向

// 假定M1連接左馬達，M2連接右馬達
#define MOTOR_RIGHT_SPEED M2_SPEED_PIN
#define MOTOR_RIGHT_DIRECTION M2_DIRECTION_PIN
#define MOTOR_LEFT_SPEED M1_SPEED_PIN
#define MOTOR_LEFT_DIRECTION M1_DIRECTION_PIN

void setup() {
  pinMode(MOTOR_RIGHT_DIRECTION, OUTPUT);
  pinMode(MOTOR_LEFT_DIRECTION, OUTPUT);
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
  digitalWrite(MOTOR_RIGHT_DIRECTION, !reverse);
  analogWrite(MOTOR_RIGHT_SPEED, speed);
}
void setMotorLeft(int speed, boolean reverse) {
  digitalWrite(MOTOR_LEFT_DIRECTION, !reverse);
  analogWrite(MOTOR_LEFT_SPEED, speed);
}

