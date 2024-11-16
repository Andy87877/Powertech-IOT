#include "ultra_sonic.h"

HCSR04 hcsr04_f(TRIG_PIN_FRONT, ECHO_PIN_FRONT, US_MIN_DIST, US_MAX_DIST);
HCSR04 hcsr04_l1(TRIG_PIN_LEFT1, ECHO_PIN_LEFT1, US_MIN_DIST, US_MAX_DIST); // 左前
HCSR04 hcsr04_l2(TRIG_PIN_LEFT2, ECHO_PIN_LEFT2, US_MIN_DIST, US_MAX_DIST); // 左後

ultra_sonic::ultra_sonic()
{
}

ultra_sonic::~ultra_sonic()
{
}

void ultra_sonic::read()
{
  // Serial.print("ultra_sonic::read()");
  this->mm_front = hcsr04_f.distanceInMillimeters();
  this->mm_left1 = hcsr04_l1.distanceInMillimeters();
  this->mm_left2 = hcsr04_l2.distanceInMillimeters() - US_SHIFT_MM; // 修正實際偏移量

  // Serial.print("ultra_sonic::read() 2");
  if (this->mm_front > MAX_DIST || this->mm_front <= -1)
    this->mm_front = MAX_DIST;
  if (this->mm_left1 > MAX_DIST || this->mm_left1 <= -1)
    this->mm_left1 = MAX_DIST;
  if (this->mm_left2 > MAX_DIST || this->mm_left2 <= -1)
    this->mm_left2 = MAX_DIST;

  this->mm_left = (this->mm_left2 + this->mm_left1) / 2;

  this->print();
  /*
    if (this->print_serial)
    {
      Serial.print("\nUltraSonic\tF: ");
      Serial.print(this->mm_front);
      Serial.print("\tR(AVG): ");
      Serial.println(this->mm_left);
      Serial.print("\tL2: ");
      Serial.println(this->mm_left2);
      Serial.print("\tL1: ");
      Serial.println(this->mm_left1);
    }
    */
}

// 計算左輪差 : need_distance: 要跟牆壁保持的距離, distance: 目前偵測到的牆壁距離
int ultra_sonic::calc_pid1()
{
  // 外部統一呼叫 read(), 這裡不呼叫
  // this->read();

  // 計算偏差
  this->error_r1 = this->mm_left2 - KEEP_DIST_RIGHT;

  // 計算積分項
  this->integral_r1 += this->error_r1;

  // 計算微分項
  this->derivative_r1 = this->error_r1 - this->last_error_r1;

  // 計算 PID 控制量
  double pid_output = Kp_r1 * this->error_r1 + Ki_r1 * this->integral_r1 + Kd_r1 * this->derivative_r1;

  // 更新 lastthis->error_r
  this->last_error_r1 = this->error_r1;

  return (int)pid_output;
}

// 計算右輪差 : need_distance: 要跟牆壁保持的距離, distance: 目前偵測到的牆壁距離
int ultra_sonic::calc_pid2()
{
  // 外部統一呼叫 read(), 這裡不呼叫
  // this->read();

  // 計算偏差
  this->error_r2 = this->mm_left1 - KEEP_DIST_RIGHT;

  // 計算積分項
  this->integral_r2 += this->error_r2;

  // 計算微分項
  this->derivative_r2 = this->error_r2 - this->last_error_r2;

  // 計算 PID 控制量
  double pid_output = Kp_r2 * this->error_r2 + Ki_r1 * this->integral_r2 + Kd_r1 * this->derivative_r2;

  // 更新 lastthis->error_r
  this->last_error_r2 = this->error_r2;

  return (int)pid_output;
}

