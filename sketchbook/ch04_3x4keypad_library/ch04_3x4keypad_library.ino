#include <Keypad.h>
#define SERIAL_BAUDRATE 19200
// 定義矩陣鍵盤的針腳（A~G）與Arduino腳位的連接關係
#define A_PIN 8
#define B_PIN 7
#define C_PIN 6
#define D_PIN 5
#define E_PIN 4
#define F_PIN 3
#define G_PIN 2
#define COL 3 // 3直欄
#define ROW 4 // 4橫列

// 定義矩陣鍵盤的針腳（A~G）與列欄的關係
#define COL_0_PIN A_PIN
#define COL_1_PIN B_PIN
#define COL_2_PIN C_PIN
#define ROW_0_PIN D_PIN
#define ROW_1_PIN E_PIN
#define ROW_2_PIN F_PIN
#define ROW_3_PIN G_PIN
byte rowPins[ROW] = {ROW_0_PIN, ROW_1_PIN, ROW_2_PIN, ROW_3_PIN};
byte colPins[COL] = {COL_0_PIN, COL_1_PIN, COL_2_PIN};
char keys[ROW][COL] = { // 每個按鍵所對應的字元
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
// 建立Keypad物件
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROW, COL);

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
}
void loop() {
  char key = keypad.getKey();
  if(key != NO_KEY){
    Serial.println(key);
  }
}

