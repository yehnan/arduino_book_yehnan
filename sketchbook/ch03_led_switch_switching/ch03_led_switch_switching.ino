#define LED_PIN 11
#define SWITCH_PIN 7

boolean led_status;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT);
  
  led_status = LOW;
  digitalWrite(LED_PIN, led_status);
}

void loop() {
  boolean switch_status = digitalRead(SWITCH_PIN);
  if(switch_status == HIGH){
    led_status = led_status == HIGH ? LOW : HIGH;
    digitalWrite(LED_PIN, led_status);
  }
}

