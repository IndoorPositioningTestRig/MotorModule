#ifndef LOGIC_H
#define LOGIC_H

#include "Arduino.h"
#include "main.h"

int setValues(int startPos, int desiredPos, int desiredSpeed);

int calculateSpeed(int currentPos,bool & direction, int & speed);



#endif