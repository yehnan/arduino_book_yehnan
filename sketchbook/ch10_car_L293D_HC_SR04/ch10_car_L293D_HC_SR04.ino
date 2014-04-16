#include <Ultrasonic.h>
#define TRIG_PIN 4
#define ECHO_PIN 5
// 定義多近才算見到障礙物
#define RANGE_THRESHOLD 20 // 公分
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

#define SPEED 200 // 0~255

// 建立代表超音波感測器的物件
Ultrasonic s(TRIG_PIN, ECHO_PIN);
void setup() {
  pinMode(MOTOR_RIGHT_FORWARD, OUTPUT);
  pinMode(MOTOR_RIGHT_BACKWARD, OUTPUT);
  pinMode(MOTOR_LEFT_FORWARD, OUTPUT);
  pinMode(MOTOR_LEFT_BACKWARD, OUTPUT);
  randomSeed(analogRead(A0));
}
boolean checkObstacle(){
  float ms = s.timing();
  float cm = s.convert(ms, Ultrasonic::CM);
  return cm < RANGE_THRESHOLD;
}
void loop() {
  if(checkObstacle()){ // 見到障礙物了
    stop(); // 先停下來
    int d = random(2); // 亂數決定旋轉方向
    if(d == 0)
      rotateRight(SPEED);
    else
      rotateLeft(SPEED);
    while(checkObstacle()){
      // 仍有障礙物，就繼續旋轉
    }
    delay(300); // 再多旋轉一小段時間
    stop(); // 停止
  }
  else{
    forward(SPEED); // 平常無事就前進
  }
}
void forward(int speed){ // 兩個馬達都正轉，往前進
  setMotorRight(speed, false);
  setMotorLeft(speed, false);
}
void backward(int speed){ // 兩個馬達都逆轉，往後退
  setMotorRight(speed, true);
  setMotorLeft(speed, true);
}
void rotateRight(int speed){ // 原地向右旋轉
  setMotorRight(speed, true);
  setMotorLeft(speed, false);
}
void rotateLeft(int speed){ // 原地向左旋轉
  setMotorRight(speed, false);
  setMotorLeft(speed, true);
}
void turnRight(int speed){ // 向右轉彎
  setMotorRight(0, false);
  setMotorLeft(speed, false);
}
void turnLeft(int speed){ // 向左轉彎
  setMotorRight(speed, false);
  setMotorLeft(0, false);
}
void moveAndTurnRight(int speed){ // 邊前進邊向右轉彎
  setMotorRight(speed/2, false);
  setMotorLeft(speed, false);
}
void moveAndTurnLeft(int speed){ // 邊前進邊向左轉彎
  setMotorRight(speed, false);
  setMotorLeft(speed/2, false);
}
void stop(){ // 停止
  setMotorRight(0, false);
  setMotorLeft(0, false);
}
// 設定馬達的速度（0~255）與轉向
void setMotorRight(int speed, boolean reverse) {
  if(speed <= 0)
    speed = 0;
  else if(255 < speed)
    speed = 255;
  analogWrite(MOTOR_RIGHT, speed);
  digitalWrite(MOTOR_RIGHT_FORWARD, !reverse);
  digitalWrite(MOTOR_RIGHT_BACKWARD, reverse);
}
void setMotorLeft(int speed, boolean reverse) {
  if(speed <= 0)
    speed = 0;
  else if(255 < speed)
    speed = 255;
  analogWrite(MOTOR_LEFT, speed);
  digitalWrite(MOTOR_LEFT_FORWARD, !reverse);
  digitalWrite(MOTOR_LEFT_BACKWARD, reverse);
}

