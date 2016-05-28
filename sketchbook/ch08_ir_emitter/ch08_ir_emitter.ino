#define SERIAL_BAUDRATE 19200

#include <IRremote.h>
// 因為IRremote內部設定的關係，板子不同，
// IR LED也必須接到不同的腳位，Uno是3，Leonardo是13，
// 其他請查詢IRremote的IRremoteInt.h
IRsend irsend;

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
}
void loop() {
  byte d;
  if( (d = Serial.read()) != -1) { // 讀取序列埠
    unsigned long v = 0x0;
    switch(d){ // 對應出紅外線指令碼
      case '1':
        v = 0x77E14050;
      break;
      case '2':
        v = 0x77E12050;
      break;
      case '3':
        v = 0x77E1D050;
      break;
      case '4':
        v = 0x77E1B050;
      break;
      case '5':
        v = 0x77E1E050;
      break;
      case '6':
        v = 0x77E11050;
      break;
    }
   
    if(v != 0x0){
      Serial.print("read ");
      Serial.print(d);
      Serial.print(", IR send ");
      Serial.println(v, HEX);
      irsend.sendNEC(v, 32); // 送出符合NEC協定的指令碼
    }
  }
}

