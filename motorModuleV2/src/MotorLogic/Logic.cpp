#include <Arduino.h>
#include "Logic.hpp"
#include <PID_v1.h>
#include <ArduinoJson.h>

using namespace MotorLogic;

void Logic::setSpeed(unsigned short speed)
{
  _speed = speed;
}

Logic::Logic() : _state(STATE_IDLE),
                 _speed(255),
                 _p(4),
                 _i(0.5),
                 _d(1),
                 _setpoint(0),
                 _output(0)
{
  _pid = new PID(&_input, &_output, &_setpoint, _p, _i, _d, DIRECT);

  _forceDetector.init();
  _input = this->_counter.getCount();

  _pid->SetMode(AUTOMATIC);
  _pid->SetOutputLimits(-255, 255);
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
  StaticJsonBuffer<255> jsonBuffer;
  JsonObject& jsonMsg = jsonBuffer.parseObject((char*)msg.data);

  const char * command = jsonMsg["command"];
  String commandStr = String(command);

  // Interpet the message.
  if (commandStr == "setPoint")
  {
    int value = jsonMsg["point"];
    _setpoint = value;
    _state = STATE_IDLE;
  }
  else if (commandStr == "retract") {
    int amount = jsonMsg["amount"];
    int speed = jsonMsg["speed"];
    _motor.retract(speed);
    delay(amount);
    _motor.stop();
  }
  else if (commandStr == "feed") {
    int amount = jsonMsg["amount"];
    int speed = jsonMsg["speed"];
    _motor.feed(speed);
    delay(amount);
    _motor.stop();
  }
  else if (commandStr == "execute") {
    _state = STATE_PID;
  }
  else if (commandStr == "resetEncoder") {
    _counter.reset();
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
    Serial.println("END!");
    return;
  }

  if(error > 150){

  } 
  if(error < 80){

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
  _input = _counter.getCount();
  if (_state == STATE_PID)
  {
    pidLoop();
  }
}
