#include <IRremote.h>
#define SERIAL_BAUDRATE 19200
// IRremote needs specific pin to send IR signals
// Uno uses 3, Leonardo uses 13, more in IRremoteInt.h
IRsend irsend;
void setup() {
  Serial.begin(SERIAL_BAUDRATE);
}
void loop() {
  byte d;
  if( (d = Serial.read()) != -1) {
    unsigned long v = 0x0;
    switch(d){
      case '1':
        v = 0x77E14050;
      break;
      case '2':
        v = 0x77E12050;
      break;
      case '3':
        v = 0x77E1D050;
      break;
      case '4':
        v = 0x77E1B050;
      break;
      case '5':
        v = 0x77E1E050;
      break;
      case '6':
        v = 0x77E11050;
      break;
    }
   
    if(v != 0x0){
      Serial.print("read ");
      Serial.print(d);
      Serial.print(", IR send ");
      Serial.println(v, HEX);
      irsend.sendNEC(v, 32);
    }
  }
}
