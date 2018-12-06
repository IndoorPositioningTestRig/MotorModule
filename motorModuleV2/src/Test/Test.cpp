#include <Arduino.h>
#include "Test.hpp"
#include <PID_v1.h>

using namespace MotorLogic;
using namespace TestNamespace;

void Test::setSpeed(unsigned short speed)
{
  _speed = speed;
}

Test::Test() : _speed(255),
               _p(5),
               _i(0),
               _d(0),
               _setpoint(0),
               _output(0)
{
  _pid = new PID(&_input, &_output, &_setpoint, _p, _i, _d, DIRECT);
  _counter = new Counter();

  //_forceDetector.init();
  _input = this->_counter->getCount();

  _pid->SetMode(AUTOMATIC);
  _pid->SetOutputLimits(-255, 255);
  isPid = false;
}

bool Test::isForceMin()
{
  return _forceDetector.min;
}

bool Test::isForceMax()
{
  return _forceDetector.max;
}

void Test::manualPIDloop()
{
  if (isPid)
  {
    _input = _counter->getCount();

    double error = abs(_setpoint - _input);
    _pid->Compute();

    // Serial.print(_setpoint);
    // Serial.print(",");
    // Serial.print(_input);
    // Serial.print(",");
    // Serial.println(_output);

    setSpeed(abs(_output));
    // if (abs(error) < ERROR_MARGIN && abs(_output) < OUTPUT_MARGIN) {
    //   isPid = !isPid;
    //   _motor.stop();
    //   Serial.println("END!");
    //   return;
    // }

    if (_output == 0.00 || (_setpoint == _input && ( abs(_output) <= 20)))
    {
      isPid = !isPid;
      _motor.stop();
      Serial.println("PID DONE!");
    }
    else if (_output > 0)
    {
      _motor.feed(_speed);
    }
    else if (_output < 0)
    {
      _motor.retract(_speed);
    }
  }
  else
  {
    if (Serial.available())
    {
      char input = Serial.read();
      if (input == 'r')
      {
        Serial.println("retracting");
        _motor.retract(255);
        delay(100);
      }
      else if (input == 'f')
      {
        Serial.println("feeding");
        _motor.feed(255);
        delay(100);
      }
      else if (input == 'p')
      {
        isPid = !isPid;
        Serial.print("isPid = ");
        Serial.println(isPid);
      }
      else if (input == 's')
      {
        _counter->reset();
      }
      else if (input == 'u')
      {
        _p += 0.1;
      }
      else if (input == 'j')
      {
        _p -= 0.1;
      }
      else if (input == 'i')
      {
        _i += 0.1;
      }
      else if (input == 'k')
      {
        _i -= 0.1;
      }
      else if (input == 'o')
      {
        _d += 0.1;
      }
      else if (input == 'l')
      {
        _d -= 0.1;
      }
      else if (input == 'h')
      {
        Serial.print("P: ");
        Serial.print(_p);
        Serial.print(" I: ");
        Serial.print(_i);
        Serial.print(" D: ");
        Serial.println(_d);
      }
      _pid->SetTunings(_p, _i, _d);
    }
    _motor.stop();
  }
}

void Test::teabagging()
{
  if (_setpoint > 0)
    _setpoint = 0;
  else
    _setpoint = 200;


  while (!isPid)
  {
    _input = _counter->getCount();
    double error = abs(_setpoint - _input);

    
    Serial.print(_setpoint);
    Serial.print(",");
    Serial.print(_input);
    Serial.print(",");
    Serial.println(_output);

    _pid->Compute();

    setSpeed(abs(_output));
    //TODO fix this
    // if (abs(error) < ERROR_MARGIN && abs(_output) < OUTPUT_MARGIN)
    // {
    //   isPid = !isPid;
    //   _motor.stop();
    //   return;
    // }

    if (_output == 0 || (_setpoint == _input))
    {
      _motor.stop();
      isPid = !isPid;
      return;
    }
    else if (_output > 0)
    {
      _motor.feed(_speed);
    }
    else if (_output < 0)
    {
      _motor.retract(_speed);
    }
  }
}