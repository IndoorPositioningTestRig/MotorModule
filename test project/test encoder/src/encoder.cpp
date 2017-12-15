#include "encoder.h"

// Arduino Pins:
#define EncoderPinA 7
#define EncoderPinB 8

// Local variables
int encoderPosTicks = 0;
int desiredPosTicks = 0;

int desiredSpeedTicks = 0;
int currentSpeedTicks = 0;

//variables for speed:
unsigned long previousTime = 0;
unsigned long latestTime = 0;
int previousPos = 0;

//true == feed some rope
//false == eat some rope
bool direction;

//PRIVATE FUNCTIONS
void interruptEncoder();
double calculateCurrentSpeed();

int setupEncoder(){
    Serial.println("setting up encoder");
    // encoder setup
    pinMode(EncoderPinA, INPUT);
    pinMode(EncoderPinB, INPUT);
      //interrupt setup:
    attachInterrupt(digitalPinToInterrupt(EncoderPinA), interruptEncoder, RISING);
    return STATUS_OK;
}

int setEncoderData(int lengthmm, int speedmms ){
    //position in mm 
    desiredPosTicks = lengthmm / MMPERTICK;
    desiredSpeedTicks = speedmms / MMPERTICK;
    int ticksToMove = desiredPosTicks - encoderPosTicks;
    if(ticksToMove < 0) {
        ticksToMove = ticksToMove * -1;
        direction = false;
    }else{
        direction = true;
    }
    setLogicValues(encoderPosTicks,ticksToMove,desiredSpeedTicks);
    return STATUS_OK;
}

int resetEncoderData()
{
    desiredPosTicks = desiredPosTicks = currentSpeedTicks = encoderPosTicks = 0;
    resetLogicValues();
    return STATUS_OK;
}

int getEncoderData(int & encoderPosition, int & desiredPosition)
{
    encoderPosition = encoderPosTicks;
    desiredPosition = desiredPosTicks;
    return STATUS_OK;
}

int setCurrentPosition(int locationmm)
{
    encoderPosTicks = locationmm / MMPERTICK;
    return STATUS_OK;
}   

int calculateMotorSpeed(bool & retractDirection, int & speedPWM, bool & done)
{
    //first check if position is reached
    if(encoderPosTicks == desiredPosTicks){
        done = 1;
        currentSpeedTicks = speedPWM = 0;
        retractDirection = false;
        return STATUS_OK;
    }else 
        done = 0;

    //get current speed
    double currentSpeedTicks = calculateCurrentSpeed();
    
    //get desiredcurrent speed:
    double currentDesiredSpeed = currentSpeedTicks;
    calculateSpeed(encoderPosTicks,currentDesiredSpeed);
    
    //check if speed is hard enough
    //if going to hard
    if(currentDesiredSpeed < currentSpeedTicks -1)
        //Going to hard
        speedPWM -= 1;
    //if going to slow
    else if(currentDesiredSpeed > currentSpeedTicks +1)
        //Go harder
        speedPWM += 1;
    //set speed in correct directio
    retractDirection = direction;   
    return STATUS_OK;
}

//private interrupt function:
void interruptEncoder()
{
    if (digitalRead(EncoderPinB) == LOW)
        encoderPosTicks ++;
    else
        encoderPosTicks --;
    Serial.print("got interrupt, current pos: ");
    Serial.println(encoderPosTicks);
}

//calculates current speed in ticks per second
double calculateCurrentSpeed(){
    latestTime = millis();
    unsigned long timeDifference = latestTime - previousTime;
    int tickDifference = encoderPosTicks - previousPos;
    double ticksPerMicroSecond = tickDifference / timeDifference;
    double ticksPSec = ticksPerMicroSecond * 1000;
    previousPos = encoderPosTicks;
    previousTime = latestTime;
    return ticksPSec;
}


