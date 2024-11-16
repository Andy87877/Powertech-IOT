#ifndef ARDUINO_MOTOR_H
#define ARDUINO_MOTOR_H
#include <Arduino.h>
#include "const.h"

// 不計速度之誤差值
#define IGNORE_SPEED 80
// 馬達運轉最小值
#define MIN_SPEED 110
// 馬達運轉最大值
#define MAX_SPEED 150

#define MOTOR_RUN

/*
// 馬達運轉最小值
#define MIN_SPEED 110
// 馬達運轉最大值
#define MAX_SPEED 160

// 縱向
#define Kp_f 0.6
#define Ki_f 0.1
#define Kd_f 0.2

// 橫向
#define Kp_r 0.2
#define Ki_r 0.02
#define Kd_r 0.04
*/

// 帶 PID 控制的 馬達控制
class Motor
{
private:
	bool print_serial = false;

	double error_f = 0;
	double last_error_f = 0;
	double integral_f = 0;
	double derivative_f = 0;

	double error_r = 0;
	double last_error_r = 0;
	double integral_r = 0;
	double derivative_r = 0;

public:
	// 定義 PID 控制器參數

	Motor();
	~Motor();

	// 印出資料
	void print_data(int need_dist, int dist, double error, double integral, double derivative, int speed, double pid_output);

	void setup(bool print_serial);

	// 取得縱向(前進/後退)速度, need_distance: 要跟前車保持的距離(mm), distance: 目前偵測到的前車距離(mm)
	int calc_speed(int need_distance, int distance);

	// 計算左右輪差 : need_distance: 要跟牆壁保持的距離, distance: 目前偵測到的牆壁距離
	// int calc_speed_diff(int need_distance, int distance);

	int min_speed(int speed);
	// 轉換馬達係數
	int convert_speed(int speed);

	// 前進
	void drive(int speed, int speed_diff, String &data_json);
	// 使用超音波偵測距離方式
	void driveUS(int speed, int leftSpeed, int rightSpeed, String &data_json);
};
#endif
