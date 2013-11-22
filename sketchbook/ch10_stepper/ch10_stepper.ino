#include <Stepper.h>
#define SERIAL_BAUDRATE 19200
// 連接步進馬達的腳位
#define IN1_PIN 12
#define IN2_PIN 11
#define IN3_PIN 10
#define IN4_PIN 9
#define STEPS 512 // 此步進馬達轉一圈需幾步
// 建立Stepper物件
Stepper motor(STEPS, IN1_PIN, IN2_PIN, IN3_PIN, IN4_PIN);

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);
  
  motor.setSpeed(30); // 設定轉動速度，單位是RPM
}
void loop() {
  if(Serial.available()) {
    int steps = Serial.parseInt(); // 將ASCII碼轉成int
    motor.step(steps); // 叫步進馬達旋轉該步數
    Serial.println(steps);
  }
}

