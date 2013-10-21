#define SERIAL_BAUDRATE 19200
#define LED_PIN 11
#define PR_PIN A0 // photo resistor

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
}
 
void loop() {
  int r = analogRead(PR_PIN);

  // LED is brighter if environmental light is stronger
  int b = map(r, 0, 1023, 0, 255);
  
  // LED is brighter if environmental light is weaker
  // int b = map(r, 0, 1023, 255, 0);
  
  analogWrite(LED_PIN, b);
}

