#define SERIAL_BAUDRATE 19200
#define LED_PIN 11
#define FSR_PIN A0 // force sensitive resistor
 
void setup() {
  Serial.begin(SERIAL_BAUDRATE);
}
 
void loop() {
  int r = analogRead(FSR_PIN);

  // LED is brighter if force is stronger
  int b = map(r, 0, 1023, 0, 255);
  
  // LED is brighter if force is weaker
  // int b = map(r, 0, 1023, 255, 0);
  
  analogWrite(LED_PIN, b);
  
  Serial.println(r);
}

