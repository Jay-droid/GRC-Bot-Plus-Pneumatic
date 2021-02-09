// Include headers and libraries ---------------------
#include "Bot.h"
#include "Pneumatic.h"
#include <Encoder.h>

// Definition of pins ---------------------------------
// Relay in order from vcc - 43, 45, 41, A12 
#define GrabP1 A12  
#define GrabP2 41
#define ThrowP1 45
#define ThrowP2 43

#define limitClkPin A6
#define limitAclkPin A0
#define reedPin A7

// Motor pinouts
#define Grab_pwm 4
#define Grab_in1 5
#define Grab_in2 22

#define FRD 13 
#define FRP 6

#define BRD 7
#define BRP 12

#define BLD 9
#define BLP 10

#define FLD 11
#define FLP 8

// Definition of digitalReads -------------------------
#define limitClk digitalRead(limitClkPin)
#define limitAclk digitalRead(limitAclkPin)
#define reedSwitch digitalRead(reedPin)
#define readEncoder GrabEnc.read()

// Creating objects of classes-------------------------
Motor GrabMotor(Grab_pwm, Grab_in1, Grab_in2);
Encoder GrabEnc(2,3);
Pneumatic Thrower(ThrowP1, ThrowP2);
Pneumatic Grabber(GrabP1, GrabP2);


// Base motors and Bot object
Motor motor3(FRP, FRD);
Motor motor2(BRP, BRD);
Motor motor4(BLP, BLD);
Motor motor1(FLP, FLD);

Bot bot(motor1, motor2, motor3, motor4);

// Variables- -----------------------------------------
int reedCount = 0;
byte button = 0;
bool PSDisconnected = 0;
unsigned long currentMillis = 0;

// Custom functions ----------------------------------
void pinModes()
{
  pinMode(GrabP1, OUTPUT);
  pinMode(GrabP2, OUTPUT);
  pinMode(ThrowP1, OUTPUT);
  pinMode(ThrowP2, OUTPUT);
  pinMode(reedPin, INPUT_PULLUP); //Reed Switch
  pinMode(limitClkPin, INPUT_PULLUP); //LimitClock
  pinMode(limitAclkPin, INPUT_PULLUP); //LimitAntiClock
}

void relaysOff()
{
  digitalWrite(GrabP1, HIGH);
  digitalWrite(GrabP2, HIGH);
  digitalWrite(ThrowP1, HIGH);
  digitalWrite(ThrowP2, HIGH);
}

void (*resetFunc)(void) = 0;

// Constants for PS ------------------------------
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
#define UPRIGHT 20
#define UPLEFT 21
#define DOWNLEFT 22
#define DOWNRIGHT 23
#define DISC 255
