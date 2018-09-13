#include "Motor.hpp"
#include <Arduino.h>

using namespace MotorLogic;

unsigned short Motor::clockWise = 7;
unsigned short Motor::counterClockWise = 4;
unsigned short Motor::pwmPin = 3;

Motor::Motor() {
    pinMode(pwmPin, OUTPUT);
    pinMode(clockWise, OUTPUT);
    pinMode(counterClockWise, OUTPUT);
}

void Motor::move(int amount, unsigned short speed) {
    if (amount > 0) {
        this->feed(speed);
    } else {
        amount *= -1;
        this->retract(speed);
    }

    delay(amount);
    stop();
}

void Motor::feed(unsigned short speed) {
    digitalWrite(clockWise, true);
    digitalWrite(counterClockWise, false);
    analogWrite(pwmPin, speed);
}

void Motor::retract(unsigned short speed) {
    digitalWrite(clockWise, false);
    digitalWrite(counterClockWise, true);
    analogWrite(pwmPin, speed);
}

void Motor::stop() {
    analogWrite(pwmPin, 0);
}
