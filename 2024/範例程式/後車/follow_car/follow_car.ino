#include <Wire.h>
// https://github.com/maykon/ButtonDebounce
#include <ButtonDebounce.h>
#include <SoftwareSerial.h>

// 常數
#include "const.h"
// 慣性導航
// #include "INS_MPU6050.h"

// 超音波
#include "ultra_sonic.h"
// 馬達控制
#include "Motor.h"

// 感測器數據監控
#include "SensorService.h"
#include "MotorKy010.h"

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
ButtonDebounce button(B1, 350); // 50ms debounce time
ultra_sonic radar;
// INS_MPU6050 ins;
Motor motor;
bool sensor_ky010 = false;

void readSensors(); // 讀取感測器數值

void setup()
{

  Serial.begin(115200); // 與電腦序列埠連線
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Follow Car ready!\n");

  Wire.begin();

  pinMode(B1, INPUT_PULLUP);

  delay(500);

  // digitalWrite(B1, HIGH);

  // 前右二組超音波雷達
  radar.setup(false);

  // 慣性導航初始化, 需靜置到蜂鳴器響一長聲
  // ins.setup(false);

  // KY010 光遮斷計數器
  KY010_setup();

  // 馬達初始化, 需先定義 MR_F, MR_B, ML_F, ML_B 針腳常數於 const.h
  motor.setup(true);

#ifdef ARDUINO_SENSORSERVICE_H
  monitorBT.begin(BT_BAUD_RATE);
#endif

#ifdef BUZZER
  // 蜂鳴器 響 0.8 秒
  tone(BUZZER, 2000, 800);
#endif

  // 每 0.1 秒( 100 millis )定時呼叫
  timer.setInterval(readSensors, TIMER_INTERVAL);
}

void loop()
{
  button.update();
  if (button.state() == LOW)
  {
    Serial.println("Button Pressed...");
#ifdef BUZZER
    // 蜂鳴器
    tone(BUZZER, 2000, 100);
#endif
  }

  timer.handle();
}

void readSensors()
{
  int count_L = 0, count_R = 0;

  radar.read();

  // 主速度
  int speed_f = motor.calc_speed(KEEP_DIST_FRONT, radar.getFront());
  KY010_read(count_L, count_R);

  // int speed_diff = ins.calc_speed_diff();
  // 使用超音波與牆壁保持 KEEP_DIST_RIGHT mm
  // int speed_diff = 0; // radar.calc_speed_diff();

  String data_json = "{";
#ifdef ARDUINO_SENSORSERVICE_H
  monitor.listen();
  data_json += "\"df\":" + String(radar.getFront(), 1);
  data_json += ",\"dl1\":" + String(radar.getLeft1(), 1);
  data_json += ",\"dl2\":" + String(radar.getLeft2(), 1);
  data_json += ",\"cL\":" + String(count_L);
  data_json += ",\"cR\":" + String(count_R);
#endif

  if (radar.in_wall())
  { // 超音波有偵測到牆面
    if (speed_f > MIN_SPEED || speed_f < -MIN_SPEED)
    {
      int sL = 0, sR = 0;
      int speed = motor.convert_speed(speed_f);
      radar.getSpeed(speed, &sL, &sR);
      /*

            Serial.print( "in wall after radar.getSpeed\tspeed_f:" );
            Serial.print( speed_f );
            Serial.print( "\tspeed:" );
            Serial.println( speed );

            Serial.print("after getSpeed\tsL:");
            Serial.print(sL);
            Serial.print("\tsR:");
            Serial.println(sR);
            Serial.println();
      */
      // 驅動車輛
      motor.driveUS(speed, sL, sR, data_json);
    }
    else
    {
      motor.driveUS(0, 0, 0, data_json);
    }

    KY010_reset_pid();
  }
  else
  {
    // 使用光遮斷計數器 KY010 保持直線
    int speed_diff = KY010_pid(count_L, count_R);
    Serial.print("NOT in wall, speed_diff=");
    Serial.println(speed_diff);
    // 驅動車輛
    motor.drive(speed_f, speed_diff, data_json);
  }
/*
    // 使用光遮斷計數器 KY010 保持直線
    int speed_diff = KY010_pid(count_L, count_R);
    // 驅動車輛
    motor.drive(speed_f, speed_diff, data_json);
*/
#ifdef ARDUINO_SENSORSERVICE_H
  data_json += "}";
  // Serial.println( data_json );
  if (monitor.b_started)
  {
    monitor.send_data(data_json);
  }
#endif
}
