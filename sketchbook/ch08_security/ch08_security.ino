#include <LiquidCrystal.h> // LCD螢幕
#include <EEPROM.h> // 儲存密碼
#include <Keypad.h> // 矩陣鍵盤
#define SERIAL_BAUDRATE 19200

// 定義3x4矩陣鍵盤針腳A~G（從左到右）與Arduino腳位的連接關係
#define A_PIN 12
#define B_PIN 11
#define C_PIN 10
#define D_PIN 9
#define E_PIN 8
#define F_PIN 7
#define G_PIN 6
// 定義矩陣鍵盤的列欄對應到哪隻針腳（A~G）
#define COL_0_PIN A_PIN
#define COL_1_PIN B_PIN
#define COL_2_PIN C_PIN
#define ROW_0_PIN D_PIN
#define ROW_1_PIN E_PIN
#define ROW_2_PIN F_PIN
#define ROW_3_PIN G_PIN
// 矩陣鍵盤 3直欄 4橫列
#define KEYPAD_COL 3 
#define KEYPAD_ROW 4
// 定義LCD螢幕的腳位與Arduino腳位的連接關係
#define LCD_RS_PIN A0
#define LCD_E_PIN A1
#define LCD_D4_PIN A2
#define LCD_D5_PIN A3
#define LCD_D6_PIN A4
#define LCD_D7_PIN A5
// LCD有 2列 16欄
#define LCD_ROW 2 
#define LCD_COL 16
// 蜂鳴器（或小喇叭）連接Arduino的腳位
#define BUZZER_PIN 3 
// PIR動作感測器連接Arduino的腳位
#define PIR_PIN 2
// 定義矩陣鍵盤每個按鍵代表的字元
#define KEYCHAR_0 '0'
#define KEYCHAR_1 '1'
#define KEYCHAR_2 '2'
#define KEYCHAR_3 '3'
#define KEYCHAR_4 '4'
#define KEYCHAR_5 '5'
#define KEYCHAR_6 '6'
#define KEYCHAR_7 '7'
#define KEYCHAR_8 '8'
#define KEYCHAR_9 '9'
#define KEYCHAR_STAR '*' // 進入修改密碼的狀態
#define KEYCHAR_SHARP '#' // 代表Enter輸入密碼

// 發聲頻率，供函式tone使用
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
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976

// 3x4矩陣鍵盤
byte rowPins[KEYPAD_ROW] = {ROW_0_PIN, ROW_1_PIN, ROW_2_PIN, ROW_3_PIN};
byte colPins[KEYPAD_COL] = {COL_0_PIN, COL_1_PIN, COL_2_PIN};
char keys[KEYPAD_ROW][KEYPAD_COL] = { // 每個按鍵所對應的字元
  {KEYCHAR_1, KEYCHAR_2, KEYCHAR_3},
  {KEYCHAR_4, KEYCHAR_5, KEYCHAR_6},
  {KEYCHAR_7, KEYCHAR_8, KEYCHAR_9},
  {KEYCHAR_STAR, KEYCHAR_0, KEYCHAR_SHARP}
};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROW, KEYPAD_COL);

