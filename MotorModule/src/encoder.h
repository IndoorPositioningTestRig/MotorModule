#ifndef ENCODER_H
#define ENCODER_H
#include "Arduino.h"
#include "main.h"

#define PI 3.1415926535897932384626433832795
//te ver => diameter groter
#define ENCODER_DIAMETER 20.75
#define TICKS 128
#define MMPERTICK (ENCODER_DIAMETER * PI) / TICKS

// Arduino Pins:
#define EncoderPinA 7
#define EncoderPinB 8

//global fields
extern int EncoderPos;
extern int desiredPos;

extern int desiredSpeed;
extern int currentSpeed;

extern bool direction;
extern int acceleration;

int setupEncoder();

///Sets the wanted encoder length and speed,
///Lenght in mm and speed in mm / s
int setEncoderData(int length, int speed);

int calculateMotorSpeed(bool & retractDirection, int & speed, bool & done);

#endif