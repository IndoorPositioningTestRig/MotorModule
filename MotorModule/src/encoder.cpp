#include "encoder.h"

// Global variables
int EncoderPos = 0;
int desiredPos = 0;

int desiredSpeed = 0;
int currentSpeed = 0;

bool direction;
int acceleration = 0;

void interruptEncoder();

int setupEncoder(){
    Serial.println("setting up encoder");
    // encoder setup
    pinMode(EncoderPinA, INPUT);
    pinMode(EncoderPinB, INPUT);
      //interrupt setup:
    attachInterrupt(digitalPinToInterrupt(EncoderPinA), interruptEncoder, RISING);
    return STATUS_OK;
}

//interrupt functions:
void interruptEncoder()
{
    if (digitalRead(EncoderPinB) == LOW)
        EncoderPos--;
    else
        EncoderPos++;
    Serial.println(EncoderPos);
}

int setEncoderData(int length, int speed ){
    desiredPos = round(length / ((ENCODER_DIAMETER * PI) / TICKS));
    desiredSpeed = speed;
    Serial.print("desired position:");
    Serial.println(desiredPos);
    Serial.print("desired speed:");
    Serial.println(desiredSpeed);
    Serial.print("current position:");
    Serial.println(EncoderPos);

    return STATUS_OK;
}

int calculateMotorSpeed(bool & retractDirection, int & speed, bool & done){
    done = (EncoderPos == desiredPos);
    // Move rope to desired length
    if (desiredPos > EncoderPos)
        retractDirection = false;
    else
        retractDirection = true;

    
    // Speed
    if (acceleration > 10)
    {
        // Breakingzone
        if (((EncoderPos > desiredPos - 50 && !direction) || (EncoderPos < desiredPos + 50 && direction)) && currentSpeed > 20)
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
    return STATUS_OK;
}


