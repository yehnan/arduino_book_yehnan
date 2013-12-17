#define R_PIN 11 // RGB LED的紅針腳
#define G_PIN 10 // RGB LED的綠針腳
#define B_PIN 9 // RGB LED的藍針腳

void setup() {
  pinMode(R_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
}
// 定義enum列舉型別代表顏色
typedef enum{
  C_RED,
  C_GREEN,
  C_BLUE,
  C_YELLOW,
  C_CYAN,
  C_MAGENTA,
  C_WHITE,
  C_BLACK,
  C_NUMBER,
} ColorEnum;
// 儲存RGB三原色的結構
typedef struct{
  boolean r; // red紅
  boolean g; // green綠
  boolean b; // blue藍
} ColorStruct;
ColorStruct colors[C_NUMBER] = {
  // 順序必須搭配之前ColorEnum裡定義的順序
  {HIGH, LOW, LOW}, // red紅
  {LOW, HIGH, LOW}, // green綠
  {LOW, LOW, HIGH}, // blue藍
  {HIGH, HIGH, LOW}, // yellow黃
  {LOW, HIGH, HIGH}, // cyan青
  {HIGH, LOW, HIGH}, // magenta洋紅
  {HIGH, HIGH, HIGH}, // white白
  {LOW, LOW, LOW}, // black黑
};

void loop() {
  int i;
  // 逐一顯示每種顏色
  for(i = C_RED; i < C_NUMBER; i++){
    digitalWrite(R_PIN, colors[i].r);
    digitalWrite(G_PIN, colors[i].g);
    digitalWrite(B_PIN, colors[i].b);
    delay(1000);
  }
}