void ultra_sonic::getSpeed(int speed, int *sL, int *sR)
{
  int L2 = this->mm_left2;
  int L1 = this->mm_left1;
  int Ravg = this->mm_left;
  int Rdiff = L1 > L2 ? L1 - L2 : L2 - L1;
  *sL = speed * RL_RATE;
  *sR = speed;

  if (speed > 0)
  { // 前進

    if (Ravg == KEEP_DIST_RIGHT)
    {
      if (Rdiff > US_TOLERANCE)
      {

        if (L2 < L1)
        { // 頭往左(逆時針) 7    頭往左(逆時針) 4
          *sL -= US_K * Rdiff;
          *sR += US_K * Rdiff;
        }
        else
        { // L2 > L1 頭往右(順時針) 4  頭往右(順時針) 7
          *sL += US_K * Rdiff;
          *sR -= US_K * Rdiff;
        }
      }
      /*
      else
      {
        // 直線前進 1
        *sL = speed;
        *sR = speed;
      }
      */
    }
    else if (Ravg > KEEP_DIST_RIGHT)
    {                           // 距離過大
      if (Rdiff > US_TOLERANCE) // 已超出容許誤差
      {

        if (L2 < L1)
        { // 頭往左(逆時針) 8 Checked
          *sL -= US_K * Rdiff;
          *sR += US_K * Rdiff;
        }
        /*
        else
        { // L2 > L1 直線前進 5 Checked
          *sL = speed;
          *sR = speed;
        }
        */
      }
      else // 低於容許誤差
      {
        // 頭往左(逆時針) 2
        *sL -= US_K * Rdiff;
        *sR += US_K * Rdiff;
        // *sL = speed + US_K * Rdiff;
        // *sR = speed - US_K * Rdiff;
      }
    }
    else
    { // 距離過小
      if (Rdiff > US_TOLERANCE)
      {

        if (L2 > L1)
        { // L2 > L1 頭往右(順時針) 6  Checked
          *sL += US_K * Rdiff;
          *sR -= US_K * Rdiff;
        }
      }
      else
      {
        // 頭往右(順時針) 3  Checked
        *sL += US_K * Rdiff;
        *sR -= US_K * Rdiff;
      }
    }
  }
  else if (speed < 0)
  { // 後退

    if (Ravg == KEEP_DIST_RIGHT)
    {
      if (Rdiff > US_TOLERANCE)
      {

        if (L2 < L1)
        { // 頭往左(逆時針) 16 Checked
          *sL -= US_K * Rdiff;
          *sR += US_K * Rdiff;
        }
        else
        { // L2 > L1 頭往右(順時針) 13 Checked
          *sL += US_K * Rdiff;
          *sR -= US_K * Rdiff;
        }
      }
      /*
      else
      {
        // 直線後退 10 Checked
        *sL = speed;
        *sR = speed;
      }
      */
    }
    else if (Ravg > KEEP_DIST_RIGHT)
    { // 距離過大
      if (Rdiff > US_TOLERANCE)
      {
        if (L2 > L1)
        { // L2 > L1 頭往右(順時針) 14 頭往右(順時針) 17
          *sL += US_K * Rdiff;
          *sR -= US_K * Rdiff;
        }
      }
      else
      {
        // 頭往右(順時針) 11
        *sL += US_K * Rdiff;
        *sR -= US_K * Rdiff;
      }
    }
    else
    { // Ravg < KEEP_DIST_RIGHT
      if (Rdiff > US_TOLERANCE)
      {

        if (L2 > L1)
        { // L2 > L1 頭往左(逆時針) 18 頭往右(順時針) 18
          *sL -= US_K * Rdiff;
          *sR += US_K * Rdiff;
        }
      }
      else
      {
        // 頭往左(逆時針) 12 頭往右(順時針) 12
        *sL -= US_K * Rdiff;
        *sR += US_K * Rdiff;
      }
    }
  }
  /*
    Serial.print("getSpeed\tsL:");
    Serial.print(*sL);
    Serial.print("\tsR:");
    Serial.println(*sR);
  */
}

void ultra_sonic::print()
{
  /*
      if (this->print_serial)
      {
        Serial.println("\nUS_R1\tUS_R2\tDist\tInt\tDev\tpid");
        Serial.print("\t");
        Serial.print(this->mm_left2);
        Serial.print("\t");
        Serial.print(this->mm_left1);
        Serial.print("\t");
        Serial.print(this->integral_r);
        Serial.print("\t");
        Serial.print(this->derivative_r);
        Serial.print("\t");
        Serial.println(pid_output);
      }
  */

  if (this->print_serial)
  {
    Serial.print("\nUltraSonic\tF: ");
    Serial.print(this->mm_front);
    Serial.print("\tR(AVG): ");
    Serial.println(this->mm_left);
    Serial.print("\tL1: ");
    Serial.println(this->mm_left1);
    Serial.print("\tL2: ");
    Serial.println(this->mm_left2);
  }
}