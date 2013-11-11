#include <Servo.h>
#define SERIAL_BAUDRATE 19200
#define SERVO_PIN 9
#define FEEDBACK_PIN A0

Servo s; // 建立Servo物件
void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  s.attach(SERVO_PIN); // 連接伺服馬達，開始輸出脈衝訊號
}
void pf(const char *fmt, ... ){
    char tmp[128]; // 最多128個字元，含NULL
    va_list args;
    va_start(args, fmt);
    vsnprintf(tmp, 128, fmt, args);
    va_end(args);
    Serial.print(tmp);
}
// 假設花角度與回饋值呈線性關係
void loop() {
  int fb80, fb90, fb100; // fb是feedback回饋的縮寫
  // 先取得角度80、90、100的回饋值，作為參考
  s.write(90);
  delay(300);
  fb90 = analogRead(FEEDBACK_PIN);
  s.write(80);
  delay(300);
  fb80 = analogRead(FEEDBACK_PIN);
  s.write(100);
  delay(300);
  fb100 = analogRead(FEEDBACK_PIN);
  
  // 逐步加大轉動角度，檢查回饋值是否符合比例
  // 找出最大可達角度
  int feedbackMax = fb100;
  int angleMax = 100;
  pf("degree 90, feedback %d\n", fb90);
  pf("degree 100, feedback %d\n", fb100);
  for(int a = angleMax+10; a <= 180; a += 10){
    s.write(a);
    delay(300);
    int v = analogRead(FEEDBACK_PIN);
    pf("degree %d, feedback %d\n", a, v);
    // 以100度與90度的回饋差值作為基準
    float r = float(v - feedbackMax) / float(fb100 - fb90);
    if(0.8 <= abs(r) && abs(r) <= 1.2){ // 比例若介於誤差範圍內
      angleMax = a;
      feedbackMax = v;
    }
    else{
      break;
    }
  }
  pf("max degree %d, feedback %d\n", angleMax, feedbackMax);
  
  // 逐步減小轉動角度，檢查回饋值是否符合比例
  // 找出最小可達角度
  int feedbackMin = fb80;
  int angleMin = 80;
  pf("degree 90, feedback %d\n", fb90);
  pf("degree 80, feedback %d\n", fb80);
  for(int a = angleMin - 10; a >= 0; a -= 10){
    s.write(a);
    delay(300);
    int v = analogRead(FEEDBACK_PIN);
    pf("degree %d, feedback %d\n", a, v);
    // 以90度與80度的回饋差值作為基準
    float r = float(feedbackMin - v) / float(fb90 - fb80);
    if(0.8 <= abs(r) && abs(r) <= 1.2){ // 比例若介於誤差範圍內
      angleMin = a;
      feedbackMin = v;
    }
    else{
      break;
    }
  }
  pf("min degree %d, feedback %d\n", angleMin, feedbackMin);
  
  // 推算出可行脈衝寬度的上下限
  int pwMin = float(angleMin) / 180 * (MAX_PULSE_WIDTH-MIN_PULSE_WIDTH) + MIN_PULSE_WIDTH;
  int pwMax = float(angleMax) / 180 * (MAX_PULSE_WIDTH-MIN_PULSE_WIDTH) + MIN_PULSE_WIDTH;
  pf("min pulse width is %d, max pulse width is %d\n", pwMin, pwMax);

  delay(3000);
}

