// 七段顯示器每一段連接的腳位定義
#define SEG_E_PIN 7
#define SEG_D_PIN 6
#define SEG_C_PIN 5
#define SEG_DP_PIN 4
#define SEG_B_PIN 3
#define SEG_A_PIN 2
#define SEG_F_PIN 9
#define SEG_G_PIN 8

#define SEG_TOTAL 8 // 總共八段（包含小數點）
// 將腳位都放進陣列裡，方便存取
int pins[SEG_TOTAL] = {
  SEG_A_PIN, SEG_B_PIN, SEG_C_PIN, SEG_D_PIN,
  SEG_E_PIN, SEG_F_PIN, SEG_G_PIN, SEG_DP_PIN
};

void setup() {
  int i;
  for(i = 0; i < SEG_TOTAL; i++){
    pinMode(pins[i], OUTPUT);   
  }
}
void loop() {
  int i;
  // 使用迴圈逐一點亮某一段
  for(i = 0; i < SEG_TOTAL; i++){
    digitalWrite(pins[i], HIGH);
    delay(1000);
    digitalWrite(pins[i], LOW);
  }
}

