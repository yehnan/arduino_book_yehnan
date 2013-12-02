#include <Ultrasonic.h>
#define SERIAL_BAUDRATE 19200
#define TRIG_PIN 4
#define ECHO_PIN 5

// 建立代表超音波感測器的物件
Ultrasonic s(TRIG_PIN, ECHO_PIN);

void setup(){
  Serial.begin(SERIAL_BAUDRATE);
}
void loop(){
  float ms = s.timing(); // microsecond，毫秒
  float cm = s.convert(ms, Ultrasonic::CM); // centimeter，公分
  float in = s.convert(ms, Ultrasonic::IN); // inch，英吋
  
  Serial.print(ms);
  Serial.print(" ms, ");
  Serial.print(cm);
  Serial.print(" cm, ");
  Serial.print(in);
  Serial.println(" inch, ");
  delay(1000);
}

