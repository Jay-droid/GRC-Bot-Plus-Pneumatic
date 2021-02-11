//  M4-----F-----M1
//  |      |      |
//  |      |      |
//  L------+------R   --- NEGATTIVE MPU VALUE THIS SIDE
//  |      |      |
//  |      |      |
//  M3-----B-----M2

#include "Config.h"



void forward() {
  mpu6050.update();
  angleZ =  mpu6050.getAngleZ();
  Serial.println(angleZ);
  if (angleZ < 5 && angleZ > -5)
  {
    bot.forward(pwm, pwm, pwm, pwm);
  }
  if (angleZ > 5 && angleZ < 40) //WHEN GOING LEFT SIDE
  {
    bot.forward(pwm, pwm, pwm + 20, pwm + 20);
  }
  if (angleZ < -5 && angleZ > -40) //WHEN GOING RIGHT
  {
    bot.forward(pwm + 20, pwm + 20, pwm, pwm);
  }
}

void backward() {
  mpu6050.update();
  angleZ =  mpu6050.getAngleZ();
  Serial.println(angleZ);
  if (angleZ < 5 && angleZ > -5)
  {
    bot.backward(pwm, pwm, pwm, pwm);
  }
  if (angleZ > 5 && angleZ < 40)
  {
    bot.backward(pwm + 20, pwm + 20, pwm, pwm);
  }
  if(angleZ < -5 && angleZ > -40)
  {
    bot.backward(pwm, pwm, pwm + 20, pwm + 20);
  }
}
//
void left() {
  mpu6050.update();
  if (angleZ < 5 && angleZ > -5)
  {
    bot.left(pwm, pwm, pwm, pwm);
    Serial.println("Left...");
  }
  else if (angleZ > 5 && angleZ < 40)
  {
    bot.left(pwm, pwm, pwm, pwm);
    Serial.println("Goes Backward bt then goes Leftward");
  }
  else if (angleZ < -5 && angleZ > -40)
  {
    bot.left(pwm, pwm, pwm, pwm);
    Serial.println("Goes Forward bt then goes Leftward");
  }
}


void right() {
  mpu6050.update();

  if (angleZ < 5 && angleZ > -5)
  {
    bot.right(pwm, pwm, pwm, pwm);
    Serial.println("Right...");
  }
  else if (angleZ > 5 && angleZ < 40)
  {
    bot.right(pwm, pwm, pwm, pwm);
    Serial.println("Goes Forward bt then goes Rightward");
  }
  else if (angleZ < -5 && angleZ > -40)
  {
    bot.right(pwm, pwm, pwm, pwm);
    Serial.println("Goes Backward bt then goes Rightward");
  }
}


//void ftbreak()
//{
//  while (angleZ <= 1)
//  {
//
//    mpu6050.update();
//    angleZ = mpu6050.getangleZ();
//    bot.anticlockwise(40, 40, 20, 20);
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
//        bot.clockwise(40, 40, 20, 20);
//        Serial.println("Clockwise for 15 degrees only...");
//        //          Serial.println(mpu6050.getangleZ());
//      }
//    }

//==================================================================================
