#include "Motor.hpp"
#include <Arduino.h>
#include "../Pins.hpp"

using namespace MotorLogic;

void Motor::init(HallSensor * hallSensor) {
  _hallSensor = hallSensor;
  pinMode(PIN_MOTOR_PWM, OUTPUT);
  pinMode(PIN_MOTOR_CLOCKWISE, OUTPUT);
  pinMode(PIN_MOTOR_COUNTER_CLOCKWISE, OUTPUT);
}

void Motor::feed(unsigned short speed)
{
  digitalWrite(PIN_MOTOR_CLOCKWISE, true);
  digitalWrite(PIN_MOTOR_COUNTER_CLOCKWISE, false);
  analogWrite(PIN_MOTOR_PWM, speed);
}

void Motor::retract(unsigned short speed)
{
  if (_hallSensor->isActive()) {  
    digitalWrite(PIN_MOTOR_CLOCKWISE, false);
    digitalWrite(PIN_MOTOR_COUNTER_CLOCKWISE, true);
    analogWrite(PIN_MOTOR_PWM, speed);
  } else {
    stop();
  }
}

void Motor::retract(unsigned short speed, int duration) {
  
}

void Motor::stop()
{
  analogWrite(PIN_MOTOR_PWM, 0);
}
