#include <Wire.h> // I2C
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>
#define SERIAL_BAUDRATE 19200

Adafruit_BMP085 bmp = Adafruit_BMP085(10085);
float seaLevelPressure = 1013.25;

void setup(void) 
{
  Serial.begin(SERIAL_BAUDRATE);
  if(!bmp.begin()){
    Serial.println("No BMP085!");
    while(1)
      ;
  }
}

void loop(void) 
{
  Serial.print("Sea-level pressure: ");
  Serial.print(seaLevelPressure);
  Serial.println(" hPa");
  
  float pressure;
  bmp.getPressure(&pressure);
  pressure /= 100.0F; // from 100hPa to hPa
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");
   
  float temperature;
  bmp.getTemperature(&temperature);
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Altitude: "); 
  Serial.print(bmp.pressureToAltitude(seaLevelPressure,
    pressure, temperature)); 
  Serial.println(" m");
  Serial.println("");

  delay(2000);
}

