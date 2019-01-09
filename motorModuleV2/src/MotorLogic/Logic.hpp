#ifndef LOGIC_HPP
#define LOGIC_HPP

#include "Motor.hpp"
#include "ForceDetector.hpp"
#include "../PID/PID_v2.h"
#include "Counter.hpp"
#include "../Communication/Message.hpp"
#include <ArduinoJson.h>
#include "HallSensor.hpp"

namespace MotorLogic
{

static const uint8_t STATE_IDLE = 0;
static const uint8_t STATE_PID = 1;
static const uint8_t STATE_ENCODER = 2;

class Logic
{
public:
  Logic();
  explicit Logic(uint8_t speed);

  void init();
  void setSpeed(uint8_t speed);
  void loop(Test::Debug *debug);

  bool isForceMin();
  bool isForceMax();

  void message(Communication::Message message, Communication::Communicator *communicator, Test::Debug *debug);

private:
  void pidLoop(Test::Debug *debug);
  void encoderLoop(Test::Debug *debug);

  bool _reportDone;

  uint8_t _state;

  uint8_t _speed;
  double _p;
  double _i;
  double _d;
  double _setpoint;
  double _output;
  double _input;

  ForceDetector _forceDetector;
  HallSensor _hallSensor;
  Counter _counter;
  Motor _motor;

  PID *_pid;
  StaticJsonBuffer<255> _jsonBuffer;

  constexpr static double ERROR_MARGIN = 10;
  constexpr static double OUTPUT_MARGIN = 20;
};
} // namespace MotorLogic

#endif // LOGIC_HPP