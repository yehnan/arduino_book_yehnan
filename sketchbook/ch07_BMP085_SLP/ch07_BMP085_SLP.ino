#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <Bounce.h>
#include <Timer.h>
#include <Wire.h> // I2C
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>

#define LCD_RS_PIN 2
#define LCD_E_PIN 3
#define LCD_D4_PIN 4
#define LCD_D5_PIN 5
#define LCD_D6_PIN 6
#define LCD_D7_PIN 7
#define BUTTON_UP_PIN 8
#define BUTTON_DOWN_PIN 9

LiquidCrystal lcd(LCD_RS_PIN, LCD_E_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);
#define DEBOUNCE_DELAY 50 // milliseconds
Bounce bUp = Bounce(BUTTON_UP_PIN, DEBOUNCE_DELAY);
Bounce bDown = Bounce(BUTTON_DOWN_PIN, DEBOUNCE_DELAY);

Adafruit_BMP085 bmp = Adafruit_BMP085(10085);
#define SLP_EEPROM_ADDRESS_START 0 // SLP is Sea-Level Pressure
#define SLP_BYTE_NUMBER 6
#define SLP_GENERIC 1013.25
float seaLevelPressure = SLP_GENERIC;
float pressure = -1;
float temperature = -1;
float alitude = -1;

boolean needToRefresh = false;
void lcdRefresh(){
  if(needToRefresh == false){
    return;
  }
  lcd.clear();
  lcd.print("S"); // Sea-Level Pressure
  lcd.print(seaLevelPressure);
  
  lcd.print(" T"); // Temperature
  lcd.print(temperature);
  
  lcd.setCursor(0, 1);
  lcd.print("P"); // Pressure
  lcd.print(pressure);
  
  lcd.print(" A"); // Alitude
  lcd.print(int(alitude));
  
  needToRefresh = false;
}

boolean needToSLP = false;
void saveSLP(){
  if(needToSLP == false){
    return;
  }

  unsigned long p = seaLevelPressure * 100;
  for(int i = 0; i < SLP_BYTE_NUMBER; i++){
    EEPROM.write(SLP_EEPROM_ADDRESS_START + i, p % 10);
    p /= 10;
  }
  
  needToSLP = false;
}

Timer timerUpdateReadings;
void updateReadings(void *context){
  bmp.getPressure(&pressure);
  pressure /= 100.0F; // from 100hPa to hPa
  bmp.getTemperature(&temperature);
  alitude = bmp.pressureToAltitude(seaLevelPressure,
    pressure, temperature);

  needToRefresh = true;
  
  saveSLP();
}

void setup(void) 
{
  if(!bmp.begin()){
    lcd.clear();
    lcd.print("No BMP085!");
    while(1)
      ;
  }

  lcd.begin(16, 2);
  pinMode(BUTTON_UP_PIN, INPUT_PULLUP);
  pinMode(BUTTON_DOWN_PIN, INPUT_PULLUP);
  timerUpdateReadings.every(3000, updateReadings, NULL);
  needToRefresh = true;
  
  seaLevelPressure = 0;
  for(int i = 0; i < SLP_BYTE_NUMBER; i++){
    byte v = EEPROM.read(SLP_EEPROM_ADDRESS_START + i);
    if(v == 0xFF){
      seaLevelPressure = SLP_GENERIC * 100;
      break;
    }
    else{
      seaLevelPressure += v * pow(10, i);
    }
  }
  seaLevelPressure /= 100;
}

void loop(void) 
{
  timerUpdateReadings.update();
  lcdRefresh();
  bUp.update();
  bDown.update();
  if(bUp.read() == LOW){
    seaLevelPressure += 0.01;
    needToRefresh = true;
    needToSLP = true;
  }
  if(bDown.read() == LOW){
    seaLevelPressure -= 0.01;
    needToRefresh = true;
    needToSLP = true;
  }
}

