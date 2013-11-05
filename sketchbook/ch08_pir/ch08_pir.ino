#define SERIAL_BAUDRATE 19200
#define PIR_PIN 2 // PIR模組的訊號腳位
#define LED_PIN 13

boolean pirStatus = LOW; // 記錄PIR模組訊號輸出的狀態
// 輸出PIR模組的偵測狀態，並且輸出millis()
void printStatusAndTime(){
  Serial.print("Status: ");
  Serial.print(pirStatus);
  Serial.print(", time: ");
  Serial.println(millis());
}
void setup(){
  Serial.begin(SERIAL_BAUDRATE);
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  printStatusAndTime();
}
void loop(){
  boolean s = digitalRead(PIR_PIN); // 讀取PIR模組狀態
  digitalWrite(LED_PIN, s); //以該狀態控制LED燈
  if(pirStatus != s){ // 若狀態改變了，才輸出序列埠
    pirStatus = s;
    printStatusAndTime();
  }
}

