
#include "Config.h"
#include <SPI.h>

void setup()
{

  Serial.begin(115200);
  Serial.println("Mega restarted");
  pinMode(MISO, OUTPUT); // have to send on master in so it set as output
  SPCR |= _BV(SPE);
  SPI.attachInterrupt(); // enable spi module'
  pinModes();
  relaysOff();
}

ISR(SPI_STC_vect)
{
  button = SPDR;
}

void loop()
{
  if (button == DISC) {
    resetFunc();
  }
  if (limitClk == LOW || limitAclk == LOW)
  {
    stopGrabberMotor();
  }
  else
  {
    switch (button)
    {
      case UP:
        bot.forward(50, 50, 50, 50);
        break;

      case DOWN:
        bot.backward(50, 50, 50, 50);
        break;

      case LEFT:
        bot.left(50, 50, 50, 50);
        break;

      case RIGHT:
        bot.right(50, 50, 50, 50);
        break;

      case UPRIGHT:
        bot.upRight(50, 50, 50, 50);
        break;

      case UPLEFT:
        bot.upLeft(50, 50, 50, 50);
        break;

      case DOWNRIGHT:
        bot.downRight(50, 50, 50, 50);
        break;

      case DOWNLEFT:
        bot.downLeft(50, 50, 50, 50);
        break;

      case L1:
        GrabMotor.clk(100);
        Serial.println("gRABBER Clock");
        break;

      case R1:
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
        delay(10);
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
        iniPos();
        break;

      case SELECT:
        Grabber.Close();
        grabberAclk(25);
        GrabMotor.brake();
        //move bot forward
        delay(3000);
        grabberAclk(2400);
        delay(3000);
        Thrower.Close();
        delay(3000);
        grabberAclk(2800);
        Grabber.Open();
        delay(1000);
        grabberAclk(3500);
        GrabMotor.brake();
        break;

      default:
        GrabMotor.brake();
        break;
    }
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
