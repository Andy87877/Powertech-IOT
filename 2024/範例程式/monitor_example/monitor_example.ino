#include <SoftwareSerial.h>

// 常數
#include "const.h"

// 感測器數據監控
#include "SensorService.h"

// timer: AsyncTimer 2.4.0
#include <AsyncTimer.h>
AsyncTimer timer; // 建立AsyncTimer物件
float time = 0.0; // 時間軸

//=========相關函數=========
void timerHandler(); // 計時器定時呼叫
void readSensors();  // 讀取感測器數值

// 軸宣告
String func_axis_declaration()
{
#ifdef PRINT_SERIAL
  Serial.println("func_axis_declaration");
#endif
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
  s += "}\n"; // \n 很重要!! 請勿去掉

  return s;
}

#ifdef ARDUINO_SENSORSERVICE_H
SoftwareSerial monitorBT(PIN_BT_RX, PIN_BT_TX);
SensorService monitor(&monitorBT, func_axis_declaration);
#endif

void setup()
{

  Serial.begin(SERIAL_BAUD_RATE); // 與電腦序列埠連線
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }
#ifdef PRINT_SERIAL
  Serial.println("Arduino Monitor Ready!\n");
#endif

#ifdef ARDUINO_SENSORSERVICE_H
  monitorBT.begin(BT_BAUD_RATE);
#endif

  // 每 0.1 秒( 100 millis )定時呼叫
  timer.setInterval(timerHandler, TIMER_INTERVAL);
}

void loop()
{
  timer.handle();
}

void timerHandler()
{
  // 接收藍芽
  monitor.listen();

  // 讀取感測器數據
  readSensors();
}


// 讀取相關感測模組的數據
void readSensors()
{

#ifdef ARDUINO_SENSORSERVICE_H
  if (monitor.b_started)
  {
    // 數據模擬
    time += (float) ( TIMER_INTERVAL / 1000.0 );
    int df = (int) (64 * sin( 0.5 * 2 *3.14 *time) + 127);   // sin bias: 127, frequency: 0.5
    int dl1 = (int) (32 * sin( 0.25 * 2 *3.14 *time) + 127); // sin bias: 127, frequency: 0.25
    int dl2 = (int) (32 * cos( 0.25 * 2 *3.14 *time) + 127); // cos bias: 127, frequency: 0.25
    
    int cL = (int) (10 * sin( 0.2 * 2 *3.14 *time) + 15);    // sin bias: 15, frequency: 0.2
    int cR = (int) (10 * cos( 0.2 * 2 *3.14 *time) + 15);    // cos bias: 15, frequency: 0.2
    
    int s  = (int) (250 * sin( 0.1 * 2 *3.14 *time));   // sin bias: 0, frequency: 0.1, wave height: 250
    int sL = (int) (250 * sin( 0.1 * 2 *3.14 * ( time + 1 )));   // sin bias: 0, frequency: 0.1, wave height: 250
    int sR = (int) (250 * cos( 0.1 * 2 *3.14 *time));   // cos bias: 0, frequency: 0.1, wave height: 250

#if !defined(PRINT_SERIAL) && defined(PRINT_PLOTTER)
    Serial.print("cL:");
    Serial.print(cL);
    Serial.print(",cR:");
    Serial.print(cR);
    Serial.print(",s:");
    Serial.print(s);
    Serial.print(",sL:");
    Serial.print(sL);
    Serial.print(",sR:");
    Serial.println(sR);
#endif

    String data_json = "{";
    data_json += "\"df\":" + String(df);
    data_json += ",\"dl1\":" + String(dl1);
    data_json += ",\"dl2\":" + String(dl2);
    data_json += ",\"cL\":" + String(cL);
    data_json += ",\"cR\":" + String(cR);

    // 這邊進行相關處理
    // 例如: 馬達控制中要傳給 App 速度資訊等數據
    data_json += ",\"s\":" + String(s);
    data_json += ",\"sL\":" + String(sL);
    data_json += ",\"sR\":" + String(sR);
    data_json += "}";

#ifdef PRINT_SERIAL
    Serial.println( data_json );
#endif
    monitor.send_data(data_json);
  }
#endif
}
