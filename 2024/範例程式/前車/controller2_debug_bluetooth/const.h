#ifndef CONST_H
#define CONST_H

#define API_VERSION 2
#define DEBOUNCE_TIME 250
#define JSON_BUFFER_LEN 256

#define BUZZER 13

// Nano
// #define PIN_BT_RX 3 // 2
// #define PIN_BT_TX 2 // 3
// Mega 2560
#define PIN_BT_RX 50
#define PIN_BT_TX 51

#define SR_BAUD_RATE 38400
#define BT_BAUD_RATE 19200

//==== 馬達接腳定義 ====
#define MR_F 8 // 左馬達輸入 Forward
#define MR_B 7 // 左馬達輸入 Backward
#define ML_F 5 // 右馬達輸入 Forward
#define ML_B 6 // 右馬達輸入 Backward

// 注意: 這裡是 PCA9685 Expander 的腳位
#define PIN_SERVO_1 0
#define PIN_SERVO_2 1
#define PIN_SERVO_3 2
#define PIN_SERVO_4 3

// #define ServoFrameMillis 10       // minimum time between servo updates
// #define SERVO_ANIMATION_TIME 5000 // minimum time between servo updates
#define SERVO_DEGREE_PER_SECOND 45  // 每秒幾度

// 若要偵錯主要程式, 則可開啟此旗標
#define DEBUG_PT
// 若要偵錯更多細節, 則可開啟此旗標
#define DEBUG

// 若要設定伺服馬達角度, 則可開啟此旗標
// 注意: 當使用 App 控制時, 務必關閉 TRAINING_MODE
// #define TRAINING_MODE

#define INIT_ANG1 90
#define INIT_ANG2 60
#define INIT_ANG3 60
#define INIT_ANG4 120

#endif