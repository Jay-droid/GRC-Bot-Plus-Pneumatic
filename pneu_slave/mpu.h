//  M4-----F-----M1
//  |      |      |
//  |      |      |
//  L------X------R   --- NEGATIVE MPU VALUE THIS SIDE
//  |      |      |
//  |      |      |
//  M3-----B-----M2

#include "Config.h"

byte pwm = 120;
byte offset = 20;

void forward() {
  mpu6050.update();
  angleZ =  mpu6050.getAngleZ();
//  Serial.println(angleZ);
  if (angleZ < 3 && angleZ > -3)
  {
    bot.forward(pwm, pwm, pwm, pwm);
  }
  if (angleZ > 3 && angleZ < 40) //WHEN GOING LEFT SIDE
  {
    bot.forward(pwm, pwm, pwm + offset, pwm + offset);
  }
  if (angleZ < -3 && angleZ > -40) //WHEN GOING RIGHT
  {
    bot.forward(pwm + offset, pwm + offset, pwm, pwm);
  }
}

void backward() {
  mpu6050.update();
  angleZ =  mpu6050.getAngleZ();
//  Serial.println(angleZ);
  if (angleZ < 3 && angleZ > -5)
  {
    bot.backward(pwm, pwm, pwm, pwm);
  }
  if (angleZ > 3 && angleZ < 40)
  {
    bot.backward(pwm + offset, pwm + offset, pwm, pwm);
  }
  if (angleZ < -3 && angleZ > -40)
  {
    bot.backward(pwm, pwm, pwm + offset, pwm + offset);
  }
}
//
void left() {
  mpu6050.update();
  if (angleZ < 3 && angleZ > -3)
  {
    bot.left(pwm, pwm, pwm, pwm);
//    Serial.println("Left...");
  }
  else if (angleZ > 3 && angleZ < 40)
  {
    bot.left(pwm, pwm + offset, pwm + offset, pwm);
//    Serial.println("Goes Backward bt then goes Leftward");
  }
  else if (angleZ < -3 && angleZ > -40)
  {
    bot.left(pwm + offset, pwm, pwm, pwm + offset);
//    Serial.println("Goes Forward bt then goes Leftward");
  }
}


void right() {
  mpu6050.update();

  if (angleZ < 3 && angleZ > -3)
  {
    bot.right(pwm, pwm, pwm, pwm);
//    Serial.println("Right...");
  }
  else if (angleZ > 3 && angleZ < 40)
  {
    bot.right(pwm + offset, pwm, pwm, pwm + offset);
//    Serial.println("Goes Forward bt then goes Rightward");
  }
  else if (angleZ < -3 && angleZ > -40)
  {
    bot.right(pwm, pwm + offset, pwm + offset, pwm);
//    Serial.println("Goes Backward bt then goes Rightward");
  }
}


//void ftbreak()
//{
//  while (angleZ <= 1)
//  {
//
//    mpu6050.update();
//    angleZ = mpu6050.getangleZ();
//    bot.anticlockwise(40, 40, offset, offset);
//    Serial.println("Anticlockwise for 15 degrees only...");
//    //          Serial.println(mpu6050.getangleZ());
//  }
//}
//
//    //===================================Clockwise 15 degree break======================
//
//    void Negftbreak()
//    {
//      while (angleZ >= -75)
//      {
//        mpu6050.update();
//        angleZ = mpu6050.getangleZ();
//        bot.clockwise(40, 40, offset, offset);
//        Serial.println("Clockwise for 15 degrees only...");
//        //          Serial.println(mpu6050.getangleZ());
//      }
//    }

//==================================================================================
