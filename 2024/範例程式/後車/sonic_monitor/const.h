#ifndef CONST_H
#define CONST_H

#define PRINT_SERIAL 1

// 每 100 ms 呼叫一次
#define TIMER_INTERVAL 100

// 藍芽設定(偵錯用)
#define PIN_BT_RX 50
#define PIN_BT_TX 51
#define BT_BAUD_RATE 9600

// HC-SR04 超音波測距模組
// 前方
#define TRIG_PIN_FRONT 4
#define ECHO_PIN_FRONT 7

// 左側(前)
#define TRIG_PIN_LEFT1 12
#define ECHO_PIN_LEFT1 13

// 左側(後)
#define TRIG_PIN_LEFT2 15
#define ECHO_PIN_LEFT2 14

// 與前車距離 12 公分 ( 120mm )
#define KEEP_DIST_FRONT 120

// 與左方牆壁距離 4 公分 ( 40mm )
#define KEEP_DIST_RIGHT 40
// 與左方牆壁距離超出 7 公分 ( 70mm ) ( 22 軌寬 - 15 車寬) 算沒有牆壁, 改用 KY010 轉速偵測直線前進
#define LOST_DIST_RIGHT 70

// 右側 (前) - 右側 (後) (距離牆壁差 單位: mm)
#define US_SHIFT_MM 8

#define MAX_DIST 400 // 超音波最大距離 mm

#endif