// 數位輸入腳
#define sensorPin 18

volatile int count = 0; // 遮断计数器
int lastState = LOW; // 上一次传感器状态

void setup() {
  pinMode(sensorPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(sensorPin), countPulses, CHANGE);
  Serial.begin(115200);
}

void loop() {
}

void countPulses() {
  int state = digitalRead(sensorPin);
  if( state == HIGH) {
    Serial.println("H");
  } else {
    Serial.println("L");
  }
  lastState = state;
}
