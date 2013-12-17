#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <Bounce.h>
#include <Timer.h>
#include <Wire.h> // I2C
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>

// LCD螢幕的腳位
#define LCD_RS_PIN 2
#define LCD_E_PIN 3
#define LCD_D4_PIN 4
#define LCD_D5_PIN 5
#define LCD_D6_PIN 6
#define LCD_D7_PIN 7
// 調整海平面氣壓的按壓開關的腳位
#define BUTTON_UP_PIN 8
#define BUTTON_DOWN_PIN 9

// 建立LiquidCrystal物件
LiquidCrystal lcd(LCD_RS_PIN, LCD_E_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

// 使用Bounce程式庫控制開關並除彈跳
#define DEBOUNCE_DELAY 50 // milliseconds
Bounce bUp = Bounce(BUTTON_UP_PIN, DEBOUNCE_DELAY);
Bounce bDown = Bounce(BUTTON_DOWN_PIN, DEBOUNCE_DELAY);

// 建立能讀取BMP085感測器IC的物件
Adafruit_BMP085 bmp = Adafruit_BMP085(10085);
// 為了儲存修改後的海平面氣壓，需要六個位元組的空間，
// 這兩個常數定義了EEPROM存放空間的起始位址與總大小
#define SLP_EEPROM_ADDRESS_START 0 // SLP是Sea-Level Pressure海平面氣壓的縮寫
#define SLP_BYTE_NUMBER 6
#define SLP_GENERIC 1013.25 // 一般標準的海平面氣壓
// 全域變數
float seaLevelPressure = SLP_GENERIC; // 海平面氣壓
float pressure = -1; // 氣壓
float temperature = -1; // 溫度
float alitude = -1; // 海拔高度

boolean needToRefresh = false; // 此布林值控制要不要刷新LCD
void lcdRefresh(){ // 將資料輸出到LCD
  if(needToRefresh == false){
    return;
  }
  lcd.clear();
  lcd.print("S"); // Sea-Level Pressure海平面氣壓
  lcd.print(seaLevelPressure);
  
  lcd.print(" T"); // Temperature溫度
  lcd.print(temperature);
  
  lcd.setCursor(0, 1);
  lcd.print("P"); // Pressure氣壓
  lcd.print(pressure);
  
  lcd.print(" A"); // Alitude海拔高度
  lcd.print(int(alitude));
  
  needToRefresh = false;
}

// 由此布林值控制需不需要儲存海平面氣壓到EEPROM
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

// 計時器物件，控制每幾秒便讀取氣壓與溫度
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

void setup(void) {
  if(!bmp.begin()){ // 啟用BMP085物件
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
  
  // 從EEPROM讀出海平面氣壓
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
void loop(void) {
  timerUpdateReadings.update(); // 更新氣壓與溫度
  lcdRefresh(); // 刷新LCD
  bUp.update(); // 更新開關的狀態
  bDown.update();
  if(bUp.read() == LOW){ // 若被按下（為LOW）
    seaLevelPressure += 0.01; // 增加海平面氣壓的數值
    needToRefresh = true;
    needToSLP = true;
  }
  if(bDown.read() == LOW){ // 若被按下（為LOW）
    seaLevelPressure -= 0.01; // 減少海平面氣壓的數值
    needToRefresh = true;
    needToSLP = true;
  }
}

