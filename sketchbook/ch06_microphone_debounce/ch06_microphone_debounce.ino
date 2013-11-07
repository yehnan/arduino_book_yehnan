#define MIC_PIN A0 // 麥克風
#define LED_PIN 13 // 燈光
#define VOLUME_HIGH_LEVEL 300 // 超過此值便當做有高音量
#define DEBOUNCE_DELAY 50 // 除彈跳的延遲時間
unsigned long time_previous;
boolean ledStatus = LOW;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledStatus);
  time_previous = millis();
}
void loop() {
  int mic = analogRead(MIC_PIN); // 讀取麥克風輸出
  if(mic >= VOLUME_HIGH_LEVEL){ // 若超過此音量
    unsigned long time_current = millis();
    if(time_current - time_previous > DEBOUNCE_DELAY){ // 已逾時
      time_previous = time_current;
      ledStatus = !ledStatus; // 切換LED明滅
      digitalWrite(LED_PIN, ledStatus);
    }
  }
}

