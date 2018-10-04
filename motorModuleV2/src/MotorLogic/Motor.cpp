#include "Motor.hpp"
#include <Arduino.h>
#include "../Pins.hpp"

using namespace MotorLogic;

Motor::Motor()
{
  pinMode(PIN_MOTOR_PWM, OUTPUT);
  pinMode(PIN_MOTOR_CLOCKWISE, OUTPUT);
  pinMode(PIN_MOTOR_COUNTER_CLOCKWISE, OUTPUT);
}

void Motor::move(int amount, unsigned short speed)
{
  if (amount > 0)
  {
    this->feed(speed);
  }
  else
  {
    amount *= -1;
    this->retract(speed);
  }
  delay(amount);
  stop();
}

void Motor::feed(unsigned short speed)
{
  digitalWrite(PIN_MOTOR_CLOCKWISE, true);
  digitalWrite(PIN_MOTOR_COUNTER_CLOCKWISE, false);
  analogWrite(PIN_MOTOR_PWM, speed);
}

void Motor::retract(unsigned short speed)
{
  digitalWrite(PIN_MOTOR_CLOCKWISE, false);
  digitalWrite(PIN_MOTOR_COUNTER_CLOCKWISE, true);
  analogWrite(PIN_MOTOR_PWM, speed);
}

void Motor::stop()
{
  analogWrite(PIN_MOTOR_PWM, 0);
}
