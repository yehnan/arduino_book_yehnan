#define SERIAL_BAUDRATE 19200
#define LED_PIN 11
#define SWITCH_PIN 7
#define DEBOUNCE_DELAY 200 // milliseconds

boolean led_status;
unsigned long time_previous; // 記錄millis函式回傳的時間

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  pinMode(LED_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT);
  
  led_status = LOW;
  digitalWrite(LED_PIN, led_status);
}
void updateLed(){
  unsigned long time_current = millis();
  // 若這次與上次相差超過DEBOUNCE_DELAY，就切換LED狀態
  if((time_current - time_previous) > DEBOUNCE_DELAY){
    time_previous = time_current;
  
    led_status = !led_status; // 切換狀態
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

