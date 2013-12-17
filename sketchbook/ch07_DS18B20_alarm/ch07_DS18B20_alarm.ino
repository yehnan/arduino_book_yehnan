#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define SERIAL_BAUDRATE 19200
#define LCD_RS_PIN 2
#define LCD_E_PIN 3
#define LCD_D4_PIN 4
#define LCD_D5_PIN 5
#define LCD_D6_PIN 6
#define LCD_D7_PIN 7
#define BUZZER_PIN 11
#define DS18B20_PIN 12

#define TEMPERATURE_HIGH_LIMIT 38 // 攝氏Celsius
#define TEMPERATURE_LOW_LIMIT 10 // 攝氏Celsius

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

LiquidCrystal lcd(LCD_RS_PIN, LCD_E_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);
OneWire oneWire(DS18B20_PIN);
DallasTemperature tSensors(&oneWire);
float c;
float f;

void pf(const char *fmt, ... ){
    char tmp[256];
    va_list args;
    va_start(args, fmt);
    vsnprintf(tmp, 256, fmt, args);
    va_end(args);
    Serial.print(tmp);
}

void alarmHandler(uint8_t *){
  lcd.setCursor(0, 1);
  lcd.write(byte(1));
  lcd.print(' ');
  if(TEMPERATURE_HIGH_LIMIT <= c){
    lcd.print("Too Hot!");
    tone(BUZZER_PIN, NOTE_C5, 3000 / 4);
  }
  else if(c <= TEMPERATURE_LOW_LIMIT){
    lcd.print("Too Cold!");
    tone(BUZZER_PIN, NOTE_B5, 3000 / 4);
  }
}

byte smileFace[8] = { // 笑臉
  B00000,
  B10001,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
};
byte cryFace[8] = { // 哭臉
  B00000,
  B10001,
  B00000,
  B00000,
  B00000,
  B01110,
  B10001,
};
byte degreeCircle[8] = { // 代表「度」的小圈圈
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
  Serial.begin(SERIAL_BAUDRATE);
  while(!Serial){
  }
  lcd.createChar(0, smileFace);
  lcd.createChar(1, cryFace);
  lcd.createChar(2, degreeCircle);
  lcd.begin(16, 2);
  tSensors.begin();
  
  int deviceCount = tSensors.getDeviceCount();
  pf("There are %d device(s).\n", deviceCount);
  
  for(int i = 0; i < deviceCount; i++){
    uint8_t a[8];
    tSensors.getAddress(a, i);
    pf("Device index %d, address 0x %02x %02x %02x %02x %02x %02x %02x %02x\n", 
      i, a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]);
    // 設定溫度上下限
    tSensors.setHighAlarmTemp(a, TEMPERATURE_HIGH_LIMIT);
    tSensors.setLowAlarmTemp(a, TEMPERATURE_LOW_LIMIT);
    tSensors.setAlarmHandler(alarmHandler); // 設定警告處理函式
  }
}

void loop(void)
{
  tSensors.requestTemperatures();
  c = tSensors.getTempCByIndex(0);
  f = tSensors.toFahrenheit(c);
  Serial.print("Temperature is ");
  Serial.print(c);
  Serial.print(" degree(Celsius), ");
  Serial.print(f);
  Serial.println(" degree(Fahrenheit).");
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(c);
  lcd.write(byte(2));
  lcd.print('C');
  lcd.setCursor(0, 1);
  lcd.write(byte(0));
  
  tSensors.processAlarms();
  delay(1000);
}

