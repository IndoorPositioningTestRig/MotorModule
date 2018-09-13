#include <Arduino.h>
#include "MotorLogic/Logic.hpp"

static MotorLogic::Logic logic;

void setup() {
    logic = MotorLogic::Logic(128);
    logic.move(1000);
    // put your setup code here, to run once:
}

void loop() {
    // put your main code here, to run repeatedly:
}  