#include "Motor.h"
#include "SensorService.h"

Motor::Motor()
{
}

Motor::~Motor()
{
}

// 設定針腳輸出
void Motor::setup(bool print_serial)
{
      this->print_serial = print_serial;

      pinMode(MR_F, OUTPUT); // 设置引脚为输出模式
      pinMode(MR_B, OUTPUT);
      pinMode(ML_F, OUTPUT);
      pinMode(ML_B, OUTPUT);
}

void Motor::print_data(int need_dist, int dist, double error, double integral, double derivative, int speed, double pid_output)
{
      /*
            // Serial.println("\n\tneed\tdist\terr\ti\td");
            // Serial.println("\nNeed\tDist\tErr\tInt\tDev\tPID\tS\t\tdiff\tLS\tRS");
            Serial.println("Need\tDist\tErr\tInt\tDev\tPID\tS");
            // Serial.print("\tang\tsetting\tpid");
            // Serial.print("\tgz\tpid");
            // Serial.println("\tdiff\tLS\tRS");

            // Serial.print("\t");
            Serial.print(need_dist);
            Serial.print("\t");
            Serial.print(dist);
            Serial.print("\t");
            Serial.print(error);
            Serial.print("\t");
            Serial.print(integral);
            Serial.print("\t");
            Serial.print(derivative);

            Serial.print("\t");
            Serial.print(pid_output);
            Serial.print("\t");
            Serial.print(speed);
            // Serial.println();
      */
}

// 依據前方的距離計算需要的速度
// 取得縱向(前進/後退)速度, need_distance: 要跟前車保持的距離, distance: 目前偵測到的前車距離
int Motor::calc_speed(int need_distance, int distance)
{
      // 計算偏差
      this->error_f = (double)distance - (double)need_distance;

      // 計算積分項
      this->integral_f += this->error_f;

      // 計算微分項
      this->derivative_f = this->error_f - this->last_error_f;

      // 計算 PID 控制量
      double pid_output = Kp_f * this->error_f + Ki_f * this->integral_f + Kd_f * this->derivative_f;

      // 更新 lastthis->error_f
      this->last_error_f = this->error_f;

      // 計算左右輪速度
      int Speed = (int)pid_output;
      Speed = constrain(Speed, -255, 255);

      if (this->print_serial)
      {
            this->print_data(need_distance, distance, this->error_f, this->integral_f, this->derivative_f, Speed, pid_output);
      }

      return Speed;
}

// 轉換馬達係數
int Motor::min_speed(int speed)
{
      int new_speed = 0;
      if (speed > MIN_SPEED || speed < -MIN_SPEED)
      {
            new_speed = speed;
      }
      /*
      else if (speed > IGNORE_SPEED)
      {
            new_speed = MIN_SPEED;
      }
      else if (speed < -IGNORE_SPEED)
      {
            new_speed = -MIN_SPEED;
      }
      */
      else
      {
            new_speed = 0;
      }

      return new_speed;
}
// 轉換馬達係數
int Motor::convert_speed(int speed)
{
      int new_speed = this->min_speed(speed);

      return constrain(new_speed, -MAX_SPEED, MAX_SPEED);
}

