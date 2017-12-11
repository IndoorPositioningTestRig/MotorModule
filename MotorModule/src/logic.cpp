#include "logic.h"

//private constants
#define STARTAC_STATE 0
#define ACCELERATE_STATE 1
#define STOPAC_STATE 2
#define STARTBR_STATE 3
#define BRAKE_STATE 4
#define STOPBR_STATE 5

//private fields
int startPosition = 0;
int desiredPosition = 0;
int desiredMaxSpeed = 0;
int currentPos = 0;

//private functions
int startAccelerating();
int accelerate();
int stopAccelerating();
int startBraking();
int brake();
int stopBraking();
typedef int (*num_func)();
num_func stateFunctions[] = {
    startAccelerating,
    accelerate,
    stopAccelerating,
    startBraking,
    brake,
    stopBraking,
};

int startAccelerating();
int stopAccelerating();
int startBraking();
int stopBraking();

int setValues(int startPos, int desiredPos, int desiredSpeed)
{
    startPosition = startPos;
    desiredPosition = desiredPos;
    desiredMaxSpeed = desiredSpeed;
    return STATUS_OK;
}

int calculateSpeed(int currentPos, bool & direction, int & speed)
{
    return STATUS_OK;
}


//PRIVATE functions

//PRIVATE fields

//state function

int startAccelerating()
{
    return STATUS_OK;
}

int stopAccelerating()
{
    return STATUS_OK;
}

int startBraking()
{
    return STATUS_OK;
}

int stopBraking()
{
    return STATUS_OK;
}

