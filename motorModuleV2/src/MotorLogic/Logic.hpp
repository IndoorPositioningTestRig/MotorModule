#ifndef LOGIC_HPP
#define LOGIC_HPP

#include "Motor.hpp"
#include "ForceDetector.hpp"
#include "../PID/PID_v2.h"
#include "Counter.hpp"
#include "../Communication/Message.hpp"
#include <ArduinoJson.h>
#include "HallSensor.hpp"
#include "Homing/Home.hpp"
#include "Homing/HomeSupport.hpp"
#include "Id.hpp"
#include "Communication/Communicator.hpp"

namespace MotorLogic
{

static const uint8_t STATE_IDLE = 0;
static const uint8_t STATE_PID = 1;
static const uint8_t STATE_ENCODER = 2;
static const uint8_t STATE_HOME = 3;
static const uint8_t STATE_HOMESUPPORT = 4;

class Logic
{
public:
  Logic();
  explicit Logic(uint8_t speed);

  void init();
  void setSpeed(uint8_t speed);
  void loop(Test::Debug *debug, Communication::Communicator *communicator, Id *id);

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
  long _lastTime;

  ForceDetector _forceDetector;
  HallSensor _hallSensor;
  Counter _counter;
  Motor _motor;
  Homing::Home _home;
  Homing::HomeSupport _homeSupport;

  PID *_pid;
  StaticJsonBuffer<255> _jsonBuffer;

  constexpr static double ERROR_MARGIN = 1;
  constexpr static double OUTPUT_MARGIN = 20;
};
} // namespace MotorLogic

#endif // LOGIC_HPP