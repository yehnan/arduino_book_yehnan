#include <SoftwareSerial.h>
#define SERIAL_BAUDRATE 38400
#define BT_SERIAL_BAUDRATE 38400
#define RX_PIN 10
#define TX_PIN 11
#define KEY_PIN 12

SoftwareSerial mySerial(RX_PIN, TX_PIN); // RX, TX

void setup() {
  pinMode(KEY_PIN, OUTPUT);
  Serial.begin(SERIAL_BAUDRATE);
  while(!Serial){
  }
  Serial.println("Starting...s");
  
  mySerial.begin(BT_SERIAL_BAUDRATE);
  delay(100); // important!
  
  Serial.println("In AT Mode");
  digitalWrite(KEY_PIN, HIGH);
  delay(100);
  
  mySerial.println("AT");
  delay(100);
  waitAndPrintResponse();
  
  Serial.println("In Data Mode");
  digitalWrite(KEY_PIN, LOW);
}
void waitAndPrintResponse()
{
  while(mySerial.available()){
    Serial.write(mySerial.read());
  }
}
void loop() {
  if(mySerial.available()){
    Serial.write(mySerial.read());
  }
  if(Serial.available()){
    mySerial.write(Serial.read());
  }
}

