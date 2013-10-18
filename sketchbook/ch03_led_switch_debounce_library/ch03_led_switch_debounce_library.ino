#include <Bounce.h>

#define LED_PIN 11
#define SWITCH_PIN 7
#define SERIAL_BAUDRATE 19200
#define DEBOUNCE_DELAY 50 // milliseconds

Bounce bouncer = Bounce(SWITCH_PIN, DEBOUNCE_DELAY);
boolean led_status;

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  pinMode(LED_PIN, OUTPUT);
  
  led_status = LOW;
  digitalWrite(LED_PIN, led_status);
}

void loop() {
  if(bouncer.update() == true && bouncer.read() == HIGH){
    led_status = !led_status;
    digitalWrite(LED_PIN, led_status);
  }
}

