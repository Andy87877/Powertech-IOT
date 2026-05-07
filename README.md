# Powertech-IOT
PowerTech 青少年科技創作競賽 

官方網站:
http://isteam.ccda.org.tw/Client/Home

# 2022 
> 高二參加

自走車的程式碼

右邊為自走車
![alt text](/image/2022image.png)

# 2024 
> 當助教 (協助學弟妹)


跟隨車 (follow_car)
![alt text](/image/follow_car.png)


夾罐車 (claw_car)
![alt text](/image/claw_car.png)

---

# 📁 專案資料夾結構

```
Powertech-IOT/
├── README.md
├── image/                          # 圖片資源
│   ├── 2022image.png               # 2022 自走車照片
│   ├── 2024image.png               # 2024 相關照片
│   ├── claw_car.png                # 夾罐車照片
│   └── follow_car.png              # 跟隨車照片
│
├── 2022/                           # 2022 年參賽作品
│   └── main.c                      # 自走車主程式（Arduino C）
│
└── 2024/                           # 2024 年擔任助教期間的程式碼
    ├── claw_car/                   # 夾罐車（機械手臂車）主程式
    │   ├── claw_car.ino            # 主程式入口
    │   ├── const.h                 # 常數與腳位定義
    │   ├── Motor.h / Motor.cpp     # 馬達控制類別
    │   ├── JsonService.h / .cpp    # 藍芽 JSON 通訊服務
    │   ├── Buzzer.h                # 蜂鳴器工具函式
    │   ├── HCPCA9685/              # PCA9685 伺服馬達擴展板函式庫
    │   ├── HCPCA9685.zip           # 函式庫壓縮包
    │   └── doc/                    # 相關文件
    │       ├── readme.md           # HC-06 藍芽模組 AT 指令說明
    │       ├── PCA9685_Servo.docx  # PCA9685 伺服馬達使用說明
    │       ├── arduino_IIC.jpg     # I2C 接線圖
    │       ├── hc-06_AT_commands.png
    │       ├── servo問題.txt
    │       └── 設定HC05.jpg
    │
    └── 範例程式/                   # 教學用範例程式集
        ├── HCSR04/                 # HC-SR04 超音波測距範例
        │   ├── HCSR04.ino
        │   ├── const.h
        │   ├── ultra_sonic.h / .cpp
        ├── HCSR04_0/               # 超音波測距簡易範例
        │   └── HCSR04_0.ino
        ├── ky010_interrupt/        # KY-010 光遮斷器中斷計數範例
        │   └── ky010_interrupt.ino
        ├── monitor_example/        # 感測器數據即時監控範例
        │   ├── monitor_example.ino
        │   ├── SensorService.h / .cpp
        │   ├── const.h
        │   ├── monitor.jpg
        │   └── readme.md
        ├── 前車/                   # 前車（App 遙控端）相關程式
        │   ├── controller2_debug/          # 除錯版本（無藍芽）
        │   ├── controller2_debug_bluetooth/ # 藍芽除錯版本
        │   └── controller2_pca9685/        # 含 PCA9685 伺服馬達版本
        └── 後車/                   # 後車（自動跟隨端）相關程式
            ├── follow_car/         # 跟隨車完整程式
            ├── motor_test/         # 馬達模組測試程式
            ├── rc_car_example/     # 藍芽遙控車範例
            └── sonic_monitor/      # 超音波搭配監控範例
```

---

# 📄 各程式功能說明

## 2022 — 自走車 (`2022/main.c`)

自走車利用 **4 組紅外線循跡感測器**（L2、L1、R1、R2）與 **1 組超音波測距模組**（HC-SR04）來達成自動循線與避障。

### 感測器配置

| 變數 | 腳位（Analog） | 說明 |
|------|----------------|------|
| L2   | A0             | 左外側循跡感測器 |
| L1   | A1             | 左內側循跡感測器 |
| R1   | A2             | 右內側循跡感測器 |
| R2   | A3             | 右外側循跡感測器 |
| 超音波 | Trig=12 / Echo=13 | 前方障礙物偵測 |

> 感測邏輯：讀值 **≥ 850** 為白色（0），**< 850** 為黑色（1）

### 主要函式

