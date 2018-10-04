#ifndef LOGIC_HPP
#define LOGIC_HPP

#include "Motor.hpp"
#include "ForceDetector.hpp"

namespace MotorLogic
{
class Logic
{
public:
  Logic();
  explicit Logic(unsigned short speed);
  void move(int len);
  void setSpeed(unsigned short speed);
  void loop();

  bool isForceMin();
  bool isForceMax();

private:
  unsigned short _speed;
  ForceDetector _forceDetector;
  Motor _motor;
};
} // namespace MotorLogic

#endif // LOGIC_HPP