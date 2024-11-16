#include "const.h"
#include <ArduinoJson.h>
#include "SensorService.h"

SensorService::SensorService(SoftwareSerial *pBT)
{
  this->pBT = pBT;
}

SensorService::~SensorService()
{
}

void SensorService::listen()
{
  // Serial.println( "listen..." );

  // 等待接收來自 HC-05 模組的資料
  while (this->pBT->available() > 0)
  {
    // 讀取接收到的字元
    char c = this->pBT->read();
    // Serial.println( "BT:" + c );

    // 如果接收到的字元為 '{'，表示接收到一個 JSON 資料
    if (c == '{')
    {
      // this->d_counter++;

      // 建立一個 JSON 物件
      DynamicJsonDocument receivedJson(JSON_BUFFER_LEN);

      // 透過 HC-05 模組接收 JSON 資料
      String receivedString;
      receivedString += c;

      // 直到遇到 \n 為止
      while (this->pBT->available() > 0 && c != '\n')
      {
        c = this->pBT->read();
        receivedString += c;
      }
      // Serial.println( "received json:");
      // Serial.println( receivedString );

      // 解析接收到的 JSON 資料
      DeserializationError error = deserializeJson(receivedJson, receivedString);

      // 如果解析成功，則將資料印出到序列埠
      if (!error)
      {
        Serial.println("Received JSON data:");
        serializeJsonPretty(receivedJson, Serial);
        Serial.println();
      }
      else
      {
        Serial.println("Error parsing JSON data");
        Serial.println(receivedString);
      }

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

bool SensorService::on_start()
{

  String s = "{";
  s += "\"type\":\"start-r\",";
  s += "\"axis\":[";
  s += "{\"name\":\"df\",\"chart\":0},";
  s += "{\"name\":\"dl1\",\"chart\":0},";
  s += "{\"name\":\"dl2\",\"chart\":0},";
  s += "{\"name\":\"cL\",\"chart\":1},";
  s += "{\"name\":\"cR\",\"chart\":1},";
  s += "{\"name\":\"s\",\"chart\":2},";
  s += "{\"name\":\"sL\",\"chart\":2},";
  s += "{\"name\":\"sR\",\"chart\":2}],";
  s += "\"dt\":";
  s += TIMER_INTERVAL;
  s += "}\n";

  Serial.print("on_start() response :");
  Serial.println(s);
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
  Serial.print("on_stop() response :");
  Serial.print(s);

  delay(500);
  // 藍芽輸出
  this->pBT->print(s);

}