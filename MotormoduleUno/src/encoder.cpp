#include "encoder.h"

// Arduino Pins:
#define EncoderPinA 2
#define EncoderPinB 8

// Local variables
double mmpertick = MMPERTICK;
int encoderPosTicks = 1683 / mmpertick;
int desiredPosTicks = 1683 / mmpertick;
// int encoderPosTicks = 0;
// int desiredPosTicks = 0;
int encoderDiffTicks = 0;

int desiredSpeedTicks = 0;

//variables for speed:
unsigned long previousTime = 0;
unsigned long latestTime = 0;
double speed = 0;

//true == feed some rope
//false == eat some rope
bool direction;

//PRIVATE FUNCTIONS
void interruptEncoder();
// bool calculateCurrentSpeed(double & speed);

int setupEncoder()
{
    // encoder setup
    pinMode(EncoderPinA, INPUT);
    pinMode(EncoderPinB, INPUT);
    //interrupt setup:
    attachInterrupt(digitalPinToInterrupt(EncoderPinA), interruptEncoder, RISING);
    return STATUS_OK;
}

int setEncoderPos(int millimeters)
{
    encoderPosTicks = millimeters / mmpertick;
    return STATUS_OK;
}

int setEncoderData(int lengthmm, int speedmms)
{
    desiredPosTicks = (double)lengthmm / mmpertick + 1;
    desiredSpeedTicks = (double)speedmms / mmpertick + 1;
    int ticksToMove = desiredPosTicks - encoderPosTicks;
    direction = true;
    if (ticksToMove < 0)
    {
        ticksToMove = abs(ticksToMove);
        direction = false;
    }
    return STATUS_OK;
}

int getEncoderData(int &encoderPositionMm, int &desiredPositionMm)
{
    encoderPositionMm = encoderPosTicks * mmpertick;
    desiredPositionMm = desiredPosTicks * mmpertick;
    return STATUS_OK;
}

int calculateMotorSpeed(bool &retractDirection, int &speedPWM, bool &done)
{
    
    latestTime = millis();
    double timeDifference =  latestTime - previousTime;
    if(timeDifference >=10){
        speed = fabs(encoderDiffTicks)/timeDifference *1000;
        encoderPosTicks += encoderDiffTicks;
        previousTime = latestTime;
        encoderDiffTicks = 0;
    }else{
        return;
    }

    done = false;
    double calculatedspeed = 0;
    // bool success = calculateCurrentSpeed(currentSpeedTicks);
    // if(!success) return STATUS_OK;
    getCalculatedSpeed(desiredSpeedTicks,encoderPosTicks,desiredPosTicks,direction, calculatedspeed, done);

    //check if speed is hard enough
    //if going to hard
    if(done){
        speedPWM = 0;
        return STATUS_OK;
    }
    if (fabs(calculatedspeed) < fabs(speed))
        //Going to hard
        speedPWM -= 1;
    //if going to slow
    else if (fabs(calculatedspeed) > fabs(speed))
        //Go harder
        speedPWM += 1;
    //set speed in correct direction
    retractDirection = direction;
    return STATUS_OK;
}

//private interrupt function:
void interruptEncoder()
{
    bool feeding = digitalRead(EncoderPinB);
    if (feeding == LOW)
        encoderDiffTicks--;
    else if(feeding == HIGH)
        encoderDiffTicks++;
}