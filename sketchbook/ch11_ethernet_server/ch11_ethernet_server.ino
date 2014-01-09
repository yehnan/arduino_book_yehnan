#include <SPI.h> // 以太網路擴充板透過SPI介面與Arduino板溝通
#include <Ethernet.h> // Ethernet程式庫
#define SERIAL_BAUDRATE 19200

// MAC實體位址，若無可自己隨意填入
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
// 區域網路IP位址，需根據組態設定
IPAddress ip(192, 168, 1, 177);
EthernetServer server(80); // Port 80是HTTP預設的連接埠號

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
   while(!Serial){
    ; // 等待開啟序列埠，Leonardo才需要
  }
  Ethernet.begin(mac, ip); // 初始化
  server.begin(); // 啟動伺服器
  Serial.println("server starting");
}
void loop() {
  EthernetClient client = server.available(); // 是否有客戶端連線
  if(client){
    Serial.println("new client");
    while(client.connected()){
      if(client.available()){
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println("Connection: close");
        client.println();
        client.println("<html>");
        client.println("<head>");
        client.println("<title>");
        client.println("Arduino station");
        client.println("</title>");
        client.println("</head>");
        client.println("<body>");
        client.println("Hello, world.<br/>");
        client.println("millis() is ");
        client.println(millis());
        client.println("<br/>IP address is: ");
        client.println(Ethernet.localIP());
        client.println("</body>");
        client.println("</html>");
        break;
      }
    }
    delay(1); // 讓瀏覽器有時間接收資料
    client.stop(); // 關閉連線:
    Serial.println("client disonnected");
  }
}

