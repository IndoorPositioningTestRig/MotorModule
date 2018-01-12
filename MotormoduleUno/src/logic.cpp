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
	int deltaTime = currentTime - startMovingTime;

	if(deltaTime < 1000){
		//accelerating:
		int x = currentTime = startMovingTime;
		double y = x * (desiredSpeed / 500); 
		calculatedSpeed = y;
		Serial.println("accelerating");
	}
	else if((!feeding && (currentPos <= desiredPos))|| (feeding && (currentPos >= desiredPos))){
		calculatedSpeed = 0;
		done = true;
		Serial.println("done");
	}
	else if((feeding && (currentPos <= desiredPos - 100)) || (!feeding && currentPos >= desiredPos + 100 )){
		int x = fabs(desiredPos - currentPos);
		double y = -(-desiredSpeed / 100) * x + desiredSpeed;
		calculatedSpeed = y;
		Serial.println("braking");
	}
	else{
		calculatedSpeed = desiredSpeed;
		Serial.println("moving");
	}
}

