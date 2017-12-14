#include "logic.h"

//private states
#define ACCELERATE_STATE    0
#define MOVE_STATE          1
#define BRAKE_STATE         2
#define PI 3.1415926535897932384626433832795

//private fields
int startPosition = 0;
int desiredPosition = 0;
int desiredMaxSpeed = 0;
int currentPos = 0;
int positionToMove = 0;

//private functions
int getState(int currentDeltaPos, int currentSpeed);

int accelerate(int currentDeltaPos, int & currentSpeed);
int move(int currentDeltaPos, int & currentSpeed);
int brake(int currentDeltaPos, int & currentSpeed);

typedef int (*num_func)(int currentDeltaPos, int & currentSpeed);
num_func stateFunctions[] = {
    accelerate,
    move,
    brake,
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
int posToAccelerate = 0;

int getState(int currentDeltaPos, int currentSpeed)
{
    //Check if is accelerating
    if(currentDeltaPos < positionToMove /2){
        //if desiredspeed is not reached:
        if(currentSpeed < desiredMaxSpeed){
            return ACCELERATE_STATE;
        }
        //correct speed is set
        else {
            return MOVE_STATE;
        }       
    }else{
        //half of the work is done now check if it is time for a brake

        //still possible to move at desired speed:
        if(currentDeltaPos < desiredPosition - posToAccelerate){
            return MOVE_STATE;
        }else{
            return BRAKE_STATE;
        }
    }
    return -1;
}

//state functions

int accelerate(int currentDeltaPos, int & currentSpeed)
{
    // speed = (desirespeed * 0.5) * sin((1 / desiredspeed * currentDeltaPos) - 0.5pi) + 1
    // desiredspeed * 0.5                >> sets correct amplitude
    // 1/desiredspeed * currentdeltaPos  >> sets correct sinus length
    // -0.5pi                            >> translates the sinus to the right
    // +1                                >> makes the sinus always positive and starting at (0,0)

    currentSpeed = (desiredMaxSpeed * 0.5) * sin((1/desiredMaxSpeed * currentDeltaPos)-0.5 * PI) +1;

    posToAccelerate = currentDeltaPos;
    currentSpeed += 3;

    return STATUS_OK;
}

int move(int currentDeltaPos, int & currentSpeed)
{
    currentSpeed = currentSpeed;
    return STATUS_OK;
}

int brake(int currentDeltaPos, int & currentSpeed)
{
    // speed = desiredspeed * 0.5 * (sin(1 / desiredspeed * currentpos +0.5*π) + 1)
    // desiredspeed * 0.5                >> sets correct amplitude
    // 1/desiredspeed * currentdeltaPos  >> sets correct sinus length
    // +0.5pi                            >> translates the sinus to the left
    // +1                                >> makes the sinus always positive and starting at (0,0)
    currentSpeed -= 3;
    return STATUS_OK;
}

