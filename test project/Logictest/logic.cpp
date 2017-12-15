#include "logic.h"

//constants
#define M_PI 3.1415926535897932384626433832795

//states
#define ACCELERATE_STATE    0
#define MOVE_STATE          1
#define BRAKE_STATE         2

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
int accelerate(int & currentSpeed);
int move(int & currentSpeed);
int brake(int & currentSpeed);
typedef int(*num_func)(int & currentSpeed);
num_func stateFunctions[] = {
	accelerate,
	move,
	brake
};

//private function
//get state number
int getState(int & speed);

int setLogicValues(int startPos, int positionsToMove, int desiredSpeed)
{
	StartPos = StartPos;
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

int calculateSpeed(int currentPos, int & speed) {
	int deltaPos = currentPos - StartPos;
	if (deltaPos < 0) deltaPos = deltaPos * -1;
	Positionsmoved = deltaPos;
	int state = getState(speed);
	stateFunctions[state](speed);
	return STATUS_OK;
}

int getState(int & currentSpeed)
{
	//check if 50% done   
	if (Positionsmoved < PositionsToMove / 2) {
		//check if desired speed is reached
		if (currentSpeed < DesiredSpeed - 1)
			//if not accelerate
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

int accelerate(int & currentSpeed)
{
	int amplitude = DesiredSpeed * 0.5;
	int length = 1 / DesiredSpeed;
	int xTrans = 0.5 * M_PI;
	int yTrans = 1;
	currentSpeed = amplitude * sin((length * Positionsmoved) - xTrans) + yTrans;
	return STATUS_OK;
}

int move(int & currentSpeed)
{
	currentSpeed = DesiredSpeed;
	return STATUS_OK;
}

int brake(int & currentSpeed)
{
	int amplitude = DesiredSpeed * 0.5;
	int length = 1 / DesiredSpeed;
	int xTrans = -0.5 * M_PI;
	int yTrans = 1;
	//calculate 0 point
	int deltaBraking = Positionsmoved - (DesiredPos - TicksToReachDesSpeed);
	currentSpeed = amplitude * sin((length * deltaBraking) - xTrans) + yTrans;
	return STATUS_OK;
}
