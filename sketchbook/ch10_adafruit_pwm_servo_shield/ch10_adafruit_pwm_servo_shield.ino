#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
// 定義脈衝寬度上下限，每個伺服馬達都不一樣，
// 此處以Tower Pro SG90為例
#define PW_LOWER_BOUND 500 // PW是Pulse Width脈衝寬度
#define PW_UPPER_BOUND 2400

// 這塊擴充板需要的設定
#define FREQ 50 // Hz，送出脈衝的頻率
#define RESOLUTION 4096 // 12位元
// 建立代表PWM/Servo擴充板的物件
Adafruit_PWMServoDriver shield = Adafruit_PWMServoDriver();
double pwTotal; // 儲存一個完整脈衝的總長度，高低電位的部份都包含

void setup() {
  shield.begin(); // 初始化並啟動
  shield.setPWMFreq(FREQ); // 設定發出PWM脈衝的頻率
  pwTotal = 1000000; // 1秒有1,000,000μs
  pwTotal /= FREQ; // 除以頻率，找出一次完整脈衝佔多長時間
}
// 參數n，第幾個伺服馬達，0~15
// 參數us，microsecond(μs)，脈衝寬度
void setPulseWidth(int n, double us){
  if(us < PW_LOWER_BOUND)
    us = PW_LOWER_BOUND;
  if(us > PW_UPPER_BOUND)
    us = PW_UPPER_BOUND;
  
  shield.setPWM(n, 0, us / pwTotal * RESOLUTION);
}
// 參數n，第幾個伺服馬達，0~15
// 參數angle，角度0~180，映射到脈衝寬度PW_LOWER_BOUND與PW_UPPER_BOUND
void setAngle(int n, double angle){
  if(angle < 0)
    angle = 0;
  if(angle > 180)
    angle = 180;
    
  double pw = map(angle, 0, 180, PW_LOWER_BOUND, PW_UPPER_BOUND);
  setPulseWidth(n, pw);
}
void loop() {
  int i;
  for(i = PW_LOWER_BOUND; i <= PW_UPPER_BOUND; i++){
    setPulseWidth(0, i);
  }
  delay(1000);
  for(i = PW_UPPER_BOUND; i >= PW_LOWER_BOUND; i--){
    setPulseWidth(0, i);
  }
  delay(1000);
  for(i = 0; i <= 180; i++){
    setAngle(0, i);
  }
  delay(1000);
  for(i = 180; i >= 0; i--){
    setAngle(0, i);
  }
  delay(1000);
}

