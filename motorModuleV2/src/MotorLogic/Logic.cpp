#include <Arduino.h>
#include "Logic.hpp"
#include <PID_v1.h>

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

void Logic::message(Message msg)
{
  String data = "";
  for (size_t i = 0; i < msg.length - 5; i++)
  {
    data += msg.data[i];
  }

  if (data == "go")
  {
    _state = STATE_PID;
  }
  else if (data = "r")
  {
    _motor.retract(255);
    delay(100);
    _motor.stop();
  }
  else if (data = "f")
  {
    _motor.feed(255);
    delay(100);
    _motor.stop();
  }
  else
  {
    int val = data.toInt();
    _setpoint = val;
    _state = STATE_IDLE;
  }
}

void Logic::pidLoop()
{
  double error = abs(_setpoint - _input);
  _pid->Compute();

  Serial.print("pid(in: ");
  Serial.print(_input);
  Serial.print(", out: ");
  Serial.print(_output);
  Serial.println(")");

  setSpeed(abs(_output));
  if (abs(error) < ERROR_MARGIN && abs(_output) < OUTPUT_MARGIN)
  {
    _state = STATE_IDLE;
    _motor.stop();
    Serial.println("END!");
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
  _input = _counter.getCount();
  if (_state == STATE_PID)
  {
    pidLoop();
  }
}
