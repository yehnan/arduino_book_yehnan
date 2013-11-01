#include <IRremote.h>
#define SERIAL_BAUDRATE 19200
#define IR_RECEIVER_PIN 9
#define BUZZER_PIN 3

IRrecv irrecv(IR_RECEIVER_PIN);
decode_results results;

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  irrecv.blink13(true);
  irrecv.enableIRIn();
}

#define NOTE_ 0
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

typedef struct{
  unsigned long irValue;
  int note;
} IRValueNote;

#define DATA_NUMBER 9
IRValueNote data[DATA_NUMBER] = {
  {0xFF00FF, NOTE_C5},
  {0xFF807F, NOTE_D5},
  {0xFF40BF, NOTE_E5},
  {0xFFC03F, NOTE_F5},
  {0xFF20DF, NOTE_G5},
  {0xFFA05F, NOTE_A5},
  {0xFF609F, NOTE_B5},
  {0xFFE01F, NOTE_C6},
  {0xFF10EF, NOTE_D6},
};

void loop() {
  if(irrecv.decode(&results)){
    Serial.print("Value is ");
    Serial.print(results.value, HEX);
    Serial.print(", ");
    Serial.print(results.bits);
    Serial.print(" bits, decode_type is ");
    Serial.println(results.decode_type);
    int n = NOTE_;
    for(int i = 0; i < DATA_NUMBER; i++){
      if(data[i].irValue == results.value){
        n = data[i].note;
        break;
      }
    }
    if(n != NOTE_)
      tone(BUZZER_PIN, n, 3000 / 8);

    irrecv.resume();
  }
}

