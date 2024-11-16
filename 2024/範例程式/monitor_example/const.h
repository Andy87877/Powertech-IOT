#ifndef CONST_H
#define CONST_H

// 顯示文字訊息於 Serial Monitor 視窗
// 如果此項目打開, 底下的 PRINT_PLOTTER 將無效
#define PRINT_SERIAL

// 顯示文字訊息於 Serial Plotter 視窗
#define PRINT_PLOTTER

// 每 100 ms 呼叫一次
#define TIMER_INTERVAL 100

// Serial Monitor
#define SERIAL_BAUD_RATE 115200

// 藍芽設定(數據偵錯用)
//#define PIN_BT_RX 3
//#define PIN_BT_TX 2
#define PIN_BT_RX 50
#define PIN_BT_TX 51
#define BT_BAUD_RATE 38400

#endif