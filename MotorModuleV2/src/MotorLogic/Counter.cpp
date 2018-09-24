#include "Counter.hpp"
#include <Arduino.h>
#include <string.h>

using namespace MotorLogic;

#define PIN_A 2
#define PIN_B 8

RotaryEncoder * Counter::encoder = nullptr;

Counter::Counter() {
    encoder = new RotaryEncoder(PIN_A, PIN_B);

    delay(500);
    attachInterrupt(digitalPinToInterrupt(PIN_A), [](){
        encoder->tick(); 
    }, CHANGE);
    attachInterrupt(digitalPinToInterrupt(PIN_B), [](){
        encoder->tick();
    }, CHANGE);
    delay(500);
}

long Counter::getCount() {
    return encoder->getPosition();
}
