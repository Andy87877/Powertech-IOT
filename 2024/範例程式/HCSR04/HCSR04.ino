// https://github.com/jeremylindsayni/Bifrost.Arduino.Sensors.HCSR04
//超音波
#include "ultra_sonic.h"

ultra_sonic radar;

void setup() {
  
  Serial.begin(115200);   // 與電腦序列埠連線
  Serial.println("HCSR04 test ready!\n");

  radar.setup( true );
}

void loop() {

  radar.read();
  // Serial.println("read()");
  delay( 200 );
}
