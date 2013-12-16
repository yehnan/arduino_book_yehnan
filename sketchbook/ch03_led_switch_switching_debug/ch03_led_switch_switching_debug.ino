#define SERIAL_BAUDRATE 19200 // 序列埠傳輸速率
#define LED_PIN 11
#define SWITCH_PIN 7

boolean led_status;

void setup() {
  Serial.begin(SERIAL_BAUDRATE); // 初始化並設定傳輸速率
  pinMode(LED_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT);
  
  led_status = LOW;
  digitalWrite(LED_PIN, led_status);
}

int count = 0;

void loop() {
  boolean switch_status = digitalRead(SWITCH_PIN);
  if(switch_status == HIGH){
    led_status = led_status == HIGH ? LOW : HIGH;
    digitalWrite(LED_PIN, led_status);
    Serial.println(count);
    count++;
  }
}

