// 4511解碼器連接的腳位
#define DA_PIN 2
#define DB_PIN 5
#define DC_PIN 4
#define DD_PIN 3
#define PIN_TOTAL 4
int pins[PIN_TOTAL] = {
  DA_PIN, DB_PIN, DC_PIN, DD_PIN,
};

void displayNumber(int n){
  if(n < 0 || 9 < n)
    return;
  
  for(int i = 0; i < PIN_TOTAL; i++){
    digitalWrite(pins[i], (n >> i) & 0x01);
  }
}
void setup() {
  for(int i = 0; i < PIN_TOTAL; i++){
    pinMode(pins[i], OUTPUT);   
  }
}
void loop() {
  int x;
  for(x = 0; x <= 9; x++){ // 顯示數字0~9
    displayNumber(x);
    delay(1000);
  }
}

