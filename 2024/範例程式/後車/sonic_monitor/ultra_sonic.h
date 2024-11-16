#ifndef ARDUINO_ULTRA_SONIC_H
#define ARDUINO_ULTRA_SONIC_H
#include <Arduino.h>
#include "const.h"
// https://github.com/jeremylindsayni/Bifrost.Arduino.Sensors.HCSR04
// 超音波
#include <hcsr04.h>

// 最小偵測距離 10 mm
#define US_MIN_DIST 10
// 最大偵測距離 400 mm
#define US_MAX_DIST 400
// 距離容許誤差 5 mm
#define US_TOLERANCE 5
// 距離轉換速度係數
#define US_K 2

class ultra_sonic
{
private:
	bool print_serial = false; // 要不要輸出文字到序列埠

public:
	float mm_front = 0; // 距離前車 mm
	float mm_left2 = 0; // 距離右牆 mm 前方
	float mm_left1 = 0; // 距離右牆 mm 後方
	float mm_left = 0;	// 距離右牆 mm (平均)

	// PID 變數1
	float error_r1 = 0;
	float last_error_r1 = 0;
	float integral_r1 = 0;
	float derivative_r1 = 0;
	// PID 變數2
	float error_r2 = 0;
	float last_error_r2 = 0;
	float integral_r2 = 0;
	float derivative_r2 = 0;

	ultra_sonic();
	~ultra_sonic();

	void setup(bool print_serial) { this->print_serial = print_serial; }
	void read();
	void print();

	int calc_pid1(); // 右前
	int calc_pid2(); // 右後

	float getFront() { return mm_front; }
	float getRight() { return mm_left; } // 這是平均值
	float getLeft2() { return mm_left2; }
	float getLeft1() { return mm_left1; }

	void getSpeed(int speed, int *sL, int *sR);

	// 是否右側前後都有牆面
	bool in_wall()
	{
		return ((this->mm_left2 <= LOST_DIST_RIGHT) && (this->mm_left1 <= LOST_DIST_RIGHT));
	}
};
#endif
