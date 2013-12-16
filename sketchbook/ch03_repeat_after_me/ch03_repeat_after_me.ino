#define SERIAL_BAUDRATE 19200
#define NUMBER 5 // 5個LED、5個按壓開關
// 將連接腳位儲存在陣列裡
const int switches[NUMBER] = {11, 9, 7, 5, 3};
const int leds[NUMBER] = {12, 10, 8, 6, 4};

#define Q_MAX 8 // 出題的最多個數
int questions[Q_MAX]; // 題目
int answers[Q_MAX]; // 答案
int q_num;
int answer_num;

// 狀態機的可能狀態
typedef enum{
  STATE_START,
  STATE_QUESTION,
  STATE_ANSWER,
  STATE_CORRECT,
  STATE_WRONG,
  STATE_COMPLETE,
} State;
State state;

void setup() {
  for(int i = 0; i < NUMBER; i++){
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
    pinMode(switches[i], INPUT_PULLUP);
  }

  randomSeed(analogRead(A0));
  Serial.begin(SERIAL_BAUDRATE);
  
  state = STATE_START;
  q_num = 3;
  answer_num = 0;
}

boolean checkAnswers(){ // 檢查答案對不對
  for(int i = 0; i < q_num; i++){
    if(questions[i] != answers[i]){
      return false;
    }
  }
  return true;
}

void loop() {
  switch(state){
    case STATE_START:{
      int i;
      for(i = 0; i < NUMBER; i++){
        digitalWrite(leds[i], HIGH);
      }
      delay(2000);
      for(i = 0; i < NUMBER; i++){
        digitalWrite(leds[i], LOW);
      }
      delay(2000);
      state = STATE_QUESTION;
    }
    break;
    case STATE_QUESTION:{
      int i;
      for(i = 0; i < q_num; i++){
        questions[i] = random(0, NUMBER);
      }
      for(i = 0; i < q_num; i++){
        digitalWrite(leds[questions[i]], HIGH);
        delay(500);
        digitalWrite(leds[questions[i]], LOW);
        delay(300);
      }
      answer_num = 0;
      state = STATE_ANSWER;
    }
    break;
    case STATE_ANSWER:{
      for(int i = 0; i < NUMBER; i++){
        boolean ss = digitalRead(switches[i]);
        if(ss == LOW){
          answers[answer_num] = i;
          answer_num++;
          digitalWrite(leds[i], HIGH);
          delay(300);
          digitalWrite(leds[i], LOW);
          break;
        }
      }
      
      if(answer_num == q_num){
        state = checkAnswers() ? STATE_CORRECT : STATE_WRONG;
      }
    }
    break;
    case STATE_CORRECT:{
      q_num++;
      if(q_num > Q_MAX){
        state = STATE_COMPLETE;
      }
      else{
        state = STATE_START;
      }
      delay(500);
    }
    break;
    case STATE_WRONG:{
      int i;
      for(i = 0; i < NUMBER; i++){
        digitalWrite(leds[i], HIGH);
        delay(200);
        digitalWrite(leds[i], LOW);
      }
    }
    break;
    case STATE_COMPLETE:{
      int i;
      for(i = 0; i < NUMBER; i++){
        digitalWrite(leds[i], HIGH);
      }
      delay(500);
      for(i = 0; i < NUMBER; i++){
        digitalWrite(leds[i], LOW);
      }
      delay(500);
    }
    break;
  }
}

