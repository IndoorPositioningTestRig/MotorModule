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
  void init();

  void retract(unsigned short speed);
  void feed(unsigned short speed);
  void stop();
};
} // namespace MotorLogic

#endif // MOTOR_HPP