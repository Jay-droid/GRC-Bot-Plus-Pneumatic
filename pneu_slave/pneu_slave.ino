#include "mpu.h"
#include <SPI.h>

//1. test ps reset
//3. add disconnect safety
//4. replace delay with millis
void setup()
{
  Serial.begin(115200);
  Serial.println("Mega restarted");
  SPCR |= _BV(SPE);
  SPI.attachInterrupt();
  pinModes();
  relaysOff();
  mpuSetup();
  Serial.println("setup khatam");
}

ISR(SPI_STC_vect)
{
  if (SPDR != 135) {
    button = SPDR;
  }
//  Serial.print("Button - "); Serial.println(button);
  resetMillis = currentMillis;
}

void loop()
{
  //  Serial.println(currentMillis - startMillis);
  currentMillis = millis();
  if (abs(currentMillis - resetMillis) > 1000) {
    resetFunc();
  }


  stopGrabberMotor();
  switch (button)
  {
    case UP:
      forward();
      //      Serial.println("Forward");
      break;

    case DOWN:
      backward();
      //      Serial.println("Back");
      break;

    case LEFT:
      left();
      //      Serial.println("Left");
      break;

    case RIGHT:
      right();
      //      Serial.println("Right");
      break;

    case UPRIGHT:
      bot.upRight(80);
      //      Serial.println("UR");
      break;

    case UPLEFT:
      bot.upLeft(80);
      //      Serial.println("UL");
      break;

    case DOWNRIGHT:
      bot.downRight(80);
      //      Serial.println("DR");
      break;

    case DOWNLEFT:
      bot.downLeft(80);
      //      Serial.println("DL");
      break;

    case CLOCKWISE:
      bot.clk(80, 80, 80, 80);
      Serial.println("clk");
      break;

    case ANTICLOCKWISE:
      bot.aclk(80, 80, 80, 80);
      Serial.println("aclk");
      break;
    //
    case L2:
      if (pwm > 110) {
        pwm -= 20;
      }
      Serial.println("Decrease by 20 - ");
      Serial.println(pwm);
      break;

    case R2:
      if (pwm < 250) {
        pwm += 20;
      }
      Serial.println("INcrease by 20 - ");
      Serial.println(pwm);
      break;

    case JOYRIGHT:
      GrabMotor.clk(100);
      Serial.print("Encoder - ");
      Serial.println(readEncoder);
      break;

    case JOYLEFT:
      GrabMotor.aclk(100);
      Serial.print("Encoder - ");
      Serial.println(readEncoder);
      break;

    case SQUARE:
      Grabber.Close();
      Serial.println("Open the grabber");
      break;

    case CIRCLE:
      Grabber.Open();
      Serial.println("Grab the arrow");
      break;

    case CROSS:
      Thrower.Close();
      Serial.println("Thrower Down");
      break;

    case TRIANGLE:
      Serial.println("Thrower Up");
      while (reedCount < 2)
      {
        if (reedSwitch == 0)
        {
          //           Serial.println("reed plus");
          reedCount++;
        }
        else
        {
          //           Serial.println("free throw");
          Thrower.Free();
        }
      }
      Serial.println("shoot");
      Thrower.Open();
      delay(100);
      reedCount = 0;
      break;

    case R3:
      mpu6050.update();
      while (mpu6050.getAngleZ() > -20) {
        mpu6050.update();
        Serial.println(mpu6050.getAngleZ());
        bot.aclk(50, 50, 50, 50);
      }
      bot.brake();
      bot.clk(50, 50, 50, 50);
      delay(50);
      bot.brake();
      break;


    case START:

      Grabber.Close();
      grabberAclk(100);
      bot.forward(50, 50, 50, 50);
      delay(700);
      bot.brake();
      
      break;

    case SELECT:
      GrabEnc.write(0);
      grabberAclk(2400);
      delay(1000);
      Thrower.Close();
      delay(1000);
      grabberAclk(2800);
      Grabber.Open();
      delay(1000);
      grabberAclk(3500);
      GrabMotor.brake();
      mpu6050.update();
      while (mpu6050.getAngleZ() > -20) {
        mpu6050.update();
        Serial.println(mpu6050.getAngleZ());
        bot.aclk(50, 50, 50, 50);
      }
      bot.brake();
      bot.clk(50, 50, 50, 50);
      delay(70);
      bot.brake();
      break;

    case PS:
      Serial.println("Reset");
      resetFunc();
      break;

    default:
      bot.brake();
      GrabMotor.brake();
      break;
  }
}

void iniPos()
{
  while (limitClk == HIGH)
  {
    GrabMotor.clk(60);
  }
  GrabEnc.write(0);
  GrabMotor.brake();
  grabberAclk(35);
  GrabEnc.write(0);
}

void grabberAclk(int pulses)
{
  while (readEncoder < pulses)
  {
    GrabMotor.aclk(50);
    //    Serial.println(GrabEnc.read());
  }
  GrabMotor.brake();
}

void grabberClk(int pulses)
{
  while (readEncoder > -pulses)
  {
    GrabMotor.clk(50);
    //    Serial.println(GrabEnc.read());
  }
  GrabMotor.brake();
}



void stopGrabberMotor()
{
  if (limitClk == LOW || limitAclk == LOW)
  {
    GrabMotor.brake();
    GrabEnc.write(0);
    if (limitClk == LOW && limitAclk == HIGH)
    {
      grabberAclk(30);
      GrabEnc.write(0);
    }
    else if (limitAclk == LOW && limitClk == HIGH)
    {
      grabberClk(30);
      GrabEnc.write(0);
    }
  }
}
