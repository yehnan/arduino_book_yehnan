#define LED_PIN 11
#define SWITCH_PIN 7
#define SERIAL_BAUDRATE 19200
#define DEBOUNCE_DELAY 200 // milliseconds

boolean led_status;
unsigned long time_previous;

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  pinMode(LED_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT);
  
  led_status = LOW;
  digitalWrite(LED_PIN, led_status);
}

void updateLed(){
  unsigned long time_current = millis();
  if((time_current - time_previous) > DEBOUNCE_DELAY){
    time_previous = time_current;
  
    led_status = !led_status;
    digitalWrite(LED_PIN, led_status);
    Serial.println(led_status);
  }
}

void loop() {
  boolean switch_status = digitalRead(SWITCH_PIN);
  if(switch_status == HIGH){
    updateLed();
  }
}