// LCD螢幕
LiquidCrystal lcd(LCD_RS_PIN, LCD_E_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

// 這支程式共有底下這些狀態
typedef enum{
  S_Off, // 無保全
  S_On, // 開啟保全
  S_Alert, // 進入警戒狀態
  S_Alarm, // 警報狀態，發現入侵者
  S_Password_Change, // 修改密碼程序之一，先輸入舊密碼
  S_Password_Input1, // 修改密碼程序之二，輸入新密碼
  S_Password_Input2, // 修改密碼程序之三，再次輸入新密碼確認
}State;
State state;

#define PASSWORD_EEPROM_ADDRESS_START 0 // 儲存密碼的EEPROM起始位址
#define PASSWORD_NUM 4 // 密碼有幾個數字
byte password[PASSWORD_NUM]; // 密碼
byte passwordNew[PASSWORD_NUM]; // 修改密碼時，暫時存放新密碼

byte inputBuffer[LCD_COL]; // 輸入緩衝區
int inputBufferLen; // 目前輸入數字的長度

// 比較兩個陣列的內容，用來比較密碼
boolean compareArray(const byte *x, const byte *y, int len){
  for(int i = 0; i < len; i++){
    if(x[i] != y[i]){
      return false;
    }
  }
  return true;
}

// 驗證密碼，依狀態有不同的行為
boolean verifyPassword(){
  switch(state){
    // 在這些狀態時，驗證輸入的密碼是否正確
    case S_Off: case S_On: case S_Alert: case S_Alarm: case S_Password_Change:
      if(inputBufferLen == PASSWORD_NUM && 
        compareArray(password, inputBuffer, PASSWORD_NUM)){
        return true;
      }
    break;
    case S_Password_Input1: // 在此狀態時，暫時將輸入的密碼存起來
      if(inputBufferLen == PASSWORD_NUM){
        for(int i = 0; i < PASSWORD_NUM; i++){
          passwordNew[i] = inputBuffer[i];
        }
        return true;
      }
    break;
    case S_Password_Input2: // 在此狀態時，比較兩次輸入的新密碼是否相同
      if(inputBufferLen == PASSWORD_NUM &&
        compareArray(passwordNew, inputBuffer, PASSWORD_NUM)){
        return true;
      }
    break;
  }
  return false;
}

boolean needToRefreshLcd; // 控制要不要更新LCD
void refreshLcd(){
  if(needToRefreshLcd == false)
    return;
  lcd.clear();
  switch(state){ // 按照狀態顯示不同的字串
    case S_Off:
      lcd.print("Off");
    break;
    case S_On:
      lcd.print("On");
    break;
    case S_Alert:
      lcd.print("Alert!");
    break;
    case S_Alarm:
      lcd.print("Alarm!");
    break;
    case S_Password_Change:
      lcd.print("Old password:");
    break;
    case S_Password_Input1:
      lcd.print("Input new:");
    break;
    case S_Password_Input2:
      lcd.print("Input again:");
    break;
  }
  if(inputBufferLen > 0){ // 以'*'代表輸入的數字
    lcd.setCursor(0, 1);
    for(int i = 0; i < inputBufferLen; i++){
      lcd.write('*');
    }
  }
  needToRefreshLcd = false;
}
void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  lcd.begin(LCD_COL, LCD_ROW);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(PIR_PIN, INPUT);
  
  // 從EEPROM載入密碼
  for(int i = 0; i < PASSWORD_NUM; i++){
    byte b = EEPROM.read(PASSWORD_EEPROM_ADDRESS_START + i);
    if(b != 0xFF){
      password[i] = b;
    }
    else{
      for(int j = 0; j < PASSWORD_NUM; j++){
        password[j] = '0'; // 預設密碼是0000
      }
      break;
    }
  }
  
  state = S_Off; // 重置後處於未開啟保全的狀態
  needToRefreshLcd = true;
}
// 輸入密碼後若驗證正確，改變到後續的狀態
void changeState(){
  switch(state){
    case S_Off:
      state = S_On;
    break;
    case S_On:
    case S_Alert:
    case S_Alarm:
      state = S_Off;
    break;
    case S_Password_Change:
      state = S_Password_Input1;
    break;
    case S_Password_Input1:
      state = S_Password_Input2;
    break;
    case S_Password_Input2:
      for(int i = 0; i < PASSWORD_NUM; i++){ // 儲存新密碼
        password[i] = passwordNew[i];
        EEPROM.write(PASSWORD_EEPROM_ADDRESS_START+i, password[i]);
      }
      state = S_Off;
    break;
  }
  inputBufferLen = 0;
  needToRefreshLcd = true;
}

// 第一次偵測到移動時（有人入侵），先記錄當時的時間在timeAlerted，
// 經過ALERT_DURATION毫秒後，若還繼續偵測到移動，便發出警報。
unsigned long timeAlerted;
#define ALERT_DURATION 60000 // millisecond

void loop() {
  refreshLcd();
  char key = keypad.getKey();
  if(key != NO_KEY){
    Serial.println(key);
    if(key == KEYCHAR_SHARP){ // 此按鍵代表Enter輸入密碼
      if(inputBufferLen > 0){
        if(verifyPassword()){ // 若驗證成功
          inputBufferLen = 0;
          needToRefreshLcd = true;
          changeState(); // 進入下一個狀態
        }
        else{ // 若驗證失敗，發出錯誤聲響
          tone(BUZZER_PIN, NOTE_C5, 3000 / 8);
          inputBufferLen = 0;
          state = S_Off;
          needToRefreshLcd = true;
        }
      }
    }
    else if(key == KEYCHAR_STAR){
      // 只有在S_Off狀態時按下KEYCHAR_STAR，才能進入
      // 修改密碼的狀態
      if(state == S_Off){
        state = S_Password_Change;
        needToRefreshLcd = true;
      }
    }
    else{ // 若輸入的是數字（0~9），存起來
      if(inputBufferLen < LCD_COL){
        inputBuffer[inputBufferLen] = key;
        inputBufferLen++;
        needToRefreshLcd = true;
      }
      else{ // 輸入的數字超過極限了，發出錯誤聲響
        tone(BUZZER_PIN, NOTE_D5, 3000 / 8);
      }
    }
  }
  
  switch(state){
    case S_Off:
    break;
    case S_On: // 保全開啟狀態
      if(digitalRead(PIR_PIN)){ // 發現有人移動的話
        timeAlerted = millis(); 
        state = S_Alert; // 進入警戒狀態
        needToRefreshLcd = true;
      }
    break;
    case S_Alert:{
      unsigned long timeNow = millis();
      if(timeNow - timeAlerted > ALERT_DURATION && 
        timeNow - timeAlerted < (ALERT_DURATION * 2)){
        // 經過一段時間後若還偵測到有人移動
        if(digitalRead(PIR_PIN)){
          state = S_Alarm; // 進入警報狀態
          needToRefreshLcd = true;
        }
      }
      else if(timeNow - timeAlerted > (ALERT_DURATION * 2)){
        // 經過一段時間後沒偵測到入侵者，回到保全開啟的狀態
        state = S_On;
        needToRefreshLcd = true;
      }
    }
    break;
    case S_Alarm: // 警報狀態，發出聲響
      tone(BUZZER_PIN, NOTE_B6, 3000 / 8);
    break;
    case S_Password_Change:
    break;
    case S_Password_Input1:
    break;
    case S_Password_Input2:
    break;
  }
}

