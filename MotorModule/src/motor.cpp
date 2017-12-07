#include "motor.h"

// Motor driver
#define retractPin 2
#define motorDriverPwmPin 3
#define feedPin 4

int setupMotor(){
    Serial.println("setting up motor");
    // Motor driver setup
    pinMode(retractPin, OUTPUT);
    pinMode(motorDriverPwmPin, OUTPUT);
    pinMode(feedPin, OUTPUT);
    return STATUS_OK;
}

int setMotor(bool retract, int speed){
    if(speed < 0 || speed > 255)
        return STATUS_ERROR;

    digitalWrite(retractPin, retract);
    digitalWrite(feedPin, !retract);
    analogWrite(motorDriverPwmPin, speed);
    return STATUS_OK; 
}