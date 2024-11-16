#include "const.h"
#include <ButtonDebounce.h>
#include <SoftwareSerial.h>
#include "Servo.h"

#define USE_PCA9685_SERVO_EXPANDER
#define ENABLE_EASE_CUBIC
#include "ServoEasing.hpp"

#include "JsonService.h"
#include "Motor.h"

// 與 App 通訊的藍芽 HC05
SoftwareSerial appBT(PIN_BT_RX, PIN_BT_TX);
// 建立一個 JSON 物件
DynamicJsonDocument json(JSON_BUFFER_LEN);
JsonService btJson(&appBT, &json);
Motor motor;

unsigned long lastTime = 0;

Servo _servo1;
Servo _servo2;
Servo _servo3;
Servo _servo4;

ServoEasing servo1(PCA9685_DEFAULT_ADDRESS);
ServoEasing servo2(PCA9685_DEFAULT_ADDRESS);
ServoEasing servo3(PCA9685_DEFAULT_ADDRESS);
ServoEasing servo4(PCA9685_DEFAULT_ADDRESS);

// 預設角度
//    "{\"s0\":90,\"s1\":60,\"s2\":60,\"s3\":135,\"s4\":90,\"s5\":90}",   // M0 抬升 行進位置
int ang1 = INIT_ANG1;
int ang2 = INIT_ANG2;
int ang3 = INIT_ANG3;
int ang4 = INIT_ANG4;

void servo_control()
{
    int s0 = (int)(json["data"]["s0"]);
    int s1 = (int)(json["data"]["s1"]);
    int s2 = (int)(json["data"]["s2"]);
    int s3 = (int)(json["data"]["s3"]);
    // int s4 = (int)(json["data"]["s4"]);
    // int s5 = (int)(json["data"]["s5"]);
    /*
    Serial.print("\ts0=");
    Serial.print(s0);
    Serial.print("\ts1=");
    Serial.print(s1);
    Serial.print("\ts2=");
    Serial.print(s2);
    Serial.print("\ts3=");
    Serial.println(s3);
    */

  servo1.startEaseTo(s0, SERVO_DEGREE_PER_SECOND, START_UPDATE_BY_INTERRUPT);  // Non blocking call
  servo2.startEaseTo(s1, SERVO_DEGREE_PER_SECOND, START_UPDATE_BY_INTERRUPT);  // Non blocking call
  servo3.startEaseTo(s2, SERVO_DEGREE_PER_SECOND, START_UPDATE_BY_INTERRUPT);  // Non blocking call
  servo4.startEaseTo(s3, SERVO_DEGREE_PER_SECOND, START_UPDATE_BY_INTERRUPT);  // Non blocking call
}

void json_callback()
{
  const char *pType = (const char *)json["type"]; // Ex: C1
  const char type0 = *pType;                      // Ex: C
  const char type1 = *(pType + 1);                // Ex: 1

  Serial.print("type =");
  Serial.print(pType);
  Serial.print(", type0 =");
  Serial.print(type0);
  Serial.print(", type1 =");
  Serial.println(type1);

  if (type0 == 'M') // App Controll Message ( preset command )
  {
    // 重新 Servos 連結
    // attach_servos();
    servo_control();
  }
  else if (type0 == 'S') // App Controll Message
  {
    if( type1 == '0') {
      // 重新 Servos 連結
      // attach_servos();  // 自動 attach
      servo_control();
    } else if( type1 == '1' ) {
      int at = (int)(json["data"]["at"]);
      if( at == 1 ) {
        Serial.println("attach_servos");
        // 重新 Servos 連結
        attach_servos();
      } else if( at == 0 ) {
        Serial.println("detach_servos");
        // 重新 Servos 連結
        detach_servos();
      }
    }
  }
  else if (type0 == 'C')
  { // App Controll Message

    // 去除 Servos 連結
    // detach_servos(); // 改為手動

    Serial.print("Received C: type1=");
    Serial.print(type1);
    if( type1 == '1') {
      float x = (float)(json["data"]["x1"]);
      float y = (float)(json["data"]["y1"]);

      Serial.print("\tx1=");
      Serial.print(x);
      Serial.print("\ty1=");
      Serial.println(y);
      motor.drive(x, y);
    } else if( type1 == '2')  {
      float mL = (float)(json["data"]["ml"]);
      float mR = (float)(json["data"]["mr"]);

      Serial.print("\tmL=");
      Serial.print(mL);
      Serial.print("\tmR=");
      Serial.println(mR);
      motor.drive2(mL, mR);
    }
  }
  else if (type0 == 'R')
  { // Response
  }
}

