#include <Wire.h>
#include <Adafruit_MotorShield.h>
#define STEPS 512 // 一周步數，請根據您的步進馬達修改此值
// 建立代表馬達控制板的物件
Adafruit_MotorShield motorShield = Adafruit_MotorShield(); 
// 取得代表步進馬達的物件（是個指標）
// 參數一是一周有幾步，參數二則代表連接到哪個端子台，
// 1是M1與M2，2是M3與M4
Adafruit_StepperMotor *stepper = motorShield.getStepper(STEPS, 1);

void setup() {
  motorShield.begin(); // 啟用並初始化
  stepper->setSpeed(20);  // 設定轉速，單位是RPM   
}
void loop() {
  // 呼叫step方法命令步進馬達轉動，有三個參數
  // 參數一是步數
  // 參數二控制轉向，FORWARD與BACKWARD
  // 參數三是步進模式：SINGLE、DOUBLE、INTERLEAVE、MICROSTEP.
  stepper->step(STEPS/2, FORWARD, SINGLE); delay(500);
  stepper->step(STEPS/2, BACKWARD, SINGLE); delay(500);
  stepper->step(STEPS/2, FORWARD, DOUBLE); delay(500);
  stepper->step(STEPS/2, BACKWARD, DOUBLE); delay(500);
  stepper->step(STEPS/2, FORWARD, INTERLEAVE); delay(500);
  stepper->step(STEPS/2, BACKWARD, INTERLEAVE); delay(500);
  stepper->step(STEPS/4, FORWARD, MICROSTEP); delay(500);
  stepper->step(STEPS/4, BACKWARD, MICROSTEP); delay(500);
}

