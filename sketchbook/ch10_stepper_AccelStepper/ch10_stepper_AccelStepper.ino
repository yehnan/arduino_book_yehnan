#include <AccelStepper.h>
#define SERIAL_BAUDRATE 19200
// 連接步進馬達的腳位
#define IN1_PIN 12
#define IN2_PIN 11
#define IN3_PIN 10
#define IN4_PIN 9

AccelStepper stepper(AccelStepper::FULL4WIRE, IN1_PIN, IN2_PIN, IN3_PIN, IN4_PIN);

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  stepper.setMaxSpeed(80 * 512 / 60);
  stepper.setAcceleration(100);
}
void loop() {
  stepper.run();
  if(Serial.available()) {
    int s = Serial.parseInt(); // 將ASCII碼轉成int
    stepper.move(s);
    Serial.println(s);
  }
}

