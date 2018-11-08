#include <Arduino.h>
#include "Logic.hpp"
#include <PID_v1.h>

using namespace MotorLogic;

void Logic::setSpeed(unsigned short speed)
{
  _speed = speed;
}

Logic::Logic() :
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

void Logic::loop() {
  if(pid) {
    _input = _counter.getCount();

    double error = abs(_setpoint - _input); 
    _pid->Compute();

    Serial.print("Input: ");
    Serial.print(_input);
    Serial.print("    Output: ");
    Serial.println(_output);

    setSpeed(abs(_output));
    if (abs(error) < ERROR_MARGIN && abs(_output) < OUTPUT_MARGIN) {
      pid = !pid;
      _motor.stop();
      Serial.println("END!");
      return;
    }

    if(_output == 0){
      _motor.stop();
    } else if (_output > 0){
      _motor.feed(_speed);
    } else if (_output < 0){
      _motor.retract(_speed);
    }
  } else {
      if(Serial.available()){
      char input = Serial.read();
      if(input == 'r'){
          _motor.retract(255);
          delay(100);
      } else if (input == 'f') {
          _motor.feed(255);
          delay(100);
      } else if (input == 'p'){
        pid = !pid;
      }
    }
    _motor.stop();
  }
}