| 函式 | 說明 |
|------|------|
| `judge()` | 主判斷邏輯，根據感測器讀值決定動作 |
| `US()` | 超音波避障，距離小於 18cm 時停車 |
| `gs()` | 直走 |
| `sl()` | 小左轉（左輪減速） |
| `ml()` | 中左轉（左輪停止） |
| `bl()` | 大左轉（左輪反轉） |
| `sr()` | 小右轉（右輪減速） |
| `mr()` | 中右轉（右輪停止） |
| `br()` | 大右轉（右輪反轉） |
| `stop()` | 停車（含短暫煞車動作） |
| `L1_R1()` | 舊版單感測器判斷（已被 `judge()` 取代） |
| `L2_R2()` | 舊版外側感測器判斷（已被 `judge()` 取代） |

### 循線邏輯說明

程式設有 `bool_overL` / `bool_overR` 旗標，記憶車子是否偏出軌道邊界，以便在全白（四感測器皆為白）時仍能以正確方向大角度修正回軌。

---

## 2024 — 夾罐車 (`2024/claw_car/`)

夾罐車為機械手臂結合移動底盤的車輛，透過 **HC-05/HC-06 藍芽模組** 接收來自 App 的 JSON 指令，控制 **4 個伺服馬達**（機械手臂）及 **2 個直流馬達**（車輪）。

### 硬體平台
- 微控制器：**Arduino Mega 2560**
- 伺服馬達擴展：**PCA9685**（I2C，16 路 PWM）
- 藍芽模組：**HC-05**（RX=Pin 50, TX=Pin 51）
- 蜂鳴器：Pin 13

### 腳位定義（`const.h`）

| 常數 | 腳位 | 說明 |
|------|------|------|
| `MR_F` | 8 | 右馬達前進 PWM |
| `MR_B` | 7 | 右馬達後退 PWM |
| `ML_F` | 5 | 左馬達前進 PWM |
| `ML_B` | 6 | 左馬達後退 PWM |
| `PIN_SERVO_1~4` | 0~3 | PCA9685 伺服馬達通道 |
| `BUZZER` | 13 | 蜂鳴器 |
| `BT_BAUD_RATE` | 9600 | 藍芽鮑率 |

### 伺服馬達預設角度

| 伺服 | 初始角度 | 說明 |
|------|----------|------|
| servo1 | 90° | 手臂旋轉 |
| servo2 | 60° | 手臂大臂 |
| servo3 | 60° | 手臂小臂 |
| servo4 | 120° | 夾爪 |

### App 通訊協定（JSON over Bluetooth）

```json
{"version": 2, "type": "<TYPE>", "data": {...}}
```

| Type 前綴 | 說明 |
|-----------|------|
| `M`  | 預設動作（伺服馬達移動到預設角度） |
| `S0` | 自訂伺服馬達角度控制 |
| `S1` | attach / detach 伺服馬達 |
| `C1` | 虛擬搖桿控制（`x1`, `y1`） |
| `C2` | 左右馬達獨立控制（`ml`, `mr`） |
| `R`  | 回應訊息 |

### 主要模組

#### `Motor.cpp / Motor.h`
馬達驅動類別，提供兩種驅動方式：

- **`drive(float x, float y)`**：搖桿輸入（-1.0 ~ 1.0），依 `y/x` 比例自動計算左右輪差速，最大速度 250 PWM。
- **`drive2(float mL, float mR)`**：直接給定左右輪速度比例（-1.0 ~ 1.0）。

#### `JsonService.cpp / JsonService.h`
藍芽 JSON 通訊服務，核心功能：

- **`listen(callback)`**：持續讀取藍芽接收緩衝區，偵測以 `{` 開頭、`\n` 結尾的 JSON 字串，解析後觸發 callback。
- **`send_data(type, data_json)`**：封裝並傳送 JSON 訊息至藍芽。
- **`success_response()`**：傳送成功回應 `R1`。
- **`error_response(reason)`**：傳送失敗回應 `R0`。

#### `Buzzer.h`
蜂鳴器工具，提供 `_beep(int times)` 函式，讓蜂鳴器響指定次數（每次 100ms，間隔 200ms）。

---

## 2024 — 範例程式集 (`2024/範例程式/`)

### HC-SR04 超音波測距 (`HCSR04/`, `HCSR04_0/`)

示範如何使用 `ultra_sonic` 封裝類別讀取前方與左側超音波感測器數值，並透過 Serial 輸出偵錯。

### KY-010 光遮斷器中斷計數 (`ky010_interrupt/`)

使用 `attachInterrupt` 接收 KY-010 光遮斷感測器的脈衝中斷，統計馬達轉速脈衝數，可用於計算車輪轉速。

