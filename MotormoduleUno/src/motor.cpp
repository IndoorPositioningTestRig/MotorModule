#include "motor.h"

// Motor driver
#define retractPin 7
#define motorDriverPwmPin 3
#define feedPin 4

int pwmSpeed = 0;

int setupMotor(){
    Serial.println("setting up motor");
    // Motor driver setup
    pinMode(retractPin, OUTPUT);
    pinMode(motorDriverPwmPin, OUTPUT);
    pinMode(feedPin, OUTPUT);
    pwmSpeed = 0;
    return STATUS_OK;
}

void getPwmSpeed(int &speed)
{
    speed = pwmSpeed;
}

int setMotor(bool retract, int speed){
    if(speed < 0 || speed > 255)
        return STATUS_ERROR;
    pwmSpeed = speed;

    digitalWrite(retractPin, retract);
    digitalWrite(feedPin, !retract);
    analogWrite(motorDriverPwmPin, speed);
    return STATUS_OK; 
}