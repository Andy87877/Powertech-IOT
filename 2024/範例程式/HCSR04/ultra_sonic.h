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

class ultra_sonic
{
private:
	bool print_serial = false; // 要不要輸出文字到序列埠

public:
	float mm_front = 0;		   // 距離前車 mm
	float mm_left1 = 0;		   // 距離左牆 前 mm
	float mm_left2 = 0;		   // 距離左牆 後 mm

	ultra_sonic();
	~ultra_sonic();

	void setup(bool print_serial) { this->print_serial = print_serial; }
	void read();

	float getFront() { return mm_front; }
	float getLeft1() { return mm_left1; }
	float getLeft2() { return mm_left2; }
};
#endif
