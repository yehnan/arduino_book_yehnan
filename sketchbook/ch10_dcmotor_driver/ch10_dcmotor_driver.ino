#define SERIAL_BAUDRATE 19200
// 連接馬達的腳位
#define ENABLE_PIN 11 // 需具備PWM功能
#define Y1_PIN 10
#define Y2_PIN 9
#define VR_PIN A0 // 可變電阻

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  pinMode(Y1_PIN, OUTPUT);
  pinMode(Y2_PIN, OUTPUT);
}
void loop() {
  int vr = analogRead(A0); // 讀取可變電阻
  Serial.print("Variable Resistor input is ");
  Serial.print(vr);
  
  int speed;
  if(vr > 1023/2){ // 若往某方向旋轉超過一半
    speed = map(vr, 1023/2, 1023, 0, 255); // 映射出適當的PWM值
    setMotor(speed, true); // 讓馬達往某一方向轉
  }
  else{ // 若往另一方向旋轉超過一半
    speed = map(vr, 1023/2 - 1, 0, 0, 255); // 映射出適當的PWM值
    setMotor(abs(speed), false); // 讓馬達往另一方向轉
  }
}
// 設定馬達的速度（0~255）與旋轉方向
void setMotor(int speed, boolean reverse) {
  Serial.print(", Speed is ");
  Serial.print(speed);
  Serial.print(", reverse is ");
  Serial.println(reverse);
  analogWrite(ENABLE_PIN, speed);
  digitalWrite(Y1_PIN, !reverse); // 兩者準位相反，
  digitalWrite(Y2_PIN, reverse); // 便可控制馬達轉向
}

