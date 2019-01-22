#include "Home.hpp"

using namespace Homing;

void Home::init(MotorLogic::HallSensor *hallsensor, MotorLogic::Motor *motor, MotorLogic::ForceDetector *forceDetector)
{
    _hallSensor = hallsensor;
    _motor = motor;
    _forceDetector = forceDetector;
}

bool Home::loop()
{
    if (_hallSensor->isActive())
    {
        _motor->stop();
        return true;
    }
    // else if (_forceDetector->max)
    // {
    //     _motor->retract(40);
    // }
    else
    {
        _motor->retract(64);
    }
    return false;
}
