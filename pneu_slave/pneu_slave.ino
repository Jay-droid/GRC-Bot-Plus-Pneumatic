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
  if(SPDR != 135) {
    button = SPDR;
  }
  
  Serial.print("Button - "); Serial.println(button);
  startMillis = currentMillis;
}

void loop()
{

//  Serial.println(currentMillis - startMillis);
  currentMillis = millis();
  if (abs(currentMillis - startMillis) > 1000) {
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
      Serial.println("gRABBER Clock");
      break;

    case JOYLEFT:
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
      while (button == TRIANGLE && reedCount < 2)
      {
        if (reedSwitch == 0)
        {
          reedCount++;
        }
        else
        {
          Thrower.Free();
        }
        Serial.println("Thrower loop");
      }
      Serial.println("Exited thrower loop");
      Thrower.Open();
      reedCount = 0;
      break;

    case START:
      Grabber.Close();
      grabberAclk(100);
      delay(500);
      bot.forward(50, 50, 50, 50);
      delay(700);
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
