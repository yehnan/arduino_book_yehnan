#include <SPI.h>
#include <Ethernet.h>
#define SERIAL_BAUDRATE 19200

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
// 想要連線的對象，IP或網址與埠號
char serverName[] = "www.google.com";
int port = 80;

EthernetClient client;
void setup() {
  Serial.begin(SERIAL_BAUDRATE);
   while (!Serial) {
    ; // 等待開啟序列埠，Leonardo才需要
  }
  Serial.println("Useing DHCP");
  if(Ethernet.begin(mac) == 0){
    Serial.println("Failed");
    while(true)
      ;
  }
  delay(1000); // 讓擴充板有時間初始化
  Serial.println("connecting...");
  if(client.connect(serverName, port)){
    Serial.println("connected"); // 連線成功 
    // 請求網頁
    client.println("GET /search?q=arduino HTTP/1.0");
    client.println();
  }
  else{ // 連線失敗
    Serial.println("connection failed");
  }
}
void loop() {
  if(client.available()){
    char c = client.read(); // 伺服器送來的資料
    Serial.print(c); // 輸出到序列埠監控視窗
  }

  if(!client.connected()){ // 斷線了
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    while(true) // 不作事，進入無窮迴圈
      ;
  }
}

