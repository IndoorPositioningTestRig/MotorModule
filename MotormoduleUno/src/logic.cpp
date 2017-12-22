#include "logic.h"

//constants
#define M_PI 3.1415926535897932384626433832795

//states
#define ACCELERATE_STATE    0
#define MOVE_STATE          1
#define BRAKE_STATE         2
#define DONE_STATE			3

//fields:

//startposition in ticks
int StartPos = 0;
//desiredPosition in ticks
int DesiredPos = 0;
//positionmoved
int Positionsmoved = 0;
//difference between start & desire pos int ticks
int PositionsToMove = 0;
//speed in ticks / second
int DesiredSpeed = 0;
//ticks needed to reach full speed
int TicksToReachDesSpeed = 0;

//STATEMACHINE:
int accelerate(double & currentSpeed);
int move(double & currentSpeed);
int brake(double & currentSpeed);
int done(double & currentSpeed);
typedef int(*num_func)(double & currentSpeed);
num_func stateFunctions[] = {
	accelerate,
	move,
	brake,
	done
};

//private function
//get state number
int getState(double & speed);

int setLogicValues(int startPos, int positionsToMove, int desiredSpeed)
{
	StartPos = startPos;
	PositionsToMove = positionsToMove;
	Positionsmoved = 0;
	DesiredPos = StartPos + PositionsToMove;
	DesiredSpeed = desiredSpeed;
	TicksToReachDesSpeed = 0;

	return STATUS_OK;
}

int resetLogicValues() {
	return setLogicValues(0, 0, 0);
}

int calculateSpeed(int currentPos, double & speed) {
	int deltaPos = currentPos - StartPos;
	if (deltaPos < 0) deltaPos = deltaPos * -1;
	Positionsmoved = deltaPos;
	int state = getState(speed);
	stateFunctions[state](speed);
	return STATUS_OK;
}

int getState(double & currentSpeed)
{
	if (Positionsmoved >= PositionsToMove)
		return DONE_STATE;
	//check if 50% done   
	if (Positionsmoved < PositionsToMove / 2) {
		//check if desired speed is reached
		if (currentSpeed < DesiredSpeed)
			//if accelerate
			return ACCELERATE_STATE;
		else
			//if moving fast enough > stay moving
			return MOVE_STATE;
	}
	else {
		//check te amount of moving rope is lefs
		int positionStillToDo = PositionsToMove - Positionsmoved;
		//check if it is time for a brake
		if (positionStillToDo <= TicksToReachDesSpeed)
			//time to end this
			return BRAKE_STATE;
		else
			return MOVE_STATE;
	}
}

int accelerate(double & currentSpeed)
{
	double amplitude = DesiredSpeed *0.5;
	double length =  M_PI / DesiredSpeed ;
	double xTrans = 0.5 * M_PI;
	double yTrans = DesiredSpeed * 0.5;
	//desspeed * 0.5 * sin((PI / desspeed)*moved) - 0.5 * pi) + desspeed * 0.5
	//example:
	//desspeed = 100
	//50 * sin(((PI / 100)) * moved) - PI/2) + 50

	currentSpeed = amplitude * sin((length * Positionsmoved) - xTrans) + yTrans;
	if(currentSpeed < 1) currentSpeed =1;
	TicksToReachDesSpeed = Positionsmoved;
	return STATUS_OK;
}

int move(double & currentSpeed)
{
	currentSpeed = DesiredSpeed;
	return STATUS_OK;
}

int brake(double & currentSpeed)
{
	double amplitude = DesiredSpeed * 0.5;
	double length = M_PI / DesiredSpeed;
	double xTrans = -0.5 * M_PI;
	double yTrans = DesiredSpeed * 0.5;
	//calculate 0 point
	int deltaBraking = Positionsmoved - (DesiredPos - TicksToReachDesSpeed);
	currentSpeed = amplitude * sin((length * deltaBraking) - xTrans) + yTrans;
	return STATUS_OK;
}

int done(double & currentSpeed)
{
	currentSpeed = 0;
	return STATUS_OK;
}
