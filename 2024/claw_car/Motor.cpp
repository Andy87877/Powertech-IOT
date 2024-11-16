#include "Motor.h"
#include "const.h"

Motor::Motor()
{
}

Motor::~Motor()
{
}

// 控制車子前進
void Motor::drive(float x, float y)
{
      // 先不管馬達死區
      // int sp = y * MAX_SPEED;

      float abs_x = x > 0 ? x : -x;
      float abs_y = y > 0 ? y : -y;
      float rate = 1.0;
      int leftSpeed = 0;
      int rightSpeed = 0;
      int type = 0;
      if( x == 0.0 ) {
        rate = 5;
      } else {
        rate = abs_y / abs_x;
      }

      if( rate > 2 ) {
        leftSpeed  = y * MAX_SPEED + x *0.1* MAX_SPEED;
        rightSpeed = y * MAX_SPEED - x *0.1* MAX_SPEED;
        type = 1;
      } else if ( rate >= 1 ) {
        leftSpeed  = y * MAX_SPEED + x *0.3* MAX_SPEED;
        rightSpeed = y * MAX_SPEED - x *0.3* MAX_SPEED;
        type = 2;
      } else if ( rate < 1 ) {
        leftSpeed  = y * 0.3 * MAX_SPEED + x * MAX_SPEED;
        rightSpeed = y * 0.3 * MAX_SPEED - x * MAX_SPEED;
        type = 3;
      } else if ( rate <= 0.5 ) {
        leftSpeed  = y * 0.1 * MAX_SPEED + x * MAX_SPEED;
        rightSpeed = y * 0.1 * MAX_SPEED - x * MAX_SPEED;
        type = 4;
      } else {
        leftSpeed  = y * MAX_SPEED + x * MAX_SPEED;
        rightSpeed = y * MAX_SPEED - x * MAX_SPEED;
        type = 5;
      }

      // 計算左右輪速度
      // int leftSpeed = sp + x *0.3* MAX_SPEED;
      // int rightSpeed = sp - x *0.3* MAX_SPEED;

      leftSpeed = constrain(leftSpeed, -255, 255);
      rightSpeed = constrain(rightSpeed, -255, 255);

#ifdef DEBUG
      // Serial.println("Motor\ttype\tLS\tRS");
      Serial.print("\ttype:");
      Serial.print(type);
      Serial.print("\tL:");
      Serial.print(leftSpeed);
      Serial.print("\tR:");
      Serial.println(rightSpeed);
#endif

      // 控制左右馬達，讓車子前進
      if (rightSpeed > 0)
      {
            analogWrite(MR_F, rightSpeed);
            analogWrite(MR_B, 0);
      }
      else
      {
            analogWrite(MR_F, 0);
            analogWrite(MR_B, -rightSpeed);
      }

      if (leftSpeed > 0)
      {
            analogWrite(ML_F, leftSpeed);
            analogWrite(ML_B, 0);
      }
      else
      {
            analogWrite(ML_F, 0);
            analogWrite(ML_B, -leftSpeed);
      }
}

// 控制車子前進
void Motor::drive2(float mL, float mR)
{
      int leftSpeed  = mL * MAX_SPEED;
      int rightSpeed = mR * MAX_SPEED;

      leftSpeed = constrain(leftSpeed, -255, 255);
      rightSpeed = constrain(rightSpeed, -255, 255);

#ifdef DEBUG
      // Serial.println("Motor\ttype\tLS\tRS");
      Serial.print("\tL:");
      Serial.print(leftSpeed);
      Serial.print("\tR:");
      Serial.println(rightSpeed);
#endif

      // 控制左右馬達，讓車子前進
      if (rightSpeed > 0)
      {
            analogWrite(MR_F, rightSpeed);
            analogWrite(MR_B, 0);
      }
      else
      {
            analogWrite(MR_F, 0);
            analogWrite(MR_B, -rightSpeed);
      }

      if (leftSpeed > 0)
      {
            analogWrite(ML_F, leftSpeed);
            analogWrite(ML_B, 0);
      }
      else
      {
            analogWrite(ML_F, 0);
            analogWrite(ML_B, -leftSpeed);
      }
}