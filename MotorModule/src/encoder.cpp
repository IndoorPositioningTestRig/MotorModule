#include "encoder.h"

// Arduino Pins:
#define EncoderPinA 7
#define EncoderPinB 8

// Local variables
int encoderPos = 0;
int desiredPos = 0;
int positionsToMove = 0;

int desiredSpeed = 0;
int currentSpeed = 0;

//true == feed some rope
//false == eat some rope
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
    //position in mm 
    desiredPos = round(length / ((ENCODER_DIAMETER * PI) / TICKS));
    //speed in mm/s
    desiredSpeed = speed;
    direction = encoderPos < desiredPos;
    if(direction){
        positionsToMove = desiredPos - encoderPos;
    }else{
        positionsToMove = encoderPos = desiredPos;
    }
    setLogicValues(encoderPos,positionsToMove,desiredSpeed);
    return STATUS_OK;
}

int resetEncoderData(){
    desiredPos = 0;
    desiredSpeed = 0;
    resetLogicValues();
    return STATUS_OK;
}

int getEncoderData(int & encoderPosition, int & desiredPosition){
    encoderPosition = encoderPos;
    desiredPosition = desiredPos;
    return STATUS_OK;
}

int calculateMotorSpeed(bool & retractDirection, int & speed, bool & done){
    //first check if position is reached
    if(encoderPos == desiredPos){
        done = 1;
        currentSpeed = speed = 0;
        retractDirection = false;
        return STATUS_OK;
    }else 
        done = 0;

    int currentSpeed =  calculateCurrentSpeed();
    // Move rope to desired length
    if (desiredPos > encoderPos)
        retractDirection = false;
    else
        retractDirection = true;

    // Speed
    if (acceleration > 10)
    {
        // Breakingzone
        if (((encoderPos > desiredPos - 50 && !direction) || (encoderPos < desiredPos + 50 && direction)) && currentSpeed > 20)
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
        Serial.print(encoderPos);
        Serial.print(" Desired length: ");
        Serial.print(desiredPos);
        Serial.print(" Current speed: ");
        Serial.println(currentSpeed);
    }
    return STATUS_OK;
}

//private interrupt function:
void interruptEncoder()
{
    if (digitalRead(EncoderPinB) == LOW)
        encoderPos --;
    else
        encoderPos --;
}

int calculateCurrentSpeed(){
    latestTime = millis();
    unsigned long timeDifference = latestTime - previousTime;
    int tickDifference = encoderPos - previousPos;
    float mmDifference = tickDifference * MMPERTICK;
    float mmPerMSecond = mmDifference / timeDifference;
    int mmPSec = mmPerMSecond * 1000;
    previousPos = encoderPos;
    previousTime = latestTime;
    return mmPSec;
}


