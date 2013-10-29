#include <DHT.h>
#define SERIAL_BAUDRATE 19200
#define DHT_PIN 12

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

void setup(void)
{
  Serial.begin(SERIAL_BAUDRATE);
  while(!Serial){
  }
  dht.begin();
}

void loop(void)
{
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  
  Serial.print("Temperature is ");
  Serial.print(t);
  Serial.print(" degree(Celsius), Humidity is ");
  Serial.print(h);
  Serial.println("%.");
  
  delay(2000);
}

