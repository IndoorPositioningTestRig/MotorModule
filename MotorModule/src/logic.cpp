#include "logic.h"

//private states
#define STARTAC_STATE       0
#define ACCELERATE_STATE    1
#define STOPAC_STATE        2
#define MOVE_STATE          3
#define STARTBR_STATE       4
#define BRAKE_STATE         5
#define STOPBR_STATE        6

// constants
int toState2Pos = 25;
int toState3Speed = -1;
int toState4Speed = -1;
int toState5Pos = -1;
int toState6Speed = -1;
int toState7Pos = -1;


//private fields
int startPosition = 0;
int desiredPosition = 0;
int desiredMaxSpeed = 0;
int currentPos = 0;
int positionToMove = 0;

//private functions
int getState(int currentDeltaPos, int currentSpeed);

int startAccelerating(int currentDeltaPos, int & currentSpeed);
int accelerate(int currentDeltaPos, int & currentSpeed);
int stopAccelerating(int currentDeltaPos, int & currentSpeed);
int move(int currentDeltaPos, int & currentSpeed);
int startBraking(int currentDeltaPos, int & currentSpeed);
int brake(int currentDeltaPos, int & currentSpeed);
int stopBraking(int currentDeltaPos, int & currentSpeed);

typedef int (*num_func)(int currentDeltaPos, int & currentSpeed);
num_func stateFunctions[] = {
    startAccelerating,
    accelerate,
    stopAccelerating,
    move,
    startBraking,
    brake,
    stopBraking,
};

//public functions
int setValues(int startPos, int desiredPos, int desiredSpeed)
{
    //check for invalid parameters
    if((desiredPos <= startPos) || (desiredSpeed <= 0))
        return STATUS_ERROR;
    
    startPosition = startPos;
    desiredPosition = desiredPos;
    desiredMaxSpeed = desiredSpeed;
    positionToMove = desiredPos - startPos;
    if(positionToMove <=50){
        toState2Pos = positionToMove /2;
        toState7Pos = positionToMove /2; 
    }

    return STATUS_OK;
}

int calculateSpeed(int currentPos, int currentSpeed, bool & direction, int & speed)
{
    int state = getState(currentPos-startPosition,currentSpeed);
    stateFunctions[state](currentPos-startPosition,currentSpeed);

    return STATUS_OK;
}


//PRIVATE functions

//PRIVATE fields

int getState(int currentDeltaPos, int currentSpeed)
{
    //Check if is accelerating
    if(currentDeltaPos < positionToMove /2){
        //if position < startaccelerating position
        if(currentDeltaPos < toState2Pos){
            return STARTAC_STATE;
        }
        //if speed < stopaccelerating speed
        else if(currentSpeed < desiredMaxSpeed - toState3Speed){
            return ACCELERATE_STATE;
        }
        //if desiredspeed is almost reached:
        else if(currentSpeed < desiredMaxSpeed){
            return STOPAC_STATE;
        }
        //correct speed is set
        else {
            return MOVE_STATE;
        }       
    }else {
        //half of the work is done now check if it is time for a brake

        //still possible to move at desired speed:
        if(currentDeltaPos < toState5Pos ){
            return MOVE_STATE;
        }else{
            //at desired speed, need to start braking
            if(currentSpeed > toState6Speed){
                return STARTBR_STATE;
            }
            //if position for braking the braking is not reached
            else if(currentDeltaPos < toState7Pos){
                return BRAKE_STATE;
            }
            //slowly stop braking
            else if(currentDeltaPos < positionToMove){
                return STOPBR_STATE;
            }
        }
    }
    return -1;
}

//state functions

int startAccelerating(int currentDeltaPos, int & currentSpeed)
{

    return STATUS_OK;
}

int accelerate(int currentDeltaPos, int & currentSpeed)
{
    return STATUS_OK;
}

int stopAccelerating(int currentDeltaPos, int & currentSpeed)
{
    return STATUS_OK;
}

int move(int currentDeltaPos, int & currentSpeed)
{
    return STATUS_OK;
}

int startBraking(int currentDeltaPos, int & currentSpeed)
{
    return STATUS_OK;
}

int brake(int currentDeltaPos, int & currentSpeed)
{
    return STATUS_OK;
}

int stopBraking(int currentDeltaPos, int & currentSpeed)
{
    return STATUS_OK;
}

