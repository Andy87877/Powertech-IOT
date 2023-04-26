#include <Ultrasonic.h>

void stop();
void gs();
void ml();
void sl();
void bl();
void sr();
void mr();
void br();
void US(); // 超音波
  // US();
}

void judge(){
  US();
  digitalWrite( 7 , LOW);
  digitalWrite( 8 , LOW);
  digitalWrite( 2 , LOW);
  digitalWrite( 3 , LOW);
  digitalWrite( 6 , LOW);
  digitalWrite( 11 , LOW);
  digitalWrite( 5 , LOW);
  digitalWrite( 10 , LOW);

  if (bool_ABVAR_3_R1 && bool_ABVAR_1_L2 && bool_ABVAR_2_L1 && bool_ABVAR_4_R2) { //都黑色
    stop();
    bool_overR = 0;
    bool_overL = 0;
  }

  if (!bool_ABVAR_3_R1 && !bool_ABVAR_1_L2 && !bool_ABVAR_2_L1 && !bool_ABVAR_4_R2) { //都白色
    if (bool_overR) {
      br();
    } else if (bool_overL) {
      bl();
    } else {
      gs();
    }
  }

  if (bool_ABVAR_3_R1 && !bool_ABVAR_4_R2) { //正正
    sr();
    bool_overR = 0;
  }

  if (bool_ABVAR_2_L1 && !bool_ABVAR_1_L2) { //正正
    sl();
    bool_overL = 0;
  }

  if (bool_ABVAR_1_L2 && !bool_ABVAR_2_L1) { //正反
    ml();
    bool_overL = 1;
  }

  if (bool_ABVAR_4_R2 && !bool_ABVAR_3_R1) { //正反
    mr();
    bool_overR = 1;
  }

  if (bool_ABVAR_3_R1 && bool_ABVAR_4_R2) { //正反 兩個都碰
    mr();
    bool_overR = 1;
  }

  if (bool_ABVAR_2_L1 && bool_ABVAR_1_L2) { //正反 兩個都碰
    ml();
    bool_overL = 1;
  }

}

void US()
{
  if (( ( ( _ABVAR_8_UltraSonic ) < ( 18 ) ) && ( ( _ABVAR_8_UltraSonic ) > ( 0 ) ) ))
  {
    stop();
  }
}

void stop() {
  digitalWrite( 6 , LOW );
  analogWrite(5 , 0);
  digitalWrite( 11 , LOW );
  analogWrite(10 , 0);
  digitalWrite( 7 , LOW );
  digitalWrite( 8 , LOW );
  digitalWrite( 2 , LOW );
  digitalWrite( 3 , LOW );
  delay( 100 );
  digitalWrite( 7 , HIGH );
  digitalWrite( 8 , HIGH );
  digitalWrite( 2 , HIGH );
  digitalWrite( 3 , HIGH );
  delay( 100 );
};
void gs() {
  digitalWrite( 2 , HIGH );
  digitalWrite( 8 , HIGH );
  analogWrite(5 , 170);
  analogWrite(10 , 170);
};
void sl() {
  digitalWrite( 2 , HIGH );
  digitalWrite( 8 , HIGH );
  analogWrite(5 , 130);
  analogWrite(10 , 170);
};
void ml() {
  digitalWrite( 2 , HIGH );
  digitalWrite( 8 , HIGH );
  analogWrite(6 , 0);
  analogWrite(10 , 170);
}
void bl() {
  digitalWrite( 2 , HIGH );
  digitalWrite( 8 , HIGH );
  analogWrite(6 , 170);
  analogWrite(10 , 170);
};
void sr() {
  digitalWrite( 2 , HIGH );
  digitalWrite( 8 , HIGH );
  analogWrite(5 , 170);
  analogWrite(10 , 130);
};
void mr() {
  digitalWrite( 2 , HIGH );
  digitalWrite( 8 , HIGH );
  analogWrite(5 , 170);
  analogWrite(11 , 0);
};
void br() {
  digitalWrite( 2 , HIGH );
  digitalWrite( 8 , HIGH );
  analogWrite(5 , 170);
  analogWrite(11 , 170);
};

void L2_R2()
{
  if (( ( ( _ABVAR_1_L2 ) < ( _ABVAR_5_IR ) ) && ( ( ( _ABVAR_2_L1 ) > ( _ABVAR_5_IR ) ) && ( ( ( _ABVAR_3_R1 ) > ( _ABVAR_5_IR ) ) && ( ( _ABVAR_4_R2 ) > ( _ABVAR_5_IR ) ) ) ) ))
  {
    digitalWrite( 7 , HIGH );
    while ( ( ( analogRead(1) ) > ( _ABVAR_5_IR ) ) )
    {
      digitalWrite( 5 , LOW );
      analogWrite(6 , _ABVAR_7_MBSpeed);
      digitalWrite( 11 , LOW );
      analogWrite(10 , _ABVAR_6_MFSpeed);
    }

  }
  if (( ( ( _ABVAR_4_R2 ) < ( _ABVAR_5_IR ) ) && ( ( ( _ABVAR_3_R1 ) > ( _ABVAR_5_IR ) ) && ( ( ( _ABVAR_2_L1 ) > ( _ABVAR_5_IR ) ) && ( ( _ABVAR_1_L2 ) > ( _ABVAR_5_IR ) ) ) ) ))
  {
    digitalWrite( 3 , HIGH );
    while ( ( ( analogRead(2) ) >= ( _ABVAR_5_IR ) ) )
    {
      digitalWrite( 6 , LOW );
      analogWrite(5 , _ABVAR_6_MFSpeed);
      digitalWrite( 10 , LOW );
      analogWrite(11 , _ABVAR_7_MBSpeed);
    }

  }
}

void L1_R1()
{
  if (( ( ( _ABVAR_2_L1 ) < ( _ABVAR_5_IR ) ) && ( ( ( _ABVAR_1_L2 ) > ( _ABVAR_5_IR ) ) && ( ( ( _ABVAR_3_R1 ) > ( _ABVAR_5_IR ) ) && ( ( _ABVAR_4_R2 ) > ( _ABVAR_5_IR ) ) ) ) ))
  {
    digitalWrite( 8 , HIGH );
    digitalWrite( 5 , LOW );
    analogWrite(6 , _ABVAR_7_MBSpeed);
    digitalWrite( 11 , LOW );
    analogWrite(10 , _ABVAR_6_MFSpeed);
  }
  if (( ( ( _ABVAR_3_R1 ) < ( _ABVAR_5_IR ) ) && ( ( ( _ABVAR_4_R2 ) > ( _ABVAR_5_IR ) ) && ( ( ( _ABVAR_2_L1 ) > ( _ABVAR_5_IR ) ) && ( ( _ABVAR_1_L2 ) > ( _ABVAR_5_IR ) ) ) ) ))
  {
    digitalWrite( 2 , HIGH );
    digitalWrite( 6 , LOW );
    analogWrite(5 , _ABVAR_6_MFSpeed);
    digitalWrite( 10 , LOW );
    analogWrite(11 , _ABVAR_7_MBSpeed);
  }
}
