#include <Arduino.h>
#include "Logic.hpp"
#include "PID/PID_v2.h"

using namespace MotorLogic;

void Logic::setSpeed(uint8_t speed)
{
  _speed = speed;
}

Logic::Logic() : _state(STATE_IDLE),
                 _speed(255),
                 _p(4),
                 _i(0.5),
                 _d(1),
                 _setpoint(0),
                 _output(0),
                 _input(0)
{
  _pid = new PID(&_input, &_output, &_setpoint, _p, _i, _d, DIRECT);
  _pid->SetMode(AUTOMATIC);
  _pid->SetOutputLimits(-255, 255);
}

void Logic::init() {
  _motor.init();
  _counter.init();
  _input = _counter.getCount();
  _forceDetector.init();
}

bool Logic::isForceMin()
{
  return _forceDetector.min;
}

bool Logic::isForceMax()
{
  return _forceDetector.max;
}

void Logic::message(Communication::Message msg)
{
  JsonObject& jsonMsg = _jsonBuffer.parseObject((char*)msg.data);

  const char *command = jsonMsg["command"];
  String commandStr = String(command);

  if (msg.type == Communication::TYPES::COMMAND)
  {
    // Interpet the message.
    if (commandStr == "setPoint")
    {
      int value = jsonMsg["point"];
      _setpoint = value;
      _state = STATE_IDLE;
    }
    else if (commandStr == "retract")
    {
      int amount = jsonMsg["amount"];
      int speed = jsonMsg["speed"];
      _motor.retract(speed);
      delay(amount);
      _motor.stop();
    }
    else if (commandStr == "feed")
    {
      int amount = jsonMsg["amount"];
      int speed = jsonMsg["speed"];
      _motor.feed(speed);
      delay(amount);
      _motor.stop();
    }
    else if (commandStr == "execute")
    {
      _state = STATE_PID;
    }
    else if (commandStr == "resetEncoder")
    {
      _counter.reset();
    }
  } else if (msg.type == Communication::TYPES::REQUEST){
    if (commandStr == "debug")
    {
      //Serial.println("printing log...");
      delay(2000);
      //_communicator->write_c(1, 0, 2, (uint8_t*)"{\"command\":\"kutrs485\"}", 22);

      // _debug->print(*_communicator);
    }
    
  }
}

void Logic::pidLoop()
{
  double error = abs(_setpoint - _input);
  _pid->Compute();

  setSpeed(abs(_output));
  if (abs(error) < ERROR_MARGIN && abs(_output) < OUTPUT_MARGIN)
  {
    _state = STATE_IDLE;
    _motor.stop();
    return;
  }

  // Control the motor based on output
  if (_output == 0)
  {
    _motor.stop();
  }
  else if (_output > _setpoint)
  {
    _motor.feed(_speed);
  }
  else if (_output < _setpoint)
  {
    _motor.retract(_speed);
  }
}

void Logic::loop()
{
  // _input = _counter.getCount();
  if (_state == STATE_PID)
  {
    pidLoop();
  }
}
