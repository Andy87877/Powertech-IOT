// 直流馬達模組測試

//==== 接腳定義 ====
#define ML1    8   //右馬達輸入2
#define ML2    7   //右馬達輸入1

#define MR1    5  //左馬達輸入1
#define MR2    6  //左馬達輸入2

#define B1     2   //按鈕1

//=========設定數值=========
#define SPEED_L  100   //馬達速度 低
#define SPEED_H 200   //馬達速度 高
int speed[] = {0, SPEED_L, SPEED_H, SPEED_L, 0, -SPEED_L, -SPEED_H, -SPEED_L };
int i = 0;

void setup() {
  
  Serial.begin(9600);  // 用於手動輸入文字
  
  Serial.println("Motor L9110s Test");
  
  // 告知使用者可以開始手動輸入訊息
/*
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Use Serial Mon");
  lcd.setCursor(0, 1);
  lcd.print("Type to display");
    pinMode(IR_RR,INPUT);
    pinMode(IR_R, INPUT);
    pinMode(IR_L, INPUT);
    pinMode(IR_LL,INPUT);
    pinMode(MR1,OUTPUT);
    pinMode(MR2,OUTPUT);
    pinMode(ML1,OUTPUT);
    pinMode(ML2,OUTPUT);
*/  
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
