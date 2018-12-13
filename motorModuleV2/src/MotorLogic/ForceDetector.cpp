#include "ForceDetector.hpp"
#include "../Pins.hpp"
#include <Arduino.h>

using namespace MotorLogic;

bool ForceDetector::max = false;
bool ForceDetector::min = false;

void ForceDetector::init()
{
  pinMode(PIN_MAX_FORCE, INPUT);
  pinMode(PIN_MIN_FORCE, INPUT);

  max = digitalRead(PIN_MAX_FORCE) == HIGH;
  min = digitalRead(PIN_MIN_FORCE) == HIGH;

  attachInterrupt(digitalPinToInterrupt(PIN_MAX_FORCE), []() {
    ForceDetector::triggerMax();
  }, CHANGE);

  attachInterrupt(digitalPinToInterrupt(PIN_MIN_FORCE), []() {
    ForceDetector::triggerMin();
  }, CHANGE);
}

void ForceDetector::triggerMax()
{
  max = digitalRead(PIN_MAX_FORCE) == HIGH;
}

void ForceDetector::triggerMin()
{
  min = digitalRead(PIN_MIN_FORCE) == HIGH;
}
