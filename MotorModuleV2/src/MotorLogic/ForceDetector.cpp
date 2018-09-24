#include "ForceDetector.hpp"
#include <Arduino.h>

using namespace MotorLogic;

#define MAX_FORCE_PIN 10
#define MIN_FORCE_PIN 11

bool ForceDetector::max = false;
bool ForceDetector::min = false;

void ForceDetector::init() {
    pinMode(MAX_FORCE_PIN, INPUT);
    pinMode(MIN_FORCE_PIN, INPUT);

    max = digitalRead(MAX_FORCE_PIN) > 0;
    min = digitalRead(MIN_FORCE_PIN) > 0;

    Serial.println("attach interruppt");
    attachInterrupt(digitalPinToInterrupt(MAX_FORCE_PIN), [](){
        ForceDetector::triggerMax();
    }, CHANGE);

    attachInterrupt(digitalPinToInterrupt(MIN_FORCE_PIN), [](){
        ForceDetector::triggerMin();
    }, CHANGE);
}

void ForceDetector::triggerMax() {
    max = digitalRead(MAX_FORCE_PIN) > 0;
}

void ForceDetector::triggerMin() {
    min = digitalRead(MIN_FORCE_PIN) > 0;
}
