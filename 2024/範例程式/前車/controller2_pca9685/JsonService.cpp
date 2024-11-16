#include "const.h"
#include "JsonService.h"

JsonService::JsonService(SoftwareSerial *pBT, DynamicJsonDocument *pJsonDoc)
{
  this->pBT = pBT;
  this->pJsonDoc = pJsonDoc;
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
    // Serial.println( "BT:" + c );
    if (this->b_rcv_begined)
    {
      if (c == '\n') // 結束字元
      {
/*
#ifdef DEBUG
        Serial.println("received json:");
        Serial.println(this->sTemp);
#endif
*/
        // 建立一個 JSON 物件
        // DynamicJsonDocument receivedJson(JSON_BUFFER_LEN);

        // 解析接收到的 JSON 資料
        DeserializationError error = deserializeJson(*(this->pJsonDoc), this->sTemp);
        this->sTemp = "";
        this->b_rcv_begined = false;

        // 如果解析失敗，則將狀態歸零，重新接收
        if (error)
        {
#ifdef DEBUG
          Serial.println("Error parsing JSON data");
          Serial.println(this->sTemp);
#endif
          // 狀態歸零
          this->sTemp = "";
          this->b_rcv_begined = false;
        }
        else
        {
          // 如果解析成功，則將資料印出到序列埠
          // #ifdef DEBUG
          //           Serial.println("Received JSON data:");
          //           serializeJsonPretty(receivedJson, Serial);
          //           Serial.println();
          // #endif
          /*
                    int version = (int)(*this->pJsonDoc)["version"];
                    // #ifdef DEBUG
                    //           Serial.print("JSON API version:");
                    //           Serial.println(version);
                    // #endif
                    if (version == API_VERSION)
                    {
                      const char* type = (*this->pJsonDoc)["type"];
                      Serial.print("receivedJson type=");
                      Serial.println( type );
                      JsonCallback();
                    }
                    else
                    {
#ifdef DEBUG
                      Serial.println("JSON API version NOT Match");
#endif
                    }
          */
          const char *type = (*this->pJsonDoc)["type"];
          Serial.print("receivedJson type=");
          Serial.println(type);
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