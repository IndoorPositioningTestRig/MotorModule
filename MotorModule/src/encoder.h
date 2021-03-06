#ifndef ENCODER_H
#define ENCODER_H

#include "Arduino.h"
#include "main.h"
#include "logic.h"

#define PI 3.1415926535897932384626433832795

//te ver >> diameter groter
#define ENCODER_DIAMETER 40.75
#define TICKS 128
#define MMPERTICK (ENCODER_DIAMETER * PI) / TICKS

//test function:
void addEncoderPos();

int setupEncoder();

///Sets the wanted encoder length and speed,
///Length in mm and speed in mm / s
int setEncoderData(int length, int speed);
int resetEncoderData();
int getEncoderData(int & encoderPosition, int & desiredPosition);

int calculateMotorSpeed(bool & retractDirection, int & speed, bool & done);

#endif