#include <LiquidCrystal.h>
#define LCD_RS_PIN 2
#define LCD_E_PIN 3
#define LCD_D4_PIN 4
#define LCD_D5_PIN 5
#define LCD_D6_PIN 6
#define LCD_D7_PIN 7

// 建立LiquidCrystal物件
LiquidCrystal lcd(LCD_RS_PIN, LCD_E_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

void setup(){
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Hello, world!");
}
void loop(){
  lcd.setCursor(0, 1);
  lcd.print(millis() / 1000);
}

