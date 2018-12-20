#include "HallSensor.hpp"

#ifndef MOTOR_HPP
#define MOTOR_HPP

namespace MotorLogic
{
enum MotorState
{
  NONE,
  RETRACT,
  FEED
};

class Motor
{
public:
  Motor() = default;
  void init(HallSensor * hallSensor);

  void retract(unsigned short speed);
  void retract(unsigned short speed, int duration);
  void feed(unsigned short speed);
  void feed(unsigned short speed, int duration);
  void stop();
private:
  HallSensor * _hallSensor;
};
} // namespace MotorLogic

#endif // MOTOR_HPP