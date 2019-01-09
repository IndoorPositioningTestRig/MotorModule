#ifndef HOME_HPP
#define HOME_HPP

#include "MotorLogic/HallSensor.hpp"
#include "MotorLogic/Motor.hpp"
#include "MotorLogic/ForceDetector.hpp"

namespace Homing
{

class Home
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
#endif // HOME_HPP
