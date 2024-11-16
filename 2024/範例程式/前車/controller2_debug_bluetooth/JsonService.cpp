#include "const.h"
#include "JsonService.h"

JsonService::JsonService(SoftwareSerial *pBT, DynamicJsonDocument *pJsonDoc)
{
  this->pBT = pBT;
  this->pJsonDoc = pJsonDoc;
  this->sTemp = "";
}

JsonService::~JsonService()
{
}

void JsonService::listen(void (*JsonCallback)())
{
  bool finished = false;
  // 等待接收來自 HC-05 模組的資料
  while (this->pBT->available() > 0)
  {
    // 讀取接收到的字元
    char c = this->pBT->read();
#ifdef DEBUG
     Serial.println( "BT:" + c );
#endif
    if (c == '\n') { // 結束字元
#ifdef DEBUG
     Serial.println( "LF" );
#endif
    }
    if (this->b_rcv_begined)
    {
      if (c == '\n') // 結束字元
      {
#ifdef DEBUG
        Serial.println("received json:");
        Serial.println(this->sTemp);
#endif
        // 解析接收到的 JSON 資料
        DeserializationError error = deserializeJson(*(this->pJsonDoc), this->sTemp);
        this->sTemp = "";
        this->b_rcv_begined = false;

#ifdef DEBUG
        Serial.print("deserializeJson json :");
        Serial.println(error.f_str()); // code());
#endif
        // 如果解析失敗，則將狀態歸零，重新接收
        if (error)
        {
#if defined( DEBUG_PT ) || defined( DEBUG )
          Serial.print("Error :");
          Serial.println(error.f_str());

          Serial.println("Error parsing JSON :(");
          Serial.print(this->sTemp);
          Serial.println(")");
#endif
          // 狀態歸零
          this->sTemp = "";
          this->b_rcv_begined = false;
        }
        else
        {
          const char *type = (*this->pJsonDoc)["type"];

#ifdef DEBUG
          Serial.print("no error (1): ");
          Serial.println(error.code());
          Serial.print("no error (2): ");
          Serial.println(error.f_str());
#endif
#ifdef DEBUG
          Serial.print("receivedJson type=");
          Serial.println(type);
#endif
          JsonCallback();
        }
      }
      else
      { // 非結束字元, 則接續
        this->sTemp += c;
      }
    }
    else
    {
      if (c == '{') // 起始字元
      {
        this->b_rcv_begined = true;
        sTemp = "{";
      }
    }
  }
}

// 傳送資料
// bool JsonService::send_data(Data *d, size_t length)
bool JsonService::send_data(String type, String data_json)
{
  String s = "{\"version\":2,";
  s += "\"type\":\"";
  s += type;
  s += "\",\"data\":";
  s += data_json;
  s += "}\n";
#ifdef DEBUG
  Serial.println("Send Command:");
  Serial.println(s);
#endif
  this->pBT->print(s);
  return true;
}

// 回應成功
bool JsonService::success_response()
{
  String s = "{\"version\":2,";
  s += "\"type\":\"R1\",";
  s += "\"message\":\"OK\"";
  s += "}\n";
#ifdef DEBUG
  Serial.println("Success Response:");
  Serial.println(s);
#endif
  this->pBT->print(s);
  return true;
}

// 回應錯誤
bool JsonService::error_response(String reason)
{
  String s = "{\"version\":2,";
  s += "\"type\":\"R0\",";
  s += "\"message\":\"";
  s += reason;
  s += "\"}\n";
#ifdef DEBUG
  Serial.println("Error Response:");
  Serial.println(s);
#endif
  this->pBT->print(s);
  return true;
}