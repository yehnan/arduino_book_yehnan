#include <LiquidCrystal.h>
#define LCD_RS_PIN 2
#define LCD_E_PIN 3
#define LCD_D4_PIN 4
#define LCD_D5_PIN 5
#define LCD_D6_PIN 6
#define LCD_D7_PIN 7
#define SWITCH_PIN 12
#define BOUNCE_DELAY 200
#define STONE_FALLING_DELAY 1000
#define STONE_GEN_DELAY 2000
#define LCD_ROW_NUMBER 2
#define LCD_COL_NUMBER 16
LiquidCrystal lcd(LCD_RS_PIN, LCD_E_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

#define ENEMY_MAX 5
typedef struct{
  boolean live;
  int x;
  int y;
}Enemy;
Enemy enemies[ENEMY_MAX];
int enemy_number;
void genEnemy(){
  if(enemy_number < ENEMY_MAX){
    for(int i = 0; i < ENEMY_MAX; i++){
      if(enemies[i].live == false){
        enemies[i].live = true;
        enemies[i].x = LCD_COL_NUMBER - 1;
        enemies[i].y = random(0, LCD_ROW_NUMBER);
        break;
      }
    }
    enemy_number++;
  }
}

void moveEnemies(){
  for(int i = 0; i < ENEMY_MAX; i++){
    if(enemies[i].live == true){
      lcd.setCursor(enemies[i].x, enemies[i].y);
      lcd.write(' ');
      enemies[i].x -= 1;
      if(enemies[i].x <= -1){
        enemies[i].live = false;
        enemy_number--;
      }
      else{
        lcd.setCursor(enemies[i].x, enemies[i].y);
        lcd.write('@');
      }
    }
  }
}

typedef enum{
  S_Start,
  S_Run,
  S_Over,
}State;
State state;

unsigned long time_previous;
unsigned long time_stone_falling;
unsigned long time_stone_gen;

void setup(){
  lcd.begin(LCD_COL_NUMBER, LCD_ROW_NUMBER);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  state = S_Start;
  time_previous = time_stone_falling = time_stone_gen = millis();
  randomSeed(analogRead(A0));
}

int player_y;
void showPlayer(){
  lcd.setCursor(0, player_y);
  lcd.write('O');
  lcd.setCursor(0, 1 - player_y);
  lcd.write(' ');
}

boolean isGameOver(){
  for(int i = 0; i < ENEMY_MAX; i++){
    if(enemies[i].live == true){
      if(enemies[i].x == 0 && enemies[i].y == player_y){
        return true;
      }
    }
  }
  return false;
}
void loop(){
  unsigned long time_current = millis();
  switch(state){
    case S_Start:
      lcd.setCursor(0, 0);
      lcd.print("Game starting...");
      delay(3000);
      lcd.clear();
      player_y = 0;
      showPlayer();
      state = S_Run;
    break;
    case S_Run:
      if(time_current - time_previous >= BOUNCE_DELAY){
        time_previous = time_current;
        if(digitalRead(SWITCH_PIN) == LOW){
          player_y = 1 - player_y;
          showPlayer();
        }
      }
      if(time_current - time_stone_falling >= STONE_FALLING_DELAY){
        time_stone_falling = time_current;
        moveEnemies();
      }
      if(time_current - time_stone_gen >= STONE_GEN_DELAY){
        time_stone_gen = time_current;
        genEnemy();
      }
      if(isGameOver()){
        state = S_Over;
        delay(2000);
        lcd.clear();
        lcd.print("Game Over");
      }
    break;
    case S_Over:
    break;
  }
}

