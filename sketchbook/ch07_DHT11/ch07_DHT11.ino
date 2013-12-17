#include <DHT.h>
#define SERIAL_BAUDRATE 19200
#define DHT_PIN 12

// DHT程式庫適用多種感測器，請改成您手上的感測器型號
#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22, AM2302
//#define DHTTYPE DHT21   // DHT 21, AM2301
DHT dht(DHT_PIN, DHTTYPE);

void pf(const char *fmt, ... ){
    char tmp[256];
    va_list args;
    va_start (args, fmt );
    vsnprintf(tmp, 256, fmt, args);
    va_end (args);
    Serial.print(tmp);
}

void setup(void) {
  Serial.begin(SERIAL_BAUDRATE);
  while(!Serial){
  }
  dht.begin(); // 初始化並啟動
}
void loop(void) {
  float t = dht.readTemperature(); // 讀取溫度
  float h = dht.readHumidity(); // 讀取濕度
  
  Serial.print("Temperature is ");
  Serial.print(t);
  Serial.print(" degree(Celsius), Humidity is ");
  Serial.print(h);
  Serial.println("%.");
  
  delay(2000);
}

