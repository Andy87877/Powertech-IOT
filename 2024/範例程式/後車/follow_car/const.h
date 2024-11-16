#ifndef CONST_H
#define CONST_H

#define PRINT_SERIAL 1

// 每 100 ms 呼叫一次
#define TIMER_INTERVAL 100

// 藍芽設定(偵錯用)
#define PIN_BT_RX 50
#define PIN_BT_TX 51
#define BT_BAUD_RATE 38400

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

//==== 馬達接腳定義 ====
#define MR_B 11 // 5  // 左馬達輸入 Forward
#define MR_F 10 // 6  // 左馬達輸入 Backward
#define ML_B 5  // 11 // 右馬達輸入 Forward
#define ML_F 6  // 10 // 右馬達輸入 Backward

#define M_KY010_L_PIN 19 // 左馬達轉速編碼 中斷腳
#define M_KY010_R_PIN 18 // 右馬達轉速編碼 中斷腳

// 左右馬達轉速修正比例 L * RL_RATE = R
#define RL_RATE 1.4

// 蜂鳴器 註解掉就不會響
#define BUZZER 9

#define B1 2 // 按鈕1

/*
PID控制器的震盪
可能是由於參數設定不正確造成的，這时可以通過調整參數來解決。

比例係數調整：
如果系統出現過衝現象，則應該減小比例係數，
反之如果響應過慢，則可以增大比例係數。

積分時間調整：
如果系統存在靜態誤差，則可以增大積分時間以減小誤差，
但如果增大積分時間過度，則可能引起震盪。
反之，如果系統存在震盪，則可以減小積分時間以減小震盪。

微分時間調整：
微分時間的作用是減小震盪，如果系統存在震盪，則可以增加微分時間。
但是，增加微分時間也會增加系統的靈敏度，
如果增加過度，系統可能會產生不穩定的響應。

需要注意的是，每个系統都有不同的參數設定範圍，所以需要根據實際情況進行調整。
另外，一些高級的控制方法，
如模糊控制和神經網路控制等，
也可以用來處理複雜的非線性系統，以減小或消除震盪。

*/

// 縱向
#define Kp_f 3 // 5
#define Ki_f 0.05
#define Kd_f 1

// 橫向(光遮斷計數 KY010) 保持直線運動用
/*
#define Kp_r3 50
#define Ki_r3 10
#define Kd_r3 20
*/

#define Kp_r3 3
#define Ki_r3 0.01
#define Kd_r3 0.5

// 橫向(超音波 HCSR04)
#define Kp_r1 3
#define Ki_r1 0.1
#define Kd_r1 1

// 橫向(陀螺儀 GY521) 保持直線運動用
#define Kp_r2 0.1
#define Ki_r2 0.02
#define Kd_r2 0.05

#endif