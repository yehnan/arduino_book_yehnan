#include <Servo.h>
#define SERIAL_BAUDRATE 19200
#define SERVO_PIN 9
#define FEEDBACK_PIN A0
#define FEEDBACK_TOLERANCE 3

void pf(const char *fmt, ... ){
    char tmp[128]; // 最多128個字元，含NULL
    va_list args;
    va_start(args, fmt);
    vsnprintf(tmp, 128, fmt, args);
    va_end(args);
    Serial.print(tmp);
}

Servo s; // 建立Servo物件
int feedbackMin; // 最大回饋值
int pwMin; // 最長脈衝寬度
int feedbackMax; // 最小回饋值
int pwMax; // 最短脈衝寬度
int fbs[19]; // 記錄角度0、10、20、...、180的回饋值

// 找出pwMin與pwMax
void findPulseWidth(){ // 假設角度與回饋值呈線性關係
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
  feedbackMax = fb100;
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
  feedbackMin = fb80;
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
  pwMin = float(angleMin) / 180 
    * (MAX_PULSE_WIDTH-MIN_PULSE_WIDTH) 
    + MIN_PULSE_WIDTH;
  pwMax = float(angleMax) / 180 
    * (MAX_PULSE_WIDTH-MIN_PULSE_WIDTH) 
    + MIN_PULSE_WIDTH;
  pf("min pulse width is %d, max pulse width is %d\n", pwMin, pwMax);
}
void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  s.attach(SERVO_PIN);
  // 先使用Servo程式庫預設的脈衝寬度上下限
  findPulseWidth(); // 找出此伺服馬達可允許的範圍
  s.detach();
  s.attach(SERVO_PIN, pwMin, pwMax); // 重新連接
  for(int i = 0; i <= 18; i+=1){ // 記錄角度0~180的回饋值
    s.write(i * 10); // 以10度為間隔
    delay(300);
    fbs[i] = analogRead(FEEDBACK_PIN);
    pf("degree %d, feedback %d\n", i*10, fbs[i]);
  }
}
// 移動到指定的位置（角度，0~180），然後才回傳
void moveTo(int angle){
  s.write(angle);
  int i = angle / 10;
  int fb = map(angle, i*10, (i+1)*10, fbs[i], fbs[i+1]);
  while(abs(analogRead(FEEDBACK_PIN) - fb) > FEEDBACK_TOLERANCE){
    // 直到回饋值與預想的回饋值相差少於誤差容忍範圍內
    // 然後才跳出迴圈，回傳
  }
}
// 回傳現在的位置（角度），0~180
int getAngle(){
  int fb = analogRead(FEEDBACK_PIN); // 根據回饋值，推算出角度
  int i;
  for(i = 1; i <= 18; i++){
    if(fb < fbs[i]){
      break;
    }
  }
  return map(fb, fbs[i-1], fbs[i], (i-1)*10, i*10);
}
void loop() { // 讓馬達轉過來轉過去，不使用delay函式
  int i;
  for(i = 0; i <= 180; i += 10){
    moveTo(i);
    pf("after moveTo(%d), angle is %d\n", i, getAngle());
  }
  for(i = 170; i > 0; i -= 10){
    moveTo(i);
    pf("after moveTo(%d), angle is %d\n", i, getAngle());
  }
}

