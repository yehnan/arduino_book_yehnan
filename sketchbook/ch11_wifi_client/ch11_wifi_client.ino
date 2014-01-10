#include <SPI.h> // 溝通介面是SPI
// 匯入Adafruit WiFi擴充板需要的標頭檔
#include <Adafruit_CC3000.h>
#include <ccspi.h>
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

Adafruit_CC3000_Client client; // 建立客戶端物件

const unsigned long connectTimeout  = 15L * 1000L; // Max time to wait for server connection
const unsigned long responseTimeout = 15L * 1000L; // Max time to wait for data from server

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  Serial.println("Initializing CC3000...");
  if(!cc3000.begin()){ // 初始化CC3000
    Serial.println("begin() failed!"); // 失敗
    while(1) // 進入無窮迴圈
      ;
  }  
  Serial.println("Deleting old connection profiles");
  if(!cc3000.deleteProfiles()){ // 刪除舊的組態設定
    Serial.println(F("Failed!"));
    while(1)
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
}
void loop() {
  unsigned long t = queryTime(); // 取得時間
  Serial.print("Current UNIX time: ");
  Serial.print(t);
  Serial.println(" seconds since 1/1/1970 UTC");
  printTime(t); // 以易讀易懂的格式輸出
  
  // 注意，不該太常查詢時間，其實一天校準一次就夠了
  delay(60000); // 60秒
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
// 向NTP伺服器查詢時間
unsigned long queryTime(void){ 
  uint8_t buf[48];
  unsigned long ip, startTime, t = 0L;
  Serial.println("Locating time server...");
  // pool.ntp.org含有多組NTP伺服器，分攤負擔
  // 查詢IP位址
  if(cc3000.getHostByName("pool.ntp.org", &ip)) {
    static const char PROGMEM
      timeReqA[] = {227,  0,  6, 236},
      timeReqB[] = { 49, 78, 49,  52};

    Serial.println("Attempting connection...");
    startTime = millis();
    do{
      client = cc3000.connectUDP(ip, 123); // 試著連線
    }while((!client.connected()) &&
            ((millis() - startTime) < connectTimeout));

    if(client.connected()){
      Serial.print(F("connected!\r\nIssuing request..."));

      // Assemble and issue request packet
      memset(buf, 0, sizeof(buf));
      memcpy_P(buf, timeReqA, sizeof(timeReqA));
      memcpy_P(&buf[12], timeReqB, sizeof(timeReqB));
      client.write(buf, sizeof(buf));

      Serial.print("Awaiting response...");
      memset(buf, 0, sizeof(buf));
      startTime = millis();
      while((!client.available()) &&
            ((millis() - startTime) < responseTimeout))
        ;
      if(client.available()){
        client.read(buf, sizeof(buf));
        t = (((unsigned long)buf[40] << 24) |
             ((unsigned long)buf[41] << 16) |
             ((unsigned long)buf[42] <<  8) |
              (unsigned long)buf[43]) - 2208988800UL;
      }
      client.close(); // 關閉連線
    }
  }
  if(!t) 
    Serial.println("Error");
  else
    Serial.println("OK");
  return t;
}

#define SECONDS_FROM_1970_TO_2000 946684800
// 每月含有的天數
const unsigned char daysInMonth [] PROGMEM = {31,28,31,30,31,30,31,31,30,31,30,31};
// 以易懂的格式輸出時間日期
void printTime(unsigned long t){
  unsigned char yOff, m, d, hh, mm, ss;
  t -= SECONDS_FROM_1970_TO_2000; // 改從2000開始起算
  
  ss = t % 60;
  t /= 60;
  mm = t % 60;
  t /= 60;
  hh = t % 24;
  uint16_t days = t / 24;
  uint8_t leap;
  for(yOff = 0; ;yOff++){ // 潤年
      leap = yOff % 4 == 0;
      if (days < 365 + leap)
          break;
      days -= 365 + leap;
  }
  for(m = 1; ;m++){
      uint8_t daysPerMonth = pgm_read_byte(daysInMonth + m - 1);
      if (leap && m == 2)
          ++daysPerMonth;
      if (days < daysPerMonth)
          break;
      days -= daysPerMonth;
  }
  d = days + 1;
  
  Serial.print(yOff+2000);
  Serial.print("/");
  Serial.print(m);
  Serial.print("/");
  Serial.print(d);
  Serial.print(" ");
  Serial.print(hh);
  Serial.print(":");
  Serial.print(mm);
  Serial.print(":");
  Serial.println(ss);
}

