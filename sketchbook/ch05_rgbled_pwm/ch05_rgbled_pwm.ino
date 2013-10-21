#define R_PIN 11 // RGB LED's Red pin
#define G_PIN 10 // RGB LED's Green pin
#define B_PIN 9 // RGB LED's Blue pin

#define VR_R_PIN A0 // variable resistor controling red
#define VR_G_PIN A1 // variable resistor controling green
#define VR_B_PIN A2 // variable resistor controling blue

void setup() {
}

void loop() {
  int s;
  int brightness;
  
  s = analogRead(VR_R_PIN);
  brightness = map(s, 0, 1023, 0, 255);
  analogWrite(R_PIN, brightness);
  
  s = analogRead(VR_G_PIN);
  brightness = map(s, 0, 1023, 0, 255);
  analogWrite(G_PIN, brightness);
  
  s = analogRead(VR_B_PIN);
  brightness = map(s, 0, 1023, 0, 255);
  analogWrite(B_PIN, brightness);
}

