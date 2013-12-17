#include <Wire.h> // I2C
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>
#define SERIAL_BAUDRATE 19200

// 建立Adafruit_BMP085物件，參數是由你決定的辨識碼，
// 若有多個感測器便能分別彼此，但此例只有一個BMP085，
// 所以隨便傳入一個數字即可。
Adafruit_BMP085 bmp = Adafruit_BMP085(10085);
// 海平面氣壓的一般值
float seaLevelPressure = 1013.25;

void setup(void) {
  Serial.begin(SERIAL_BAUDRATE);
  // 呼叫begin方法啟動BMP085，回傳true代表一切正常
  if(!bmp.begin()){
    Serial.println("No BMP085!");
    while(1)
      ;
  }
}
void loop(void) {
  Serial.print("Sea-level pressure: "); // 海平面氣壓
  Serial.print(seaLevelPressure);
  Serial.println(" hPa");
  
  float pressure;
  bmp.getPressure(&pressure); // 取得氣壓，單位是100hPa
  pressure /= 100.0F; // 轉成百帕（hPa）
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");
   
  float temperature;
  bmp.getTemperature(&temperature); // 取得溫度，單位是攝氏
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Altitude: "); 
  Serial.print(bmp.pressureToAltitude(seaLevelPressure,
    pressure, temperature));  // 推算出海拔高度
  Serial.println(" m");
  Serial.println("");

  delay(2000);
}

