#define LED_PIN 11
#define VR_PIN A0 // 可變電阻（variable resistor）

int brightness = 0; // 亮度
int fadeAmount = 5; // 每次調整多少
int delayDuration = 10; // 隔多久調整一次

void setup() {
}
void loop() {
  brightness += fadeAmount;
  if(brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount ;
  }
  
  analogWrite(LED_PIN, brightness);
  delay(delayDuration);
  
  int v = analogRead(A0); // 可變電阻控制呼吸燈簗按變化的速率
  delayDuration = map(v, 0, 1023, 1, 50);
}

