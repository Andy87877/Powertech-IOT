#ifndef ARDUINO_MOTOR_H
#define ARDUINO_MOTOR_H
#include <Arduino.h>
#include "const.h"

// 不計速度之誤差值
#define IGNORE_SPEED 80
// 馬達運轉最小值
#define MIN_SPEED 120
// 馬達運轉最大值
#define MAX_SPEED 250

// 帶 PID 控制的 馬達控制
class Motor
{
public:
	Motor();
	~Motor();

	// 動作
	void drive(float x, float y);
	void drive2(float mL, float mR);
};
#endif
