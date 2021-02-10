// Include headers and libraries ---------------------
#include "Bot.h"
#include "Pneumatic.h"
#include <Encoder.h>

// Definition of pins ---------------------------------
// Relay in order from vcc - 43, 45, 41, A12 
#define ThrowP1 A12  
#define ThrowP2 41
#define GrabP1 45
#define GrabP2 43

#define limitClkPin A6
#define limitAclkPin A0
#define reedPin A7

// Motor pinouts
#define Grab_pwm 4
#define Grab_in1 28
#define Grab_in2 5

#define m3d 13 
#define m3p 6

#define m2d 7
#define m2p 12

#define m4d 9
#define m4p 10

#define m1d 11
#define m1p 8

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
Motor motor1(m1p, m1d);
Motor motor2(m2p, m2d);
Motor motor3(m3p, m3d);
Motor motor4(m4p, m4d);

Bot bot(motor1, motor2, motor3, motor4);

// Variables- -----------------------------------------
int reedCount = 0;
byte button = 0;
bool PSDisconnected = 0;
unsigned long currentMillis = 0;
unsigned long [previousMillis = 0;

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
//////////////////////////
#define DISC 255
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
