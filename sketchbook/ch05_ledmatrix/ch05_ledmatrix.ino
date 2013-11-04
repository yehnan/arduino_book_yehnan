#include <MaxMatrix.h>
// Uno相容開發板，SS(10), MOSI(11), MISO(12), SCK(13)
#define MAX7219_DIN_PIN 11 // SPI MOSI
#define MAX7219_LOAD_PIN 10 // SPI SS(Slave Select)
#define MAX7219_CLK_PIN 13 // SPI CLK(Clock)

// Leonardo相容開發板，SS(17), MOSI(16, ICSP 4), MISO(14, ICSP 1), SCK(15, ICSP 3)
//#define MAX7219_DIN_PIN 16 // SPI MOSI
//#define MAX7219_LOAD_PIN 2 // SPI SS(Slave Select), 腳位17不易連接
//#define MAX7219_CLK_PIN 15 // SPI CLK(Clock)

#define ROW_NUM 8 // 8列
#define COL_NUM 8 // 8欄
#define LED_INTENSITY 5 // LED亮度，0~15
MaxMatrix m(MAX7219_DIN_PIN, MAX7219_LOAD_PIN, MAX7219_CLK_PIN, 1);

void setup() {
  m.init();
  m.clear(); // 清除，全部熄滅
  m.setIntensity(LED_INTENSITY); // 設定亮度
}
void loop() {
  for(int r = 0; r < ROW_NUM; r++){
    for(int c = 0; c < COL_NUM; c++){
      m.setDot(c, r, HIGH); // 逐一點亮
      delay(200);
    }
  }
  m.clear();
  delay(1000);
}

