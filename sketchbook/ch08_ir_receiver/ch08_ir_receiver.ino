#include <IRremote.h>
#define SERIAL_BAUDRATE 19200
#define IR_RECEIVER_PIN 2 // 紅外線接收器的腳位

IRrecv irrecv(IR_RECEIVER_PIN); // 建立IRrecv物件
decode_results results; // 存放訊號解碼後的資料

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  irrecv.blink13(true); // 收到資料時便閃爍連接腳位13的LED
  irrecv.enableIRIn(); // 初始化並啟用
}
void loop() {
  if(irrecv.decode(&results)){ // 解碼紅外線訊號，放在results裡
    Serial.print("Value is ");
    Serial.print(results.value, HEX);
    Serial.print(", ");
    Serial.print(results.bits);
    Serial.print(" bits, decode_type is ");
    Serial.println(results.decode_type);
    irrecv.resume(); // 必須再次呼叫resume才會進行下一次解碼
  }
}

