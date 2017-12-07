#include "motor.h"

void setupMotor(){
  // Motor driver setup
  pinMode(retractPin, OUTPUT);
  pinMode(motorDriverPwmPin, OUTPUT);
  pinMode(feedPin, OUTPUT);
}