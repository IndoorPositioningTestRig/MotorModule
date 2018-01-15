#include "logic.h"

unsigned long startMovingTime = 0;


void startMoving(){
	startMovingTime = millis();
}

void getCalculatedSpeed(int desiredSpeed, int currentPos, int desiredPos, bool feeding, double & calculatedSpeed, bool & done)
{

	if(startMovingTime == 0) startMoving();
	int currentTime = millis();
	int deltaTime = currentTime - startMovingTime;

	if((currentTime - startMovingTime) < 1000){
		//accelerating:
		int x = currentTime = startMovingTime;
		double y = x * (desiredSpeed / 500); 
		calculatedSpeed = y;
		Serial.println("accelerating");
		return;
	}
	if((!feeding && (currentPos <= desiredPos))||(feeding && (currentPos >= desiredPos))){
		calculatedSpeed = 0;
		done = true;
		startMovingTime = 0;
		Serial.println("done");
		return;
	}
	if((feeding && currentPos <= desiredPos - 50)|| (!feeding && currentPos >= desiredPos + 50 )){
		int x = fabs(desiredPos - currentPos);
		double y = -(-desiredSpeed / 50) * x + desiredSpeed;
		calculatedSpeed = y;
		Serial.println("braking");
		return;
	}
	//else
	calculatedSpeed = desiredSpeed;
	Serial.println("moving");
	
}