// 控制車子與牆壁平行 (超音波)
// speed_diff 大約等於 speedL - speedR
void Motor::driveUS(int speed, int leftSpeed, int rightSpeed, String &data_json)
{
      // 主要速度使用最小速度控制部分
      // int sp = this->convert_speed(speed);

      // 計算左右輪速度
      // int leftSpeed = speed_diff;
      // int rightSpeed = sp + speedR;
      /*
      if (leftSpeed < MIN_SPEED && leftSpeed > -MIN_SPEED)
      {
            leftSpeed = 0;
      }
      if (rightSpeed < MIN_SPEED && rightSpeed > -MIN_SPEED)
      {
            rightSpeed = 0;
      }
      */
      if ((leftSpeed < MIN_SPEED && leftSpeed > -MIN_SPEED) || (rightSpeed < MIN_SPEED && rightSpeed > -MIN_SPEED))
      {
            leftSpeed = 0;
            rightSpeed = 0;
      }
      leftSpeed = constrain(leftSpeed, -255, 255);
      rightSpeed = constrain(rightSpeed, -255, 255);
      /*
      if (this->print_serial)
      {
            Serial.println("driveUS()\tS\tLS\tRS");
            Serial.print("\t\t");
            Serial.print(speed);
            Serial.print("\t");
            Serial.print(leftSpeed);
            Serial.print("\t");
            Serial.println(rightSpeed);
      }
      */
#ifdef ARDUINO_SENSORSERVICE_H
      data_json += ",\"s\":" + String(speed);
      data_json += ",\"sL\":" + String(leftSpeed);
      data_json += ",\"sR\":" + String(rightSpeed);
#endif

#ifdef MOTOR_RUN
      // 控制左右馬達，讓車子前進
      if (rightSpeed >= 0)
      {
            analogWrite(MR_F, rightSpeed);
            analogWrite(MR_B, 0);
      }
      else
      {
            analogWrite(MR_F, 0);
            analogWrite(MR_B, -rightSpeed);
      }

      if (leftSpeed >= 0)
      {
            analogWrite(ML_F, leftSpeed);
            analogWrite(ML_B, 0);
      }
      else
      {
            analogWrite(ML_F, 0);
            analogWrite(ML_B, -leftSpeed);
      }
#endif
}

// 控制車子與牆壁平行
// void Motor::drive(int speed, int speed_diff, String &data_json)
// speed_diff 大約等於 speed_dL - speed_dR
void Motor::drive(int speed, int speed_diff, String &data_json)
{
      // 因 KY010 只有正的計數
      if (speed < 0)
      {
            speed_diff = -speed_diff;
      }

      // 主要速度使用最小速度控制部分
      int sp = this->convert_speed(speed);

      // 計算左右輪速度
      int leftSpeed = sp * RL_RATE - speed_diff;
      int rightSpeed = sp + speed_diff;
      /*
      if (leftSpeed < MIN_SPEED && leftSpeed > -MIN_SPEED)
      {
            leftSpeed = 0;
      }
      if (rightSpeed < MIN_SPEED && rightSpeed > -MIN_SPEED)
      {
            rightSpeed = 0;
      }
      */
      if ((leftSpeed < MIN_SPEED && leftSpeed > -MIN_SPEED) || (rightSpeed < MIN_SPEED && rightSpeed > -MIN_SPEED))
      {
            leftSpeed = 0;
            rightSpeed = 0;
      }
      leftSpeed = constrain(leftSpeed, -255, 255);
      rightSpeed = constrain(rightSpeed, -255, 255);

      if (this->print_serial)
      {
            Serial.println("drive\tS\tSDiff\tLS\tRS");
            Serial.print("\t");
            Serial.print(speed);
            Serial.print("\t");
            Serial.print(speed_diff);
            Serial.print("\t");
            Serial.print(leftSpeed);
            Serial.print("\t");
            Serial.println(rightSpeed);
      }

#ifdef ARDUINO_SENSORSERVICE_H
      data_json += ",\"s\":" + String(speed);
      data_json += ",\"sL\":" + String(leftSpeed);
      data_json += ",\"sR\":" + String(rightSpeed);
#endif

#ifdef MOTOR_RUN
      // 控制左右馬達，讓車子動作
      if (rightSpeed >= 0)
      { // 前進
            analogWrite(MR_F, rightSpeed);
            analogWrite(MR_B, 0);
      }
      else
      { // 後退
            analogWrite(MR_F, 0);
            analogWrite(MR_B, -rightSpeed);
      }

      if (leftSpeed >= 0)
      { // 前進
            analogWrite(ML_F, leftSpeed);
            analogWrite(ML_B, 0);
      }
      else
      { // 後退
            analogWrite(ML_F, 0);
            analogWrite(ML_B, -leftSpeed);
      }
#endif
}
