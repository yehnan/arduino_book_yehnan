#include <SoftwareSerial.h> // 軟體序列埠
#define SERIAL_BAUDRATE 38400 // 電腦USB埠與Arduino之間的序列介面
#define BT_SERIAL_BAUDRATE 38400 // Arduino與藍牙模組之間的序列介面
#define RX_PIN 10
#define TX_PIN 11
#define KEY_PIN 12

SoftwareSerial mySerial(RX_PIN, TX_PIN); // RX, TX

void setup() {
  pinMode(KEY_PIN, OUTPUT);
  Serial.begin(SERIAL_BAUDRATE); // 初始化
  while(!Serial){
    // 等待Leonardo的虛擬序列埠
  }
  Serial.println("Starting...");
  
  mySerial.begin(BT_SERIAL_BAUDRATE); // 初始化
  delay(100); // 重要，稍微等一小段時間
  
  Serial.println("In AT Mode");
  digitalWrite(KEY_PIN, HIGH); // 高電位時可下AT指令
  delay(100);
  
  mySerial.println("AT"); // 下達"AT"指令
  delay(100);
  waitAndPrintResponse(); // 取得回應
  
  Serial.println("In Data Mode");
  digitalWrite(KEY_PIN, LOW); // 進入一般模式
  // 但若尚未配對，此時仍可下達AT指令
}
void waitAndPrintResponse()
{
  // 等待藍牙模組回傳訊息
  while(mySerial.available()){
    Serial.write(mySerial.read());
  }
}
void loop() {
  // 從藍牙模組傳來的資料，轉傳給序列埠監控視窗
  if(mySerial.available()){
    Serial.write(mySerial.read());
  }
  // 從序列埠監控視窗傳來的資料，轉傳給藍牙模組
  if(Serial.available()){
    mySerial.write(Serial.read());
  }
}

