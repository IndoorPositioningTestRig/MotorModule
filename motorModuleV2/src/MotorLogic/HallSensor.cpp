#include "HallSensor.hpp"

using namespace MotorLogic;

int HallSensor::state = LOW;

bool HallSensor::isActive() const {
  return state != HIGH;
}

void HallSensor::init() {
  pinMode(HALL_SENSOR, INPUT);
  state = digitalRead(HALL_SENSOR);

  attachInterrupt(digitalPinToInterrupt(HALL_SENSOR), [](){
    state = digitalRead(HALL_SENSOR);
  }, CHANGE);
}
