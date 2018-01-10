#include "encoder.h"

// Arduino Pins:
#define EncoderPinA 2
#define EncoderPinB 8

// Local variables
double mmpertick = MMPERTICK;
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
bool calculateCurrentSpeed(double & speed);

//test function delete this when testing some real stuff
void addEncoderPos()
{
    encoderPosTicks++;
}

int setupEncoder()
{
    Serial.println("setting up encoder");
    // encoder setup
    pinMode(EncoderPinA, INPUT);
    pinMode(EncoderPinB, INPUT);
    //interrupt setup:
    attachInterrupt(digitalPinToInterrupt(EncoderPinA), interruptEncoder, RISING);
    return STATUS_OK;
}

int setEncoderData(int lengthmm, int speedmms)
{
    desiredPosTicks = (double)lengthmm / mmpertick;
    desiredSpeedTicks = (double)speedmms / mmpertick;
    int ticksToMove = desiredPosTicks - encoderPosTicks;
    if (ticksToMove < 0)
    {
        ticksToMove = ticksToMove * -1;
        direction = false;
    }
    else
    {
        direction = true;
    }
    return STATUS_OK;
}

int resetEncoderData()
{
    desiredPosTicks = currentSpeedTicks = encoderPosTicks = 0;
    return STATUS_OK;
}

int getEncoderData(int &encoderPosition, int &desiredPosition)
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

int startMovingEncoder()
{
    startMoving();
    return STATUS_OK;
}

int calculateMotorSpeed(bool &retractDirection, int &speedPWM, bool &done)
{
    done = false;
    double calculatedspeed = 0;
    getCalculatedSpeed(desiredSpeedTicks,encoderPosTicks,desiredPosTicks,direction, calculatedspeed, done);
    //check if speed is hard enough
    //if going to hard
    Serial.print("Current speed: ");
    Serial.println(currentSpeedTicks);
    Serial.print("Desired speed: ");
    Serial.println(calculatedspeed);
    if(done){
        speedPWM = 0;
        return STATUS_OK;
    }
    if (fabs(calculatedspeed) < fabs(currentSpeedTicks))
        //Going to hard
        speedPWM -= 1;
    //if going to slow
    else if (fabs(calculatedspeed) > fabs(currentSpeedTicks))
        //Go harder
        speedPWM += 1;
    //set speed in correct direction
    retractDirection = direction;
    return STATUS_OK;
}

//private interrupt function:
void interruptEncoder()
{
    if (digitalRead(EncoderPinB) == LOW)
        encoderPosTicks--;
    else if(digitalRead(EncoderPinB == HIGH))
        encoderPosTicks++;
}

//calculates current speed in ticks per second
bool calculateCurrentSpeed(double & speed)
{
    latestTime = millis();
    int minDifference = 10;
    double timeDifference = latestTime - previousTime;
    if(timeDifference < minDifference)
        return false;

    double tickDifference = encoderPosTicks - previousPos;
    double ticksPerMicroSecond = tickDifference / timeDifference;
    double ticksPSec = ticksPerMicroSecond * 1000;

    previousPos = encoderPosTicks;
    previousTime = latestTime;
    speed = ticksPSec;
    return true;
}
