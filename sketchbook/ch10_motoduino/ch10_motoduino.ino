// 一個馬達以兩個腳位操控
// 以digitalWrite控制轉向：正轉、逆轉
// 以analogWrite控制轉速，0停止，255最快
#define M1_SPEED_PIN 6 // 馬達M1的轉速
#define M1_DIRECTION_PIN 7 // 馬達M1的轉向
#define M2_SPEED_PIN 5 // 馬達M2的轉速
#define M2_DIRECTION_PIN 8 // 馬達M2的轉向

void setup() {
  // 腳位初始設定
  pinMode(M1_DIRECTION_PIN, OUTPUT);
  pinMode(M2_DIRECTION_PIN, OUTPUT);
}
void loop() {
  forward();
  delay(2000);
  backward();
  delay(2000);
  stop();
  delay(2000);
  turnRight();
  delay(2000);
  turnLeft();
  delay(2000);
}

// 假定馬達M1在車子右邊，馬達M2在車子左邊，
// 假定兩個馬達正轉會讓車子前進
void forward(){ // 兩個馬達都正轉，往前進
  digitalWrite(M1_DIRECTION_PIN, HIGH);
  digitalWrite(M2_DIRECTION_PIN, HIGH);
  analogWrite(M1_SPEED_PIN, 255);
  analogWrite(M2_SPEED_PIN, 255);
}
void backward(){ // 兩個馬達都逆轉，往後退
  digitalWrite(M1_DIRECTION_PIN, LOW);
  digitalWrite(M2_DIRECTION_PIN, LOW);
  analogWrite(M1_SPEED_PIN, 255);
  analogWrite(M2_SPEED_PIN, 255);
}
void turnRight(){ // 向右轉彎
  digitalWrite(M1_DIRECTION_PIN, HIGH);
  digitalWrite(M2_DIRECTION_PIN, HIGH);
  analogWrite(M1_SPEED_PIN, 255);
  analogWrite(M2_SPEED_PIN, 0);
}
void turnLeft(){ // 向左轉彎
  digitalWrite(M1_DIRECTION_PIN, HIGH);
  digitalWrite(M2_DIRECTION_PIN, HIGH);
  analogWrite(M1_SPEED_PIN, 0);
  analogWrite(M2_SPEED_PIN, 255);
}
void stop(){ // 停止
  analogWrite(M1_SPEED_PIN, 0);
  analogWrite(M2_SPEED_PIN, 0);
}

