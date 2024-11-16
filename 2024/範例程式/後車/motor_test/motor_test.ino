// 直流馬達模組測試

//==== 馬達接腳定義 ====
#define MR1 10 // 左馬達輸入 Forward
#define MR2 11 // 左馬達輸入 Backward
#define ML1 6  // 右馬達輸入 Forward
#define ML2 5  // 右馬達輸入 Backward

//=========設定數值=========
#define SPEED_L  100   //馬達速度 低
#define SPEED_H 200   //馬達速度 高

int speed[] = {0, SPEED_L, SPEED_H, SPEED_L, 0, -SPEED_L, -SPEED_H, -SPEED_L };
int i = 0;

void setup() {
  
  Serial.begin(38400);  // 用於手動輸入文字
  
  Serial.println("Motor L9110s Example:");
  
  // 告知使用者可以開始手動輸入訊息
    pinMode(MR1,OUTPUT);
    pinMode(MR2,OUTPUT);
    pinMode(ML1,OUTPUT);
    pinMode(ML2,OUTPUT);

  //  pinMode(B1,INPUT);
    digitalWrite(MR1, LOW);
    digitalWrite(MR1, LOW);
    digitalWrite(ML1, LOW);
    digitalWrite(ML2, LOW);
  //  digitalWrite(B1,HIGH);
    
}

void loop() {
  int s = speed[i];
  Serial.print( i ); Serial.print(" speed="); Serial.println(s);

  motor( s );
  i++;
  if( i>7 ) i=0;
  delay(1000);
}

void motor( int s )
{
  if( s > 255 ) s  =255;
  else if( s < -255 ) s = -255;  
  if( s > 0 ) {
    analogWrite(ML1, s);
    analogWrite(ML2, 0);
    analogWrite(MR1, s);
    analogWrite(MR2, 0);
  } else if( s == 0 ) {
    analogWrite(ML1, 0);
    analogWrite(ML2, 0);
    analogWrite(MR1, 0);
    analogWrite(MR2, 0);
  } else {
    analogWrite(ML1, 0);
    analogWrite(ML2,-s);
    analogWrite(MR1, 0);
    analogWrite(MR2,-s);
  }
}
