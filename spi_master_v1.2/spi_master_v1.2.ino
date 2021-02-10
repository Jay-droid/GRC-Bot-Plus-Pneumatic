#include "setup.h"
void setup()
{
  pinMode(5, OUTPUT);
  SPI.begin();  //hspi->begin(0, 2, 4, 33); //SCLK, MISO, MOSI, SS
  Serial.begin(115200);
  Ps3.attach(vspiCommand);
  Ps3.attachOnConnect(onConnect);
  Ps3.begin("33:33:33:33:33:33");
  Serial.println("Ready.");
  pinMode(5, OUTPUT); //VSPI SS
  pinMode(2, OUTPUT);
  digitalWrite(2, 1);
}
void spi_send(int x)
{
  SPI.beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(5, LOW); //pull SS slow to prep other end for transfer
  SPI.transfer(x);
  digitalWrite(5, HIGH); //pull ss high to signify end of Data transfer
  SPI.endTransaction();
  digitalWrite(2, 1);
}
void vspiCommand()
{
  //  if ( Ps3.event.button_up.cross ){}
  /***************************PS3 DISCONNECTED********************************************/
  if (!Ps3.isConnected()) {
    digitalWrite(2, 0);
    set_arr(0);
    spi_send(DISC);
  }
  /***********************PS3 CONNECTED************************************************/
  if (Ps3.isConnected()) {
    /*************************JOYSTICK ARRAYED DATA**********************************************/
    joy_map();
    for (byte i = 0; i < sizeof joy; i++) {
      spi_send(joy[i]);
      //      Serial.print(joy[0]); Serial.print('\t');
      //      Serial.print(joy[1]); Serial.print('\t');
      //      Serial.print(joy[2]); Serial.print('\t');
      //      Serial.print(joy[3]); Serial.print('\t'); Serial.println(joy[4]);
      //
    }
    /***********************************************************************/
    if (Ps3.data.button.l1)
    {
      spi_send(CLOCKWISE);
      Print("L1-1");
    }
    else if (Ps3.data.button.r1)
    {
      spi_send(ANTICLOCKWISE);
      Print("R1-2");
    }
    else if (Ps3.event.button_down.r2)
    {
      spi_send(R2);
      Print("R1-2");
    }
    else if (Ps3.event.button_down.l2)
    {
      spi_send(L2);
      Print("R1-2");
    }
    else if ( (Ps3.data.analog.stick.rx >= -128  && Ps3.data.analog.stick.rx < -1) &&
              (Ps3.data.analog.stick.ry >= -128  && Ps3.data.analog.stick.ry < -1)) {
      spi_send(UPLEFT);
    }
    else if ( (Ps3.data.analog.stick.rx > -1  && Ps3.data.analog.stick.rx <= 127) &&
              (Ps3.data.analog.stick.ry >= -128  && Ps3.data.analog.stick.ry < -1)) {
      spi_send(UPRIGHT);
    }
    else if ( (Ps3.data.analog.stick.rx < -1  && Ps3.data.analog.stick.rx >= -128) &&
              (Ps3.data.analog.stick.ry > -1  && Ps3.data.analog.stick.ry <= 127)) {
      spi_send(DOWNLEFT);
    }
    else if ( (Ps3.data.analog.stick.rx > -1  && Ps3.data.analog.stick.rx <= 127) &&
              (Ps3.data.analog.stick.ry <= 127  && Ps3.data.analog.stick.ry > -1)) {
      spi_send(DOWNRIGHT);
    }
    else if ( (Ps3.data.analog.stick.lx >= -128  && Ps3.data.analog.stick.lx < 127) &&
              (Ps3.data.analog.stick.ly == -128)) {
      
      spi_send(JOYUP);
    }
    else if ( (Ps3.data.analog.stick.lx > -128  && Ps3.data.analog.stick.lx <= 127) &&
              (Ps3.data.analog.stick.ly == 127)) {
      
      spi_send(JOYDOWN);
    }
    else if ( (Ps3.data.analog.stick.lx == -128) &&
              (Ps3.data.analog.stick.ly > -127 && Ps3.data.analog.stick.ly <= 127)) {
      
     spi_send(JOYLEFT);
    }
    else if ( (Ps3.data.analog.stick.lx == 127) &&
              (Ps3.data.analog.stick.ly <= 127  && Ps3.data.analog.stick.ly > -128)) {
      
      spi_send(JOYRIGHT);
    }
    /***********************************************************************/
    else if (Ps3.data.button.up)
    {
      spi_send(UP);
      Print("UP-3");
    }
    else if (Ps3.data.button.right)
    {
      spi_send(RIGHT);
      Print("RIGHT-4");
    }
    else if (Ps3.data.button.down)
    {
      spi_send(DOWN);
      Print("DOWN-5");
    }
    else if (Ps3.data.button.left)
    {
      spi_send(LEFT);
      Print("LEFT-6");
    }
    /***********************************************************************/
    else if (Ps3.data.button.triangle)
    {
      spi_send(TRIANGLE);
      Print("TRIANGLE-7");
    }
    else if (Ps3.data.button.circle)
    {
      spi_send(CIRCLE);
      Print("CIRCLE-8");
    }
    else if (Ps3.data.button.cross)
    {
      spi_send(CROSS);
      Print("CROSS-9");
    }
    else if (Ps3.data.button.square)
    {
      spi_send(SQUARE);
      Print("SQUARE-10");
    }
    /***********************************************************************/
  
    /***********************************************************************/
    else if (Ps3.data.button.start)
    {
      spi_send(START);
      Print("START-21");
    }
    else if (Ps3.data.button.ps)
    {
      spi_send(DISC);
      ESP.restart();
      Print("MEGA RESET");
    }
    else if (Ps3.data.button.select)
    {
      spi_send(SELECT);
      Print("SELECT-22");
    }
    /***********************************************************************/
    else if (Ps3.data.button.r3)
    {
      spi_send(R3);
      Print("R3-23");
    }
    else if (Ps3.data.button.l3)
    {
      spi_send(L3);
      Print("L3-24");
    }
    /***********************************************************************/
    else
    {
      spi_send(set_arr(0));
      set_arr(0);
      Print("BLANK");
    }
    delay(1);
  }
  else {
    set_arr(0);
    spi_send(set_arr(0));
    Print("ELSE");
  }
  yield;
}

void Print(String passed_string) {
#if serial_print
  Serial.println(passed_string);
#endif
}
void loop()
{
  yield();
}
