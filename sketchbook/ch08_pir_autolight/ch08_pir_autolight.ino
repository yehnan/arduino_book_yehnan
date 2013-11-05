#define SERIAL_BAUDRATE 19200
#define PIR_PIN 2 // PIR模組的訊號腳位
#define LED_PIN 13 // 燈光的腳位
#define PHOTORESISTOR_PIN A0 // 光敏電阻，偵測周圍光線強度
#define LIGHT_DURATION 10000 // millisecond，偵測到人體移動後，燈光點亮的延續時間
#define DARK_THRESHOLD 300 // 判斷周圍光線夠不夠強的臨界值

unsigned long lightOffTime; // 到此時間時便應關閉燈光
boolean pirStatus = LOW; // 記錄PIR模組訊號輸出的狀態
void setup(){
  Serial.begin(SERIAL_BAUDRATE);
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  lightOffTime = millis();
}
void loop(){
  int dark = analogRead(A0);
  if(dark < DARK_THRESHOLD){
    boolean s = digitalRead(PIR_PIN); // 讀取PIR模組狀態
    unsigned long t = millis();
    if(s){
      digitalWrite(LED_PIN, HIGH);
      lightOffTime = t + LIGHT_DURATION;
    }
    else{
      if(t > lightOffTime){
        digitalWrite(LED_PIN, LOW);
      }
    }
  }
  else{
    digitalWrite(LED_PIN, LOW);
  }
}

