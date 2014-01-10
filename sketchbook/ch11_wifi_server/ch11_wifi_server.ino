#include <SPI.h> // 溝通介面是SPI
// 匯入Adafruit WiFi擴充板需要的標頭檔
#include <Adafruit_CC3000.h>
#include "utility/debug.h"
#include "utility/socket.h"
#define SERIAL_BAUDRATE 19200
// 定義連接腳位
#define ADAFRUIT_CC3000_IRQ 3 // 必須是支援中斷功能的腳位
#define ADAFRUIT_CC3000_VBAT 5 // 控制電源的腳位
#define ADAFRUIT_CC3000_CS 10 // 連接CC3000的CS的腳位
// 其他SPI腳位則要視使用的Arduino開發板而定
// 以Uno為例，MOSI(11)、MISO(12)、SCK(13)

// 建立Adafruit_CC3000物件，代表WiFi網路晶片
Adafruit_CC3000 cc3000 = Adafruit_CC3000(
  ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
  SPI_CLOCK_DIV2); // 最後參數是時脈

// 請根據您的無線路由器，填入底下設定
//#define WLAN_SSID "myNetwork" // 無線網路的名稱（SSID）
//#define WLAN_PASS "myPassword" // 密碼
#define WLAN_SSID       "N10U"
#define WLAN_PASS       "yn0933!@"
// 加密方式：WLAN_SEC_UNSEC、WLAN_SEC_WEP、WLAN_SEC_WPA、WLAN_SEC_WPA2
#define WLAN_SECURITY WLAN_SEC_WPA2 

#define LISTEN_PORT 7 // ECHO協定預設使用連接埠7
Adafruit_CC3000_Server echoServer(LISTEN_PORT); // 建立ECHO伺服器

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  Serial.println("Initializing CC3000...");
  if(!cc3000.begin()){ // 初始化CC3000
    Serial.println("begin() failed!"); // 失敗
    while(1) // 進入無窮迴圈
      ;
  }
  // 連接無線路由器（AP）
  if(!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)){
    Serial.println("AP connection failed!"); // 失敗
    while(1) // 進入無窮迴圈
      ;
  }
  Serial.println("AP connected."); // 連接無線網路AP成功
  while(!cc3000.checkDHCP()){ // 以DHCP取得網路組態
    delay(100); // 等待一段時間再嘗試
  }
  // 顯示網路組態，IP位址、閘道器、DNS伺服器、等等
  while(!displayConnectionDetails()){
    delay(1000);
  }
  
  echoServer.begin(); // 啟動ECHO伺服器，開始聆聽接受客戶端連線
  Serial.println("Listening for connections...");
}
void loop() {
  // 有連線時便可取得代表客戶端的物件
  Adafruit_CC3000_ClientRef client = echoServer.available();
  if(client){
     if(client.available() > 0){ // 檢查有無資料
       // 收到什麼就回送什麼
       uint8_t ch = client.read(); // 讀取
       client.write(ch); // 回傳
     }
  }
}
bool displayConnectionDetails(){
  uint32_t ipAddress, netmask, gateway, dhcpserv, dnsserv;
  if(!cc3000.getIPAddress(&ipAddress, &netmask, &gateway, &dhcpserv, &dnsserv)){
    Serial.println("Unable to get connection details!");
    return false;
  }
  else{
    Serial.print("IP address: "); // IP位址
    cc3000.printIPdotsRev(ipAddress); Serial.println();
    Serial.print("Netmask: "); // 子網路遮罩
    cc3000.printIPdotsRev(netmask); Serial.println();
    Serial.print("Gateway: "); // 閘道器
    cc3000.printIPdotsRev(gateway); Serial.println();
    Serial.print("DHCP server: "); // DHCP伺服器位址
    cc3000.printIPdotsRev(dhcpserv); Serial.println();
    Serial.print("DNS server: "); // DNS伺服器位址
    cc3000.printIPdotsRev(dnsserv); Serial.println();
    return true;
  }
}

