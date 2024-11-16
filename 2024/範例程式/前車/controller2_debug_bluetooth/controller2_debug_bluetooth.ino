#include "const.h"
#include <SoftwareSerial.h>
#include "JsonService.h"

// 與 App 通訊的藍芽 HC05
SoftwareSerial appBT(PIN_BT_RX, PIN_BT_TX);
// 建立一個 JSON 物件
DynamicJsonDocument json(JSON_BUFFER_LEN);
JsonService btJson(&appBT, &json);

unsigned long lastTime = 0;


void servo_control()
{
  Serial.println("servo_control()");
}

void json_callback()
{
  Serial.println("\njson_callback()...");
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
      servo_control();
    } else if( type1 == '1' ) {
      int at = (int)(json["data"]["at"]);
      if( at == 1 ) {
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
      // motor.drive(x, y);
    } else if( type1 == '2')  {
      float mL = (float)(json["data"]["ml"]);
      float mR = (float)(json["data"]["mr"]);

      Serial.print("\tmL=");
      Serial.print(mL);
      Serial.print("\tmR=");
      Serial.println(mR);
    //  motor.drive2(mL, mR);
    }
  }
  else if (type0 == 'R')
  { // Response
  }
}

void attach_servos()
{
  Serial.println("attach_servos");
}

void detach_servos()
{
  Serial.println("detach_servos");
}

void setup()
{
  Serial.begin(SR_BAUD_RATE);
  appBT.begin(BT_BAUD_RATE);
  Serial.println("Controller2 DEBUG bluetooth:");

}

void loop()
{
  btJson.listen(&json_callback);
}
