#ifndef CONST_H
#define CONST_H

#define API_VERSION 2
#define DEBOUNCE_TIME 250
#define JSON_BUFFER_LEN 256

// Nano
// #define PIN_BT_RX 3 // 2
// #define PIN_BT_TX 2 // 3
// Mega 2560
#define PIN_BT_RX 50
#define PIN_BT_TX 51

#define SR_BAUD_RATE 38400
#define BT_BAUD_RATE 9600

//==== 馬達接腳定義 ====
#define MR_F 10 // 左馬達輸入 Forward
#define MR_B 11 // 左馬達輸入 Backward
#define ML_F 6 // 右馬達輸入 Forward
#define ML_B 5 // 右馬達輸入 Backward

// 若要偵錯, 則可開啟此旗標
#define DEBUG

#endif