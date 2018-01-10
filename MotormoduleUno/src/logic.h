#ifndef LOGIC_H
#define LOGIC_H

#include "main.h"
#include <math.h>

//initialize the values for moving
//startPos < desiredPos
//speed alway positive
void startMoving();

void getCalculatedSpeed(int desiredSpeed, int currentPos, int desiredPos, bool feeding, double & calculatedSpeed, bool & done);


#endif