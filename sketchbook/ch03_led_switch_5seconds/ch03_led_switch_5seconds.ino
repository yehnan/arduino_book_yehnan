#include <Bounce.h>
#define SERIAL_BAUDRATE 19200
#define LED_PIN 11
#define SWITCH_PIN 7
#define DEBOUNCE_DELAY 50 // milliseconds
#define DURATION 5000 // milliseconds

Bounce bouncer = Bounce(SWITCH_PIN, DEBOUNCE_DELAY);

// 定義狀態機的可能狀態
typedef enum{
  S_OFF,
  S_OFF_NO_PRESS,
  S_ON,
  S_ON_PRESS
} State;
State state = S_OFF;

void updateLed(){
  if(state == S_OFF || state == S_OFF_NO_PRESS){
    digitalWrite(LED_PIN, LOW);
  }
  else if(state == S_ON || state == S_ON_PRESS){
    digitalWrite(LED_PIN, HIGH);
  }
  else{
    Serial.print("Error: in wrong state ");
    Serial.print(state);
  }
}
void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  pinMode(LED_PIN, OUTPUT);
  
  updateLed();
}

unsigned long time_previous;
void loop() {
  bouncer.update();
  boolean switch_status = bouncer.read();
  
  // 以switch述句根據狀態作相對應的動作
  switch(state){
    case S_OFF:
      if(switch_status == LOW){
        time_previous = millis();
        state = S_OFF_NO_PRESS;
      }
    break;
    case S_OFF_NO_PRESS:
      if(switch_status == LOW){
        unsigned long time_current = millis();
        if(time_current - time_previous >= DURATION){
          state = S_ON;
        }
      }
      else{
        state = S_OFF;
      }
    break;
    case S_ON:
      if(switch_status == HIGH){
        time_previous = millis();
        state = S_ON_PRESS;
      }
    break;
    case S_ON_PRESS:
      if(switch_status == HIGH){
        unsigned long time_current = millis();
        if(time_current - time_previous >= DURATION){
          state = S_OFF;
        }
      }
      else{
        state = S_ON;
      }
    break;
  }
  // 前面更新狀態state後，接下來只要根據state更新LED即可
  updateLed();
}

