#define SERIAL_BAUDRATE 19200
#define LED_PIN 11
#define PR_PIN A0 // photo resistor
#define THRESHOLD 300
#define VOLTAGE 5

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  pinMode(LED_PIN, OUTPUT);
}
 
void loop() {
  int r = analogRead(PR_PIN);
  float v = float(r) / 1023 * VOLTAGE;

  if(r > THRESHOLD){
    digitalWrite(LED_PIN, LOW);
  }
  else{
    digitalWrite(LED_PIN, HIGH);
  }

  Serial.print("A0 reading is: ");
  Serial.print(r);
  Serial.print(", voltage is ");
  Serial.println(v);
  
  delay(1000);
}

