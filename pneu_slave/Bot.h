#include "Motor.h"
class Bot
{
  private:
    Motor m1, m2, m3, m4;

  public:

    Bot(Motor m1, Motor m2, Motor m3, Motor m4)
    {
      this->m1 = m1;
      this->m2 = m2;
      this->m3 = m3;
      this->m4 = m4;
    }
    void left(int pwm1, int pwm2, int pwm3, int pwm4) {

      
      m1.aclk(pwm1);
      m2.clk(pwm2);
      m3.clk(pwm3);
      m4.aclk(pwm4);

    }
    void right(int pwm1, int pwm2, int pwm3, int pwm4) {

      m1.clk(pwm1);
      m2.aclk(pwm2);
      m3.aclk(pwm3);
      m4.clk(pwm4);
    }
    void backward(int pwm1, int pwm2, int pwm3, int pwm4) {

      m1.clk(pwm1);
      m2.clk(pwm2);
      m3.aclk(pwm3);
      m4.aclk(pwm4);


    }
    void forward(int pwm1, int pwm2, int pwm3, int pwm4) {
      m1.aclk(pwm1);
      m2.aclk(pwm2);
      m3.clk(pwm3);
      m4.clk(pwm4);
    }
    void downLeft(int pwm) {

      m1.brake();
      m2.clk(pwm);
      m3.brake();
      m4.aclk(pwm);
    }
    void downRight(int pwm) {

      m1.aclk(pwm);
      m2.brake();
      m3.clk(pwm);
      m4.brake();
    }
    void upLeft(int pwm) {
      m1.clk(pwm);
      m2.brake();
      m3.aclk(pwm);
      m4.brake();
    }
    void upRight(int pwm) {
      m1.brake();
      m2.aclk(pwm);
      m3.brake();
      m4.clk(pwm);
    }
    void clk(int pwm1, int pwm2, int pwm3, int pwm4) {
      m1.aclk(pwm1);
      m2.aclk(pwm2);
      m3.aclk(pwm3);
      m4.aclk(pwm4);
    }
    void aclk(int pwm1, int pwm2, int pwm3, int pwm4) {
      m1.clk(pwm1);
      m2.clk(pwm2);
      m3.clk(pwm3);
      m4.clk(pwm4);
    }
    void brake() {
      m1.brake();
      m2.brake();
      m3.brake();
      m4.brake();
    }
    void testMotors(int pwm) {
      m1.clk(pwm);
      delay(3000);
      m1.aclk(pwm);
      delay(3000);
      m2.clk(pwm);
      delay(3000);
      m2.aclk(pwm);
      delay(3000);
      m3.clk(pwm);
      delay(3000);
      m3.aclk(pwm);
      delay(3000);
      m3.brake();
      m4.clk(pwm);
      delay(3000);
      m4.aclk(pwm);
      delay(3000);
       m4.brake();
    }


};
