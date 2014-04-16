// L293D連接Arduino的腳位定義
#define E12_PIN 10 // 需具備PWM功能
#define Y1_PIN 11
#define Y2_PIN 12
#define E34_PIN 9 // 需具備PWM功能
#define Y3_PIN 8
#define Y4_PIN 7

// 輪子馬達的兩極所連接的腳位定義
// 假定當電流從FORWARD流向BACKWARD，輪子往前轉，車子往前走
// 假定當電流從BACKWARD流向FORWARD，輪子往後轉，車子往後退
#define MOTOR_RIGHT E34_PIN
#define MOTOR_RIGHT_FORWARD Y3_PIN
#define MOTOR_RIGHT_BACKWARD Y4_PIN
#define MOTOR_LEFT E12_PIN
#define MOTOR_LEFT_FORWARD Y1_PIN
#define MOTOR_LEFT_BACKWARD Y2_PIN

void setup() {
  pinMode(MOTOR_RIGHT_FORWARD, OUTPUT);
  pinMode(MOTOR_RIGHT_BACKWARD, OUTPUT);
  pinMode(MOTOR_LEFT_FORWARD, OUTPUT);
  pinMode(MOTOR_LEFT_BACKWARD, OUTPUT);
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
  analogWrite(MOTOR_RIGHT, speed);
  digitalWrite(MOTOR_RIGHT_FORWARD, !reverse);
  digitalWrite(MOTOR_RIGHT_BACKWARD, reverse);
}
void setMotorLeft(int speed, boolean reverse) {
  analogWrite(MOTOR_LEFT, speed);
  digitalWrite(MOTOR_LEFT_FORWARD, !reverse);
  digitalWrite(MOTOR_LEFT_BACKWARD, reverse);
}

