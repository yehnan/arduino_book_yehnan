#include <IRremote.h>
#define SERIAL_BAUDRATE 19200
#define IR_RECEIVER_PIN 2

IRrecv irrecv(IR_RECEIVER_PIN);
decode_results results;

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  irrecv.blink13(true);
  irrecv.enableIRIn();
}

void loop() {
  if(irrecv.decode(&results)){
    Serial.print("Value is ");
    Serial.print(results.value, HEX);
    Serial.print(", ");
    Serial.print(results.bits);
    Serial.print(" bits, decode_type is ");
    Serial.println(results.decode_type);
    irrecv.resume();
  }
}
