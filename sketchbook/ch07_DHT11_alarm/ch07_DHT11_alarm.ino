#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <DHT.h>
#include <Bounce.h>
#include <Timer.h>
#define LCD_RS_PIN 2
#define LCD_E_PIN 3
#define LCD_D4_PIN 4
#define LCD_D5_PIN 5
#define LCD_D6_PIN 6
#define LCD_D7_PIN 7
#define BUTTON_MODE_PIN 8
#define BUTTON_UP_PIN 9
#define BUTTON_DOWN_PIN 10
#define BUZZER_PIN 11
#define DHT_PIN 12

LiquidCrystal lcd(LCD_RS_PIN, LCD_E_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22, AM2302
//#define DHTTYPE DHT21   // DHT 21, AM2301
DHT dht(DHT_PIN, DHTTYPE);

#define DEBOUNCE_DELAY 50 // milliseconds
Bounce bMode = Bounce(BUTTON_MODE_PIN, DEBOUNCE_DELAY);
Bounce bUp = Bounce(BUTTON_UP_PIN, DEBOUNCE_DELAY);
Bounce bDown = Bounce(BUTTON_DOWN_PIN, DEBOUNCE_DELAY);

#define NOTE_C5  523 // Do
#define NOTE_CS5 554
#define NOTE_D5  587 // Re
#define NOTE_DS5 622
#define NOTE_E5  659 // Mi
#define NOTE_F5  698 // Fa
#define NOTE_FS5 740
#define NOTE_G5  784 // So
#define NOTE_GS5 831
#define NOTE_A5  880 // La
#define NOTE_AS5 932
#define NOTE_B5  988 // Si

float t;
float h;

typedef enum{
  S_Temperature_High_Limit,
  S_Temperature_Low_Limit,
  S_Humidity_High_Limit,
  S_Humidity_Low_Limit,
  S_Normal,
  S_Max = S_Normal,
}State;
State state;
byte limits[S_Max] = {
  50, 10, 80, 10,
};

boolean needToRefresh = false;
void lcdRefresh(){
  if(needToRefresh == false){
    return;
  }
  lcd.clear();
  switch(state){
    case S_Normal:
      lcd.print("T ");
      lcd.print(t);
      lcd.write(byte(0));
      lcd.print('C');
      lcd.setCursor(0, 1);
      lcd.print("H ");
      lcd.print(h);
      lcd.print('%');
    break;
    case S_Temperature_High_Limit:
      lcd.print("T High Limit: ");
      lcd.setCursor(0, 1);
      lcd.print(limits[S_Temperature_High_Limit]);
      lcd.write(byte(0));
      lcd.print('C');
    break;
    case S_Temperature_Low_Limit:
      lcd.print("T Low Limit: ");
      lcd.setCursor(0, 1);
      lcd.print(limits[S_Temperature_Low_Limit]);
      lcd.write(byte(0));
      lcd.print('C');
    break;
    case S_Humidity_High_Limit:
      lcd.print("H High Limit: ");
      lcd.setCursor(0, 1);
      lcd.print(limits[S_Humidity_High_Limit]);
      lcd.print('%');
    break;
    case S_Humidity_Low_Limit:
      lcd.print("H Low Limit: ");
      lcd.setCursor(0, 1);
      lcd.print(limits[S_Humidity_Low_Limit]);
      lcd.print('%');
    break;
  }
  needToRefresh = false;
}

Timer timerUpdateReadings;
void updateReadings(void *context){
  t = dht.readTemperature();
  h = dht.readHumidity();
  needToRefresh = true;
}
 
Timer timerCheckLimits;
void checkLimits(void *context){
  if(t < limits[S_Temperature_Low_Limit]){
    tone(BUZZER_PIN, NOTE_C5, 3000 / 4);
  }
  else if(limits[S_Temperature_High_Limit] < t){
    tone(BUZZER_PIN, NOTE_D5, 3000 / 4);
  }
  
  if(h < limits[S_Humidity_Low_Limit]){
    tone(BUZZER_PIN, NOTE_E5, 3000 / 4);
  }
  else if(limits[S_Humidity_High_Limit] < h){
    tone(BUZZER_PIN, NOTE_F5, 3000 / 4);
  }
}

byte degreeCircle[8] = {
  B00010,
  B00101,
  B00010,
  B00000,
  B00000,
  B00000,
  B00000,
};
void setup(void)
{
  pinMode(BUTTON_MODE_PIN, INPUT_PULLUP);
  pinMode(BUTTON_UP_PIN, INPUT_PULLUP);
  pinMode(BUTTON_DOWN_PIN, INPUT_PULLUP);
  lcd.createChar(0, degreeCircle);
  lcd.begin(16, 2);
  dht.begin();
  timerUpdateReadings.every(2000, updateReadings, NULL);
  timerCheckLimits.every(1000, checkLimits, NULL);
  state = S_Normal;
  needToRefresh = true;
  
  byte v;
  for(int i = S_Temperature_High_Limit; i < S_Max; i++){
    v = EEPROM.read(i);
    if(v != 0xFF){
      limits[i] = v;
    }
  }
}

boolean needToSaveLimits = false;
void saveLimits(){
  if(needToSaveLimits == false){
    return;
  }
  for(int i = S_Temperature_High_Limit; i < S_Max; i++){
    EEPROM.write(i, limits[i]);
  }
  needToSaveLimits = false;
}
void loop(void)
{ 
  timerUpdateReadings.update();
  timerCheckLimits.update();
  lcdRefresh();
  saveLimits();
  boolean bModePressed = bMode.update() == true && bMode.read() == LOW;
  boolean bUpPressed = bUp.update() == true && bUp.read() == LOW;
  boolean bDownPressed = bDown.update() == true && bDown.read() == LOW;
  
  if(bModePressed){
    needToRefresh = true;
    switch(state){
      case S_Normal:
        state = S_Temperature_High_Limit;
      break;
      case S_Temperature_High_Limit:
        state = S_Temperature_Low_Limit;
      break;
      case S_Temperature_Low_Limit:
        state = S_Humidity_High_Limit;
      break;
      case S_Humidity_High_Limit:
        state = S_Humidity_Low_Limit;
      break;
      case S_Humidity_Low_Limit:
        state = S_Normal;
      break;
    }
  }
  
  switch(state){
    case S_Temperature_High_Limit:
    case S_Temperature_Low_Limit:
    case S_Humidity_High_Limit:
    case S_Humidity_Low_Limit:
      if(bUpPressed){
        limits[state]++;
        needToRefresh = true;
        needToSaveLimits = true;
      }
      if(bDownPressed){
        limits[state]--;
        needToRefresh = true;
        needToSaveLimits = true;
      }
      delay(100);
    break;
  }
}

