#ifndef TEST_HPP
#define TEST_HPP

#include "../MotorLogic/Motor.hpp"
#include "../MotorLogic/ForceDetector.hpp"
#include <PID_v1.h>
#include "../MotorLogic/Counter.hpp"

namespace TestNamespace
{
  class Test
  {
  public:
    Test();
    explicit Test(unsigned short speed);
    void setSpeed(unsigned short speed);
    void manualPIDloop();
    void teabagging();

    bool isForceMin();
    bool isForceMax();

  private:
    unsigned short _speed;
    MotorLogic::ForceDetector _forceDetector;
    MotorLogic::Motor _motor;
    MotorLogic::Counter * _counter;

    double _p;
    double _i;
    double _d;
    double _input;
    double _output;
    double _setpoint;

    PID * _pid;
    bool isPid;

    constexpr static double ERROR_MARGIN = 10;
    constexpr static double OUTPUT_MARGIN = 20;
  };
} 

#endif