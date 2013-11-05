#include <IRremote.h>
#define SERIAL_BAUDRATE 19200
#define IR_RECEIVER_PIN 2 // 紅外線接收器連接腳位
IRrecv irrecv(IR_RECEIVER_PIN);

// IRremote程式庫需要特別的腳位來傳送IR訊號，
// Uno使用腳位3，Leonardo使用腳位13，
// 詳情請看IRremoteInt.h
IRsend irsend;

decode_results results; // 儲存解碼後的結果
void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  irrecv.enableIRIn();
}
void loop() {
  // 從序列埠接收，若是數字1~6，送出相對應的指令碼
  byte d;
  if( (d = Serial.read()) != -1) {
    unsigned long v = 0x0;
    switch(d){
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
      irsend.sendNEC(v, 32);
      // 傳送紅外線時，就會關閉接收功能，
      // 必須再次呼叫enableIRIn重新啟動
      irrecv.enableIRIn(); // 重要！
    }
  }
  
  // 接收紅外線訊號並解碼
  if(irrecv.decode(&results)){
    Serial.print("Value is ");
    Serial.print(results.value, HEX);
    Serial.print(", ");
    Serial.print(results.bits);
    Serial.print(" bits, decode_type is ");
    Serial.println(results.decode_type);
    irrecv.resume(); // 準備進行下次解碼
  }
}