void attach_servos()
{
  servo1.attach(PIN_SERVO_1, INIT_ANG1);
  servo2.attach(PIN_SERVO_2, INIT_ANG2);
  servo3.attach(PIN_SERVO_3, INIT_ANG3);
  servo4.attach(PIN_SERVO_4, INIT_ANG4);
}

void detach_servos()
{
  servo1.detach();
  servo2.detach();
  servo3.detach();
  servo4.detach();
}

void setup()
{
  Serial.begin(SR_BAUD_RATE);
  appBT.begin(BT_BAUD_RATE);
  Serial.println("Controller2 PCA9685:");

  servo1.InitializeAndCheckI2CConnection(&Serial);
  servo2.InitializeAndCheckI2CConnection(&Serial);
  servo3.InitializeAndCheckI2CConnection(&Serial);
  servo4.InitializeAndCheckI2CConnection(&Serial);

  // Servos 連結
  attach_servos();
  
  servo1.startEaseTo(INIT_ANG1, SERVO_DEGREE_PER_SECOND, START_UPDATE_BY_INTERRUPT);  // Non blocking call
  servo2.startEaseTo(INIT_ANG2, SERVO_DEGREE_PER_SECOND, START_UPDATE_BY_INTERRUPT);  // Non blocking call
  servo3.startEaseTo(INIT_ANG3, SERVO_DEGREE_PER_SECOND, START_UPDATE_BY_INTERRUPT);  // Non blocking call
  servo4.startEaseTo(INIT_ANG4, SERVO_DEGREE_PER_SECOND, START_UPDATE_BY_INTERRUPT);  // Non blocking call

}

void loop()
{
  btJson.listen(&json_callback);

  servo1.update();
  servo2.update();
  servo3.update();
  servo4.update();

// 注意: 當使用 App 控制時, 務必關閉 TRAINING_MODE
/*
#ifdef TRAINING_MODE

  unsigned long currentTime = millis(); // 獲取當前的時間
  if( currentTime - lastTime > 1000 ) {
    lastTime = currentTime;

    // Read Analog
    int R1 = analogRead(A0);
    int R2 = 1023 - analogRead(A1); // 反向
    int R3 = 1023 - analogRead(A2); // 反向
    int R4 = 1023 - analogRead(A3); // 反向

    ang1 = map(R1, 0, 1023, 0, 180);
  	servo1.easeTo(ang1, SERVO_ANIMATION_TIME);
    ang2 = map(R2, 0, 1023, 0, 180);
  	servo2.easeTo(ang2, SERVO_ANIMATION_TIME);
    ang3 = map(R3, 0, 1023, 0, 180);
  	servo3.easeTo(ang3, SERVO_ANIMATION_TIME);
    ang4 = map(R4, 0, 1023, 0, 180);
  	servo4.easeTo(ang4, SERVO_ANIMATION_TIME);

    Serial.print("\tR1:");
    Serial.print(R1);
    Serial.print("(");
    Serial.print(ang1);
    Serial.print(")\tR2:");
    Serial.print(R2);
    Serial.print("(");
    Serial.print(ang2);
    Serial.print(")\tR3:");
    Serial.print(R3);
    Serial.print("(");
    Serial.print(ang3);
    Serial.print(")\tR4:");
    Serial.print(R4);
    Serial.print("(");
    Serial.print(ang4);
    Serial.println(")");
  }
  // delay(MOVE_INTERVAL_MS);
#endif
*/

}
