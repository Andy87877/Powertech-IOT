#include "ultra_sonic.h"

HCSR04 hcsr04_f(TRIG_PIN_FRONT, ECHO_PIN_FRONT, US_MIN_DIST, US_MAX_DIST);
HCSR04 hcsr04_l1(TRIG_PIN_LEFT1, ECHO_PIN_LEFT1, US_MIN_DIST, US_MAX_DIST); // 左前
HCSR04 hcsr04_l2(TRIG_PIN_LEFT2, ECHO_PIN_LEFT2, US_MIN_DIST, US_MAX_DIST); // 左後

ultra_sonic::ultra_sonic()
{
}

ultra_sonic::~ultra_sonic()
{
}

void ultra_sonic::read()
{
  // Serial.print("ultra_sonic::read()");
  this->mm_front = hcsr04_f.distanceInMillimeters();
  this->mm_left1 = hcsr04_l1.distanceInMillimeters();
  this->mm_left2 = hcsr04_l2.distanceInMillimeters() - US_SHIFT_MM; // 修正實際偏移量

  // Serial.print("ultra_sonic::read() 2");
  if (this->mm_front > MAX_DIST || this->mm_front <= -1)
    this->mm_front = MAX_DIST;
  if (this->mm_left1 > MAX_DIST || this->mm_left1 <= -1)
    this->mm_left1 = MAX_DIST;
  if (this->mm_left2 > MAX_DIST || this->mm_left2 <= -1)
    this->mm_left2 = MAX_DIST;

  this->mm_left = (this->mm_left2 + this->mm_left1) / 2;

  this->print();
}

void ultra_sonic::print()
{
  if (this->print_serial)
  {
    Serial.print("\nUltraSonic\tF: ");
    Serial.print(this->mm_front);
    Serial.print("\tR(AVG): ");
    Serial.println(this->mm_left);
    Serial.print("\tL1: ");
    Serial.println(this->mm_left1);
    Serial.print("\tL2: ");
    Serial.println(this->mm_left2);
  }
}