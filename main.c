int _ABVAR_1_L2 = 0 ;
int _ABVAR_2_L1 = 0 ;
int _ABVAR_3_R1 = 0 ;
int _ABVAR_4_R2 = 0 ;
int _ABVAR_5_IR = 0 ;
int _ABVAR_6_MFSpeed = 0 ;
int _ABVAR_7_MBSpeed = 0 ;
int _ABVAR_8_UltraSonic = 0 ;
int ardublockUltrasonicSensorCodeAutoGeneratedReturnCM(int trigPin, int echoPin)
{
  long duration;
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(20);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  duration = duration / 59;
  if ((duration < 2) || (duration > 300)) return false;
  return duration;
}

void US();
void L2_R2();
void L1_R1();

void setup()
{
  pinMode( 11 , OUTPUT);
  pinMode( 5 , OUTPUT);
  pinMode( 6 , OUTPUT);
  pinMode( 10 , OUTPUT);
  digitalWrite( 12 , LOW );

  Serial.begin(9600);
  pinMode( 7 , OUTPUT);
  pinMode( 8 , OUTPUT);
  pinMode( 2 , OUTPUT);
  pinMode( 3 , OUTPUT);
  pinMode( 6 , OUTPUT);
  pinMode( 11 , OUTPUT);
  pinMode( 5 , OUTPUT);
  pinMode( 10 , OUTPUT);
}

void loop()
{
  _ABVAR_1_L2 = analogRead(0) ;
  _ABVAR_2_L1 = analogRead(1) ;
  _ABVAR_3_R1 = analogRead(2) ;
  _ABVAR_4_R2 = analogRead(3) ;
  _ABVAR_5_IR = 700 ;
  _ABVAR_6_MFSpeed = 135 ;
  _ABVAR_7_MBSpeed = 130 ;
  _ABVAR_8_UltraSonic = ardublockUltrasonicSensorCodeAutoGeneratedReturnCM( 12 , 13 ) ;
  Serial.print("L2 =");
  Serial.print(_ABVAR_1_L2);
  Serial.println();
  Serial.print("L1 =");
  Serial.print(_ABVAR_2_L1);
  Serial.println();
  Serial.print("R1 =");
  Serial.print(_ABVAR_3_R1);
  Serial.println();
  Serial.print("R2 =");
  Serial.print(_ABVAR_4_R2);
  Serial.println();
  Serial.print("US =");
  Serial.print(_ABVAR_8_UltraSonic);
  Serial.println();
  digitalWrite( 7 , LOW );
  digitalWrite( 8 , LOW );
  digitalWrite( 2 , LOW );
  digitalWrite( 3 , LOW );
  if (( ( ( _ABVAR_1_L2 ) >= ( _ABVAR_5_IR ) ) && ( ( ( _ABVAR_2_L1 ) > ( _ABVAR_5_IR ) ) && ( ( ( _ABVAR_3_R1 ) > ( _ABVAR_5_IR ) ) && ( ( _ABVAR_4_R2 ) > ( _ABVAR_5_IR ) ) ) ) ))
  {
    digitalWrite( 6 , LOW );
    analogWrite(5 , _ABVAR_6_MFSpeed);
    digitalWrite( 11 , LOW );
    analogWrite(10 , _ABVAR_6_MFSpeed);
  }
  if (( ( ( _ABVAR_1_L2 ) < ( _ABVAR_5_IR ) ) && ( ( ( _ABVAR_2_L1 ) < ( _ABVAR_5_IR ) ) && ( ( ( _ABVAR_3_R1 ) < ( _ABVAR_5_IR ) ) && ( ( _ABVAR_4_R2 ) < ( _ABVAR_5_IR ) ) ) ) ))
  {
    digitalWrite( 7 , HIGH );
    digitalWrite( 8 , HIGH );
    digitalWrite( 2 , HIGH );
    digitalWrite( 3 , HIGH );
    digitalWrite( 6 , LOW );
    analogWrite(5 , 0);
    digitalWrite( 11 , LOW );
    analogWrite(10 , 0);
  }
  if (( ( ( _ABVAR_1_L2 ) < ( _ABVAR_5_IR ) ) && ( ( ( _ABVAR_2_L1 ) < ( _ABVAR_5_IR ) ) && ( ( _ABVAR_3_R1 ) < ( _ABVAR_5_IR ) ) ) ))
  {
    digitalWrite( 7 , HIGH );
    digitalWrite( 8 , HIGH );
    digitalWrite( 2 , HIGH );
    digitalWrite( 6 , LOW );
    analogWrite(5 , 0);
    digitalWrite( 11 , LOW );
    analogWrite(10 , 0);
  }
  if (( ( ( _ABVAR_4_R2 ) < ( _ABVAR_5_IR ) ) && ( ( ( _ABVAR_3_R1 ) < ( _ABVAR_5_IR ) ) && ( ( _ABVAR_2_L1 ) < ( _ABVAR_5_IR ) ) ) ))
  {
    digitalWrite( 8 , HIGH );
    digitalWrite( 2 , HIGH );
    digitalWrite( 3 , HIGH );
    digitalWrite( 6 , LOW );
    analogWrite(5 , 0);
    digitalWrite( 11 , LOW );
    analogWrite(10 , 0);
  }
  L1_R1();
  L2_R2();
  US();
}

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

void US()
{
  if (( ( ( _ABVAR_8_UltraSonic ) < ( 18 ) ) && ( ( _ABVAR_8_UltraSonic ) > ( 0 ) ) ))
  {
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
