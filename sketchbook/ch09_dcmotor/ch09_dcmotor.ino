#define SERIAL_BAUDRATE 19200
#define MOTOR_PIN 3

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
}

void loop() {
  for(int i = 0; i <= 255; i+=50){
    Serial.print(i);
    Serial.println(" / 255");
    analogWrite(MOTOR_PIN, i);
    delay(5000);
  }
}

