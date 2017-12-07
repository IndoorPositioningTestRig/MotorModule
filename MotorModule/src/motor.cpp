#include "motor.h"

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

    direction = retract;
    currentSpeed = speed;
    digitalWrite(retractPin, direction);
    digitalWrite(feedPin, !direction);
    analogWrite(motorDriverPwmPin, currentSpeed);
    return STATUS_OK; 
}