#ifndef HOME_SUPPORT_H
#define HOME_SUPPORT_H

#include "MotorLogic/HallSensor.hpp"
#include "MotorLogic/Motor.hpp"
#include "MotorLogic/ForceDetector.hpp"

namespace Homing
{
class HomeSupport
{
  public:
    void init(MotorLogic::HallSensor *hallsensor, MotorLogic::Motor *motor, MotorLogic::ForceDetector *forceDetector);
    bool loop();

  private:
    MotorLogic::HallSensor *_hallSensor;
    MotorLogic::Motor *_motor;
    MotorLogic::ForceDetector *_forceDetector;
};

} // namespace Homing
#endif // HOME_SUPPORT_H