### 感測器監控範例 (`monitor_example/`)

透過 **SensorService** 模組，定時（每 100ms）將模擬感測器數據以 JSON 格式傳送至藍芽監控 App（sin/cos 波形模擬），搭配 Arduino Serial Plotter 或自製 App 即時繪圖。

### 前車系列（App 遙控端）

| 資料夾 | 功能 |
|--------|------|
| `controller2_debug/` | 不含藍芽的本地除錯版，使用序列埠輸出除錯訊息，控制伺服馬達與車輪 |
| `controller2_debug_bluetooth/` | 含藍芽的除錯版，透過 HC-05 接收 App 指令 |
| `controller2_pca9685/` | 正式版，使用 PCA9685 控制多路伺服馬達（同 claw_car 架構） |

### 後車系列（自動跟隨端）

| 資料夾 | 功能 |
|--------|------|
| `follow_car/` | 完整跟隨車程式：超音波測距保持與前車距離、KY-010 光遮斷器輔助直線修正（PID 控制）、SensorService 藍芽監控 |
| `motor_test/` | L9110s 馬達驅動模組測試，以陣列循環測試不同速度（低速/高速/正轉/反轉） |
| `rc_car_example/` | 藍芽遙控車最簡範例，透過 App JSON 指令控制車輪（搖桿 C1 或按鈕 C2 模式） |
| `sonic_monitor/` | 超音波搭配 SensorService 監控，定時讀取三組超音波並透過藍芽傳回數據 |

---

## 跟隨車（`follow_car/`）詳細說明

### 超音波配置（`const.h`）

| 方向 | Trig | Echo | 用途 |
|------|------|------|------|
| 前方 | Pin 4 | Pin 7 | 偵測前車距離（目標保持 120mm） |
| 左前 | Pin 12 | Pin 13 | 偵測左側牆壁（目標保持 40mm） |
| 左後 | Pin 15 | Pin 14 | 配合左前計算車身偏角 |

### PID 控制器

| 方向 | Kp | Ki | Kd | 說明 |
|------|----|----|----|------|
| 縱向（前後） | 3 | 0.05 | 1 | 維持與前車距離 |
| 橫向 KY010 | 3 | 0.01 | 0.5 | 光遮斷器計數差值，保持直線 |
| 橫向超音波 | 3 | 0.1 | 1 | 超音波測距差值，靠牆修正 |
| 橫向陀螺儀 | 0.1 | 0.02 | 0.05 | GY-521 保持直線（備用） |

### 控制流程

```
每 100ms 執行一次 readSensors():
  1. 讀取三組超音波距離
  2. 計算縱向速度 (calc_speed) → PID 調整前後速度
  3. 讀取 KY-010 左右計數差
  4. 判斷是否偵測到牆壁 (in_wall):
     - 有牆壁 → 超音波橫向 PID 修正左右輪差速 (driveUS)
     - 無牆壁 → KY-010 PID 修正左右輪差速 (drive)
  5. 透過 SensorService 將數據傳送至監控 App
```

---

# 🔧 使用函式庫

| 函式庫 | 用途 |
|--------|------|
| `ArduinoJson` | JSON 解析與產生 |
| `ServoEasing` | 伺服馬達平滑動作（含 PCA9685 支援） |
| `SoftwareSerial` | 軟體序列埠（藍芽通訊） |
| `ButtonDebounce` | 按鈕去彈跳 |
| `AsyncTimer` | 非同步定時器 |
| `Ultrasonic` | 超音波測距（2022 版） |
| `Wire` | I2C 通訊（PCA9685） |

---

# 🔌 硬體清單

| 元件 | 型號 | 用途 |
|------|------|------|
| 微控制器 | Arduino Mega 2560 | 2024 主控板 |
| 微控制器 | Arduino（相容板） | 2022 自走車 |
| 藍芽模組 | HC-05 / HC-06 | 無線通訊 |
| 超音波模組 | HC-SR04 | 距離感測 |
| 伺服馬達擴展板 | PCA9685 | 多路 PWM 伺服控制（I2C） |
| 馬達驅動模組 | L9110s | 直流馬達驅動 |
| 光遮斷感測器 | KY-010 | 馬達轉速偵測 |
| 蜂鳴器 | 被動式蜂鳴器 | 狀態提示音 |
| 按鈕 | 一般按鈕 | 啟動 / 偵錯用 |

