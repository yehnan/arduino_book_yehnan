#define LED_PIN 11
#define VR_PIN A0 // variable resistor

int brightness = 0;
int fadeAmount = 5;
int delayDuration = 10;

void setup() {
}

void loop() {
  brightness += fadeAmount;
  if(brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount ;
  }
  
  analogWrite(LED_PIN, brightness);
  delay(delayDuration);
  
  int v = analogRead(A0);
  delayDuration = map(v, 0, 1023, 1, 50);
}

