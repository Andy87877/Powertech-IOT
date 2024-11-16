/**
 * 這是後車超音波搭配監控程式範例
 */

#include <Wire.h>
// https://github.com/maykon/ButtonDebounce
#include <SoftwareSerial.h>

// 常數
#include "const.h"

// 超音波
#include "ultra_sonic.h"
// 馬達控制
// #include "Motor.h"

// 感測器數據監控
#include "SensorService.h"
// #include "MotorKy010.h"

// timer
// #include <arduino-timer.h>
// https://crazymaker.com.tw/arduino-how-to-use-timer/
// #include <Timer.h>
#include <AsyncTimer.h>
AsyncTimer timer; // 建立AsyncTimer物件

#ifdef ARDUINO_SENSORSERVICE_H
SoftwareSerial monitorBT(PIN_BT_RX, PIN_BT_TX);
SensorService monitor(&monitorBT);
#endif

//=========相關物件=========
ultra_sonic radar;
bool sensor_ky010 = false;

void readSensors(); // 讀取感測器數值

void setup()
{

  Serial.begin(38400); // 與電腦序列埠連線

  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Sonic Monitor Example ready!\n");

  Wire.begin();

  delay(500);

  // 前右二組超音波雷達
  radar.setup(false);

#ifdef ARDUINO_SENSORSERVICE_H
  monitorBT.begin(BT_BAUD_RATE);
#endif

  // 每 0.1 秒( 100 millis )定時呼叫
  timer.setInterval(readSensors, TIMER_INTERVAL);
}

void loop()
{
  timer.handle();
}

void readSensors()
{
  int count_L = 0, count_R = 0;

  radar.read();

  String data_json = "{";
#ifdef ARDUINO_SENSORSERVICE_H
  monitor.listen();
  data_json += "\"df\":" + String(radar.getFront(), 1);
  data_json += ",\"dl1\":" + String(radar.getLeft1(), 1);
  data_json += ",\"dl2\":" + String(radar.getLeft2(), 1);
#endif

#ifdef ARDUINO_SENSORSERVICE_H
  data_json += "}";
  // Serial.println( data_json );
  if (monitor.b_started)
  {
    monitor.send_data(data_json);
  }
#endif
}
