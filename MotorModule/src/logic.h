#ifndef LOGIC_H
#define LOGIC_H

#include "Arduino.h"
#include "main.h"
#include <math.h>

//initialize the values for moving
//startPos < desiredPos
//speed alway positive
int setValues(int startPos, int desiredPos, int desiredSpeed);

int calculateSpeed(int currentPos,bool & direction, int & speed);



#endif