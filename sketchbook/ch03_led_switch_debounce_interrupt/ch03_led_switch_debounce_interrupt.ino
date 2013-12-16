#define SERIAL_BAUDRATE 19200
#define LED_PIN 11
// Uno: int.0 is pin 2, int.1 is pin 3
// Leonardo: int.0 is pin 3, int.1 is pin 2, int.2 is pin 0, int.3 is pin 1, int.4 is pin 7
#define SWITCH_INTERRUPT_NUM 0
#define DEBOUNCE_DELAY 200 // milliseconds

// 回呼函式裡會存取的變數應加上volatile
volatile boolean led_status; 
unsigned long time_previous;

// 中斷發生時（觸發）呼叫的函式
void switchChanged(){
  unsigned long time_current = millis();
  if((time_current - time_previous) > DEBOUNCE_DELAY){
    time_previous = time_current;
    led_status = !led_status;
  }
}
void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  pinMode(LED_PIN, OUTPUT);
  
  led_status = LOW;
  digitalWrite(LED_PIN, led_status);
  
  // 使用外部中斷，監看腳位的狀態變化
  attachInterrupt(SWITCH_INTERRUPT_NUM, switchChanged, RISING);
}
void loop() {
  digitalWrite(LED_PIN, led_status);
}

