#include "Counter.hpp"
#include "../Pins.hpp"
#include <Arduino.h>
#include <string.h>

using namespace MotorLogic;

RotaryEncoder *Counter::encoder = nullptr;

Counter::Counter()
{
  encoder = new RotaryEncoder(PIN_ENCODER_A, PIN_ENCODER_B);

  delay(500);
  attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_A), []() {
    encoder->tick();
  }, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_B), []() {
    encoder->tick();
  }, CHANGE);
  delay(500);

  Serial.println("Encoder initialized");
}

long Counter::getCount()
{
  return encoder->getPosition();
}

void Counter::reset()
{
  encoder->setPosition(0);
}
