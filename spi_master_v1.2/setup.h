#include <Ps3Controller.h>
#include <SPI.h>
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4
#define L1 5
#define L2 6
#define R1 7
#define R2 8
#define TRIANGLE 9
#define CIRCLE 10
#define CROSS 11
#define SQUARE 17
#define L3 15
#define R3 16
#define PS 12
#define START 13
#define SELECT 14
////////////////////////
#define UPRIGHT 20
#define UPLEFT 21
#define DOWNLEFT 22
#define DOWNRIGHT 23
#define CLOCKWISE 24
#define ANTICLOCKWISE 25
#define JOYUP 26
#define JOYRIGHT 27
#define JOYDOWN 28
#define JOYLEFT 29

/*#define L_UP 187
  //#define R_UP 19
  #define L_DOWN 188
  //#define R_DOWN 21
  #define L_RIGHT 189
  //#define R_RIGHT 3
  #define L_LEFT 190
  //#define R_LEFT 25
  //#define L_UP_RIGHT 26
  #define R_UP_RIGHT 191
  //#define L_DOWN_RIGHT 28
  #define R_DOWN_RIGHT 192
  //#define L_DOWN_LEFT 30
  #define R_DOWN_LEFT 193
  //#define L_UP_LEFT 32
  #define R_UP_LEFT 194
  #define AnalogLEFT 195
  #define AnalogRIGHT 196*/
#define DISC 255
#define serial_print 1
static const int spiClk = 1000000; // 1 MHz
volatile byte joy[5] = {0, 0, 0, 0, 0};
void onConnect() {
  Serial.println("Connected!.");
}

void joy_map() {
  joy[0] = map(Ps3.data.analog.stick.lx, -128, 127, 18, 253);
  joy[1] = map(Ps3.data.analog.stick.ly, -128, 127, 18, 253);
  joy[2] = map(Ps3.data.analog.stick.rx, -128, 127, 18, 253);
  joy[3] = map(Ps3.data.analog.stick.ry, -128, 127, 18, 253);
  joy[4] = 254;
}
byte set_arr(byte x) {
  joy[5] = joy[4] = joy[3] = joy[2] = joy[1] = joy[0] = x;
  return x;
}
/*******************************NONE OF YOUR CONCERN IF STATEMENTS***************************************/
/*else  if (!(Ps3.data.analog.stick.lx == -1))
  {
  int s = map(Ps3.data.analog.stick.lx, -128, 127, 0, 127);
  //      int target = (s<<4)| (lsb & 0xff)
  spi_send(s);
  Serial.println(s);
  }
  else if (!(Ps3.data.analog.stick.ly == -1))
  {
  int m = map(Ps3.data.analog.stick.ly, -128, 127, 128, 254);
  spi_send(m);
  Serial.println(m);
  }
  else if ((Ps3.data.analog.stick.lx == -1) && (Ps3.data.analog.stick.ly == -1)) {
  spi_send(64);
  Serial.println("and and");
  }
      else if (Ps3.data.analog.stick.ry < -3 && Ps3.data.analog.stick.rx < -3)
      {
      spi_send(R_UP_LEFT);
      Print("DIAG LEFT-13");
      }
      else if (Ps3.data.analog.stick.ry < -3 && Ps3.data.analog.stick.rx > 3)
      {
      spi_send(R_UP_RIGHT);
      Print("DIAG RIGHT-14");
      }
      else if (Ps3.data.analog.stick.ry > 3 && Ps3.data.analog.stick.rx > 3)
      {
      spi_send(R_DOWN_LEFT);
      Print("DIAG RIGHT BACK-15");
      }
      else if (Ps3.data.analog.stick.ry > 3 && Ps3.data.analog.stick.rx < -3)
      {
      spi_send(R_DOWN_RIGHT);
      Print("DIAG LEFT BACK-16");
      }
      else if (Ps3.data.analog.stick.ly < -5 && Ps3.data.analog.stick.lx < 10 && Ps3.data.analog.stick.lx > -10) {
      spi_send(L_UP);
      Print("FORWARD-17");
      }
      else if (Ps3.data.analog.stick.ly > 5 && Ps3.data.analog.stick.lx > -10 && Ps3.data.analog.stick.lx < 10) {
      spi_send(L_DOWN);
      Print("JOY BACKWARD-18");
      }
      else if (Ps3.data.analog.stick.lx > 5)
      {
      spi_send(L_RIGHT);
      Print("JOY RIGHT-19");
      }
      else if (Ps3.data.analog.stick.lx < -5)
      {
      spi_send(L_LEFT);
      Print("JOY LEFT-20");
      }*/
