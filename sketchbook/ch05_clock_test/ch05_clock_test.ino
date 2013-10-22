#define SERIAL_BAUDRATE 19200
#define POS1_PIN A1
#define POS2_PIN 12
#define POS3_PIN 11
#define POS4_PIN 8
#define A_PIN 9
#define B_PIN 13
#define C_PIN 4
#define D_PIN 6
#define E_PIN 7
#define F_PIN 10
#define G_PIN A0
#define DP_PIN 5

#define POS_TOTAL 4
#define SEG_TOTAL 8
int pos_pins[POS_TOTAL] = {POS1_PIN, POS2_PIN, POS3_PIN, POS4_PIN};
int seg_pins[SEG_TOTAL] = {A_PIN, B_PIN, C_PIN, D_PIN, E_PIN, F_PIN, G_PIN, DP_PIN};

#define NUMBER_TOTAL 10
boolean numbers[NUMBER_TOTAL][SEG_TOTAL] = {
  // A, B, C, D, E, F, G, DP
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW}, // 0
  {LOW, HIGH, HIGH, LOW, LOW, LOW, LOW, LOW}, // 1
  {HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH, LOW}, // 2
  {HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH, LOW}, // 3
  {LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH, LOW}, // 4
  {HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH, LOW}, // 5
  {HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH, LOW}, // 6
  {HIGH, HIGH, HIGH, LOW, LOW, HIGH, LOW, LOW}, // 7
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW}, // 8
  {HIGH, HIGH, HIGH, HIGH, LOW, HIGH, HIGH, LOW}, // 9
};

void displayDigit(int pos, int n){
  if(pos < 0 || POS_TOTAL <= pos){
    return;
  }
  if(n < 0 || NUMBER_TOTAL <= n){
    return;
  }
  
  for(int p = 0; p < POS_TOTAL; p++){
    if(p == pos)
      digitalWrite(pos_pins[p], LOW);
    else
      digitalWrite(pos_pins[p], HIGH);
  }
  
  for(int i = 0; i < SEG_TOTAL; i++){
    digitalWrite(seg_pins[i], numbers[n][i]);
  }
}

void displayNumber(int n){
  int d[POS_TOTAL];
  n %= 10000;
  d[3] = n / 1000;
  n %= 1000;
  d[2] = n / 100;
  n %= 100;
  d[1] = n / 10;
  d[0] = n % 10;

  for(int i = 0; i < POS_TOTAL; i++){
    displayDigit(i, d[i]);
    delay(5);
  }
}

unsigned long time_previous;
void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  for(int i = 0; i < POS_TOTAL; i++){
    pinMode(pos_pins[i], OUTPUT);
    digitalWrite(pos_pins[i], HIGH);
  }
  for(int i = 0; i < SEG_TOTAL; i++){
    pinMode(seg_pins[i], OUTPUT);
    digitalWrite(seg_pins[i], LOW);
  }
  
  time_previous = millis();
}

int count = 0;
void loop() {
  unsigned long time_current = millis();
  if(time_current - time_previous > 1000){
    count++;
    time_previous += 1000;
  }

  displayNumber(count);
  Serial.println(count);
}

