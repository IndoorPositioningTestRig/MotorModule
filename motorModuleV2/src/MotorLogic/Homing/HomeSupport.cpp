#include "HomeSupport.hpp"

using namespace Homing;

void HomeSupport::init(MotorLogic::HallSensor *hallsensor, MotorLogic::Motor *motor, MotorLogic::ForceDetector *forceDetector)
{
    _hallSensor = hallsensor;
    _motor = motor;
    _forceDetector = forceDetector;
}

bool HomeSupport::loop()
{
    if (_forceDetector->min)
    {
        _motor->retract(64);
        Serial.println("min, retract");
    }
    else if (_forceDetector->max)
    {
        _motor->feed(64);
        Serial.println("max, feed");

    }
    else
    {
        _motor->feed(64);
        Serial.println("nothing, feed");

    }
    return false;
}
