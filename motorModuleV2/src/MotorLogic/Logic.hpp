#ifndef LOGIC_HPP
#define LOGIC_HPP

#include "Motor.hpp"
#include "ForceDetector.hpp"
#include "../PID/PID_v2.h"
#include "Counter.hpp"
#include "../Communication/Message.hpp"

namespace MotorLogic
{

static const int STATE_IDLE = 0;
static const int STATE_PID = 1;

class Logic
{
public:
  Logic();
  explicit Logic(unsigned short speed);
  void setSpeed(unsigned short speed);
  void loop();

  bool isForceMin();
  bool isForceMax();

  void message(Communication::Message message);
private:
  void pidLoop();

  int _state;

  unsigned short _speed;
  double _p;
  double _i;
  double _d;
  double _setpoint;
  double _output;
  double _input;
  
  ForceDetector _forceDetector;
  Motor _motor;
  Counter _counter;


  PID * _pid;

  constexpr static double ERROR_MARGIN = 10;
  constexpr static double OUTPUT_MARGIN = 20;
};
} // namespace MotorLogic

#endif // LOGIC_HPP