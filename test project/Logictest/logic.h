#ifndef LOGIC_H
#define LOGIC_H

#include "main.h"
#include <math.h>

//initialize the values for moving
//startPos < desiredPos
//speed alway positive
int setLogicValues(int startPos, int positionsToMove, int desiredSpeed);

int resetLogicValues();

int calculateSpeed(int currentPos, bool direction, int & speed);



#endif