#define SERIAL_BAUDRATE 19200
#define MIC_PIN A0 // 麥克風
#define VOLUME_HIGH_LEVEL 300 // 超過此值便當做有高音量
void setup() {
  Serial.begin(SERIAL_BAUDRATE);
}

int count = 0; // 計算收到幾次的高音量
void loop() {
  int mic = analogRead(MIC_PIN); // 讀取麥克風輸出
  if(mic >= VOLUME_HIGH_LEVEL){
    count++;
    Serial.print("mic is ");
    Serial.print(mic);
    Serial.print(", count is ");
    Serial.println(count);
  }
}

