#include "encoder.h"

// Arduino Pins:
#define EncoderPinA 7
#define EncoderPinB 8

// Local variables
int EncoderPos = 0;
int DesiredPos = 0;

int desiredSpeed = 0;
int currentSpeed = 0;

bool direction;
int acceleration = 0;

unsigned long previousTime = 0;
unsigned long latestTime = 0;
int previousPos = 0;
int speed = 0;

//PRIVATE FUNCTIONS
void interruptEncoder();
int calculateCurrentSpeed();

int setupEncoder(){
    Serial.println("setting up encoder");
    // encoder setup
    pinMode(EncoderPinA, INPUT);
    pinMode(EncoderPinB, INPUT);
      //interrupt setup:
    attachInterrupt(digitalPinToInterrupt(EncoderPinA), interruptEncoder, RISING);
    return STATUS_OK;
}

int setEncoderData(int length, int speed ){
    DesiredPos = round(length / ((ENCODER_DIAMETER * PI) / TICKS));
    desiredSpeed = speed;
    return STATUS_OK;
}

int resetEncoderData(){
    DesiredPos = 0;
    desiredSpeed = 0;
    return STATUS_OK;
}

int getEncoderData(int & encoderPosition, int & desiredPosition){
    encoderPosition = EncoderPos;
    desiredPosition = DesiredPos;
    return STATUS_OK;
}

int calculateMotorSpeed(bool & retractDirection, int & speed, bool & done){
    //first check if position is reached
    if(EncoderPos == DesiredPos){
        done = 1;
        currentSpeed = speed = 0;
        retractDirection = false;
    }else 
        done = 0;

    int currentSpeed =  calculateCurrentSpeed();
    
    // Move rope to desired length
    if (DesiredPos > EncoderPos)
        retractDirection = false;
    else
        retractDirection = true;

    // Speed
    if (acceleration > 10)
    {
        // Breakingzone
        if (((EncoderPos > DesiredPos - 50 && !direction) || (EncoderPos < DesiredPos + 50 && direction)) && currentSpeed > 20)
        {
        currentSpeed--;
        }
        // Accelerate
        else if (currentSpeed < desiredSpeed)
        {
        currentSpeed = desiredSpeed;
        //currentSpeed++;
        }
        acceleration = 0;
    }
    acceleration++;

    speed = currentSpeed;
    if(done){
        Serial.print("Current length: ");
        Serial.print(EncoderPos);
        Serial.print(" Desired length: ");
        Serial.print(DesiredPos);
        Serial.print(" Current speed: ");
        Serial.println(currentSpeed);
    }
    return STATUS_OK;
}

//private interrupt function:
void interruptEncoder()
{
    if (digitalRead(EncoderPinB) == LOW)
        EncoderPos--;
    else
        EncoderPos++;
}

//PRIVATE FUNCTIONS:
int calculateCurrentSpeed(){
    latestTime = millis();
    unsigned long timeDifference = latestTime - previousTime;
    int tickDifference = EncoderPos - previousPos;
    float mmDifference = tickDifference * MMPERTICK;
    float mmPerMSecond = mmDifference / timeDifference;
    int mmPSec = mmPerMSecond * 1000;
    previousPos = EncoderPos;
    previousTime = latestTime;
    return mmPSec;
}


