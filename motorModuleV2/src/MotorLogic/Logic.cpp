#include <Arduino.h>
#include "Logic.hpp"
#include "PID/PID_v2.h"

using namespace MotorLogic;

void Logic::setSpeed(uint8_t speed)
{
  _speed = speed;
}

Logic::Logic() : _reportDone(false),
                 _state(STATE_IDLE),
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
  _hallSensor.init();
  _motor.init(&_hallSensor);
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

void Logic::message(Communication::Message msg, Communication::Communicator * communicator, Test::Debug * debug)
{
  Serial.println("Logic message");
  JsonObject& jsonMsg = _jsonBuffer.parseObject((char*)msg.data);

  const char *command = jsonMsg["command"];
  String commandStr = String(command);
  Serial.print("command string: ");
  Serial.println(commandStr);
  Serial.print("type: ");
  Serial.println(msg.type);

  if (msg.type == Communication::TYPES::REQUEST) {
    // Handle requests
    if (commandStr == "get_pid") {
      delay(500);
      double pid[3] = {_p, _i, _d};
      communicator->write_c(0, msg.sender, Communication::TYPES::RESPONSE, pid, 3 * 4);
    }
    else if (commandStr == "setPoint_debug") {
      // Move to setpoint and send debug data when done.
      double value = jsonMsg["setpoint"];
      _setpoint = value;
      _state = STATE_PID;
      _reportDone = true;
    } else if (commandStr == "ping") {
        _jsonBuffer.clear();
        communicator->write_c(0, msg.sender, Communication::TYPES::RESPONSE, "{\"command\":\"ping\"}", 18);
    }
  } else {
    // Handle other message types
    if (commandStr == "setPoint")
    {
      // Set the setPoint value
      int value = jsonMsg["point"];
      _setpoint = value;
      _state = STATE_IDLE;
    }
    else if (commandStr == "retract")
    {
      // Retract some distance
      int amount = jsonMsg["amount"];
      int speed = jsonMsg["speed"];
      _motor.retract(speed);
      delay(amount);
      _motor.stop();
    }
    else if (commandStr == "feed")
    {
      // Feed some distance
      int amount = jsonMsg["amount"];
      int speed = jsonMsg["speed"];
      _motor.feed(speed);
      delay(amount);
      _motor.stop();
    }
    else if (commandStr == "execute")
    {
      // Execute movement to setPont
      _reportDone = false;
      _state = STATE_PID;
    }
    else if (commandStr == "resetEncoder")
    {
      // Reset the encoder
      _counter.reset();
    }
    else if (commandStr == "debug")
    {
      // Send debug data
      delay(500);
      debug->print();
    }
    else if (commandStr == "set_pid")
    {
      _p = jsonMsg["p"];
      _i = jsonMsg["i"];
      _d = jsonMsg["d"];
    }
  }

  _jsonBuffer.clear();
}

void Logic::pidLoop(Test::Debug * debug)
{
  if (_hallSensor.isActive()) {
    _motor.stop();
    _state = STATE_IDLE;
    return;
  }

  double error = abs(_setpoint - _input);
  _pid->Compute(debug);
  setSpeed(abs(_output));

  // Check if the error or output are within margin and end the loop is if one is.
  if (abs(error) < ERROR_MARGIN && abs(_output) < OUTPUT_MARGIN)
  {
    _state = STATE_IDLE;
    _motor.stop();
    if (_reportDone) {
      debug->log(_setpoint, _output, _input, 100);
      debug->print();
    }
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

void Logic::loop(Test::Debug * debug)
{
  _input = _counter.getCount();
  if (_state == STATE_PID)
  {
    pidLoop(debug);
  }
}
