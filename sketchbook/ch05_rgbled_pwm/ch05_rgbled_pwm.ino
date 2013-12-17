#define R_PIN 11 // RGB LED的紅針腳
#define G_PIN 10 // RGB LED的綠針腳
#define B_PIN 9 // RGB LED的藍針腳
#define VR_R_PIN A0 // 可變電阻，控制紅色
#define VR_G_PIN A1 // 可變電阻，控制綠色
#define VR_B_PIN A2 // 可變電阻，控制藍色

void setup() {
}
void loop() {
  int s;
  int brightness;
  
  s = analogRead(VR_R_PIN); // 讀取可變電阻的值
  brightness = map(s, 0, 1023, 0, 255); // 映射到PWM允許的範圍（0~255）
  analogWrite(R_PIN, brightness);
  
  s = analogRead(VR_G_PIN);
  brightness = map(s, 0, 1023, 0, 255);
  analogWrite(G_PIN, brightness);
  
  s = analogRead(VR_B_PIN);
  brightness = map(s, 0, 1023, 0, 255);
  analogWrite(B_PIN, brightness);
}

