// 定義腳位
// CLK_PIN可能是A5或9，DAT_PIN可能是A4或8
// 視擴充板版本而定
#define RST_PIN 3
#define CLK_PIN A5
#define DAT_PIN A4

void setup() {   
    pinMode(RST_PIN, OUTPUT);
    pinMode(CLK_PIN, OUTPUT); 
    pinMode(DAT_PIN, OUTPUT);
    digitalWrite(RST_PIN, HIGH);
    digitalWrite(CLK_PIN, HIGH);
    digitalWrite(DAT_PIN, HIGH);
    
    // 重置
    digitalWrite(RST_PIN, LOW);
    delay(5);
    digitalWrite(RST_PIN, HIGH);
    delay(300);
}
void loop() {
  send(0x0000); // 播放檔案0000
  delay(1000);
  send(0xFFF7); // 設定音量，0xFFF0最小（靜音），0XFFF7最大
  delay(1000);
  
  send(0xFFFE); // 暫停
  delay(1000);
  send(0xFFFE); // 播放
  // send(0xFFFF); // 停止
  
  while(1) // 進入無窮迴圈
    ;
}
// 輔助函式，將控制指令送往擴充板
void send(int data)
{
  digitalWrite(CLK_PIN, LOW);
  delay(2);
  for(int i = 15; i >= 0; i--)
  { 
    delayMicroseconds(50);
    if((data >> i) & 0x0001 > 0)
      digitalWrite(DAT_PIN, HIGH);
    else
      digitalWrite(DAT_PIN, LOW);
    delayMicroseconds(50);
    digitalWrite(CLK_PIN, HIGH);
    delayMicroseconds(50);
    
    if(i > 0)
      digitalWrite(DAT_PIN, LOW);
    else
      digitalWrite(DAT_PIN, HIGH);
    delayMicroseconds(50);
    
    if(i > 0)
      digitalWrite(CLK_PIN, LOW);
    else
      digitalWrite(CLK_PIN, HIGH);
  }
  
  delay(20); 
}

