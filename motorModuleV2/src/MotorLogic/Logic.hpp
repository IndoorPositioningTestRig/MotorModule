#ifndef LOGIC_HPP
#define LOGIC_HPP

#include "Motor.hpp"
#include "ForceDetector.hpp"
#include <PID_v1.h>
#include "Counter.hpp"

namespace MotorLogic
{
class Logic
{
public:
  Logic();
  explicit Logic(unsigned short speed);
  void setSpeed(unsigned short speed);
  void loop();

  bool isForceMin();
  bool isForceMax();

private:
  unsigned short _speed;
  ForceDetector _forceDetector;
  Motor _motor;
  Counter _counter;

  double _p;
  double _i;
  double _d;
  double _input;
  double _output;
  double _setpoint;

  PID * _pid;
  bool pid = false;

  constexpr static double ERROR_MARGIN = 10;
  constexpr static double OUTPUT_MARGIN = 20;
};
} // namespace MotorLogic

#endif // LOGIC_HPP