#include "logic.h"

unsigned long startMovingTime = 0;
unsigned long accelerationTime = 0;


void startMoving(){
	startMovingTime = millis();
	accelerationTime = accelerationTime + 1000;
}

void getCalculatedSpeed(int desiredSpeed, int currentPos, int desiredPos, bool feeding, double & calculatedSpeed, bool & done)
{
	if(startMovingTime == 0) startMoving();
	int currentTime = millis();
	if((currentTime - startMovingTime) < 1000){
		//accelerating:
		int x = currentTime = startMovingTime;
		double y = x * (desiredSpeed / 500); 
		calculatedSpeed = y;
	}
	else if((!feeding && (currentPos <= desiredPos))||(feeding && (currentPos >= desiredPos))){
		calculatedSpeed = 0;
		done = true;
	}
	else if((feeding && currentPos <= desiredPos - 50)|| (!feeding && currentPos >= desiredPos + 50 )){
		int x = fabs(desiredPos - currentPos);
		double y = -(-desiredSpeed / 50) * x + desiredSpeed;
		calculatedSpeed = y;
	}
	else
		calculatedSpeed = desiredSpeed;
}

