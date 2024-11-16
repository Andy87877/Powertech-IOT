#include "const.h"
#include <ArduinoJson.h>
#include "SensorService.h"

SensorService::SensorService(SoftwareSerial *pBT, FUNC_AXIS_DECLARATION f)
{
  this->pBT = pBT;
  this->func_on_start = f;
}

SensorService::~SensorService()
{
}

void SensorService::listen()
{
  // 等待接收來自 HC-05 模組的資料
  while (this->pBT->available() > 0)
  {
    // 讀取接收到的字元
    char c = this->pBT->read();

    // 如果接收到的字元為 '{'，表示接收到一個 JSON 資料
    if (c == '{')
    {
      // 建立一個 JSON 物件
      DynamicJsonDocument receivedJson(JSON_BUFFER_LEN);

      // 透過 HC-05 模組接收 JSON 資料
      String receivedString;
      receivedString += c;

      // 直到遇到 \n 為止
      bool bCR = ( c == '\n' );
      while (this->pBT->available() > 0 && !bCR)
      {
        c = this->pBT->read();
        receivedString += c;
        bCR = ( c == '\n' );  // 遇到結尾的 \n 才算接收完畢
      }

      if( bCR ) { // 遇到結尾的 \n 才算接收完畢

        // 解析接收到的 JSON 資料
        DeserializationError error = deserializeJson(receivedJson, receivedString);

#ifdef PRINT_SERIAL
        // 如果解析成功，則將資料印出到序列埠
        if (!error)
        {
          //  Serial.println("Received JSON data:");
          serializeJsonPretty(receivedJson, Serial);
          Serial.println();
        }
        else
        {
          Serial.println("Error parsing JSON data:");
          Serial.println(receivedString);
        }
#endif

        if (receivedJson["type"] == "start")
        {
          this->on_start();
        }
        else if (receivedJson["type"] == "stop")
        {
          this->on_stop();
        }
      }
    }
  }
}

// App 最初呼叫之回應
// 告訴 App 有哪些資料要呈現
bool SensorService::on_start()
{
  String s = this->func_on_start();
#ifdef PRINT_SERIAL
  Serial.print("on_start() response :");
  Serial.println(s);
#endif
  // 藍芽輸出
  this->pBT->print(s);

  delay(500);
  this->b_started = true;
}

// 傳送資料
// bool SensorService::send_data(Data *d, size_t length)
bool SensorService::send_data(String data_json)
{
  String s = "{";
  s += "\"type\":\"data\",\"data\":";
  s += data_json;
  s += "}\n";
  this->pBT->print(s);
  return true;
}

bool SensorService::on_stop()
{
  String s = "{";
  s += "\"type\":\"stop-r\"";
  s += "}\n";

  this->b_started = false;

#ifdef PRINT_SERIAL
  Serial.print("on_stop() response :");
  Serial.print(s);
#endif

  delay(500);
  // 藍芽輸出
  this->pBT->print(s);

}