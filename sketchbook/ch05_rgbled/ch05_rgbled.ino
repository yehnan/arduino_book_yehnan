#define R_PIN 11 // RGB LED's Red pin
#define G_PIN 10 // RGB LED's Green pin
#define B_PIN 9 // RGB LED's Blue pin

void setup() {
  pinMode(R_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
}

typedef enum{
  C_RED,
  C_GREEN,
  C_BLUE,
  C_YELLOW,
  C_CYAN,
  C_MAGENTA,
  C_WHITE,
  C_BLACK,
  C_NUMBER,
} ColorEnum;

typedef struct{
  boolean r; // red
  boolean g; // green
  boolean b; // blue
} ColorStruct;

ColorStruct colors[C_NUMBER] = {
  {HIGH, LOW, LOW}, // red
  {LOW, HIGH, LOW}, // green
  {LOW, LOW, HIGH}, // blue
  {HIGH, HIGH, LOW}, // yellow
  {LOW, HIGH, HIGH}, // cyan
  {HIGH, LOW, HIGH}, // magenta
  {HIGH, HIGH, HIGH}, // white
  {LOW, LOW, LOW}, // black
};

void loop() {
  int i;
  for(i = C_RED; i < C_NUMBER; i++){
    digitalWrite(R_PIN, colors[i].r);
    digitalWrite(G_PIN, colors[i].g);
    digitalWrite(B_PIN, colors[i].b);
    delay(1000);
  }
}

