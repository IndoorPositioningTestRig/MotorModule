#include <Arduino.h>
#include "Test.hpp"
#include <PID_v1.h>

using namespace MotorLogic;
using namespace TestNamespace;

void Test::setSpeed(unsigned short speed)
{
  _speed = speed;
}

Test::Test() :
  _speed(255),
  _p(4),
  _i(0.8),
  _d(0.04),
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

void Test::manualPIDloop() {
  // Serial.print("isPid = ");
  // Serial.println(isPid);
  //Serial.println(_counter->getCount());

  if(isPid) {
    Serial.println("Handling PID stuff");
    // Serial.print("Setpoint = ");
    // Serial.println(_setpoint);
    _input = _counter->getCount();

    double error = abs(_setpoint - _input); 
    _pid->Compute();

    // Serial.print("Input: ");
    // Serial.print(_input);
    // Serial.print("    Output: ");
    // Serial.println(_output);

    setSpeed(abs(_output));
    if (abs(error) < ERROR_MARGIN && abs(_output) < OUTPUT_MARGIN) {
      isPid = !isPid;
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
    Serial.println("Reading Serial inputs");
      if(Serial.available()){
      char input = Serial.read();
      if(input == 'r'){
          _motor.retract(255);
          delay(100);
      } else if (input == 'f') {
          _motor.feed(255);
          delay(100);
      } else if (input == 'p'){
        isPid = !isPid;
        Serial.print("isPid = ");
        Serial.println(isPid);
      }
    }
    _motor.stop();
  }
}

void Test::teabagging() {
  if(_setpoint > 0)
    _setpoint = 0;
  else
  _setpoint = 200;

  //Serial.print("Setpoint");
  //Serial.println(_setpoint);

  while(!isPid){
    _input = _counter->getCount();
    double error = abs(_setpoint - _input); 


    // if (error < 50)
    // {
    //   _pid->SetTunings(4, 0.5, 1);
    // }
    // else
    // {
    //   _pid->SetTunings(_p, _i, _d);
    // }




    _pid->Compute();

    //Serial.print("Setpoint=");
    Serial.print(_setpoint);
    Serial.print(" ");
    //Serial.print("Input=");
    Serial.print(_input);
    Serial.print(" ");
    //Serial.print("Output=");
    Serial.print(_output);
    Serial.print(" ");
    //Serial.print("Error=");
    Serial.println(error);


    setSpeed(abs(_output));
    //TODO fix this
    if (abs(error) < ERROR_MARGIN && abs(_output) < OUTPUT_MARGIN) {
      isPid = !isPid;
      _motor.stop();
      return;
    }

    if(_output == 0){
      _motor.stop();
      isPid = !isPid;
      return;
    } else if (_output > 0){
      _motor.feed(_speed);
    } else if (_output < 0){
      _motor.retract(_speed);
    }
  }
}