#include "MotorKy010.h"

// 光遮斷計數器
// 左右二段
volatile int _ky010_l_count = 0;
volatile int _ky010_r_count = 0;

double _ky010_error_r = 0;
double _ky010_last_error_r = 0;
double _ky010_integral_r = 0;
double _ky010_derivative_r = 0;

void KY010_counter_r() { _ky010_r_count++; }
void KY010_counter_l() { _ky010_l_count++; }
void KY010_reset_pid()
{
  _ky010_error_r = 0;
  _ky010_last_error_r = 0;
  _ky010_integral_r = 0;
  _ky010_derivative_r = 0;
}

// 設定 Interrupt
void KY010_setup()
{
  // Set up opto-interrupter pins as inputs and enable pull-up resistors
  pinMode(M_KY010_L_PIN, INPUT_PULLUP);
  pinMode(M_KY010_R_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(M_KY010_L_PIN), KY010_counter_l, RISING);
  attachInterrupt(digitalPinToInterrupt(M_KY010_R_PIN), KY010_counter_r, RISING);
}

// 每 0.1 秒呼叫一次
// 由外面呼叫 (同時將 reset)
void KY010_read(int &l_count, int &r_count)
{
  l_count = _ky010_l_count;
  r_count = _ky010_r_count;
  /*
      Serial.print( "KY010 Left:");
      Serial.print( l_count );
      Serial.print( ", Right:");
      Serial.println( r_count );
  */
  _ky010_l_count = 0;
  _ky010_r_count = 0;
}

// 計算 PID
int KY010_pid(int l_count, int r_count)
{

  // 計算偏差
  _ky010_error_r = l_count - r_count;

  // 計算積分項
  _ky010_integral_r += _ky010_error_r;

  // 計算微分項
  _ky010_derivative_r = _ky010_error_r - _ky010_last_error_r;

  // 計算 PID 控制量
  double pid_output = Kp_r3 * _ky010_error_r + Ki_r3 * _ky010_integral_r + Kd_r3 * _ky010_derivative_r;

  // 更新 last_ky010_error_r
  _ky010_last_error_r = _ky010_error_r;
  /*
    if (this->print_serial)
    {
      Serial.println("\nINS_MPU6050\tgz\tInt\tDev\tpid");
      Serial.print("\t\t");
      Serial.print(_ky010_error_r);
      Serial.print("\t");
      Serial.print(_ky010_integral_r);
      Serial.print("\t");
      Serial.print(_ky010_derivative_r);
      Serial.print("\t");
      Serial.println(pid_output);
    }
   */
  return (int)pid_output;
}