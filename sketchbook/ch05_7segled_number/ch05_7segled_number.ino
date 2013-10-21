#define SEG_E_PIN 7
#define SEG_D_PIN 6
#define SEG_C_PIN 5
#define SEG_DP_PIN 4
#define SEG_B_PIN 3
#define SEG_A_PIN 2
#define SEG_F_PIN 9
#define SEG_G_PIN 8

#define SEG_TOTAL 8
int pins[SEG_TOTAL] = {
  SEG_A_PIN, SEG_B_PIN, SEG_C_PIN, SEG_D_PIN,
  SEG_E_PIN, SEG_F_PIN, SEG_G_PIN, SEG_DP_PIN
};

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

void displayNumber(int n, boolean dp){
  if(n < 0 || 9 < n)
    return;
  
  for(int i = 0; i < SEG_TOTAL; i++){
    digitalWrite(pins[i], numbers[n][i]);
  }
  digitalWrite(SEG_DP_PIN, dp);
}

void displayNothing(){
  for(int i = 0; i < SEG_TOTAL; i++){
    digitalWrite(pins[i], LOW);
  }
}

void setup() {
  int i;
  for(i = 0; i < SEG_TOTAL; i++){
    pinMode(pins[i], OUTPUT);   
  }
}
void loop() {
  int x;
  for(x = 0; x < NUMBER_TOTAL; x++){
    displayNumber(x, false);
    delay(1000);
    displayNothing();
  }
  for(x = 0; x < NUMBER_TOTAL; x++){
    displayNumber(x, true);
    delay(1000);
    displayNothing();
  }
}

