#define CLOCK_PIN 2 // 595 SHCP
#define LATCH_PIN 3 // 595 STCP
#define DATA_PIN 4 // 595 DS
#define LED_NUMBER 16

void setup() {              
  pinMode(DATA_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
}

void loop() {
  int i;
  unsigned int data;
  unsigned char highbyte;
  unsigned char lowbyte;
  for (i = 0; i < LED_NUMBER; i++) {
    digitalWrite(LATCH_PIN, LOW);
    data = 0;
    bitSet(data, i);
    highbyte = (data >> 8) & 0xFF;
    lowbyte = data & 0xFF;
  
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, highbyte);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, lowbyte);
    digitalWrite(LATCH_PIN, HIGH);
    delay(100);
  }
  for (i = 0; i < LED_NUMBER; i++) {
    digitalWrite(LATCH_PIN, LOW);
    data = 0;
    bitSet(data, i);
    highbyte = (data >> 8) & 0xFF;
    lowbyte = data & 0xFF;

    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, lowbyte);
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, highbyte);
    digitalWrite(LATCH_PIN, HIGH);
    delay(100);
  }
}

