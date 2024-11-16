
#ifndef ARDUINO_SENSORSERVICE_H
#define ARDUINO_SENSORSERVICE_H
#include <Arduino.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
// #include <functional>

// typedef std::function<void(const DynamicJsonDocument)> JsonCallback;
// void (*JsonCallback)(const DynamicJsonDocument);
/*
example Callback:

void json_callback(const DynamicJsonDocument json) {
      if (json["type"] == "start")
      {
        this->on_start();
      }
      else if (json["type"] == "stop")
      {
        this->on_stop();
      }
}

*/

class JsonService
{
private:
  SoftwareSerial *pBT;
  String sTemp;
  bool b_rcv_begined = false;
  DynamicJsonDocument *pJsonDoc;

public:
  bool b_started = false;

  JsonService(SoftwareSerial *pBT, DynamicJsonDocument *pJsonDoc);
  ~JsonService();

  // void listen(void (*JsonCallback)(const DynamicJsonDocument));
  void listen(void (*JsonCallback)());

  // 傳送指令
  bool send_data(String type, String data_json);

  // 成功回應
  bool success_response();

  // 失敗回應
  bool error_response(String reason);
};
#endif
