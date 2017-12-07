#ifndef MOTOR_H
#define MOTOR_H
#include "Arduino.h"
#include "main.h"

// Motor driver
#define retractPin 2
#define motorDriverPwmPin 3
#define feedPin 4

int setupMotor();
int setMotor(bool retract, int pwmSpeed);

#endif