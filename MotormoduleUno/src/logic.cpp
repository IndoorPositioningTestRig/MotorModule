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

	if((!feeding && (currentPos <= desiredPos))||(feeding && (currentPos >= desiredPos))){
		//done
		calculatedSpeed = 0;
		done = true;
		startMovingTime = 0;
		// Serial.print(" calculatedSpeed: ");
		// Serial.println(calculatedSpeed);
		return;
	}

	if(deltaTime < 1000){
		//accelerating:
		int x = currentTime - startMovingTime;
		double y = x * (desiredSpeed / 1000); 
		calculatedSpeed = y;
		if(calculatedSpeed <1) calculatedSpeed = 1;
		// Serial.print(" calculatedSpeed: ");
		// Serial.println(calculatedSpeed);
		return;
	}
	if((feeding && currentPos <= desiredPos - 100)|| (!feeding && currentPos >= desiredPos + 100 )){
		//braking
		int x = fabs(desiredPos - currentPos);
		double y = -(-desiredSpeed / 80) * x;
		calculatedSpeed = y;
		if(calculatedSpeed <1) calculatedSpeed = 1;
		// Serial.print(" calculatedSpeed: ");
		// Serial.println(calculatedSpeed);
		return;
	}
	//moving
	calculatedSpeed = desiredSpeed;
	// Serial.print(" calculatedSpeed: ");
	// Serial.println(calculatedSpeed);
}

