
#ifndef ARDUINO_MOTORKY010_H
#define ARDUINO_MOTORKY010_H
#include <Arduino.h>
#include "const.h"

// 光遮斷計數器
// 左右二段
// volatile int _ky010_l_count = 0;
// volatile int _ky010_r_count = 0;

void KY010_counter_r();
void KY010_counter_l();
void KY010_setup();
void KY010_reset_pid();

// 每 0.1 秒呼叫一次
// 由外面呼叫 (同時將 reset)
void KY010_read(int &l_count, int &r_count);

// 計算 PID
int KY010_pid(int l_count, int r_count);

#endif
