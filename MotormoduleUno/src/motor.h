#ifndef MOTOR_H
#define MOTOR_H
#include "Arduino.h"
#include "main.h"

int setupMotor();
int setMotor(bool retract, int pwmSpeed);
void getPwmSpeed(int &);

#endif