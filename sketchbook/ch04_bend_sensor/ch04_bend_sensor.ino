#define SERIAL_BAUDRATE 19200
#define LED_PIN 11
#define BS_PIN A0 // bend sensor
 
void setup() {
  Serial.begin(SERIAL_BAUDRATE);
}
 
void loop() {
  int r = analogRead(BS_PIN);

  // LED is brighter if bend sensor is straight(no bending)
  // you should change the range according to your own bend sensor
  int b = constrain(r, 180, 320);
  b = map(b, 180, 320, 0, 255);
  
  analogWrite(LED_PIN, b);
  
  Serial.println(r);
}

