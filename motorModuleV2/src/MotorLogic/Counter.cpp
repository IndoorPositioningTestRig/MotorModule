#include "Counter.hpp"
#include "../Pins.hpp"
#include <Arduino.h>
#include <string.h>

using namespace MotorLogic;

RotaryEncoder *Counter::encoder = nullptr;

void Counter::init() {
  encoder = new RotaryEncoder(PIN_ENCODER_A, PIN_ENCODER_B);

  delay(500);
  attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_A), []() {
    encoder->tick();
  }, CHANGE);
  
  attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_B), []() {
    encoder->tick();
  }, CHANGE);
  delay(500); 
}

long Counter::getCount()
{
  if (encoder == nullptr) {
    init();
  }
  return encoder->getPosition();
}

void Counter::reset()
{
  if (encoder == nullptr) {
    init();
  }
  encoder->setPosition(0);
}
