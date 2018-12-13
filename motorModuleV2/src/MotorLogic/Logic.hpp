#ifndef LOGIC_HPP
#define LOGIC_HPP

#include "Motor.hpp"
#include "ForceDetector.hpp"
#include "../PID/PID_v2.h"
#include "Counter.hpp"
#include "../Communication/Message.hpp"
#include <ArduinoJson.h>

namespace MotorLogic
{

static const uint8_t STATE_IDLE = 0;
static const uint8_t STATE_PID = 1;

class Logic
{
public:
  Logic();
  explicit Logic(uint8_t speed);

  void init();
  void setSpeed(uint8_t speed);
  void loop(Test::Debug * debug);

  bool isForceMin();
  bool isForceMax();

  void message(Communication::Message message, Communication::Communicator * communicator, Test::Debug * debug);
private:
  void pidLoop(Test::Debug * debug);

  uint8_t _state;

  uint8_t _speed;
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
  StaticJsonBuffer<255> _jsonBuffer;

  constexpr static double ERROR_MARGIN = 10;
  constexpr static double OUTPUT_MARGIN = 20;
};
} // namespace MotorLogic

#endif // LOGIC_HPP