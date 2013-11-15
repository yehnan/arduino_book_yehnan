#include <LiquidCrystal.h>
#define SERIAL_BAUDRATE 19200
#define LCD_RS_PIN 2
#define LCD_E_PIN 3
#define LCD_D4_PIN 4
#define LCD_D5_PIN 5
#define LCD_D6_PIN 6
#define LCD_D7_PIN 7
#define BUZZER_PIN 9
#define FSR_PIN A0

#define LCD_ROW 2
#define LCD_COL 16
LiquidCrystal lcd(LCD_RS_PIN, LCD_E_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);
#define ARROW_POS 1 // 顯示箭頭的位置，也就是打擊區的位置

#define HIT_TO_WIN 20 // 擊中多少次才贏
#define MISS_TO_LOSE 5 // 漏掉多少次就輸
int hitCount; // 記錄擊中次數
int missCount; // 記錄漏掉次數

#define OBJ 'O' // 代表被擊物
#define SPACE ' ' // 代表沒有東西
#define OBJECT_MAX LCD_COL
char objects[OBJECT_MAX]; // 記錄哪裡有被擊物的

#define NOTE_E4  330 // 打擊落空的音效
#define NOTE_F4  349 // 漏掉的音效
#define NOTE_B5  988 // 擊中的音效

#define TIMER_PERIOD_MAX 500 // 一開始的遊戲更新週期，每500ms被擊物前進一次
#define TIMER_PERIOD_MIN 100 // 最低可能的更新週期
#define TIMER_PERIOD_DIFF 30 // 每次減少此值，增快遊戲
int timeAdvancePeriod = TIMER_PERIOD_MAX; // 控制遊戲速度

byte arrow[8] = { // 箭頭的圖案
  B00100,
  B01010,
  B10001,
  B00100,
  B00100,
  B00100,
  B00100,
};
boolean needToRefreshCounts;
void refreshCounts(){ // 更新擊中次數與漏掉次數
  if(needToRefreshCounts == true){
    lcd.setCursor(3, 1);
    lcd.print("H:"); // 擊中次數
    lcd.print(hitCount);
    lcd.print("/M:"); // 漏掉次數
    lcd.print(missCount);
    needToRefreshCounts = false;
  }
}
void advance(){ // 推進被擊物
  if(objects[0] != SPACE){ // 漏掉了
    tone(BUZZER_PIN, NOTE_F4, 3000 / 8);
    missCount++;
    needToRefreshCounts = true;
  }
  lcd.setCursor(0, 0);
  for(int i = 1; i < OBJECT_MAX; i++){
    objects[i - 1] = objects[i];
    lcd.write(objects[i - 1]);
  }
  char c = random(2) == 0 ? SPACE : OBJ; // 隨機產生被擊
  objects[OBJECT_MAX - 1] = c;
  lcd.write(objects[OBJECT_MAX - 1]);
}
unsigned long timeAdvance; // 控制遊戲速度
unsigned long timePrevious; // 控制每秒可打擊幾次
void setup(){
  randomSeed(analogRead(A5));
  lcd.createChar(0, arrow);
  lcd.begin(LCD_COL, LCD_ROW);
  lcd.setCursor(1, 1);
  lcd.write(byte(0));
  for(int i = 0; i < OBJECT_MAX; i++){
    objects[i] = SPACE;
  }
  timePrevious = millis();
  timeAdvance = millis();
  needToRefreshCounts = true;
}
void press(){ // 打擊
  if(objects[ARROW_POS] != SPACE){ // 擊中東西
    tone(BUZZER_PIN, NOTE_B5, 3000 / 8);
    objects[ARROW_POS] = SPACE;
    lcd.setCursor(ARROW_POS, 0);
    lcd.write(SPACE);
    hitCount++;
    needToRefreshCounts = true;
    timeAdvancePeriod -= TIMER_PERIOD_DIFF;
    if(timeAdvancePeriod <= TIMER_PERIOD_MIN)
      timeAdvancePeriod = TIMER_PERIOD_MIN;
  }
  else{ // 沒擊中
    tone(BUZZER_PIN, NOTE_E4, 3000 / 8);
  }
}
#define FSR_HIT_THRESHOLD 300 // 壓力感測器超過此值才算打擊
#define FSR_HIT_DELAY 100 // 100ms，代表每一秒最多打擊10次
void checkWinOrLose(){ // 檢查輸贏
  if(hitCount == HIT_TO_WIN){
    lcd.setCursor(0, 0);
    lcd.print("You Win!");
    while(1){
    }
  }
  if(missCount == MISS_TO_LOSE){
    lcd.setCursor(0, 0);
    lcd.print("You Lose!");
    while(1){
    }
  }
}
void loop(){
  const unsigned long timeNow = millis();
  checkWinOrLose();
  refreshCounts();
  int v = analogRead(FSR_PIN);
  if(v > FSR_HIT_THRESHOLD){ // 打擊
    if(timeNow - timePrevious > FSR_HIT_DELAY){
      timePrevious = timeNow;
      press();
    }
  }
  if(timeNow - timeAdvance > timeAdvancePeriod){
    advance(); // 推進被擊物
    timeAdvance = timeNow;
  }
}

