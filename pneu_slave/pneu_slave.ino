#include "mpu.h"
#include <SPI.h>

void setup()
{
  Serial.begin(115200);
  Serial.println("Mega restarted");
  pinMode(MISO, OUTPUT); // have to send on master in so it set as output
  SPCR |= _BV(SPE);
  SPI.attachInterrupt();
  pinModes();
  relaysOff();
  mpuSetup();
}

ISR(SPI_STC_vect)
{
  button = SPDR;
  startMillis = currentMillis;
}

void loop()
{

  //  if (initial == 1) {
  //    currentMillis = millis();
  //    if (abs(currentMillis - startMillis) > 2000) {
  //      resetFunc();
  //    }
  //  }
  //  initial = 1;
  if (limitClk == LOW || limitAclk == LOW)
  {
    stopGrabberMotor();
  }
  switch (button)
  {
    case JOYUP:
      forward();
      Serial.println("Forward");
      break;

    case JOYDOWN:
      backward();
      Serial.println("Back");
      break;

    case JOYLEFT:
      bot.left(80, 80, 80, 80);
      Serial.println("Left");
      break;

    case JOYRIGHT:
      bot.right(80, 80, 80, 80);
      Serial.println("Right");
      break;

    case UPRIGHT:
      bot.upRight(80, 80, 50, 50);
      Serial.println("UR");
      break;

    case UPLEFT:
      bot.upLeft(50, 50, 50, 50);
      Serial.println("UL");
      break;

    case DOWNRIGHT:
      bot.downRight(50, 50, 50, 50);
      Serial.println("DR");
      break;

    case DOWNLEFT:
      bot.downLeft(50, 50, 50, 50);
      Serial.println("DL");
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
    //    case L2:
    //      if (pwm > 110) {
    //        pwm -= 20;
    //      }
    //      Serial.print("Decrease by 20 - ");
    //      Serial.println(pwm);
    //      break;
    //
    //    case R2:
    //      if (pwm < 250) {
    //        pwm += 20;
    //      }
    //      Serial.print("INcrease by 20 - ");
    //      Serial.println(pwm);
    //      break;

    case LEFT:
      GrabMotor.clk(100);
      Serial.println("gRABBER Clock");
      break;

    case RIGHT:
      GrabMotor.aclk(100);
      Serial.println("gRABBER anti");
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
      delay(5);
      Thrower.Free();
      Serial.println("Thrower Down");
      break;

    case TRIANGLE:
      Serial.println("Thrower Up");
      while (reedCount < 2)
      {
        if (reedSwitch == 0)
        {
          reedCount++;
        }
        else
        {
          Thrower.Free();
        }
      }
      Thrower.Open();
      delay(1000);
      reedCount = 0;
      break;

    case START:
      Grabber.Close();
      grabberAclk(100);
      delay(500);
      bot.forward(50, 50, 50, 50);
      delay(800);
      bot.brake();
      break;

    case SELECT:
      GrabEnc.write(0);
      grabberAclk(2400);
      delay(500);
      Thrower.Close();
      delay(500);
      grabberAclk(2800);
      Grabber.Open();
      delay(500);
      grabberAclk(3500);
      GrabMotor.brake();
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
  Serial.println("Limit Switch Brake");
}
