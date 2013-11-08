#include <LiquidCrystal.h>
#define LCD_RS_PIN 2
#define LCD_E_PIN 3
#define LCD_D4_PIN 4
#define LCD_D5_PIN 5
#define LCD_D6_PIN 6
#define LCD_D7_PIN 7
#define LCD_ROW_NUMBER 2
#define LCD_COL_NUMBER 16
#define SWITCH_PIN 8
#define MIC_PIN A0 // 麥克風

// 朝麥克風吹氣，若輸出值超過此常數，便開始遊戲
#define MIC_THRESHOLD 500
// 若仍持續吹出夠強的氣，便延長記錄時間，單位millisecond
#define EXTEND_DURATION 1000
LiquidCrystal lcd(LCD_RS_PIN, LCD_E_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

// 採用「狀態機」程式設計技巧
typedef enum{
  S_Start,
  S_Standby,
  S_Measuring,
  S_Stop,
}State;
State state;

void setup() {
  lcd.begin(LCD_COL_NUMBER, LCD_ROW_NUMBER);
  lcd.print("Start");
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  state = S_Start;
}
unsigned long time_to_stop; // 限定一個時間，超過便終止遊戲
unsigned long time_start; // 遊戲正式開始的時間
void loop() {
  int mic; // 讀取麥克風
  unsigned long time_now;

  if(digitalRead(SWITCH_PIN) == LOW){
    state = S_Start; // 重置
  }
  switch(state){
    case S_Start:
      lcd.clear();
      lcd.print("Ready"); // 代表準備好了，可開始吹氣
      state = S_Standby;
    break;
    case S_Standby:
      mic = analogRead(MIC_PIN);
      if(mic >= MIC_THRESHOLD){ // 超過此值才正式開始遊戲
        time_start = millis();
        time_to_stop = time_start + EXTEND_DURATION; // 設定終止時間
        lcd.clear();
        lcd.print("Keep blowing!");
        lcd.setCursor(0, 1);
        lcd.print(0);//
        lcd.print(" seconds");
        state = S_Measuring;
      }
    break;
    case S_Measuring:
      mic = analogRead(MIC_PIN);
      time_now = millis();
      if(time_now > time_to_stop){ // 超過終止時間了
        lcd.setCursor(0, 0);
        lcd.print("Over         ");
        state = S_Stop; // 遊戲終止
      }
      else{ // 還沒超過終止時間
        if(mic > MIC_THRESHOLD){ // 吹出足夠的氣便能延長終止時間
          time_to_stop = time_now + EXTEND_DURATION;
          float d = (time_now - time_start) / 1000.0; // 輸出吹氣持續秒數
          lcd.setCursor(0, 1);
          lcd.print(d);
          lcd.print(" seconds");
        }
      }
    break;
    case S_Stop: // 遊戲終止
    break;
  }
}

