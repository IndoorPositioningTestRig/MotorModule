#include "Logic.hpp"

using namespace MotorLogic;

void Logic::move(int len) {
    _motor.move(len, _speed);
}

void Logic::setSpeed(unsigned short speed) {
    _speed = speed;
}

Logic::Logic() : _speed(0) {
}

Logic::Logic(unsigned short speed) : _speed(speed) {
}
