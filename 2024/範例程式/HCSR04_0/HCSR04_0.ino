#include <hcsr04.h>

#define TRIG_PIN 12
#define ECHO_PIN 13

// HC-SR04 超音波測距模組
// 前方
#define TRIG_PIN_FRONT 4
#define ECHO_PIN_FRONT 7
// 最小偵測距離 10 mm
#define US_MIN_DIST 10
// 最大偵測距離 400 mm
#define US_MAX_DIST 400

HCSR04 hcsr04_f(TRIG_PIN_FRONT, ECHO_PIN, US_MIN_DIST, US_MAX_DIST);

void setup(){
    Serial.begin(115200);
}

void loop() {

    // Output the distance in mm
	Serial.println(hcsr04_f.distanceInMillimeters());

    // Output information about the device, driver, and distance in Bifrost JSON format
    Serial.println(hcsr04_f.ToString());

    delay(250);
}